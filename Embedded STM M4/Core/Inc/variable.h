#ifndef __C_VARIABLE_H__
#define __C_VARIABLE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ON 1;
#define OFF 0;

#include "Device.h"



#if 0
#define __VARIABLE_EXT__	extern

__VARIABLE_EXT__ SwitchCategoryMax;
__VARIABLE_EXT__ SwitchFunctionMax;
__VARIABLE_EXT__ SwitchListMax;

__VARIABLE_EXT__ SwitchCategory;
__VARIABLE_EXT__ SwitchFunction;
__VARIABLE_EXT__ SwitchList;
__VARIABLE_EXT__ SwitchDownError;
__VARIABLE_EXT__ ControlCnt;
__VARIABLE_EXT__ SwitchCounter;

__VARIABLE_EXT__ IC1;
__VARIABLE_EXT__ IC2;

#endif

#ifdef VFDSwitch
volatile uint32_t SwitchCategoryMax;

volatile uint32_t SwitchFunctionMax;
volatile uint32_t SwitchListMax;

volatile uint32_t SwitchCategory;
volatile uint32_t SwitchFunction;
volatile uint32_t SwitchList;
volatile uint32_t SwitchDownError;
volatile uint32_t ControlCnt;
volatile uint32_t SwitchCounter;
#endif

volatile uint32_t ISRCounter;
volatile uint32_t g_int32sen_cnt;
static uint32_t g_int32adc_cnt = 0;

volatile int IC1;
volatile int IC2;
volatile int menuCnt;


//motor
static int U_Sonic_flag;
static int cnt;

static int adc_cnt;


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
