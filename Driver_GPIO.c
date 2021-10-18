#include "Driver_GPIO.h"

void InPullupPulldown(MyGPIO_Struct_TypeDef * GPIO){
	if (GPIO ->GPIO_Conf == In_PullDown) {
		GPIO -> GPIO -> ODR &= ~(1 << ( GPIO -> GPIO_Pin)); 
		GPIO -> GPIO_Conf = 0x8;
	} else if (GPIO ->GPIO_Conf == In_PullUp ) {
		GPIO -> GPIO -> ODR |= (1 << ( GPIO -> GPIO_Pin));
		GPIO -> GPIO_Conf = 0x8;
	}
}

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr){
	if ((GPIOStructPtr -> GPIO_Pin) > 7) { //GPIO pin 8-15
		GPIOStructPtr -> GPIO -> CRH &= ~(0xF << ((GPIOStructPtr -> GPIO_Pin) - 8));
		GPIOStructPtr -> GPIO -> CRH |= GPIOStructPtr -> GPIO_Conf << ((GPIOStructPtr -> GPIO_Pin) - 8);
		
	} else { //GPIO pin 0-7
		GPIOStructPtr -> GPIO -> CRL &= ~(0xF) << ((GPIOStructPtr -> GPIO_Pin));
		GPIOStructPtr -> GPIO -> CRL |= (GPIOStructPtr -> GPIO_Conf) << (GPIOStructPtr -> GPIO_Pin);
	}
}

int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	if (((GPIO -> IDR >> GPIO_Pin) & 1 ) == 0) { //C'est ODR ou IDR là???
		return 0;
	} else {
		return 1;
	}
}

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
		GPIO -> ODR |= (0x1 << ( GPIO_Pin));
} 

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
		GPIO -> ODR &= ~((0x1) << ( GPIO_Pin));
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	if (((GPIO -> ODR) & (0x1 << ( GPIO_Pin))) == 0) {
		MyGPIO_Set(GPIO, GPIO_Pin);
	} else {
		MyGPIO_Reset(GPIO, GPIO_Pin);
	}
}

