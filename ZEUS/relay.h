	/* _______________________________________________________________________________________________________________________________________
		|																																																																			  |
		|																																																																			  |
		|			AUTHOR:																				TOM GONCIN																																					|
		|																																																																			  |
		| 		DATE FILE LAST EDITED:												March 14, 2026 - 03:42																															|
		|																																																																			  |
		| 		FILE DECSCRIPTION:														Relay Header File for 																															|
		|																																																																				|																		
		|_______________________________________________________________________________________________________________________________________| */
		
		
			#ifndef RELAY_H
			#define RELAY_H

							#include "stm32f10x.h"

												void Relay_Init(void);
												
												void Relay_On(void);
												void Relay_Off(void);

			#endif