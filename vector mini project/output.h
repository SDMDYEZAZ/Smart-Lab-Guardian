// Header file for LED and Buzzer control

#ifndef OUTPUT_H
#define OUTPUT_H

/* Hardware connections:
   LED    -> P0.10 (through 330R resistor to LED and then GND)
   BUZZER -> P0.11 (Active HIGH)
*/

// Define LED and Buzzer pin numbers
#define LED_PIN      15
#define BUZZER_PIN   20

// Function prototypes for output initialization and control

// Initialize LED and Buzzer GPIO pins
void INIT_OUT(void);

// Turn ON the LED
void LED_ON(void);

// Turn OFF the LED
void LED_OFF(void);

// Turn ON the Buzzer
void BUZZER_ON(void);

// Turn OFF the Buzzer
void BUZZER_OFF(void);

// Generate a beep for the specified duration in milliseconds
void BEEP(unsigned int ms);

#endif  // End of OUTPUT_H
