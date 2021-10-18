#include "MyTimer.h"
#include "stm32f10x.h"

void (* Ptrf1 ) ( void ); //Déclaration d'un pointeur de fonction 
void (* Ptrf2 ) ( void ); 
void (* Ptrf3 ) ( void ); 
void (* Ptrf4 ) ( void ); 

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) {
	
	if (Timer->Timer == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ; // Activation de l'horloge locale du périphérique
	if (Timer->Timer == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;
	if (Timer->Timer == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
	if (Timer->Timer == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;
	
	Timer->Timer->PSC = Timer->PSC; // Réglage de la période du Timer
	Timer->Timer->ARR = Timer->ARR; 
	
	Timer->Timer->CR1 |=  (1 << 0); // Activation du compteur
}


void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (* IT_Function )(void)) {
	
	char num_IT;
	Ptrf1 = IT_Function; 
	Ptrf2 = IT_Function;
	Ptrf3 = IT_Function;
	Ptrf4 = IT_Function;
	
	if (Timer == TIM1) num_IT = 25;        // Sélectionne le numéro d'interruption en fonction du timer
	else if (Timer == TIM2) num_IT = 28;
	else if (Timer == TIM3) num_IT = 29;
	else if (Timer == TIM4) num_IT = 30;
	
	Timer->DIER |= (1 << 0); // Valide l'envoi d'une demande d'interruption
	NVIC->IP[num_IT] |= (Prio << 4); // Fixe la priorité de l'interruption dans le NVIC
	NVIC->ISER[0] |= (1 << num_IT); // Autorise la prise en compte de l'interruption dans le NVIC
	
}

void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) {
	if (Channel == 1) {
		Timer->CCMR1 &= ~TIM_CCMR1_OC1M_0;                   
		Timer->CCMR1 |= TIM_CCMR1_OC1M_1| TIM_CCMR1_OC1M_2; //configuration du canal en mode PWM ;Affectation de la valeur ob110 au bit OC1M du registre CCMR1 du timer
		Timer->CCER |= TIM_CCER_CC1E;       //lancer le timer                
	}
	else if (Channel == 2) {
		Timer->CCMR1 &= ~TIM_CCMR1_OC2M_0;
		Timer->CCMR1 |= TIM_CCMR1_OC2M_1| TIM_CCMR1_OC2M_2;
		Timer->CCER |= TIM_CCER_CC2E;
	}
	else if (Channel == 3) {
		Timer->CCMR2 &= ~TIM_CCMR2_OC3M_0;
		Timer->CCMR2 |= TIM_CCMR2_OC3M_1| TIM_CCMR2_OC3M_2;
		Timer->CCER |= TIM_CCER_CC3E;
	}
	else if (Channel == 4) {
		Timer->CCMR2 &= ~TIM_CCMR2_OC4M_0;
		Timer->CCMR2 |= TIM_CCMR2_OC4M_1| TIM_CCMR2_OC4M_2;
		Timer->CCER |= TIM_CCER_CC4E;
	}
}	

void Set_PWM_Cycle (TIM_TypeDef * Timer, char Channel, char Rapp_Cycle) {
	if (Channel == 1) {
		Timer->CCR1 = (int) (Timer->ARR)*Rapp_Cycle/100;
	}
	else if (Channel == 2) {
		Timer->CCR2 = (int) ((Timer->ARR)*Rapp_Cycle)/100;
	}
	else if (Channel == 3) {
		Timer->CCR3 = (int) (Timer->ARR)*Rapp_Cycle/100;
	}
	else if (Channel == 4) {
		Timer->CCR4 = (int) (Timer->ARR)*Rapp_Cycle/100;
	}
}

void TIM1_IRQHandler ( void )
	{
		TIM1->SR &= ~TIM_SR_UIF; 
		//GPIOC->ODR = GPIOC ->ODR ^(1<<10); 
		if (Ptrf1 != 0)
			(*Ptrf1)();
	}
	
	void TIM2_IRQHandler ( void )
	{
		TIM2->SR &= ~TIM_SR_UIF; 
		//GPIOC->ODR = GPIOC ->ODR ^(1<<10);
		if (Ptrf2 != 0)
			(*Ptrf2)();
		
	}
	
	void TIM3_IRQHandler ( void )
	{
		TIM3->SR &= ~TIM_SR_UIF; 
		//GPIOC->ODR = GPIOC ->ODR ^(1<<10); 
		if (Ptrf3 != 0)
			(*Ptrf3)();
	}
	
	void TIM4_IRQHandler ( void )
	{
		TIM4->SR &= ~TIM_SR_UIF; 
		//GPIOC->ODR = GPIOC ->ODR ^(1<<10); 
		if (Ptrf4 != 0)
			(*Ptrf4)();
	}
	
	
	