#if 1
#include "menu.h"

//ServoValue = ServoValue - 1072;

#define DC 0
#define Servo 1

uint16_t InitialPWMValue = 2-1;
volatile uint16_t DCValue = 2 - 1;
volatile uint16_t ServoValue = 39200-1;

void DecreaseValue(int type, int value)
{
	//type == 0: BLDC
	//type == 1: ServoMotor
	if(!type)
	{
		DCValue = DCValue - value;

		if(2 > DCValue)
		{
			DCValue = 2;
		}

		//set DCpulse
		DCPulse = DCValue;
		VFDPrintf("%8ld", DCValue);

		HAL_Delay(50);
	}
	else
	{
		ServoValue = ServoValue - value;

		if(2 > ServoValue)
		{
			ServoValue = 2;
		}

		//set ESCpulse
		ServoPulse = ServoValue;
		VFDPrintf("%8ld", ServoValue);

		HAL_Delay(50);
	}

}

void IncreaseValue(int type, int value)
{
	//type == 0: DC
	//type == 1: ServoMotor

	if(!type)
	{
		DCValue = DCValue + value;

		if(1670 < DCValue)
		{
			DCValue = 1670;
		}
		else
		{

		}

		//set DCpulse
		DCPulse = DCValue;
		VFDPrintf("%8ld", DCValue);

		HAL_Delay(50);
	}
	else
	{
		ServoValue = ServoValue + value;

		if(55000 < ServoValue)
		{
			ServoValue = 55000;
		}
		else
		{

		}

		//set ESCpulse
		ServoPulse = ServoValue;
		VFDPrintf("%8ld", ServoValue);

		HAL_Delay(50);
	}

}

void ControlPulse(int type, int value)
{
	while(0 < SW_U)
	{

		if(SW_L == 0)
		{
			DecreaseValue(type, value);
		}
		else if(SW_R == 0)
		{
			IncreaseValue(type, value);
		}
		else
		{

		}
	}
}

//<<<First Page>>>
void DCControlPrint(void)
{
	VFDPrintf("1__DC__C");
}

void ServoControlPrint(void)
{
	VFDPrintf("1_SERV_C");
}

void IRSensorPrint(void)
{
	VFDPrintf("1___IR__");
}

void FirstPageEndPrint(void)
{
	VFDPrintf("1_%d_END_", SwitchCategory);
}

//<<<Second Page>>>

//<DCControl>

void DCInitiatePrint(void)
{
	menuCnt = 0;
	VFDPrintf("2_INIT__");
}

void DCControl100Print(void)
{
	VFDPrintf("2_D_100_");
}

void DCControl10Print(void)
{
	VFDPrintf("2_D_10__");
}

void DCControl1Print(void)
{
	VFDPrintf("2_D_1___");
}

void DCVEL10Print(void)
{
	VFDPrintf("2_VEL_10");
}

//<IR>
void getSensorValPrint(void)
{
	VFDPrintf("2_I_4095");
}

void getEncoderValPrint(void)
{
	VFDPrintf("2_ENCOD_");
}

void doZeroControlPrint(void)
{
	VFDPrintf("2_ZERO__");
}
//<Servo>

void ServoInitiatePrint(void)
{
	menuCnt = 0;
	VFDPrintf("2_INIT__");
}

void ServoControl100Print(void)
{
	VFDPrintf("2_S_100_");
}

void ServoControl10Print(void)
{
	VFDPrintf("2_S_10__");
}

void ServoControl1Print(void)
{
	VFDPrintf("2_S_1___");
}

void SecondPageEndPrint(void)
{
	VFDPrintf("2_%d_END_", SwitchFunction);
}

//<<<Third Page>>>

//<DCControl>
void DCInitiate(void)
{
	if (menuCnt == 0)
	{
		VFDPrintf("INITIATE");
		DCValue = InitialPWMValue;
		HAL_Delay(100);
		VFDPrintf("FINISHED");

		//set pulse
		DCPulse = DCValue;
		HAL_Delay(10);
		menuCnt++;
		ControlCnt = 0;
	}
	else
	{
		VFDPrintf("%8ld", DCValue);
	}

}


void DCControl100(void)
{
	ControlPulse(DC, 100);
}

void DCControl10(void)
{
	ControlPulse(DC, 10);
}

void DCControl1(void)
{
	ControlPulse(DC, 1);
}

void DCVEL10(void)
{
	move_to_target ( 1000, 0, 10, 0, ( int32_t ) 5);


	g_flag.move_state = ON;
}


//<ServoConotrol>

void ServoInitiate(void)
{
	if (menuCnt == 0)
	{
		//1.4ms
		VFDPrintf("INITIATE");
		ServoValue = 39200-1;
		ServoValue = ServoValue - 1072;
		HAL_Delay(100);
		VFDPrintf("FINISHED");

		//set pulse
		ServoPulse = ServoValue;
		HAL_Delay(10);
		menuCnt++;
	}
	else
	{
		VFDPrintf("%8ld", ServoValue);
	}

}


void ServoControl100(void)
{
	ControlPulse(Servo, 100);
}

void ServoControl10(void)
{
	ControlPulse(Servo, 10);
}

void ServoControl1(void)
{
	ControlPulse(Servo, 1);
}

//<IR>

void getSensorValue(void)
{
	volatile uint32_t sensor_cnt = 0;

#ifdef HC-SR04_ENABLED
	VFDPrintf("%8ld", ultraSonic_CH1.distance_cnt);
#endif

		if(SwitchList < 3)
		{
			for(int i = 0; i < 3; i++)
			{
				TxPrintf("%d: %d \t|", i, ir[i].u32result);
			}
			TxPrintf("\n");

			VFDPrintf("%d: %d", SwitchList, ir[SwitchList - 1].u32result);
		}
		else;

}

void getEncoderValue(void)
{
	VFDPrintf("%8ld", TIM2->CNT);
}

void ZeroControl(void)
{
	VFDPrintf("RUNNING_");



	  HAL_TIM_Base_Start_IT(&htim7);


	  g_flag.move_state = ON;

	while(SW_U)
		{

		move_to_target ( 0, 0, 0, 0, 5);


#if 1
		TxPrintf("Motor: %d \t PWM: %d \n", (int32_t) motor.pid_output, TIM1->CCR1);
#endif
		}


}

void getChannel1CM(void)
{
#ifdef HC-SR04_ENABLED
	VFDPrintf("%8ld", ultraSonic_CH1.distance_cm);
#endif
}

void ThirdPageEndPrint(void)
{
	VFDPrintf("3_%d_END", SwitchList);
}


#endif
