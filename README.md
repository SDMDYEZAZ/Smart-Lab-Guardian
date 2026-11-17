# Smart-Lab-Guardian
![My Image](proimages/circuit.png)
## 🔷 System Block Diagram

The Smart Lab Guardian system is designed using the LPC2148 microcontroller as its central processing unit. It receives inputs from multiple devices, processes them, and controls the output devices according to the programmed conditions.

### 🔹 Input Units
- **Keypad:** Used to provide user input and control system operations.
- **Emergency Switch:** Allows the user to trigger an emergency condition.
- **RTC Edit Switch:** Used to enter RTC date and time editing mode.
- **IR Receiver:** Receives signals from an IR remote for wireless control.

### 🔹 Processing Unit
- **LPC2148 Microcontroller:** Acts as the central controller, processes input signals, handles RTC operations, and manages the connected output devices.

### 🔹 Output Units
- **16×2 LCD Display:** Displays system status, date, time, and alert messages.
- **Device 1 (LED1):** Indicates the status of the first controlled device.
- **Device 2 (LED2):** Indicates the status of the second controlled device.
- **Buzzer:** Provides audible alerts during emergency conditions.

### ⚙️ Working Principle
The input devices send signals to the LPC2148 microcontroller. Based on the received inputs and programmed logic, the microcontroller processes the information and controls the LCD, LEDs, and buzzer accordingly. The RTC provides time-related information for system operations.


|===========================================================================================================================|
|===========================================================================================================================|


![Preview](gifimages/rtc.png)

## ⏰ Real-Time Clock (RTC) Module

The RTC module is used to maintain accurate date and time information in the Smart Lab Guardian system. It helps the microcontroller track real-time information and supports time-based system operations.

### 🔹 Features
- Maintains current time, date, month, and year.
- Provides real-time clock information to the microcontroller.
- Supports date and time editing through the RTC Edit Switch.
- Helps display current date and time on the 16×2 LCD.
- Maintains timekeeping independently when supported by a backup battery.

### ⚙️ Working Principle
The RTC module continuously maintains time and date information. The LPC2148 microcontroller reads this information and displays it on the LCD. When the RTC Edit Switch is activated, the system enters RTC editing mode, allowing the user to modify the time and date.

**Interface:** LPC2148 Microcontroller


|==========================================================================================================================|
|==========================================================================================================================|


![Preview](gifimages/irreceiver.png)
