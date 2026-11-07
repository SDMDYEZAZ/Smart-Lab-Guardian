#include <LPC21XX.H>

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

int main()
{
	INIT_LCD();
	CMD_LCD(GOTO_LINE1_POS0);
	STR_LCD("SMARTLABGUARDIAN");
	delay_ms(100);
	CMD_LCD(GOTO_LINE2_POS0);
	STR_LCD("LAB MONITOR");
	delay_ms(100);
	CMD_LCD(CLEAR_LCD);
	while(1);
}
