#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{

TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

/*
*****************************************************************************************
* @brie f
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_ActiveIT( TIM_TypeDef * Timer , char Prio, void (* IT_Function )(void));
void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer );

/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
           - char Channel : de 1 a 4
* @Note : Active le channel spécifié sur le timer spécifié
* la gestion de la configuration I/O n’est pas faite dans cette fonction
* ni le réglage de la période de la PWM (ARR, PSC)
**************************************************************************************************
*/
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;
void Set_PWM_Cycle (TIM_TypeDef * Timer, char Channel, char Rapp_Cycle);
	

#define MyTimer_Base_Start(Timer)( Timer-> CR1 |= TIM_CR1_CEN)
#define MyTimer_Base_Stop(Timer)( Timer-> CR1 &= TIM_CR1_CEN )


#endif

