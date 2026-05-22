# Temperature Monitoring and Control System Based on P.I.D. using a Peltier Module

## 📌 Project Overview
This project is a closed-loop thermal management system designed to monitor and regulate temperature in real-time. Utilizing an Arduino microcontroller, the system continuously compares ambient or surface temperature against a user-defined setpoint. When cooling (or heating) is required, the system drives a Peltier thermoelectric module via a MOSFET power distribution circuit. Once the target temperature is reached, the microcontroller signals the MOSFET to cut power, maintaining thermal stability and preventing overshooting.

**🎥 [Link to Hardware Demonstration Video / GIF] : https://youtu.be/-5AKqzHRqF8 

## 🛠️ Hardware Components
*   **Microcontroller:** Arduino (Uno/Nano)
*   **Thermoelectric Cooler:** Peltier Module (e.g., TEC1-12706)
*   **Power Switching:** MOSFET (Used to handle the high current required by the Peltier module)
*   **Sensor:** Temperature Sensor (e.g., DS18B20, LM35, or Thermistor)
*   **Power Supply:** Dedicated high-current DC power supply for the Peltier module

## ⚙️ How It Works (Control Logic)
1.  **Sensing:** The temperature sensor continuously reads the current temperature of the target environment.
2.  **Processing:** The Arduino processes this analog/digital signal and compares the live temperature data to a pre-programmed setpoint.
3.  **Power Distribution:** If the temperature deviates from the target, the Arduino sends a control signal to the MOSFET gate.
4.  **Actuation:** The MOSFET acts as a solid-state switch, allowing high-current power to flow from the power supply to the Peltier module. 
5.  **Regulation:** Once the sensor detects that the target temperature has been reached, the Arduino removes the signal to the MOSFET, instantly shutting off power to the Peltier module.

## 🔀 Circuit Architecture
*   The **Temperature Sensor** is connected to the Arduino's input pins to provide real-time feedback.
*   The **Arduino** isolates the low-voltage control logic from the high-power circuit.
*   The **MOSFET** is placed in series with the Peltier module and the external power supply, controlled by a digital output pin from the Arduino. 

## 💻 Code Structure
The provided C++ (`.ino`) file contains:
*   Sensor initialization and reading functions.
*   The main feedback loop comparing the current temperature to the setpoint.
*   The digital output logic governing the MOSFET state (HIGH/LOW).

## 🚀 Setup and Usage
1.  Clone this repository: `git clone https://github.com/yourusername/temperature-control-phase1.git`
2.  Open the `.ino` file in the Arduino IDE.
3.  Adjust the `targetTemperature` variable in the code to your desired setpoint.
4.  Verify the wiring matches the defined pins in the code.
5.  Upload the code to your Arduino.
6.  Turn on the external power supply for the Peltier module.
7.  Monitor the Serial Output in the Arduino IDE for real-time temperature readings and MOSFET states.

## 👨‍💻 Author
Anant Saxena 
*   www.linkedin.com/in/anant-saxena-14024b314
  
