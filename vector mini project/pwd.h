#ifndef PWD_H
#define PWD_H

/*********************************************************************/
/* File Name   : pwd.h                                               */
/* Description : Function declarations for keypad password module    */
/* Controller  : LPC2148                                             */
/*********************************************************************/

#include "types.h"
#include "pwd_defines.h"

/* Show the password prompt on the LCD */
void PWD_MESSAGE(void);

/* Read one entry from the keypad; 1 if it matches correct_pwd, else 0 */
u8   PWD_READANDCOM(u32 correct_pwd);

/* Show the wrong-password message and tries left */
void PWD_INCORRECT(u8 attempts);

/* Up to MAX_ATTEMPTS tries; 1 on success, 0 when locked */
u8   PWD_CORRECT(u32 correct_pwd);

/* Full flow used by the application: check PASSWORD, show ACCESS GRANTED */
u8   PWD_AUTH(void);

#endif  /* PWD_H */

