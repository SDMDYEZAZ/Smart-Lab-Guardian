/*************************************************************************/
/* File Name   : ext_int_defines.h                                       */
/* Description : Contains the pin selection masks, VIC channel numbers   */
/*               and status LED pin definitions for external interrupts. */
/* Controller  : LPC2129 / LPC2148                                       */
/*************************************************************************/

#include <LPC21XX.H>

/* EINT0 configuration */
#define EINT0_PIN0_1      0
#define EINT0_PIN_FUNC    0X0000000C
#define EINT0_VIC_CHNO    14
#define EINT0_STATUS_LED  16

/* EINT1 configuration */
#define EINT1_PIN0_3      0
#define EINT1_PIN_FUNC    0X000000C0
#define EINT1_VIC_CHNO    15
#define EINT1_STATUS_LED  17

/* EINT2 configuration */
#define EINT2_PIN0_3      0
#define EINT2_PIN_FUNC    0X0000C000
#define EINT2_VIC_CHNO    16
#define EINT2_STATUS_LED  18

/* EINT3 configuration */
#define EINT3_PIN0_3      0
#define EINT3_PIN_FUNC    0X000C0000
#define EINT3_VIC_CHNO    17
#define EINT3_STATUS_LED  19
