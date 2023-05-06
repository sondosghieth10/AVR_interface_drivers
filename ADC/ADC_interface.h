/**************************************************/
/* Author    : Sondos Mohamed Samir               */
/* Layer     : MCAL layer                         */
/* Component : ADC                                */
/* Date      : 12 MAR 2023                        */
/* Version   : V01                                */
/**************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

void ADC_voidinit(void);

u8 ADC_StartConversionSync(u8 Copychannel,u8 * CopyADC_Reading);


u8 ADC_StartConversionAsync(u8 Copychannel,u8 * CopyADC_ReadingResult , void (*copy_pvCallBackFunc)(void));



#endif
