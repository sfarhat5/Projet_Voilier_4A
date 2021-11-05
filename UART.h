#ifndef UART_H
#define UART_H
#include "stm32f10x.h"



//Active l'horloge de l'USART et configure le pin associé 
void UART_Init(USART_TypeDef * UARTptr, int UART_BaudRate );

//Démarre l'USART
void UART_ActiveIT(USART_TypeDef * UARTptr , char Prio, void (* IT_Function )(void));

//Envoie le message donné par l'USART  
void UART_send(USART_TypeDef * UARTptr, char * data); 


#endif 