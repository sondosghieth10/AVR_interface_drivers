/**************************************************/
/* Author    : Sondos Mohamed Samir               */
/* Layer     : MCAL layer                         */
/* Component : ADC                                */
/* Date      : 12 MAR 2023                        */
/* Version   : V01                                */
/**************************************************/

#ifndef ADC_REGISTER_H
#define ADC_REGISTER_H


#define ADMUX_Register   *((volatile u8*)0x27) // ADC Multiplexer selection register
#define ADMUX_REFS1      7  	// Reference Selection Bit1 
#define ADMUX_REFS0      6  	// Reference Selection Bit0
#define ADMUX_ADLAR      5  	// ADC left Adjust Result
 
#define ADCSRA_Register  *((volatile u8*)0x26)  // ADC Control and Status register
#define ADCSRA_ADEN      7    // ADC enable
#define ADCSRA_ADSC	     6    // Start Conversion
#define ADCSRA_ADATE     5    // Auto trigger enable 
#define ADCSRA_ADIF      4    // Interrupt flag
#define ADCSRA_ADIE      3    // Interrupt enable
#define ADCSRA_ADPS2     2    // Prescaler bit2
#define ADCSRA_ADPS1     1    // Prescaler bit1
#define ADCSRA_ADPS0     0    // Prescaler bit0


#define ADCL_Register    *((volatile u8*)0x24) // ADC Low Register

#define ADCH_Register    *((volatile u8*)0x25) // ADC High Register



#endif  
