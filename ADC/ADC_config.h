/**************************************************/
/* Author    : Sondos Mohamed Samir               */
/* Layer     : MCAL layer                         */
/* Component : ADC                                */
/* Date      : 12 Mar 2023                        */
/* Version   : V01                                */
/**************************************************/


#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H


/* Refernce Voltage options 
1. AREF
2. AVCC
3. INTERNAL_VOLTAGE
*/
#define REFERENCE_VOLTAGE  AREF

/* Prescaling Options , Copy and Paste your options:
 * 1. TIMER_COUNTER_DISABLED
 * 2. NO_PRESCALER
 * 3. CLK_DIV_8
 * 4. CLK_DIV_64
 * 5. CLK_DIV_256
 * 6. CLK_DIV_1024
 * 7. EXT_CLK_FALLING_EDGE
 * 8. EXT_CLK_RISNG_EDGE */
#define ADC_PRESCALER  		CLK_DIV_128

/*********SELECT ADJUS`TMENT_MODE ******************/
#define ADJUSTMENT_MODE      LEFT_ADJUSTED

/* Select Triggering mode */
#define TRIGGERING_MODE  	Free_Running_mode

/* Choose time out value to exit while loop at certain loop to avoid being stuck it infinetly*/
#define  ADC_TIMEOUT  50000


#endif
