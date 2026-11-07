/************************************************************************/
/* File Name   : rtc_defines.h                                          */
/* Description : Contains the clock configuration values, RTC prescaler */
/*               calculations and RTC control register bit definitions. */
/* Controller  : LPC2129 / LPC2148                                      */
/************************************************************************/

/* Oscillator and processor clock configuration */
#define FOSC 12000000
#define CCLK (FOSC*5)    
#define PCLK (CCLK/4)

/* RTC prescaler values for generating a 32.768 kHz clock */
#define PREINT_VAL  ((int) ((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768))

/* RTC control register bit definitions */
#define RTC_ENABLE (1<<0)
#define RTC_RESET  (1<<1)
#define RTC_CLKSRC (1<<4) 
