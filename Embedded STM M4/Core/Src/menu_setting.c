#include "menu_setting.h"


void MenuSetting(void)
{
	//SwitchCategory = 6; SwitchFunction = 9; SwitchList = 16;

		int Menucounter = 0;

		SwitchCategoryMax = 6;
		SwitchFunctionMax = 10;
		SwitchListMax = 17;

		//<<Define VFD FirstPage>>
		arrSwitch[0][0][0] = DCControlPrint;
		arrSwitch[1][0][0] = IRSensorPrint;
		arrSwitch[2][0][0] = ServoControlPrint;
		for(Menucounter = 3; Menucounter < SwitchCategoryMax; Menucounter++)
			{
				arrSwitch[Menucounter][0][0] = FirstPageEndPrint;
			}


		//<<Define VFD SecondPage>>

		//------DCControl--------
		arrSwitch[0][1][0] = DCInitiatePrint;
		arrSwitch[0][2][0] = DCControl100Print;
		arrSwitch[0][3][0] = DCControl10Print;
		arrSwitch[0][4][0] = DCControl1Print;
		arrSwitch[0][5][0] = DCVEL10Print;
		for(Menucounter = 6; Menucounter < SwitchFunctionMax; Menucounter++)
			{
				arrSwitch[0][Menucounter][0] = SecondPageEndPrint;
			}

		arrSwitch[1][1][0] = getSensorValPrint;
		arrSwitch[1][2][0] = getEncoderValPrint;
		arrSwitch[1][3][0] = doZeroControlPrint;

		for(Menucounter = 4; Menucounter < SwitchFunctionMax ; Menucounter++)
		{
			arrSwitch[1][Menucounter][0] = SecondPageEndPrint;
		}

		//------ServoControl--------
		arrSwitch[2][1][0] = ServoControl100Print;
		arrSwitch[2][2][0] = ServoControl10Print;
		arrSwitch[2][3][0] = ServoControl1Print;
		for(Menucounter = 4; Menucounter < SwitchFunctionMax; Menucounter++)
			{
				arrSwitch[2][Menucounter][0] = SecondPageEndPrint;
			}

		//<<Define VFD ThirdPage>>

		//------DCControl--------
		arrSwitch[0][1][1] = DCInitiate;
		arrSwitch[0][2][1] = DCControl100;
		arrSwitch[0][3][1] = DCControl10;
		arrSwitch[0][4][1] = DCControl1;
		arrSwitch[0][5][1] = DCVEL10;


		for(Menucounter = 1; Menucounter < SwitchListMax; Menucounter++)
		{
			arrSwitch[1][1][Menucounter] = getSensorValue;

		}

		arrSwitch[1][2][1] = getEncoderValue;
		arrSwitch[1][3][1] = ZeroControl;


		//------ServoControl-----------
		arrSwitch[2][1][1] = ServoControl100;
		arrSwitch[2][2][1] = ServoControl10;
		arrSwitch[2][3][1] = ServoControl1;
}

void menu(void)
{
	int32_t delay = 50;
	int logic = 0;

	//Category
	if(SwitchCounter == 0)
		{
			if (SW_D == logic)
			{
				SwitchFunction++;
				SwitchCounter++;
				HAL_Delay(delay);
			}
			else if (SW_U == logic)
			{
				VFDPrintf("WRONG");
				HAL_Delay(delay);
			}
			else if (SW_R == logic)
			{
				SwitchCategory++;

				if (SwitchCategory == SwitchCategoryMax)
				{
					SwitchCategory = 0;
				}
				HAL_Delay(delay);
			}

			else if (SW_L == logic)
			{
			if (SwitchCategory == 0)
				{
					SwitchCategory = SwitchCategoryMax - 1;
				}
			else
				{
					SwitchCategory--;
				}
				HAL_Delay(delay);
			}

		}

	//Function
	else if (SwitchCounter == 1)
		{
				if (SW_D == logic)
				{
					if(SwitchDownError == 2)
						{
							SwitchList++;
							SwitchCounter++;
							SwitchDownError = 0;
						}
					SwitchDownError++;
					HAL_Delay(delay);
				}

				else if (SW_U == logic)
				{
					SwitchFunction = 0;
					SwitchDownError = 0;
					SwitchCounter--;
					HAL_Delay(delay);
				}

				else if (SW_R == logic)
				{

					SwitchFunction++;
					if( SwitchFunction == SwitchFunctionMax)
						{
							SwitchFunction = 1;
						}
					else
						{

						}
					HAL_Delay(delay);
				}

				else if (SW_L == logic)
				{
					if (SwitchFunction == 0)
						{
							SwitchFunction = SwitchFunctionMax - 1;
						}
					else
						{
							SwitchFunction--;
						}

					HAL_Delay(delay);
				}
				else
				{

				}

		}

		//List
		else if(SwitchCounter == 2)
			{
				if (SW_D == logic)
				{
					VFDPrintf("END");
					HAL_Delay(delay);
				}

				else if (SW_U == logic)
				{
					SwitchList = 0;
					SwitchCounter--;
					HAL_Delay(delay);
				}


				else if (SW_R == logic)
				{
					SwitchList++;
					if( SwitchList == SwitchListMax)
						{
							SwitchList = 1;
						}
					HAL_Delay(delay);
				}

				else if (SW_L == logic)
				{
					if(SwitchList == 0)
						{
							SwitchList = SwitchListMax -1;
						}
					else
						{
							SwitchList--;
						}
					HAL_Delay(delay);
				}

				else
				{

				}

			}
		else
			{

			}

	//RUN!!!!
	arrSwitch[SwitchCategory][SwitchFunction][SwitchList]();

}



