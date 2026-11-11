/*********************************************************************/
/* File Name   : lab.c                                               */
/* Description : SmartLab Guardian lab module: emergency, RTC edit,  */
/*               operating hours, login, IR control and clock display*/
/* Controller  : LPC2148                                             */
/*********************************************************************/

#include <LPC214X.H>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "ext_int.h"
#include "ext_int_defines.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "ir.h"
#include "ir_defines.h"
#include "flag.h"
#include "output.h"
#include "pwd.h"
#include "pwd_defines.h"
#include "lab_defines.h"
#include "lab.h"

extern void (*EINT0_FUN)(void);
extern void (*EINT1_FUN)(void);

/* ---------------- module state (private to this file) ------------- */
static u8  dev1 = 0;              /* Device 1 (LED1) state */
static u8  dev2 = 0;              /* Device 2 (LED2) state */
static u8  authenticated = 0;     /* 1 = user logged in */
static u32 last_tog = 2;          /* last RC5 toggle bit, 2 = none yet */

/* ---------------- private helper ---------------------------------- */
/* Switch both devices OFF and clear their state */
static void DEVICES_OFF(void)
{
	dev1 = 0;
	dev2 = 0;
	LED1_OFF();
	LED2_OFF();
}

/* ---------------- initialization ---------------------------------- */
void LAB_INIT(void)
{
	INIT_LCD();
	INIT_KPM();
	INIT_RTC();
	INIT_OUT();

	EINT0_FUN = RTC_EDIT;      /* EINT0: RTC edit request */
	EINT1_FUN = EMERGENCY;     /* EINT1: emergency request */
}

/* ---------------- emergency --------------------------------------- */
void LAB_EMERGENCY(void)
{
	DEVICES_OFF();
	BUZZER_ON();

	CMD_LCD(CLEAR_LCD); STR_LCD("EMERGENCY!");
	CMD_LCD(GOTO_LINE2_POS0); STR_LCD("ALL DEVICES OFF");
	delay_s(2);

	while(PWD_AUTH() == 0);    /* stay latched until the password is entered */

	BUZZER_OFF();
	emergency_flag = 0;
	authenticated = 0;
	CMD_LCD(CLEAR_LCD);
}

/* ---------------- RTC edit ---------------------------------------- */
void LAB_RTC_EDIT(void)
{
	u32 hour = 12, min = 30, sec = 0, day = 10, month = 11, year = 2026;

	edit_flag = 0;

	if(PWD_AUTH())
	{
		CMD_LCD(CLEAR_LCD); STR_LCD("ACCESS GRANTED");
		delay_s(1);

		CMD_LCD(CLEAR_LCD); STR_LCD("ENTER HOUR:");  hour  = READ_NUM();
		CMD_LCD(CLEAR_LCD); STR_LCD("ENTER MIN:");   min   = READ_NUM();
		CMD_LCD(CLEAR_LCD); STR_LCD("ENTER SEC:");   sec   = READ_NUM();
		CMD_LCD(CLEAR_LCD); STR_LCD("ENTER DAY:");   day   = READ_NUM();
		CMD_LCD(CLEAR_LCD); STR_LCD("ENTER MONTH:"); month = READ_NUM();
		CMD_LCD(CLEAR_LCD); STR_LCD("ENTER YEAR:");  year  = READ_NUM();

		CMD_LCD(CLEAR_LCD);
		if(hour < 24 && min < 60 && sec < 60 &&
		   day >= 1 && day <= 31 && month >= 1 && month <= 12)
		{
			RTC_SET_TIME(hour, min, sec);
			RTC_SET_DATE(day, month, year);
			STR_LCD("RTC UPDATED");
		}
		else
		{
			STR_LCD("INVALID INPUT");
		}
		delay_s(1);
	}
	CMD_LCD(CLEAR_LCD);
}

/* ---------------- operating hours --------------------------------- */
u8 LAB_IN_HOURS(void)
{
	u32 hour, min, sec;

	RTC_GET_TIME(&hour, &min, &sec);
	return (hour >= LAB_OPEN_HOUR && hour < LAB_CLOSE_HOUR) ? 1 : 0;
}

void LAB_CLOSED(void)
{
	DEVICES_OFF();
	authenticated = 0;
	LAB_SHOW_CLOCK();
}

/* ---------------- login ------------------------------------------- */
u8 LAB_IS_AUTH(void)
{
	return authenticated;
}

void LAB_LOGIN(void)
{
	CMD_LCD(CLEAR_LCD); STR_LCD("LAB LOCKED");
	delay_s(1);

	if(PWD_AUTH())
	{
		authenticated = 1;
		BEEP(100);
		CMD_LCD(CLEAR_LCD); STR_LCD("ACCESS GRANTED");
		delay_s(1);
		CMD_LCD(CLEAR_LCD);
	}
}

/* ---------------- IR remote control ------------------------------- */
void LAB_IR_CONTROL(void)
{
	u32 addr, cmd, tog;

	if(IR_PIN != 0)
		return;                        /* no IR burst, TSOP idles HIGH */

	if(!IR_READ(&addr, &cmd, &tog))
		return;                        /* bad frame */

	delay_ms(10);                      /* let the frame finish */

	if(tog == last_tog)
		return;                        /* same key still held down */
	last_tog = tog;

	if(cmd == CMD_DEV1)
	{
		dev1 = !dev1;
		if(dev1) LED1_ON(); else LED1_OFF();
	}
	else if(cmd == CMD_DEV2)
	{
		dev2 = !dev2;
		if(dev2) LED2_ON(); else LED2_OFF();
	}
	else if(cmd == CMD_ALL_OFF)
	{
		DEVICES_OFF();
		authenticated = 0;             /* all-off also logs out */
		CMD_LCD(CLEAR_LCD);
	}
}

/* ---------------- clock display ----------------------------------- */
void LAB_SHOW_CLOCK(void)
{
	u32 hour, min, sec, day, month, year;

	RTC_GET_TIME(&hour, &min, &sec);
	RTC_GET_DATE(&day, &month, &year);

	RTC_DISPLAY_TIME(hour, min, sec);
	RTC_DISPLAY_DATE(day, month, year);

	delay_ms(10);
}