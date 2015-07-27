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
	isr->TC=0;
	isr->RXNE=0;
	
	/*All interrupts disabled by default*/
	cr->LBDIE=0;
	cr->RXNEIE=0;
	cr->SBKRQ=0;
	cr->TCIE=0;
	cr->TXEIE=0;
	
	vusart->registers.tx_status=VUSART_TXStatus_IDLE;
	vusart->isr_handler=isr_handler;
	return vusart;
}

void  deleteVUSART(VUSART_t * vusartObject){
	free(vusartObject);
}

void VUSART_Method_SendData(VUSART_t * vusart,char data){
	vusart->registers.TX=data;
	vusart->registers.ISR.TXE=0;
}

char VUSART_Method_ReadData(VUSART_t * vusart){
	vusart->registers.ISR.RXNE=0;
	return vusart->registers.RX;
}

void VUSART_Method_ClearFlag(VUSART_t * vusart,VUSART_FLAG_t flag){
	if(VUSART_FLAG_TCCF == flag) vusart->registers.ISR.TC=0;
	else if(VUSART_FLAG_LBDCF == flag) vusart->registers.ISR.LBD=0;
}

int VUSART_Method_GetFlagStatus(VUSART_t * vusart,VUSART_FLAG_t flag){
	if(VUSART_FLAG_TCCF == flag) return vusart->registers.ISR.TC;
	else if(VUSART_FLAG_LBDCF == flag) return vusart->registers.ISR.LBD;
	else if(VUSART_FLAG_RXNE == flag) return vusart->registers.ISR.RXNE;
	else return 0;
}

void external_sendData(VUSART_t * vusart,char data){
	vusart->registers.RX=data;
	vusart->registers.ISR.RXNE=1;
}

void external_sendBreak(VUSART_t * vusart){
	vusart->registers.ISR.LBD=1;
	printf("Hardware: Break Detected\n");
}

void VUSART_StepSimualtion(VUSART_t * vusart){
	/*Interrupt Generation*/
	VUSART_REGISTER_CR_t * cr=&(vusart->registers.CR);
	VUSART_REGISTER_ISR_t * isr=&(vusart->registers.ISR);
	
	if(vusart->registers.tx_status != VUSART_TXStatus_IDLE){
		if(isr->TC==0){
			isr->TC=1;
			printf("Hardware: Transmission Completed\n");
			vusart->registers.tx_status = VUSART_TXStatus_IDLE;
		}
	}
	
	
	if(cr->SBKRQ){
		printf("Hardware: Transmitting -> BREAK\n");
		cr->SBKRQ=0;
		isr->TC=0;
		vusart->registers.tx_status = VUSART_TXStatus_LB;
	}
	
	if(isr->TXE==0){
		printf("Hardware: Transmitting -> %c\n",vusart->registers.TX);
		isr->TC=0;
		isr->TXE=1;
		vusart->registers.tx_status = VUSART_TXStatus_DATA;
	}
	
	
	
	/*Interrupt generation*/
	if(((isr->TXE)&&(cr->TXEIE))||
		((isr->LBD)&&(cr->LBDIE))||
		((isr->RXNE)&&(cr->RXNEIE))||
		((isr->TC)&&(cr->TCIE))) vusart->isr_handler();
}