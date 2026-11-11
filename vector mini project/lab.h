#ifndef LAB_H
#define LAB_H

/*********************************************************************/
/* File Name   : lab.h                                               */
/* Description : Function declarations for the SmartLab Guardian     */
/*               lab module (access, schedule, devices, IR control)  */
/* Controller  : LPC2148                                             */
/*********************************************************************/

#include "types.h"

/* Initialize LCD, keypad, RTC, outputs and the EINT0/EINT1 hooks */
void LAB_INIT(void);

/* Emergency: devices OFF, buzzer ON, stays latched until password is entered */
void LAB_EMERGENCY(void);

/* RTC edit: password check, then set time and date from the keypad */
void LAB_RTC_EDIT(void);

/* Returns 1 if the current RTC hour is inside the lab operating hours */
u8   LAB_IN_HOURS(void);

/* Outside lab hours: devices OFF, user logged out, clock displayed */
void LAB_CLOSED(void);

/* Returns 1 if the user is logged in, 0 if not */
u8   LAB_IS_AUTH(void);

/* Ask for the password and log the user in on success */
void LAB_LOGIN(void);

/* Read the IR remote: toggle Device 1, Device 2, or all OFF and logout */
void LAB_IR_CONTROL(void);

/* Read the RTC and show time and date on the LCD */
void LAB_SHOW_CLOCK(void);

#endif  /* LAB_H */