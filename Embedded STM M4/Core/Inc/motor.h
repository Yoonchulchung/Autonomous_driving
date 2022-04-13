#ifndef __MOTOR__
#define __MOTOR__

#ifdef __cplusplus
extern "C" {
#endif

#include "Device.h"
//#include "struct.h"
//#include <stdio.h>


extern void motor_ISR(void);
//extern void motor_init( motor_str *pm);
extern void move_to_target ( volatile float dist, volatile float dec_dist, volatile float tar_vel, volatile float dec_vel, volatile float acc );




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
