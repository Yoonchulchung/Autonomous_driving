#ifndef __SENSOR__
#define __SENSOR__

#ifdef __cplusplus
extern "C" {
#endif

#include "Device.h"
#define UltraSonic_CH1_Input ((GPIOC -> IDR) & GPIO_PIN_11)

#define UltraSonic_CH1_H GPIOC -> ODR |= GPIO_PIN_10
#define UltraSonic_CH1_L GPIOC -> ODR &= ~GPIO_PIN_10

void sensorTest(void);
void sensor_ISR(void);
void sensorInit(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
