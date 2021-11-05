#include "UART.h"
#include "GPIO.h"
#include "stm32f10x.h"
static void (* Ptrf1) (void); 
static void (* Ptrf2) (void); 

void UART_Init ( USART_TypeDef * UARTptr, int UART_BaudRate ) {

	if (UARTptr==USART1) RCC->APB2ENR|= RCC_APB2ENR_USART1EN; 
	else if (UARTptr==USART2) RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	else RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
	
	
		UARTptr -> CR1 &=~ USART_CR1_M; 
		//UARTptr -> CR1 &=~ USART_CR1_PCE; 
		UARTptr -> CR2 &=~ USART_CR2_STOP; // stop bit 
	if ( UARTptr  == USART1) {
		UARTptr  -> BRR |= (int) 72000000/(UART_BaudRate); //fréquence d'horloge de l'USAR1 = 72Mhz
	}
	else if (UARTptr  == USART3 ) {
		UARTptr  -> BRR |= (int) 36000000/(UART_BaudRate); //fréquence d'horloge de l'USAR2 = 32Mhz
	} 
		UARTptr  -> CR1 |= USART_CR1_TE; //Enable transmitter 
		UARTptr  -> CR1 |= USART_CR1_RE; //Enable receiver 
		UARTptr -> CR1 |= USART_CR1_UE; //Enable l'USART 
}

void UART_ActiveIT (USART_TypeDef * UARTptr, char Prio, void (* IT_Function )(void)){
	
	char num_USART; 
	
	
	if (UARTptr  == USART1) {
		num_USART = 37; 
		UARTptr -> CR1 |=  USART_CR1_RXNEIE; // Valide l'envoi d'une demande d'interruption
		NVIC->IP[num_USART] |= (Prio << 2); // Fixe la priorité de l'interruption dans le NVIC
		NVIC->ISER[0] |= (1 << num_USART); } // Autorise la prise en compte de l'interruption dans le NVIC
	
	else if (UARTptr  == USART3) { 
		num_USART = 39; 
		UARTptr -> CR1 |=  USART_CR1_RXNEIE; // Valide l'envoi d'une demande d'interruption
		NVIC->IP[num_USART] |= (Prio << 2); // Fixe la priorité de l'interruption dans le NVIC
		NVIC->ISER[0] |= (1 << num_USART);// Autorise la prise en compte de l'interruption dans le NVIC 
	
	}
}

void USART1_IRQHandler ( void ){ 
	if (Ptrf1 != 0)(*Ptrf1)();
	}
void USART2_IRQHandler ( void ){ 
	if (Ptrf2 != 0)(*Ptrf2)();
	}	
void UART_send_string(USART_TypeDef * UARTptr, char * data){ 
 while (* data != '\0'){ 
		while(!(UARTptr->SR & USART_SR_TXE)) {} ; // Attente de la fin de transmission
		UARTptr-> DR = *data;// Ecriture de la donnée dans le registre DR	 	
		data++; 
}
 }

char UART_receive (	USART_TypeDef * UARTptr) { 
	return (char) UARTptr->DR; 
}
	


	
