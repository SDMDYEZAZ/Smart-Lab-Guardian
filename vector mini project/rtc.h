/*******************************************************************************/
/* File Name   : rtc.h                                                         */
/* Description : Contains the function prototypes for RTC initialization,      */
/*               time and date configuration, data retrieval and LCD display.  */
/* Controller  : LPC2129 / LPC2148                                             */
/*******************************************************************************/

#include "types.h"

/* RTC initialization function prototype */
void INIT_RTC(void);

/* Time configuration function prototypes */
void RTC_SET_TIME(u32 hour, u32 min, u32 sec);

/* Date and weekday configuration function prototypes */
void RTC_SET_DATE(u32 day, u32 month, u32 year);
void RTC_SET_DAY(u32 dow);

/* Time and date retrieval function prototypes */
void RTC_GET_TIME(u32* hour, u32* min, u32* sec);
void RTC_GET_DATE(u32* day, u32* month, u32* year);
void RTC_GET_DAY(u32* dow);

/* LCD display function prototypes */
void RTC_DISPLAY_TIME(u32 hour, u32 min, u32 sec);
void RTC_DISPLAY_DATE(u32 day, u32 month, u32 year);
void RTC_DISPLAY_DAY(u32 day);

