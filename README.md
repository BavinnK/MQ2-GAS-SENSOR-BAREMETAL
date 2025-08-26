# 🚨 MQ-2 Gas Sensor Alarm System (AVR Bare-Metal)


A bare-metal AVR project that uses an **MQ-2 gas sensor** to detect dangerous gas levels.  
When the threshold is reached, the system **activates an LED and a buzzer** while also sending status updates over **UART**.  

---

## ✨ Features
- 📡 Reads analog values from MQ-2 gas sensor via **ADC**  
- 🔔 Activates **buzzer + LED** when threshold exceeded  
- 🖥️ Sends real-time messages over **UART (9600 baud)**  
- ⚡ Written in **pure C (no Arduino libraries)**  

---

## 🛠 Hardware
- **ATmega328P** (Arduino Uno/Nano in bare-metal mode)  
- **MQ-2 Gas Sensor**  
- **LED** + current-limiting resistor  
- **Buzzer**  
- Breadboard + jumper wires  

---

## ⚙️ How It Works
1. The **ADC** reads the analog output of the MQ-2 sensor.  
2. If the gas value > **threshold** (`100` in this code):  
   - LED and buzzer turn **ON**  
   - `"hazardous gas detected!"` is sent via UART  
3. Otherwise:  
   - LED and buzzer turn **OFF**  
   - `"everything is fine"` is sent via UART  

---

## 📡 Serial Communication
- **Baud rate:** `9600`  
- Compatible with Arduino Serial Monitor, PuTTY, or any UART terminal.  

