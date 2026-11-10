#include <LPC214X.H>

#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "delay.h"
#include "types.h"
#include "defines.h"
#include "ext_int_defines.h"
#include "ext_int.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "ir.h"
#include "ir_defines.h"
#include "flag.h"
#include "output.h"

extern void (*EINT0_FUN)(void);
extern void (*EINT1_FUN)(void);

int main()
{
	u32 hour, min, sec, day, month, year;
	INIT_LCD();
	INIT_KPM();
	INIT_RTC();
	
  EINT0_FUN = RTC_EDIT;
  EINT1_FUN = EMERGENCY;

	while(1)
	{
	if(emergency_flag == 1)
	{
		CMD_LCD(CLEAR_LCD);
		STR_LCD("EMERGENCY!");
		delay_s(1);
		emergency_flag = 0;
		CMD_LCD(CLEAR_LCD);
		
		emergency_flag = 0;
	}
	if(edit_flag == 1)
	{
		edit_flag = 0;
		
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ENTER HOUR:");
		hour = READ_NUM();
		
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ENTER MIN:");
		min = READ_NUM();
		
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ENTER SEC:");
		sec = READ_NUM();
		
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ENTER DAY:");
		day = READ_NUM();
		
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ENTER MONTH:");
	  month = READ_NUM();
		
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ENTER YEAR:");
		year = READ_NUM();
		
		if(hour < 24 && min < 60 && sec < 60 && (day >= 1 && day <=31) && (month >= 1 && month <= 12))
		{
			RTC_SET_TIME(hour,min,sec);
      RTC_SET_DATE(day,month,year);
			
			CMD_LCD(CLEAR_LCD);
      STR_LCD("RTC UPDATED");
			
			delay_s(1);
		}
		else
		{
			CMD_LCD(CLEAR_LCD);
			STR_LCD("INVALID INPUT");
			
			delay_s(1);
			
		  edit_flag = 0;
		}
	}
	else
  {
		RTC_GET_TIME(&hour,&min,&sec);
    RTC_GET_DATE(&day,&month,&year);

    RTC_DISPLAY_TIME(hour,min,sec);
    RTC_DISPLAY_DATE(day,month,year);

    delay_ms(200);
	}
}
}
	



