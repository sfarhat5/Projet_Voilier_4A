#include "stm32f10x.h"
#include "core_cm3.h"

void My_ADC_Init_Single_Conv( ADC_TypeDef* ADC);
float My_ADC_Get_Value( ADC_TypeDef* ADC, int channel);
