

				
	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Timer Header File																																										|
		|_______________________________________________________________________________________________________________________________________________________| */
				
				

								#ifndef TIMER_H
								#define TIMER_H


														#include "stm32f10x.h"
														#include <stdint.h>

// 																			TIM2 - hardware delay (us/ms) - do not use for anything else
																						void    tim2_init(void);

// 																			TIM3 - real 1-second tick
																						void    tim3_init(void);
																						uint8_t tim3_second_elapsed(void);

// 																			MCO - clock output on PA8
																						void    MCO_on(void);
								#endif