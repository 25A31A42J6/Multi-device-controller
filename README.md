# ESP8266 Blynk IoT Controller

An IoT project using a NodeMCU/ESP8266 board, Arduino IDE, and Blynk IoT Cloud to control an LED, buzzer, and relay from a Blynk dashboard.

## Features

- Wireless LED control using Blynk Virtual Pin `V0`
- Buzzer control using Virtual Pin `V1`
- Relay control using Virtual Pin `V2`
- Wi-Fi reconnection attempts
- Blynk reconnection attempts

## Hardware

- NodeMCU ESP8266 development board
- LED and suitable current-limiting resistor
- Two-pin active buzzer (if using the tested active-buzzer setup)
- Compatible relay module
- Jumper wires and a suitable power source

## Pin mapping

| Component | NodeMCU pin | ESP8266 GPIO | Blynk virtual pin |
|---|---|---:|---|
| LED | D4 | GPIO2 | V0 |
| Buzzer | D5 | GPIO14 | V1 |
| Relay input | D6 | GPIO12 | V2 |

Check your exact board and module pin labels before wiring. Relay modules differ in trigger polarity and input requirements.

## Setup

1. Install Arduino IDE and the ESP8266 board support package.
2. Install the **Blynk** library using Arduino IDE Library Manager.
3. Copy `secrets.example.h` to a new file named `secrets.h` in the project root.
4. Enter your own Wi-Fi SSID/password and Blynk template/device credentials in `secrets.h`.
5. Open `esp8266-blynk-iot-controller.ino` in Arduino IDE.
6. Select the correct ESP8266 board and serial port, then upload.

**Never commit `secrets.h`.** It is excluded by `.gitignore`. If credentials have ever been exposed, rotate the Blynk device token and change the Wi-Fi password before using them again.

## Safety

Test the relay with a low-voltage DC load while developing. Do not connect household mains electricity unless you are qualified and using proper isolation, enclosure, and protection.

## License

MIT — see `LICENSE`.
