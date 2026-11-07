/******************************************************************************/
/* File Name   : rtc.c                                                        */
/* Description : Contains the function definitions for RTC initialization,    */
/*               time and date configuration, data retrieval and LCD display. */
/* Controller  : LPC2129 / LPC2148                                            */
/******************************************************************************/

#include <LPC21XX.H>
#include "rtc_defines.h"
#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"

/* Controller selection for RTC configuration */
#define LPC2129 0
#define LPC2148 1
//#define CPU LPC2129
#define CPU LPC2148

/* Stores the abbreviated names of the weekdays */
s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/* Enumeration for weekday indexing */
enum days{SUN,MON,TUE,WED,THU,FRI,SAT};

/*
 * Function Name : RTC_INIT
 * Description   : Initializes the RTC module and configures the clock source based on the selected controller.
 */

void RTC_INIT(void)
{
	/* Reset the RTC module */
	CCR = RTC_RESET;
	
	#if (CPU == LPC2129)
	/* Configure prescaler values for the RTC clock */
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	
	/* Enable the RTC module */
	CCR = RTC_ENABLE; 
	
	#elif (CPU == LPC2148)
	/* Enable RTC with the selected clock source */
	CCR = RTC_ENABLE | RTC_CLKSRC; 
	
	#endif
}

/*
 * Function Name : RTC_SET_TIME
 * Description   : Sets the hour, minute and second values in the RTC registers.
 */

void RTC_SET_TIME(u32 hour, u32 min, u32 sec)
{
	HOUR = hour; 
	MIN = min;
	SEC = sec;
}

/*
 * Function Name : RTC_SET_DATE
 * Description   : Sets the date, month and year values in the RTC registers.
 */

void RTC_SET_DATE(u32 date,u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}

/*
 * Function Name : RTC_GET_TIME
 * Description   : Reads the current time from the RTC registers and stores the values through pointer arguments.
 */

void RTC_GET_TIME(u32* hour, u32*min, u32*sec)
{
	*hour = HOUR;
	*min = MIN;
	*sec = SEC;
}

/*
 * Function Name : RTC_GET_DATE
 * Description   : Reads the current date from the RTC registers and stores the values through pointer arguments.
 */

void RTC_GET_DATE(u32* date, u32* month, u32* year)
{
	*date = DOM; 
	*month = MONTH;
	*year = YEAR;
}

/*
 * Function Name : RTC_DISPLAY_TIME
 * Description   : Displays the current time in HH:MM:SS format on the first line of the LCD.
 */

void RTC_DISPLAY_TIME(u32 hour, u32 min, u32 sec)
{
	/* Position the LCD cursor at the beginning of line 1 */
	CMD_LCD(GOTO_LINE1_POS0);
	
	 /* Display hours */
	CHAR_LCD((hour/10)+48);
	CHAR_LCD((hour%10)+48);
	CHAR_LCD(':');
	
	/* Display minutes */
	CHAR_LCD((min/10)+0X30);
	CHAR_LCD((min%10)+0X30);
	CHAR_LCD(':');
	
	/* Display seconds */
	CHAR_LCD((sec/10)+'0');
	CHAR_LCD((sec%10)+'0');
}

/*
 * Function Name : RTC_DISPLAY_DATE
 * Description   : Displays the current date in DD/MM/YYYY format on the second line of the LCD.
 */

void RTC_DISPLAY_DATE(u32 date, u32 month, u32 year)
{
	/* Position the LCD cursor at the beginning of line 2 */
	CMD_LCD(GOTO_LINE2_POS0);
	
  /* Display date */
	CHAR_LCD((date/10)+48);
	CHAR_LCD((date%10)+48);
	CHAR_LCD('/');
	
	/* Display month */
	CHAR_LCD((month/10)+0X30);
	CHAR_LCD((month%10)+0X30);
	CHAR_LCD('/');
	
  /* Display year */
	U32_LCD(YEAR);
}

/*
 * Function Name : RTC_GET_DAY
 * Description   : Reads the current day-of-week value from the RTC register.
 */

void RTC_GET_DAY(u32* dow)
{
	*dow = DOW;
}

/*
 * Function Name : RTC_SET_DAY
 * Description   : Sets the day-of-week value in the RTC register.
 */

void RTC_SET_DAY(u32 dow)
{
	DOW = dow;
}

/*
 * Function Name : RTC_DISPLAY_DAY
 * Description   : Displays the abbreviated weekday name on the first line of the LCD.
 */

void RTC_DISPLAY_DAY(u32 day)
{
  /* Position the LCD cursor at the weekday display location */
	CMD_LCD(GOTO_LINE1_POS0+13);
	
	/* Display the corresponding weekday */
	STR_LCD(week[day]);
}


	

