/***************************************************************/
/* File Name   : lcd_defines.h                                 */
/* Description : Contains the LCD instruction codes, GPIO pin  */
/*               assignments and interface mode configuration. */
/* Controller  : LPC2129 / LPC2148                             */
/* LCD Driver  : HD44780 Compatible                            */
/***************************************************************/
 
/* HD44780 LCD command instructions */
#define CLEAR_LCD         0X01  // Clears display and returns cursor home 
#define RET_CUR_HOME      0X02  // Returns cursor to the home position 
#define SHIFT_CUR_RIGHT   0X06  // Moves cursor position to the right 
#define SHIFT_CUR_LEFT    0X07  // Moves cursor position to the left 
#define DISP_OFF          0X08  // Turns display OFF 
#define DISP_ON_CUR_OFF   0XOC  // Turns display ON and cursor OFF 
#define DISP_ON_CUR_ON    0X0E  // Turns display ON and cursor ON 
#define DISP_ON_CUR_BLK   0X0F  // Turns display ON with blinking cursor 
#define SHIFT_DSP_RIGHT   0X14  // Shifts entire display to the right 
#define SHIFT_DSP_LEFT    0X10  // Shifts entire display to the left 
#define MODE_4BIT_1LINE   0X20  // 4-bit interface, 1-line display 
#define MODE_8BIT_1LINE   0X30  // 8-bit interface, 1-line display 
#define MODE_4BIT_2LINE   0X28  // 4-bit interface, 2-line display 
#define MODE_8BIT_2LINE   0X38  // 8-bit interface, 2-line display 
#define GOTO_LINE1_POS0   0X80  // Sets cursor to line 1, position 0 
#define GOTO_LINE2_POS0   0XC0  // Sets cursor to line 2, position 0 
#define GOTO_LINE3_POS0   0X94  // Sets cursor to line 3, position 0 
#define GOTO_LINE4_POS0   0XD4  // Sets cursor to line 4, position 0 
#define GOTO_CGRAM_START  0x40  // Sets CGRAM address to the beginning 

/* LCD GPIO pin assignments for LPC21xx */ 
#define LCD_DATA  6   // LCD data bus starting pin: P0.6 
#define LCD_RS    17  // Register Select pin: P0.17
#define LCD_RW    18  // Read/Write control pin: P0.18 
#define LCD_EN    19  // Enable control pin: P0.19

/* LCD interface configuration */
#define LCD_MODE 8  // Selects 8-bit interface mode 
//#define LCD_MODE 4  // Selects 4-bit interface mode
