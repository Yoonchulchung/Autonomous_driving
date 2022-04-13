#ifndef __MSCI_H__
#define __MSCI_H__
#endif

#ifdef _cplusplus
{
#endif

#include "Device.h"

char SCIx_RxChar(void);
void SCIx_TxChar(char Data);
void SCIx_Ttring(char *Str);
void TxPrintf(char *Form, ... );

#ifdef _cplusplus
}
#endif
