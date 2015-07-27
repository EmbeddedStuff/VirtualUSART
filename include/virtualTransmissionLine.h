/* 
 * File:   virtualTransmissionLine.h
 * Author: eLimones <limonesu.me@gmail.com>
 *
 * Created on July 26, 2015, 11:28 PM
 */

#ifndef VIRTUALTRANSMISSIONLINE_H
#define	VIRTUALTRANSMISSIONLINE_H

#include "virtualUSART.h"

#ifdef	__cplusplus
extern "C" {
#endif
	
	typedef struct{
		VUSART_t * nodeList[256];
		int nuberOfNodes;
	}VTransmissionLine_t;
	
	void VTL_StepSimulation(void);
	
#ifdef	__cplusplus
}
#endif

#endif	/* VIRTUALTRANSMISSIONLINE_H */

