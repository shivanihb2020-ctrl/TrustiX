# TrustiX
Smart tampering detection using ESP32 + Blynk IoT

Problem statement
Smart Tampering Detection System for Weighing Instruments

📖 Description
This project detects tampering in weighing instruments using vibration sensor and limit switch. It sends real-time alerts using ESP32 and Blynk IoT.

⚙️ Components Used
ESP32
HX711 Load Cell
Vibration Sensor
Limit Switch (NC/NO)
Buzzer
LED
LCD Display (I2C)

🧠 Working Principle
Monitors weight and physical disturbance
Detects tampering using vibration + switch logic
Sends real-time alert via Blynk IoT
Displays status on LCD

📡 Features
Real-time monitoring
Mobile notification alerts
LCD display status
Audio + visual alarm
IoT cloud integration

🖼️ Project Images
![Circuit Diagram](circuit.jpg)
![Prototype Setup](prototype.jpg)
![Blynk Alert](alert.jpg)

 ⚙️ Working Explanation
1. System continuously monitors vibration sensor and limit switch  
2. Load cell measures weight using HX711 module  
3. If tampering is detected (vibration or switch trigger)  
4. ESP32 activates buzzer and LED alert  
5. Blynk IoT sends real-time notification to mobile  
6. LCD displays system status (Normal / Tamper Alert)

📡 Blynk IoT Configuration
- Template ID: TMPL3xp3BajCU  
- Event Name: tamper_alert  
- Datastream: V0 (Weight)  
- Notification Type: Push Alert

  🌍 Real-World Applications
- Prevents weighing scale fraud in shops  
- Useful in warehouses and logistics  
- Ensures fair trade in markets  
- Can be used in industrial safety systems

  🏁 Conclusion
This system provides a low-cost IoT-based solution for detecting tampering in weighing instruments with real-time alerts and monitoring.
