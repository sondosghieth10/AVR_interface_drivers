/*
 * main.c
 *
 *  Created on: Nov 12, 2022
 *      Author: SONDOS
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_Interface.h"

#include "GIE_interface.h"    // will be used in Async mode
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_register.h"

//Initialize Globap Pointer Variable to recieve the value of ADC Reading and Show corrosponding Digital on 8 LEDS Corrosp. to 8 bits Resolution
//u8  ADC_GlobReadingResult; // used in Async Mode

// Prototype of ADC End of Job Notification Function
//void ADC_Notificataion(void); // Used in Async Mode

int main(){

	u8 Local_ADCReading=0;

	// Initialize Port Function
	PORT_voidInit();

	// Initialize ADC
	ADC_voidinit();

	// Enable Global Interrupt //
	//GIE_voidEnable(); used in Async Mode

	while(1){

		// Start Conversion at channel 2 (ADC2 at PORTA Pin 2) and recieve the result at a Local Variable
		ADC_StartConversionSync(2,&Local_ADCReading);

		DIO_SetPortValue(DIO_u8PORTC,Local_ADCReading);

	}



	return 0;
}

/* The Function Below is used in Async mode
// This Function is the Notification function that will be called from ISR when conversion is complete.
void ADC_Notificataion(void){

	// Set Port C value with same Digial recieved values
	DIO_SetPortValue(DIO_u8PORTC,ADC_GlobReadingResult);

}
*/


