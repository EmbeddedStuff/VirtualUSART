/* 
 * File:   virtualUSART.h
 * Author: eLimones <limonesu.me@gmail.com>
 *
 * Created on July 26, 2015, 10:26 PM
 */

#ifndef VIRTUALUSART_H
#define	VIRTUALUSART_H

#ifdef	__cplusplus
extern "C" {
#endif
	
	typedef struct{
		int RXNE;
		int TXE;
		int TX;
		int RX;
		int OVERFLOW;
		int B;
	}VUSART_Register_t;
	
	
	typedef struct{
		VUSART_Register_t registers;
		void (*isr_handler)(void);
	}VUSART_t;
	

	
	VUSART_t *  newVUSART(void (*isr_handler)(void));
	void  deleteVUSART(VUSART_t * vusartObject);
	void VUSART_Method_SendData(VUSART_t * vusart,char data);
	char VUSART_Method_ReadData(VUSART_t * vusart);
	
	void external_sendData(VUSART_t * vusart,char data);
	
		
	void VUSART_StepSimualtion(VUSART_t *);
	
#ifdef	__cplusplus
}
#endif

#endif	/* VIRTUALUSART_H */

