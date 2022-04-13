#include "sensor.h"


#define ADC_CH0		ADC_CHANNEL_2
#define ADC_CH1		ADC_CHANNEL_4
#define ADC_CH2		ADC_CHANNEL_5

#define ADC_NUM		3

volatile uint32_t adc_channel[3] = {
		ADC_CH0, ADC_CH1, ADC_CH2
};

void sensorTest(void)
{

#ifdef HC-SR04_ENABLED
	VFDPrintf("%8ld", ultraSonic_CH1.distance_cm);
#endif

}

void sensorInit(void)
{
	memset( ( void * ) ir, 0x00, sizeof(ir_str) * ADC_NUM);
}

//activates every 20us
void sensor_ISR(void)
{
#ifdef debug1
	if(ISRCounter == 0)
	{
		ISRCounter++;
		GPIOB->ODR |= GPIO_PIN_14;

	}
	else if (ISRCounter == 1)
	{
		ISRCounter = 0;
		GPIOB->ODR &= ~GPIO_PIN_14;

	}
#endif

#if 1

#ifdef HC-SR04_ENABLED

	//enable out_enable_flag
	if(ultraSonic_CH1.time_cnt == 6)
	{
		//activates ultraSonic Sensor every 50 us
		ultraSonic_CH1.out_enable_flag = ON;
		ultraSonic_CH1.time_cnt = 0;

		//disable input flag
		ultraSonic_CH1.in_enable_flag = OFF;

		//calculate distance to cm
		ultraSonic_CH1.distance_cm = ultraSonic_CH1.distance_cnt * 10 / 58;

		//reset distance count
		ultraSonic_CH1.distance_cnt = 0;
	}

	//make signal to HC-SR04
	if(ultraSonic_CH1.out_enable_flag)
	{
		//enable GPIO Output
		UltraSonic_CH1_H;

		//disable GPIO Output flag
		ultraSonic_CH1.out_enable_flag = OFF;
		ultraSonic_CH1.in_enable_flag = OFF;
	}
	else
	{
		//disable GPIO OutPut
		UltraSonic_CH1_L;

		//enable input flag
		ultraSonic_CH1.in_enable_flag = ON;
	}

	//get signal from HC-SR04
	if(ultraSonic_CH1.in_enable_flag)
	{
		//count distance
		if(!UltraSonic_CH1_Input)
		{
			//printf("GOOD!");
			ultraSonic_CH1.distance_cnt++;
		}
	}

	ultraSonic_CH1.time_cnt++;

	//stop when the distance between the car and the wall is 1 ~ 4 cm
	if(1 < ultraSonic_CH1.distance_cm && ultraSonic_CH1.distance_cm < 4)
	{
		//enable stop motor flag
		motor.break_flag = ON;

	}
	else
	{
		//disable stop motor flag
		motor.break_flag = OFF;

	}

#endif

#ifdef sharp_2Y0A21_ENABLED

	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 100);
	  ir[ g_int32adc_cnt ].u32result = HAL_ADC_GetValue(&hadc1);

#endif

#if 1
if (ir[g_int32adc_cnt].u32result > 3500)
{
	if(!g_flag.break_motor)
	{
		g_flag.break_motor = ON;
	}
}
#endif


g_int32adc_cnt ++;

if(g_int32adc_cnt == 3)
{
	g_int32adc_cnt = 0;
}


#endif

}
