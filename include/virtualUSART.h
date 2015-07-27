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
	
	/**
	 * Interrupt Status Register
	 */
	typedef struct{
		int RXNE;/*!< Read Buffer not empty*/
		int TXE;/*!< Tx Buffer empty */
		int LBD;/*!< LIN break detected*/
		int TC;/*!< Transmission complete*/
	}VUSART_REGISTER_ISR_t;
	
	
	/**
	 * Control Register
	 */
	typedef struct{ 
		int RXNEIE;/*!< RXNE Interrupt Enable*/
		int TXEIE;/*!< TXE Interrupt Enable*/
		int LBDIE;/*!< LBD Interrupt Enable*/
		int TCIE;/*!< TC Interrupt Enable*/
		int SBKRQ;/*!< Send Break*/
	}VUSART_REGISTER_CR_t;
	
	
	typedef struct{
		VUSART_REGISTER_CR_t CR;
		VUSART_REGISTER_ISR_t ISR;
		int RX;/*!< Read Buffer*/
		int TX;/*!< Tx Buffer*/
	}VUSART_Registers_t;
	
	typedef struct{
		VUSART_Registers_t registers;
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

