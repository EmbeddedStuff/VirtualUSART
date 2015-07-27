#include <stdio.h>
#include "virtualUSART.h"

static VUSART_t * usart1;
static VUSART_t * usart2;

void myIRQHandler(void){
	if(VUSART_Method_GetFlagStatus(usart1,VUSART_FLAG_RXNE)) 
		printf("Handler: Reception VUSART1 <- %c\n",VUSART_Method_ReadData(usart1));
	if(VUSART_Method_GetFlagStatus(usart1,VUSART_FLAG_TCCF)){
		VUSART_Method_ClearFlag(usart1,VUSART_FLAG_TCCF);
		printf("Handler: VUSART1 Tranmission Completed\n");
	}
	if(VUSART_Method_GetFlagStatus(usart1,VUSART_FLAG_LBDCF)){
		VUSART_Method_ClearFlag(usart1,VUSART_FLAG_LBDCF);
		printf("Handler: VUSART1 Break Detected\n");
	}
}


void myIRQHandler2(void){
	if(VUSART_Method_GetFlagStatus(usart2,VUSART_FLAG_RXNE)) 
		printf("Handler: Reception VUSART2 <- %c\n",VUSART_Method_ReadData(usart2));
	if(VUSART_Method_GetFlagStatus(usart2,VUSART_FLAG_TCCF)){
		VUSART_Method_ClearFlag(usart2,VUSART_FLAG_TCCF);
		printf("Handler: VUSART2 Tranmission Completed\n");
	}
	if(VUSART_Method_GetFlagStatus(usart2,VUSART_FLAG_LBDCF)){
		VUSART_Method_ClearFlag(usart2,VUSART_FLAG_LBDCF);
		printf("Handler: VUSART2 Break Detected\n");
	}
}

void usart1_inputPipe(TX_TYPE_t ttype, char data){
	if(ttype == TX_TYPE_DATA){
		external_sendData(usart1,data);
	}else{
		external_sendBreak(usart1);
	}
}


void usart2_inputPipe(TX_TYPE_t ttype, char data){
	if(ttype == TX_TYPE_DATA){
		external_sendData(usart2,data);
	}else{
		external_sendBreak(usart2);
	}
}

void usart1_init(){
	usart1 = newVUSART(myIRQHandler);
	usart1->registers.CR.RXNEIE=1;//
	usart1->registers.CR.TCIE=1;//
	usart1->registers.CR.LBDIE=1;//
	usart1->outputPipe=usart2_inputPipe;
}


void usart2_init(){
	usart2 = newVUSART(myIRQHandler2);
	usart2->registers.CR.RXNEIE=1;//
	usart2->registers.CR.TCIE=1;//
	usart2->registers.CR.LBDIE=1;//
}

int main(void){
	usart1_init();
	usart2_init();
	
	external_sendData(usart1,'A');
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	external_sendBreak(usart1);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_Method_SendData(usart1,'G');
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	VUSART_StepSimualtion(usart1);
	VUSART_StepSimualtion(usart2);
	deleteVUSART(usart1);
	deleteVUSART(usart2);
	return 0;
}