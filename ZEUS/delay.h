
				
	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Delay Header File																																										|
		|_______________________________________________________________________________________________________________________________________________________| */
				

					#ifndef DELAY_H
					#define DELAY_H
														#include "stm32f10x.h"
																										void delay_ms(uint32_t ms);
																										void delay_us(uint16_t delay_time_us);
					#endif