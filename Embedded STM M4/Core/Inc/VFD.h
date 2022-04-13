#if 1

#ifndef __VFD_H__
#define __VFD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Device.h"

#define VFD_DA_H	GPIOD -> ODR |= GPIO_PIN_8
#define VFD_DA_L	GPIOD -> ODR &= ~GPIO_PIN_8

#define VFD_RS_H 	GPIOB -> ODR |= GPIO_PIN_15
#define VFD_RS_L	GPIOB -> ODR &= ~GPIO_PIN_15

#define VFD_CE_H	GPIOD -> ODR |= GPIO_PIN_9
#define VFD_CE_L	GPIOD -> ODR &= ~GPIO_PIN_9

#define VFD_CLK_H	GPIOD -> ODR |= GPIO_PIN_10
#define VFD_CLK_L	GPIOD -> ODR &= ~GPIO_PIN_10

#define VFD_RESET_H GPIOD -> ODR |= GPIO_PIN_12
#define VFD_RESET_L GPIOD -> ODR &= ~GPIO_PIN_12

void VfdCtlRegInit(int CrlReg);
void VfdInit(void);
void VfdDataLoad(char *Buff);
void VFDPrintf(char *Form, ... );

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

#endif
