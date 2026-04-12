	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 20:54 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														FUNCTION HEADER FILE																																								|
		|_______________________________________________________________________________________________________________________________________________________| */
		
		
			#ifndef WATCHDOGTIMER_H
			#define WATCHDOGTIMER_H
						
						
						#include "stm32f10x.h"
			
			
										void IWDG_Init(void);
										void IWDG_Feed(void);
										
			#endif