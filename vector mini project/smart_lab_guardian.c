/*********************************************************************/
/* File Name   : smart_lab_guardian.c                                */
/* Description : SmartLab Guardian main: only calls lab functions    */
/* Controller  : LPC2148                                             */
/*********************************************************************/

#include "types.h"
#include "flag.h"
#include "lab.h"

int main()
{
	LAB_INIT();                              /* LCD, keypad, RTC, outputs, EINT hooks */

	while(1)
	{
		/* 1. emergency: highest priority */
		if(emergency_flag == 1)
		{
			LAB_EMERGENCY();
			continue;
		}

		/* 2. RTC edit request (password protected) */
		if(edit_flag == 1)
		{
			LAB_RTC_EDIT();
			continue;
		}

		/* 3. outside lab hours: devices off, login blocked */
		if(!LAB_IN_HOURS())
		{
			LAB_CLOSED();
			continue;
		}

		/* 4. inside lab hours: user must log in */
		if(!LAB_IS_AUTH())
		{
			LAB_LOGIN();
			continue;
		}

		/* 5. logged in: IR remote control and clock display */
		LAB_IR_CONTROL();
		LAB_SHOW_CLOCK();
	}
}