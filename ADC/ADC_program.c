/****************************************************/
/* Author    : Sondos Mohamed Samir                 */
/* Layer     : MCAL layer                           */
/* Component : ADC                                  */
/* Date      : 12 MAR 2023                          */
/* Version   : V01                                  */
/****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATh.h"

#include "ADC_interface.h"
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"


// Notification Function is used to inform the user that the conversion is completed
static void (*ADC_NotificationFunc)(void); // Global pointer to function that will be used in call back method of Notification function

// Initialize a Global Pointer Variable to hold the Value of ADC_Result and give it to ISR
static u8 * ADC_ReadingResult;

// Initialize a Global Variable that indicate State of ADC ,, IF ADC Is busy don't start A new conversion until first one is completed
u8 ADC_State = IDLE;

void ADC_voidinit(void){

	/* AVCC as Reference Voltage */
	CLR_BIT(ADMUX_Register,ADMUX_REFS1);
	SET_BIT(ADMUX_Register,ADMUX_REFS0);

	/* We will choose 8 bits only from 10 bits resolution , so choose Left Adjust and read ADCH only*/
	#if ADJUSTMENT_MODE == LEFT_ADJUSTED
	SET_BIT(ADMUX_Register,ADMUX_ADLAR);

	#elif ADJUSTMENT_MODE == RIGHT_ADJUSTED
	CLR_BIT(ADMUX_Register,ADMUX_ADLAR);

	#else
	#error "Wrong Choose of mode of operation "
	#endif


	// Select Prescaler using Bit Mask Method//
	ADCSRA_Register &= PRESCALERMASK;
	ADCSRA_Register |= ADC_PRESCALER;


	/* Enable Peripheral , Enable is preferred to be at end of function so perihperal will open with right configuration direct*/
	SET_BIT(ADCSRA_Register,ADCSRA_ADEN);


}

u8 ADC_StartConversionSync(u8 Copychannel,u8 * CopyADC_Reading){

	u8 Local_ErrorStatus = OK;

	if(ADC_State == IDLE){

		ADC_State = BUSY;

		// Initialize counter to be used in Time Out Mechanism.
		u32 Local_counter =0;

		/* Choose specifi channel  using 5 bit of MUXs that determine channel no. and also whether channel is single ended or differential */
		/* First Clear the 5 bits of mask before Oring Process */
		ADMUX_Register &= 0b11100000;

		/*For Example if  we want to choose single ended ADC channel 2 ,, it's value is corrosponded to 2 from table at page 213 Datasheet*/
		ADMUX_Register |= Copychannel;

		/* Start Conversion*/
		SET_BIT(ADCSRA_Register,ADCSRA_ADSC);

		/* Polling or Busy Waiting until Conversion Complete flag is set or counter reach timeout Value */
		while((GET_BIT(ADCSRA_Register,ADCSRA_ADIF)==0) && (Local_counter != ADC_TIMEOUT)){ // Busy wait here until flag is equal one to get out from while loop
			Local_counter ++;
		}

		if (Local_counter == ADC_TIMEOUT){
			// Loop is broken because time out is reached
			Local_ErrorStatus = TIMEOUTREACHED;
		}

		else{
			// Clear Flag by setting one to it , Software Clear //
			SET_BIT(ADCSRA_Register,ADCSRA_ADIF);

			// Return the Reading //
			*CopyADC_Reading = ADCH_Register;

			/* ADC Conversion is Finished ,, Return State to Idle */
			ADC_State = IDLE;
		}

	}

	else{
		Local_ErrorStatus = BUSYFUNCTION;
	}

	return Local_ErrorStatus;
}



u8 ADC_StartConversionAsync(u8 Copychannel,u8 * CopyADC_ReadingResult,void (*copy_pvCallBackFunc)(void)){

	u8 LocalErrorStatus = OK;

	if(ADC_State == IDLE){

		// Check that input pointers are not NULL
		if(CopyADC_ReadingResult == NULL || copy_pvCallBackFunc == NULL){
			LocalErrorStatus = NULL_POINTER;
		}

		else {

			/*Convert status of ADC to Busy to avoid Overwrite of Conversion on each other */
			ADC_State = BUSY;

			/* Initialize Call back method function Globally */
			ADC_NotificationFunc = copy_pvCallBackFunc;

			/* Initialize the Reading Value Globally */
			*ADC_ReadingResult= CopyADC_ReadingResult;

			/* First Clear the 5 bits of mask before Oring Process */
			ADMUX_Register &= 0b11100000;

			/*For Example if  we want to choose single ended ADC channel 2 ,, it's value is corrosponded to 2 from table at page 213 Datasheet*/
			ADMUX_Register |= Copychannel;

			/* Start Conversion*/
			SET_BIT(ADCSRA_Register,ADCSRA_ADSC);

			/* Enable ADC Conversion Complete Interrupt Enable bit*/
			SET_BIT(ADCSRA_Register,ADCSRA_ADIE);

		}
	}

	else {
		LocalErrorStatus = BUSYFUNCTION;
	}

	return LocalErrorStatus;

}



// Interrupt Vectors number table are found in page 42 in datasheet.
// Creating ISR of ADC Conversion Complete Interrupt , we subtract one from vector table number b. it numbered from one and actually they are numbered from 0
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){

	/*Now the conversion is completed , So we can read the Value of ADC */
	*ADC_ReadingResult = ADCH_Register;

	/* Return ADC State to IDLE state after Conversion is complete */
	ADC_State = IDLE;

	/* Invoke the Call Back Notificcation Function*/
	ADC_NotificationFunc();

	/* Disable ADC Conversion Complete Enable */
	CLR_BIT(ADCSRA_Register,ADCSRA_ADIE);


}
