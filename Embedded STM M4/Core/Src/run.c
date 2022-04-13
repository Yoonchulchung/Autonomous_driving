#include "run.h"

#if 1
void run(void)
{
	VFDPrintf("        ");
#if 0
	motor.move_state = ON;

	while(1)
	{
		if(motor.stop_motor_flag)
		{
			stop_motor();
		}

		if(motor.break_motor)
		{

		}

	}
#endif

}

void stop_motor(void)
{
	TIM1->CCR1 = 0;

	//motor.move_state = OFF;
	while(1)
	{
		VFDPrintf("__STOP__");
	}
}

void break_motor(void)
{
	TIM1->CCR1 = 0;


}

#endif
