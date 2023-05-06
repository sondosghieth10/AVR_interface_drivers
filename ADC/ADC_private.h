 /**************************************************/
/* Author    : Sondos Mohamed Samir                  */


#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/*********** SELECT Max reference VOLTAGE*************/
#define AREF 			  1
#define AVCC 			  2
#define INTERNAL_VOLTAGE  3

/* STATES OF ADC */
#define IDLE    1
#define BUSY    2

#define BUSYFUNCTION  3

#define TIMEOUTREACHED  4

#define PRESCALERMASK 0b11111000

/*  PreScaling Modes */
#define CLK_DIV_2 			     0
#define CLK_DIV_4 			     2
#define CLK_DIV_8  			     3
#define CLK_DIV_16 			     4
#define CLK_DIV_32  			 5
#define CLK_DIV_64  	     	 6
#define CLK_DIV_128    	     	 7	

/*  Adjustment Modes */
#define LEFT_ADJUSTED  			 1
#define RIGHT_ADJUSTED  		 2

/*******   Triggering modes  *************/
#define Free_Running_mode           	1
#define Analog_Comparator           	2
#define External_Interrupt_Request0 	3
#define Timer0_CTC                  	4
#define Timer0_OVR                  	5
#define Timer1_CTC_B                	6
#define Timer1_OVR                  	7
#define Timer1_Capture_event        	8



#endif
