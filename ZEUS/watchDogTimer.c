	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 21:06 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Watch-Dog-Timer cource file																																					|
		|																											-> Prevents system reset while watering																														|
		|_______________________________________________________________________________________________________________________________________________________| */


				#include "watchDogTimer.h"




//----> Initialization of Watch Dog <----



						void IWDG_Init(void) 
							{
								
// 								ENABLE WRITE access to IWDG_PR & IWDG_RLR registers
										IWDG->KR = 0x5555;
								
// 								SET Prescaler to 256.  [	LSI is ~40kHz. -> ( 40000 / 256 ) = 156.25 Hz clock	]	
										IWDG->PR = 0x06;	
								
// 								SET reload value --> max (0xFFF = 4095) - - - Timeout = 4095 / 156.25 Hz = ~26.2 seconds max before reset
										IWDG->RLR = 0xFFF;

// 								RELOAD IWDG counter & start the watchdog
										IWDG->KR = 0xAAAA;
										IWDG->KR = 0xCCCC; 
							}

							
							

//----> Pet the doG <----
							
														
						void IWDG_Feed(void)			{	 IWDG->KR = 0xAAAA;	}