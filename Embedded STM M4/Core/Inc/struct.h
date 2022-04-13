#include "Device.h"

#ifdef HC-SR04_ENABLED

typedef volatile struct ultra_sonic_struct
{
	int out_enable_flag : 1;
	int in_enable_flag : 1;
	uint32_t time_cnt;
	int distance_cnt;
	int32_t distance_cm;
}us_str;

us_str ultraSonic_CH1;

#endif

#ifdef sharp_2Y0A21_ENABLED

typedef volatile struct ir_sensor_struct
{
	uint32_t u32result;

}ir_str;

ir_str ir[3];
#endif

typedef volatile struct motor_struct
{

	uint32_t decel_flag: 1;
	float int32deccel_vel;
	float encoder_value;
	float decel_vel;

	float target_distance;
	float hw_distance;
	float accel;
	float int32deccel_dist;
	float hw_check_dist;
	float hw_gone_dist;
	float sw_vel;
	float err_vel_sum;
	float err_vel[4];

	float sw_new_vel;
	float target_vel;

	float target_velocity;
	float error_distance;
	float hw_distance_sum;
	float sw_target_vel[4];
	float hw_current_vel_avg;

	float kp;
	float ki;
	float kd;

	float proportion_val;
	float integral_val;
	float differential_val;
	float pid_output;

	int encoder1;
	int encoder2;


}motor_str;

motor_str motor;

typedef volatile struct bitfield_flag
{
	uint16_t stop_motor : 1;
	uint16_t break_motor : 1;
	uint16_t on_motor : 1;
	uint16_t err : 1;
	uint16_t move_state : 1;

}flag_str;

flag_str g_flag;
