/***********************************************************************************/
/* File Name   : lcd.h                                                             */
/* Description : Contains the function prototypes required for LCD initialization, */
/*               data transmission and display operations.                         */
/* Controller  : LPC2129 / LPC2148                                                 */
/* Interface   : 8-bit LCD mode                                                    */
/***********************************************************************************/
 
#include <LPC21XX.H>
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"

/* LCD data and command transmission functions */
void WRITE_LCD(u32 dat);
void CMD_LCD(u8 cmd);
void CHAR_LCD(u8 asciival);

/* LCD string and numerical display functions */
void STR_LCD(s8 *);
void U32_LCD(u32);
void S32_LCD(s32);
void F32_LCD(f32 F, u8 n);

/* LCD custom character generation function */
void BUILD_CGRAM(u8 *, u8);

/* LCD initialization function */
void INIT_LCD(void); 


