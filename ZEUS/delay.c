
				
	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 28, 2026 - 16:30 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Delay Source File																																										|
		|																												-> Using TIM2 because it is much more accurate timing to use																		|
		|_______________________________________________________________________________________________________________________________________________________| */
				

				#include "delay.h"
	
															
														void delay_us(uint16_t delay_time_us)	
															{
																
																	TIM2->CNT = 0;
																	
																	while (TIM2->CNT <= delay_time_us) 					{ 	__NOP(); 	}
															}
															
															
															
															
														void delay_ms(uint32_t ms)
															{
																
																		TIM2->CNT = 0;
																
																		for ( uint32_t i = 0; i < ms; i++ ) 			{ 	delay_us(1000); 	}
															}