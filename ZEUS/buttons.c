

				
	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Buttons Source File																																									|
		|_______________________________________________________________________________________________________________________________________________________| */
				
				




#include "buttons.h"



//----> Buttons initialization <----



				void Buttons_Init ( void )
					{
						
									RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
									
						
// 						Configure PB12-PB15 as Input with Pull-up/Pull-down  ( CNF=10, MODE=00 )
						
									GPIOB->CRH &= ~ ( 0xFFFF0000 );
									GPIOB->CRH |=   ( 0x88880000 );
									
						
// 						Set ODR bits to 1 to activate internal Pull-UP resistors
						
									GPIOB->ODR |=  ( BTN1_PIN | BTN2_PIN | BTN3_PIN | BTN4_PIN );
					}

					
					
					
					
//----> Abstration of hardware readings & priority logic <----
					
					
					
					uint8_t Buttons_Get_ACTIVE_Mode ( void )
						{
							
							
// 							IDR reads 0 when switch is flipped to GND
							
									bool btn1_active =  !(  GPIOB->IDR & BTN1_PIN  );
									bool btn2_active =  !(  GPIOB->IDR & BTN2_PIN  );
									bool btn3_active =  !(  GPIOB->IDR & BTN3_PIN  );
									bool btn4_active =  !(  GPIOB->IDR & BTN4_PIN  );
									
							
							
// 							Priority Logic: Higher buttons override lower buttons
							
									if 			 ( btn4_active ) return 4;			//	BUTTON 4 : 	FORCE SYSTEM OFF MODE -> 			Emergency OFF
									else if  ( btn3_active ) return 3; 			//	 			 3 : 	FORCE SYSTEM ON MODE 	->  	  Relay = ON -> ALL sensors & time IGNORED
									else if  ( btn2_active ) return 2; 			//	 			 2 : 	VOID TIME MODE 				->  	  Dry = Water -> No matter the time
									else if  ( btn1_active ) return 1; 			//	 			 1 : 	NORMAL MODE 					->		  No button pressed
									
							
// 							DEFAULT fallback just in case
							
									return 1; 
						}
						
						