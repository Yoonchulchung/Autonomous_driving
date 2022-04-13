#include "motor.h"

//10cm equals to 284 pulse
#define PULSE_TO_D		0.035211267				//0.035211267cm/pulse

#define PULSE_TO_V		70.422535211267605		//70.4225cm/ (s * pulse)

#define MAX_PID_OUT   8950.0

#define MIN_PID_OUT    -8950.0

#define PWM_CONVERT		0.23	//PWM주파수 최대값(EPWM.c) / MAX_PID_OUT => 2000 / 9000(수정 요망)	=> 2100 / 9000

#define SAMPLE_FRQ		0.25

void motor_init( motor_str *pm)
{
	memset( (void *) pm, 0x00, sizeof(motor_str));
	pm->accel = 5;
	pm->kp = 0.6;
	pm->ki = 0.000002;
	pm->kd = 0.65;
}

void motor_ISR(void)
{

	if(ISRCounter == 0)
	{
		GPIOE->ODR |= GPIO_PIN_9;
		ISRCounter++;
	}
	else if (ISRCounter == 1)
	{
		GPIOE->ODR &= ~GPIO_PIN_9;
		ISRCounter = 0;

	}
	//Encoder 값 받기
	motor.encoder_value = TIM2->CNT;

	//Encoder 값 초기화
	TIM2->CNT = 0;

	//encoder 부호 compute
	motor.encoder_value = - (( motor.encoder_value > 2048 )? ( motor.encoder_value ) - 4097  : motor.encoder_value);

	//기어비 틱당 거리
	motor.hw_distance = motor.encoder_value * PULSE_TO_V;

	//this part is for PID control
	motor.hw_distance_sum += motor.hw_distance;
	motor.error_distance = motor.target_distance - motor.hw_distance_sum;

	//check the distance that the car is driven
	motor.hw_check_dist += motor.hw_distance;

	motor.hw_gone_dist += motor.hw_distance;

	//속도 compute
	motor.sw_target_vel[3] = motor.sw_target_vel[2];						//[3] <- [2]
	motor.sw_target_vel[2] = motor.sw_target_vel[1];						//[2] <- [1]
	motor.sw_target_vel[1] = motor.sw_target_vel[0];						//[1] <- [0]
	motor.sw_target_vel[0] = motor.encoder_value *  PULSE_TO_V;					//[0] <- Encoder
		
	motor.hw_current_vel_avg = (motor.sw_target_vel[3] + motor.sw_target_vel[2] +
									motor.sw_target_vel[1] + motor.sw_target_vel[0]) * 0.25;

	if( motor.decel_flag )
		{
			if( motor.int32deccel_dist >= (float) fabs( (double) motor.error_distance) )
			{
				motor.target_vel = motor.decel_vel;

				motor.decel_flag = OFF;

				//g_err.over_dist = 0;
			}
		}

	if( motor.target_vel > motor.sw_new_vel )
		{
			//처음에는 이쪽으로 들어옴.
			motor.sw_new_vel += ((float) fabs( (double) motor.accel)) * ( (float) SAMPLE_FRQ);	//acceleration * 0.5ms
																//v = v0 + at
			if( motor.target_vel < motor.sw_new_vel )
				motor.sw_new_vel = motor.target_vel;
		}
		else if( motor.target_vel < motor.sw_new_vel )
		{
			//감속 구간	새로운 속도 (500us 마다 속도가 벼함. 이에 따라 함수가 끝나기 전에 새로운 속도값을 넣음)
			//			가 기존에 있었던 속도보다 큰 경우
			motor.sw_new_vel -= ((float) fabs( (double) motor.accel)) * ( (float) SAMPLE_FRQ);		//속도가 감소함.
																	//v = v0 - at
			if( motor.target_vel > motor.sw_new_vel )
				motor.sw_new_vel = motor.target_vel;
		}
		else;

	//PID 제어
	motor.err_vel_sum -= motor.err_vel[ 3 ];		//2ms 이후에 값을 빼줌.
	motor.err_vel[ 3 ] = motor.err_vel[ 2 ];		//1.5ms
	motor.err_vel[ 2 ] = motor.err_vel[ 1 ];		//1ms
	motor.err_vel[ 1 ] = motor.err_vel[ 0 ];		//handle 값은 -1.13 ~ 1.13
	motor.err_vel[ 0 ] = motor.sw_new_vel - motor.hw_current_vel_avg;
	motor.err_vel_sum += motor.err_vel[ 0 ];		//한 요소가 2ms 동안 영향을 줌.

	motor.proportion_val = motor.kp * motor.err_vel[ 0 ];	//Kp * 현재 속도.
	motor.integral_val = motor.ki * motor.err_vel_sum;	//적분이니까 2ms 동안의 값을 이용함.
	motor.differential_val = motor.kd * ( (motor.err_vel[ 0 ] - motor.err_vel[ 3 ])
									+ ((float) 3.0 * (motor.err_vel[ 1 ] - motor.err_vel[ 2 ]) ));
									//미분
	motor.pid_output += motor.proportion_val + motor.integral_val + motor.differential_val;

	//최단거리 알고리즘


#if 1
	if(g_flag.move_state)
	{
		if(motor.pid_output > 0)	//전진
		{
			if( motor.pid_output > MAX_PID_OUT )		motor.pid_output = MAX_PID_OUT;

			GPIOC->ODR |= GPIO_PIN_8;

			TIM1->CCR1 = (uint32_t) (motor.pid_output * PWM_CONVERT);
		}
		else	//후진
		{
			if( motor.pid_output < MIN_PID_OUT )		motor.pid_output = MIN_PID_OUT;

			GPIOC->ODR &= ~GPIO_PIN_8;

			TIM1->CCR1 = (uint32_t) (abs(motor.pid_output) * PWM_CONVERT) ;

		}
	}
	else
	{
		GPIOC->ODR |= GPIO_PIN_8;
		TIM1->CCR1 = 0;
	}
#endif
}

void move_to_target ( volatile float dist, volatile float dec_dist, volatile float tar_vel, volatile float dec_vel, volatile float acc )
{
	//disable motorISR

	motor.accel = acc;

	motor.int32deccel_dist = dec_dist;
	motor.target_distance = dist;

	motor.target_vel = tar_vel;

	motor.error_distance = motor.target_distance - motor.hw_distance_sum;

	motor.int32deccel_vel = dec_vel;

	motor.decel_flag = dec_vel;
	g_flag.move_state = ON;

	//enable motorISR
}
