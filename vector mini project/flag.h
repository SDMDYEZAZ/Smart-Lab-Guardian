// Header file for flag declarations

#ifndef FLAG_H
#define FLAG_H

// Include user-defined data types
#include "types.h"

// Declare global flags defined in flag.c
extern volatile u8 edit_flag;
extern volatile u8 emergency_flag;

// Function prototypes for flag operations
void RTC_EDIT(void);
void EMERGENCY(void);

#endif
