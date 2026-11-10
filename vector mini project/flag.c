// Include the user-defined data types
#include "types.h"

// Global flag to indicate RTC editing mode
volatile u8 edit_flag = 0;

// Global flag to indicate emergency condition
volatile u8 emergency_flag = 0;

// Function to set the RTC edit flag
void RTC_EDIT(void)
{
    edit_flag = 1;  // Enable RTC editing mode
}

// Function to set the emergency flag
void EMERGENCY(void)
{
    emergency_flag = 1;  // Indicate emergency condition
}