#include <stdio.h>
#include "virtualUSART.h"

static VUSART_t * usart1;

void myIRQHandler(void){
	printf("DataEvent VUSART <- %c\n",VUSART_Method_ReadData(usart1));
}

int main(void){
	usart1 = newVUSART(myIRQHandler);
	VUSART_Method_SendData(usart1,'g');
	external_sendData(usart1,'A');
	external_sendData(usart1,'B');
	deleteVUSART(usart1);
	return 0;
}