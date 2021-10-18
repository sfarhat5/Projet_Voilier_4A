#include "stm32f10x.h"


void My_ADC_Init_Single_Conv( ADC_TypeDef* ADC){
	
	if (ADC == ADC1)
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	if (ADC == ADC2)
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV8;
	ADC -> CR2 |= ADC_CR2_ADON; //Activation de l'ADC
	
	ADC->SQR1 &=0;
	
}

float My_ADC_Get_Value( ADC_TypeDef* ADC, int channel) {
	
	ADC->SQR3 |= channel; 
	ADC -> CR2 |= ADC_CR2_ADON;
	ADC -> SR |= ADC_SR_STRT ; 							 // peut-être JSTRT
	while (((ADC -> SR) & ADC_SR_EOC) == 0) {} // while end of conversion = 0	
	ADC -> SR &= ~(ADC_SR_EOC);							 // End of STRT 
	return (ADC -> DR & 65535); 						 // renvoie les 16 premieres bits de DR
}



