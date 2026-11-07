/*************************************************************************/
/* File Name   : kpm.c                                                   */
/* Description : Contains the function definitions for 4x4 matrix keypad */
/*               initialization, key scanning and numerical input.       */
/* Controller  : LPC2129 / LPC2148                                       */
/* Interface   : 4x4 Matrix Keypad                                       */
/*************************************************************************/

#include <LPC21XX.H>
#include "kpm.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "defines.h"
#include "types.h"

/* Keypad lookup table for row and column key identification */
/*u8 KPMLUT[4][4]={
	                {0,1,2,3},
	                {4,5,6,7},
	                {8,9,10,11},
	                {12,13,14,15}
                  };*/
									
/* Keypad lookup table for row and column key identification */
/*u8 KPMLUT[4][4]={
                  {'7','8','9','/'},
	                {'4','5','6','X'},
	                {'1','2','3','-'},
	                {'C','0','=','+'}
};*/

/* Keypad lookup table for row and column key identification */
u8 KPMLUT[4][4]={
	              {'7','8','9','A'},
								{'6','5','4','B'},
								{'3','2','1','C'},
								{'*','0','+','D'}
							  };

/*
 * Function Name : INIT_KPM
 * Description   : Configures the keypad row pins as output pins for key scanning operation.
 * Return Value  : None
 */
								
void INIT_KPM(void)
{
	/* Configure all row lines as output and drive them LOW */
	WRITENIBBLE(IODIR1,ROW0,15);
}

/*
 * Function Name : COL_SCAN
 * Description   : Checks whether any keypad column is pulled LOW to detect a key press.
 * Return Value  : 0 - Key press detected.
 *                 1 - No key press detected.
 */

u8 COL_SCAN(void)
{
	u8 t;
	/* Check the column input lines for an active LOW signal */
	t = (READNIBBLE(IOPIN1, COL0) < 15) ? 0 : 1;
	return t;
}

/*
 * Function Name : ROW_CHECK
 * Description   : Identifies the row in which the pressed key is located by activating each row sequentially.
 * Return Value  : Row index (0 to 3).
 */

u8 ROW_CHECK(void)
{
	u8 r;
	/* Activate each row individually and check column status */
	for(r = 0; r < 4; r++)
	{
		WRITENIBBLE(IOPIN1, ROW0, ~(1<<r));
		
		/* Activate each row individually and check column status */
		if(!COL_SCAN())
		{
			break;
		}
		
		/* Deactivate the current row before checking the next */
		WRITENIBBLE(IOPIN1, ROW0, 0);
	}
	return r;
}

/*
 * Function Name : COL_CHECK
 * Description   : Identifies the column corresponding to the pressed key by checking column input pins.
 * Return Value  : Column index (0 to 3).
 */

u8 COL_CHECK(void)
{
	u8 c;
	/* Check each column for an active LOW signal */
	for(c = 0; c < 4; c++)
	{
		if(READBIT(IOPIN1,COL0 + c) == 0)
		{
				break;
		}
	}
	return c;
}

/*
 * Function Name : KEY_SCAN
 * Description   : Detects a key press, identifies its row and column, and retrieves the corresponding key value from the keypad lookup table.
 * Return Value  : ASCII value of the pressed key.
 */

u8 KEY_SCAN(void)
{
	u8 r, c, keyv;
	
	/* Wait until a key is pressed */
	while(COL_SCAN())
	{
		/* Identify the pressed key position */
		r = ROW_CHECK();
		c = COL_CHECK();
		
		/* Retrieve the corresponding key value */
		keyv = KPMLUT[r][c];
	}
	return keyv;
}

/*
 * Function Name : READ_NUM
 * Description   : Reads numeric keypad input and constructs an unsigned integer until a non-numeric key is pressed.
 * Return Value  : Numeric value entered through the keypad.
 */

u32 READ_NUM(void)
{
	u32 keyv, sum = 0;
	while(1)
	{
		/* Read the pressed keypad key */
		keyv = KEY_SCAN();
		
		/* Check whether the key represents a numeric digit */
		if((keyv >= '0') && (keyv <= '9'))
		{
			/* Append the new digit to the accumulated number */
			sum = ((sum*10) + (keyv - '0'));
			 /* Display entered numerical value if required */
			//CMD_LCD(GOTO_LINE2,POS0);
			//U32_LCD(sum);
		}
		else
		{
			/* Handle clear key if required */
			if(keyv == 'c')
			{
				//CMD_LCD(CLEAR_LCD);
			}
			
			/* Wait until the pressed key is released */
			while(COL_SCAN() == 0);
			break;
		}
	}
	return sum;
}

/*
 * Function Name : READ_NUM2
 * Description   : Reads numeric keypad input and updates the supplied number until a non-numeric key is pressed.
 * Parameters    : num     - Pointer to the accumulated number.
 *                 lastkey - Pointer to store the last pressed key.
 * Return Value  : None
 */
void READ_NUM2(u32*num,u8*lastkey)
{
	while(1)
	{
		 /* Read the pressed keypad key */
		*lastkey = KEY_SCAN();
		
		/* Process numeric keys */
		if((*lastkey >= '0') && (*lastkey <= '9'))
		{
			 /* Append the entered digit to the existing number */
			*num = (*num * 10) + (*lastkey - '0');
			 /* Display entered digit if required */
			//CMD_LCD(GOTO_LINE2_POS0 + (++cnt));
			//U32_LCD(*num);
			//CHAR_LCD('*');
			
			/* Wait until the pressed key is released */
			while(COL_SCAN() == 0);
		}
		else
		{
			/* Handle clear key if required */
			if(*lastkey == 'c')
			{
				//CMD_LCD(CLEAR_LCD);
			}
			
			/* Wait until the pressed key is released */
			while(COL_SCAN() == 0);
			break;
		}
	}
}

