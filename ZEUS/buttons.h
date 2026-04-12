

				
	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Buttons Header File																																									|
		|_______________________________________________________________________________________________________________________________________________________| */
				
				

								#ifndef BUTTONS_H
								#define BUTTONS_H
								
//										4-Button Switch GPIO Definitions (Active LOW)
													#define BTN1_PIN  (1 << 13) 							// 		PB12: 		Normal Mode
													#define BTN2_PIN  (1 << 14) 							// 		PB13: 		Void Time (Soil Only)
													#define BTN3_PIN  (1 << 15) 							// 		PB14: 		Force ON
													#define BTN4_PIN  (1 << 12) 							// 		PB15: 		Force OFF
													
																	#include "stm32f10x.h"
																	#include <stdbool.h>
																														void Buttons_Init(void);
																														uint8_t Buttons_Get_ACTIVE_Mode(void);
								#endif