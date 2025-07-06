# 🌊 Flood Detection IoT System

An IoT-based flood detection system built using ESP32, ultrasonic sensors, and flow sensors. It measures real-time water level and flow rate, sending alerts via email if values exceed the threshold.

## 📌 Features

- Monitors water level using ultrasonic sensor
- Measures water flow rate with turbine sensor
- Sends automatic email alerts using SMTP (Gmail)
- Works with ESP32 microcontroller over Wi-Fi

## 📦 Components Used

- ESP32 Microcontroller
- HC-SR04 Ultrasonic Sensor
- Water Flow Sensor
- SMTP Protocol (via WiFi)
- ESP Mail Client Library

## 📂 Folder Structure

- `code/`: Contains the complete Arduino `.ino` file
- `docs/`: Project documentation (Abstract, Methodology, Results)
- `assets/`: Images (e.g., block diagram)

## 🚀 Getting Started

1. Install **ESP Mail Client** library.
2. Add your Wi-Fi credentials and Gmail SMTP settings.
3. Upload the code to your ESP32 using Arduino IDE.
4. View water level and flow alerts in your email.

## ⚠️ Important

Make sure to use an **App Password** for your Gmail SMTP email (2FA required).


