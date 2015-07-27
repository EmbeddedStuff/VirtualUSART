#include "virtualUSART.h"
#include <stdio.h>
#include <stdlib.h>

VUSART_t *  newVUSART(void (*isr_handler)(void)){
	VUSART_t * vusart;
	vusart = malloc(sizeof(VUSART_t));
	vusart->isr_handler=isr_handler;
	return vusart;
}

void  deleteVUSART(VUSART_t * vusartObject){
	free(vusartObject);
}

void VUSART_Method_SendData(VUSART_t * vusart,char data){
	printf("DataEvent VUSART -> %c\n",data);
}

char VUSART_Method_ReadData(VUSART_t * vusart){
	vusart->registers.ISR.RXNE=0;
	return vusart->registers.RX;
}

void external_sendData(VUSART_t * vusart,char data){
	vusart->registers.RX=data;
	vusart->registers.ISR.RXNE=1;
	vusart->isr_handler();
}

void VUSART_StepSimualtion(VUSART_t * vusart){
}