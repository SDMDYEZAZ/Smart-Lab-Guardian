/*********************************************************************/
/* File Name   : pwd.c                                               */
/* Description : Keypad password authentication for SmartLab Guardian*/
/*               (prompt, read, compare, retry limit, lockout)       */
/* Controller  : LPC2148                                             */
/*********************************************************************/

#include "types.h"
#include "pwd_defines.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "pwd.h"

/*
 * Function Name : PWD_CHECK
 * Description   : Older all-in-one password check (prompt, read, compare,
 *                 retries). Not used by PWD_AUTH(); see PWD_CORRECT().
 * Parameters    : correct_pwd - the password to compare against
 * Return Value  : 1 - password matched
 *                 0 - all MAX_ATTEMPTS used, access locked
 */
 
u8 PWD_CHECK(u32 correct_pwd)
{
	u32 pwd;
	u8 lastKey;
	u8 attempts = 0;

	while(attempts < MAX_ATTEMPTS)
	{
		pwd = 0;                              /* reset value for every attempt */
		CMD_LCD(CLEAR_LCD);
		STR_LCD("=>PWD 4Digits");              /* prompt on line 1 */
		CMD_LCD(GOTO_LINE2_POS0);             /* typed digits appear on line 2 */

		READ_NUM2(&pwd, &lastKey);            /* read digits until a non-digit key */

		CMD_LCD(CLEAR_LCD);
		if(pwd == correct_pwd)                /* correct password */
		{
			STR_LCD("PWD MATCH");
			delay_s(1);
			return 1;
		}

		attempts++;                           /* wrong password: count the attempt */
		STR_LCD("PWD FAIL");
		CMD_LCD(GOTO_LINE2_POS0);
		STR_LCD("TRIES LEFT:");
		CHAR_LCD('0' + (MAX_ATTEMPTS - attempts));   /* show remaining tries */
		delay_s(1);
	}

	/* all attempts used */
	CMD_LCD(CLEAR_LCD);
	STR_LCD("ACCESS LOCKED");
	delay_s(2);
	return 0;
}

/*
 * Function Name : PWD_MESSAGE
 * Description   : Shows the password prompt and moves the cursor to line 2.
 * Return Value  : None
 */
void PWD_MESSAGE(void)
{
	CMD_LCD(CLEAR_LCD);
	STR_LCD("ENTER PASS:");
	CMD_LCD(GOTO_LINE2_POS0);
}

/*
 * Function Name : PWD_READANDCOM
 * Description   : Reads one password entry from the keypad and compares it
 *                 with the correct password.
 * Parameters    : correct_pwd - the password to compare against
 * Return Value  : 1 - entry matches, 0 - entry does not match
 */
u8 PWD_READANDCOM(u32 correct_pwd)
{
	u32 pwd = 0;                              /* start from 0 for every entry */
	u8 lastKey;                               /* terminating (non-digit) key */

	READ_NUM2(&pwd, &lastKey);
	return (pwd == correct_pwd) ? 1 : 0;
}

/*
 * Function Name : PWD_INCORRECT
 * Description   : Shows the wrong-password message and the tries left.
 * Parameters    : attempts - number of failed attempts so far
 * Return Value  : None
 */
void PWD_INCORRECT(u8 attempts)
{
	CMD_LCD(CLEAR_LCD);
	STR_LCD("WRONG PASS");
	CMD_LCD(GOTO_LINE2_POS0);
	STR_LCD("TRIES LEFT:");
	CHAR_LCD('0' + (MAX_ATTEMPTS - attempts));   /* remaining tries as a digit */
	delay_s(1);
}

/*
 * Function Name : PWD_CORRECT
 * Description   : Gives the user up to MAX_ATTEMPTS tries to enter the
 *                 correct password.
 * Parameters    : correct_pwd - the password to compare against
 * Return Value  : 1 - password matched within the allowed attempts
 *                 0 - all attempts failed (locked)
 */
u8 PWD_CORRECT(u32 correct_pwd)
{
	u8 attempts = 0;

	while(attempts < MAX_ATTEMPTS)
	{
		PWD_MESSAGE();                        /* show the prompt */

		if(PWD_READANDCOM(correct_pwd))       /* read and compare */
		{
			CMD_LCD(CLEAR_LCD);
			STR_LCD("PASS MATCH");
			delay_s(1);
			return 1;
		}

		attempts++;                           /* wrong: count it and show tries left */
		PWD_INCORRECT(attempts);
	}

	/* all attempts used */
	CMD_LCD(CLEAR_LCD);
	STR_LCD("FAILED");
	delay_s(2);
	return 0;
}

/*
 * Function Name : PWD_AUTH
 * Description   : Complete authentication used by the application:
 *                 checks the password (PASSWORD in pwd_defines.h) and
 *                 shows "ACCESS GRANTED" on success.
 * Return Value  : 1 - access granted, 0 - access denied
 */
u8 PWD_AUTH(void)
{
	if(PWD_CORRECT(PASSWORD))
	{
		CMD_LCD(CLEAR_LCD);
		STR_LCD("ACCESS GRANTED");
		delay_s(1);
		return 1;
	}
	return 0;
}
