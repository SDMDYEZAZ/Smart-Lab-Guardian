#include "types.h"

u8 CheckPassword(u32 correct_pwd)
{
	u32 pwd;
	u8 lastKey;
	u8 attempts = 0;

	while(attempts < MAX_ATTEMPTS)
	{
		pwd = 0;                        // reset every attempt
		CMD_LCD(CLEAR_LCD);
		STR_LCD("=>PWD 4Digits");
		CMD_LCD(GOTO_LINE2_POS0);

		READ_NUM2(&pwd, &lastKey);

		CMD_LCD(CLEAR_LCD);
		if(pwd == correct_pwd)
		{
			STR_LCD("PWD MATCH");
			delay_s(1);
			return 1;
		}

		attempts++;
		STR_LCD("PWD FAIL");
		CMD_LCD(GOTO_LINE2_POS0);
		STR_LCD("TRIES LEFT:");
		CHAR_LCD('0' + (MAX_ATTEMPTS - attempts));   // use your char-print function
		delay_s(1);
	}

	CMD_LCD(CLEAR_LCD);
	STR_LCD("ACCESS LOCKED");
	delay_s(2);
	return 0;
}
