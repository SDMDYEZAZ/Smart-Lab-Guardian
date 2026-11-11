// Include LPC214x register definitions
#include <LPC214X.H>

// Include delay function declarations
#include "delay.h"

// Include LED and Buzzer pin definitions and function prototypes
#include "output.h"

// Initialize LED and Buzzer GPIO pins
void INIT_OUT(void)
{
     // Configure LED1, LED2 and Buzzer pins as output pins
    IODIR0 |= (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << BUZZER_PIN);

    // Initially turn OFF LED1, LED2 and Buzzer
    IOCLR0 = (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << BUZZER_PIN);
}

// Turn ON the LED
void LED1_ON(void)
{
    IOSET0 = (1 << LED1_PIN);
}

// Turn OFF the LED
void LED1_OFF(void)
{
    IOCLR0 = (1 << LED1_PIN);
}

// Turn ON the LED2 (Device 2)
void LED2_ON(void)
{
    IOSET0 = (1 << LED2_PIN);
}

// Turn OFF the LED2 (Device 2)
void LED2_OFF(void)
{
    IOCLR0 = (1 << LED2_PIN);
}

// Turn ON the Buzzer
void BUZZER_ON(void)
{
    IOSET0 = (1 << BUZZER_PIN);
}

// Turn OFF the Buzzer
void BUZZER_OFF(void)
{
    IOCLR0 = (1 << BUZZER_PIN);
}

// Turn ON the buzzer for the specified time in milliseconds
void BEEP(unsigned int ms)
{
    BUZZER_ON();       // Activate buzzer
    delay_ms(ms);      // Wait for the specified duration
    BUZZER_OFF();      // Deactivate buzzer
}
