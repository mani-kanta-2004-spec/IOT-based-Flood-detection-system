## Methodology

### System Components

- **Ultrasonic Sensor**: Measures water height
- **Water Flow Sensor**: Monitors flow rate
- **ESP32 Microcontroller**: Processes data and sends alerts
- **SMTP**: Protocol used for sending alert emails



### How It Works

- ESP32 reads data from ultrasonic & flow sensors
- If thresholds are breached, email alert is sent
- Real-time monitoring ensures fast response in emergencies

### Email Sending (SMTP)

1. Connect to SMTP server (`smtp.gmail.com`)
2. Authenticate using email & app password
3. Compose message with sensor data
4. Send to recipient email via WiFi
