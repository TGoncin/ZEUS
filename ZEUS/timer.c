	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Timer Source File  																																									|
		|																											-> Generating Delay times for hardware																														|
		|_______________________________________________________________________________________________________________________________________________________| */
				
		
		
				#include "stm32f10x.h"
				#include "timer.h"




//----> TIMER 2 : Generates delay times , NOT available for any other tasks <----



			void tim2_init(void)
				{
					
							RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
					
// 					ENSURE timer OFF
					
							TIM2->CR1 = 0;
					

							TIM2->PSC  = 72 - 1;       // 72MHz / 72 = 1MHz -> 1us per tick
							TIM2->ARR  = 0xFFFF - 1;
							TIM2->CR1 |= TIM_CR1_CEN;
					
//					Wait for the counter to generate its first update event
					
							while (!(TIM2->SR & TIM_SR_UIF))
								{
										__NOP();
								}
				}

	
	
			
//----> TIMER 3 : Real 1-second tick flag <----
//      																				fires every 1.000000s exactly

			void tim3_init(void)
				{
							RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

							TIM3->CR1  = 0;
							TIM3->PSC  = 7200 - 1;     	// 72MHz / 7200 = 10kHz
							TIM3->ARR  = 10000 - 1;    	// 10kHz / 10000 = 1Hz  (exactly 1 second)
							TIM3->EGR  = TIM_EGR_UG;   	// Force update to load PSC and ARR immediately
							TIM3->SR   = 0;             // Clear any pending flag
							TIM3->CR1 |= TIM_CR1_CEN;
				}				
								

				
				
				
				
// Returns 1 once for a real-human-second second, otherwise returns 0
				
			uint8_t tim3_second_elapsed(void)
				{
							if (TIM3->SR & TIM_SR_UIF)
								{
											TIM3->SR &= ~TIM_SR_UIF;   // Clear the flag
											return 1;
								}
							return 0;
				}				
				
				
				
				
				
//----> TURN ON:		Configuration & Mode <----		
				
			void MCO_on(void)
				{
					
							RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
						
// 					CONFIGURE 	PA8 -> AFIO 		[ WRITE -> 1011b -> into configuration & mode bits ]
					
							GPIOA->CRH |=  (GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0);
							GPIOA->CRH &= ~(GPIO_CRH_CNF8_0);

// 					SELECT 	pll/2 -> clock output
					
							RCC->CFGR |= RCC_CFGR_MCO_PLL;
				}


				
				