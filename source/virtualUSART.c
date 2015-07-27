#include "virtualUSART.h"
#include <stdio.h>
#include <stdlib.h>

VUSART_t *  newVUSART(void (*isr_handler)(void)){
	VUSART_t * vusart;
	vusart = malloc(sizeof(VUSART_t));
	
	VUSART_REGISTER_CR_t * cr=&(vusart->registers.CR);
	VUSART_REGISTER_ISR_t * isr=&(vusart->registers.ISR);
	
	/*Default status flags values*/
	isr->LBD=0;
	isr->TXE=1;
	isr->TC=1;
	isr->RXNE=0;
	
	/*All interrupts disabled by default*/
	cr->LBDIE=0;
	cr->RXNEIE=0;
	cr->SBKRQ=0;
	cr->TCIE=0;
	cr->TXEIE=0;
	
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
}

void VUSART_StepSimualtion(VUSART_t * vusart){
	/*Interrupt Generation*/
	VUSART_REGISTER_CR_t * cr=&(vusart->registers.CR);
	VUSART_REGISTER_ISR_t * isr=&(vusart->registers.ISR);
	
	/*Interrupt generation*/
	if(((isr->TXE)&&(cr->TXEIE))||
		((isr->LBD)&&(cr->LBDIE))||
		((isr->RXNE)&&(cr->RXNEIE))||
		((isr->TC)&&(cr->TCIE))) vusart->isr_handler();
}