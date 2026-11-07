/****************************************************/
/* File Name : delay.c                              */
/* Description : Provides software delay functions. */
/* Controller : LPC2129/LPC2148                     */
/* Clock Frequency : 60 MHZ                         */
/****************************************************/

#include "types.h"

/*
 *Function Name: delay_us
 *Description: Generates delay in micro seconds
 *Return: None
 */

void delay_us(u32 dly_us)
{
	for(dly_us*=12;dly_us>0;dly_us--); //loop for micro seconds delay
}

/*
 *Function Name: delay_ms
 *Description: Generates delay in milli seconds
 *Return: None
 */

void delay_ms(u32 dly_ms)
{
	for(dly_ms*=12000;dly_ms>0;dly_ms--); //loop for milli seconds delay
}

/*
 *Function Name: delay_s
 *Description: Generates delay in seconds
 *Return: None
 */

void delay_s(u32 dly_s)
{
	for(dly_s*=12000000;dly_s>0;dly_s--); //loop for seconds delay
}
