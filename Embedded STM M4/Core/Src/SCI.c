#include "SCI.h"

char SCIx_RxChar(void)
{	
    while(huart5.Instance->SR & 0x20)
    {
    	return huart5.Instance->DR  & 0x1FF;
    }
}

void SCIx_TxChar(char Data)
{

    huart4.Instance->DR = Data & 0x1FF;
    while(!(huart4.Instance->SR & 0x80));
}

void SCIx_TxString(char *Str)
{
    while(*Str) 
    {
        if(*Str == '\n'){
            SCIx_TxChar('\r');
        }
		
        SCIx_TxChar(*Str++ );
    }
}      
void TxPrintf(char *Form, ... )
{
    static char Buff[128];
    va_list ArgPtr;
    va_start(ArgPtr,Form);	 
    vsprintf(Buff, Form, ArgPtr);
    va_end(ArgPtr);
    SCIx_TxString(Buff);
}
