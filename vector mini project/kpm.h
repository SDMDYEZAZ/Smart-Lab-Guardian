/************************************************************************************/
/* File Name   : kpm.h                                                              */
/* Description : Contains the function prototypes for matrix keypad initialization, */
/*                key detection, scanning and numerical input.                      */
/* Controller  : LPC2129 / LPC2148                                                  */
/* Interface   : 4x4 Matrix Keypad                                                  */
/************************************************************************************/
 
#include "types.h"

/* Keypad initialization function */
void INIT_KPM(void);

/* Keypad column scanning function */
u8 COL_SCAN(void);

/* Keypad row scanning function */
u8 ROW_SCAN(void);

/* Keypad column identification function */
u8 COL_CHECK(void);

/* Key detection and identification function */
u8 KEY_SCAN(void);

/* Reads numeric input and returns the entered value */
u32 READ_NUM(void);

/* Reads numeric input and updates the supplied variables */
void READ_NUM2(u32*,u8*);

/*checks the password that user entered for security*/
u8 CheckPassword(u32 correct_pwd);


