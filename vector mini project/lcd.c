/**********************************************************/
/* File Name   : lcd.c                                    */
/* Description : LCD driver functions for data, commands, */
/*               strings and numerical value display.     */
/* Controller  : LPC2129 / LPC2148                        */
/* Interface   : 8-bit LCD mode                           */
/**********************************************************/

 
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
#include "types.h"
#include <lpc21xx.h>

/*
 * Function Name : WRITE_LCD
 * Description   : Sends 8-bit data to the LCD data pins.
 * Parameter     : dat - Data to be sent.
 */
 
void WRITE_LCD(u32 dat)
{
	/* Place data on the LCD data pins */
	WRITEBYTE(IOPIN0, LCD_DATA, dat);
	
	/* Select write operation */
	IOCLR0 = 1 << LCD_RW;
	
	/* Generate LCD enable pulse */
	IOSET0 = 1 << LCD_EN;
	delay_us(1);
	IOCLR0 = 1 << LCD_EN;
	
	/* Allow LCD time to process the instruction */
	delay_ms(2);
}

/*
 * Function Name : CMD_LCD
 * Description   : Sends a command instruction to the LCD.
 * Parameter     : cmd - LCD command.
 */

void CMD_LCD(u8 cmd)
{
	/* Select command register */
	IOCLR0 = 1 << LCD_RS; 
	
	/* Transfer command to LCD */
	WRITE_LCD(cmd);
}

/*
 * Function Name : CHAR_LCD
 * Description   : Displays a single character on the LCD.
 * Parameter     : asciival - ASCII character to be displayed.
 */

void CHAR_LCD(u8 asciival)
{
	/* Select data register */
	IOSET0 = 1 << LCD_RS;
	
	/* Transfer character to LCD */
	WRITE_LCD(asciival);
}

/*
 * Function Name : STR_LCD
 * Description   : Displays a null-terminated string on the LCD.
 * Parameter     : s - Pointer to the string.
 */

void STR_LCD(s8* s)
{
	/* Transmit characters until the null terminator is encountered */
	while(*s){
		CHAR_LCD(*s++);
	}
}

/*
 * Function Name : U32_LCD
 * Description   : Displays an unsigned 32-bit integer on the LCD.
 * Parameter     : n - Number to be displayed.
 */

void U32_LCD(u32 n)
{
	u8 a[10];
	s32 i = 0;
	/* Handle zero separately */
	if(n == 0)
	{
		CHAR_LCD('0');
	}
	else
	{
		/* Extract individual digits in reverse order */
		while(n > 0)
		{
			a[i] = (n % 10) + 48;
			n /= 10;
			i++;
		}
		/* Display digits in the correct order */
		for(--i; i >= 0; i--)
		{
			CHAR_LCD(a[i]);
		}
	}
}

/*
 * Function Name : S32_LCD
 * Description   : Displays a signed 32-bit integer on the LCD.
 * Parameter     : n - Signed number to be displayed.
 */

void S32_LCD(s32 n)
{
	/* Display negative sign for negative values */
	if(n < 0)
	{
		CHAR_LCD('-');
		n = -n;
	}
	
	/* Display the absolute numerical value */
	U32_LCD(n);
}

/*
 * Function Name : F32_LCD
 * Description   : Displays a floating-point number on the LCD.
 * Parameters    : F - Floating-point value.
 *                 n - Number of decimal places.
 */

void F32_LCD(f32 F, u8 n)
{
	u32 m, i;
	
	/* Handle negative floating-point values */
	if(F < 0.0)
	{
		CHAR_LCD('-');
		F = -F;
	}
	
	/* Display integer portion */
	m = F;
	U32_LCD(m);
	
	/* Display decimal point */
	CHAR_LCD('.');
	
	/* Extract and display fractional digits */
	for(i = 0; i < n; i++)
	{
		F = (F - m) * 10;
		m = F;
		CHAR_LCD(m + 48);
	}
}

/*
 * Function Name : BUILD_CGRAM
 * Description   : Creates custom characters in LCD CGRAM.
 * Parameters    : p     - Pointer to custom character pattern.
 *                 bytes - Number of pattern bytes.
 */

void BUILD_CGRAM(u8 *p, u8 bytes)
{
	u32 i;
	
	/* Select CGRAM address */
	CMD_LCD(GOTO_CGRAM_START);
	
	/* Select data register and write operation */
	IOSET0 = 1 << LCD_RS;
	IOCLR0 = 1 << LCD_RW;
	
	/* Transfer custom character pattern bytes */
	for(i = 0; i < bytes; i++)
	{
		WRITE_LCD(p[i]);
	}
	
	/* Return LCD cursor to the beginning of display */
	CMD_LCD(GOTO_LINE1_POS0);
}

/*
 * Function Name : INIT_LCD
 * Description   : Initializes the LCD in 8-bit, 2-line mode.
 */

void INIT_LCD(void)
{
	/* Configure LCD data and control pins as outputs */
	IODIR0 = (0xFF << LCD_DATA) | (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);
	
	/* Wait for LCD power-on initialization */
	delay_ms(15);
	
	/* Initialize LCD using the required startup sequence */
	CMD_LCD(0X30);
	delay_ms(4);
	delay_us(100);
	CMD_LCD(0X30);
	delay_us(100);
	CMD_LCD(0X30);
	
	/* Configure LCD operating mode */
	CMD_LCD(MODE_8BIT_2LINE);
	
	/* Enable display and configure cursor */
	CMD_LCD(DISP_ON_CUR_BLK);
	
	/* Clear LCD display */
	CMD_LCD(CLEAR_LCD);
	
	/* Set cursor movement direction */
	CMD_LCD(SHIFT_CUR_RIGHT);
}
