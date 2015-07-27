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

	
	typedef enum{
		VUSART_TXStatus_IDLE,/*!< Doing nothign*/
		VUSART_TXStatus_LB, /*!< Transmitting lin break*/
		VUSART_TXStatus_DATA/*!< Transmitting data*/
	}VUSART_TXStatus_t;
	
	typedef struct{
		VUSART_REGISTER_CR_t CR;
		VUSART_REGISTER_ISR_t ISR;
		VUSART_TXStatus_t tx_status;
		int RX;/*!< Read Buffer*/
		int TX;/*!< Tx Buffer*/
	}VUSART_Registers_t;
	
	typedef struct{
		VUSART_Registers_t registers;
		void (*isr_handler)(void);
	}VUSART_t;
	
	typedef enum{
		VUSART_FLAG_LBDCF,
		VUSART_FLAG_TCCF,
		VUSART_FLAG_RXNE
	} VUSART_FLAG_t;
	
	VUSART_t *  newVUSART(void (*isr_handler)(void));
	void  deleteVUSART(VUSART_t * vusartObject);
	void VUSART_Method_SendData(VUSART_t * vusart,char data);
	char VUSART_Method_ReadData(VUSART_t * vusart);
	void VUSART_Method_ClearFlag(VUSART_t * vusart,VUSART_FLAG_t flag);
	int VUSART_Method_GetFlagStatus(VUSART_t * vusart,VUSART_FLAG_t flag);
	
	void external_sendData(VUSART_t * vusart,char data);
	void external_sendBreak(VUSART_t * vusart);
		
	void VUSART_StepSimualtion(VUSART_t *);
	
#ifdef	__cplusplus
}
#endif

#endif	/* VIRTUALUSART_H */

