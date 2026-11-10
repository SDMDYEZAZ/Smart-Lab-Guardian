/******************************************************************/
/* File Name : ir.h                                               */
/* Description : contains of function declarations of ir receiver */
/* Controller : LPC2129 / LPC2148                                 */
/* Type : TSOP1738                                                */
/******************************************************************/

#include "types.h"

/*Function declarations*/
static u8 CHECK_EDGE(u32 level, u32 time_out);
static void CHECK_IDLE(void);
u8 IR_READ(u32 *address, u32 *command, u32 *toggle);
