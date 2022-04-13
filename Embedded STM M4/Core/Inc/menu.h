#ifndef __menu_H__

#define __menu_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Device.h"

#if 1
#define SW_R ((GPIOD -> IDR) & GPIO_PIN_15)
#define SW_D ((GPIOD -> IDR) & GPIO_PIN_14)
#define SW_L ((GPIOD -> IDR) & GPIO_PIN_11)
#define SW_U ((GPIOD -> IDR) & GPIO_PIN_13)

void  (* arrSwitch[6][10][17])();

#endif

#if 1

#define DCPulse TIM1->CCR1
#define ServoPulse TIM8->CCR1

#endif



void DecreaseValue(int type, int value);
void IncreaseValue(int type, int value);
void ControlPulse(int type, int value);

// first page
void DCControlPrint(void);
void DCSettingPrint(void);
void ServoControlPrint(void);
void FirstPageEndPrint(void);
void IRSensorPrint(void);

// second page
void DCInitiatePrint(void);
void DCControl100Print(void);
void DCControl10Print(void);
void DCControl1Print(void);
void DCVEL10Print(void);

void getSensorValPrint(void);
void getChannel1CMPrint(void);
void getEncoderValPrint(void);
void doZeroControlPrint(void);


void ServoInitiatePrint(void);
void ServoControl100Print(void);
void ServoControl10Print(void);
void ServoControl1Print(void);
void SecondPageEndPrint(void);

// third page
void DCInitiate(void);
void DCControl100(void);
void DCControl10(void);
void DCControl1(void);
void DCVEL10(void);


void getSensorValue(void);
void getChannel1CM(void);
void getEncoderValue(void);
void ZeroControl(void);

void ServoInitiate(void);
void ServoControl100(void);
void ServoControl10(void);
void ServoControl1(void);
void ThirdPageEndPrint(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
