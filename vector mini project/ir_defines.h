/*******************************************************************/
/* File Name    : ir_defines.h                                     */
/* Description  : Definitions for RC5 IR receiver                  */
/* Controller   : LPC2129 / LPC2148                                */
/* Type         : TSOP1738                                         */
/*******************************************************************/
#include <LPC21XX.H>

#define TSOP_PIN  16                           // TSOP1738 output connected to P0.16
#define IR_PIN    ((IOPIN0 >> TSOP_PIN) & 1)   // Read IR receiver pin status
#define IR_T      1778                         // IR bit period in microseconds 
#define IR_H      889                          // IR half-bit period in microseconds
#define IR_Q      444                          // IR quarter-bit period in microseconds
#define STEP_TIME 20                           // Sampling time interval in microseconds
