#ifndef LAB_DEFINES_H
#define LAB_DEFINES_H

/*********************************************************************/
/* File Name   : lab_defines.h                                       */
/* Description : Settings for the SmartLab Guardian lab module       */
/* Controller  : LPC2148                                             */
/*********************************************************************/

/* ---------------- Lab operating hours (24-hour format) ----------- */

/* Lab opens at this hour: 9 means 09:00 */
#define LAB_OPEN_HOUR    9

/* Lab closes at this hour: 17 means 17:00.
   Devices work from LAB_OPEN_HOUR up to, but not including, LAB_CLOSE_HOUR.
   Outside this window: devices are switched OFF and login is blocked. */
#define LAB_CLOSE_HOUR   17

/* ---------------- IR remote commands (RC5 command numbers) ------- */

/* The values below are the RC5 "command" field returned by IR_READ().
   On a standard RC5 remote, number buttons give their own number.
   Change them to match the codes your remote really sends. */

/* Remote button 1: toggle Device 1 (LED1) ON/OFF */
#define CMD_DEV1         1

/* Remote button 2: toggle Device 2 (LED2) ON/OFF */
#define CMD_DEV2         2

/* Remote button 0: switch all devices OFF and log out */
#define CMD_ALL_OFF      0

#endif  /* LAB_DEFINES_H */