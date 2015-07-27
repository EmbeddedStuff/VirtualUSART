#include <stdio.h>
#include "virtualUSART.h"

static VUSART_t * usart1;

void myIRQHandler(void){
	if(VUSART_Method_GetFlagStatus(usart1,VUSART_FLAG_RXNE)) printf("Handler: Reception VUSART <- %c\n",VUSART_Method_ReadData(usart1));
	if(VUSART_Method_GetFlagStatus(usart1,VUSART_FLAG_TCCF)){
		VUSART_Method_ClearFlag(usart1,VUSART_FLAG_TCCF);
		printf("Handler: Tranmission Completed\n");
	}
	if(VUSART_Method_GetFlagStatus(usart1,VUSART_FLAG_LBDCF)){
		VUSART_Method_ClearFlag(usart1,VUSART_FLAG_LBDCF);
		printf("Handler: Break Detected\n");
	}
}

void usart1_init(){
	usart1 = newVUSART(myIRQHandler);
	usart1->registers.CR.RXNEIE=1;//
	usart1->registers.CR.TCIE=1;//
	usart1->registers.CR.LBDIE=1;//
}

int main(void){
	usart1_init();
	VUSART_Method_SendData(usart1,'g');
	external_sendData(usart1,'A');
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart1);
	external_sendBreak(usart1);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart1);
	deleteVUSART(usart1);
	return 0;
}