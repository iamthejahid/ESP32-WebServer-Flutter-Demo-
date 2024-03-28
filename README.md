# ESP32 Web Server with Morse Code Flashing

This repository contains an Arduino sketch for setting up an ESP32-based web server capable of serving HTTP requests and flashing an LED in Morse code. Additionally, it includes a Flutter application for interacting with the web server, fetching data, and sending Morse code messages.

## ESP32 Web Server

### Features

- **Web Server**: Utilizes the ESP32's capabilities to create a simple HTTP server.
- **JSON Response**: Provides a JSON response endpoint for retrieving predefined messages.
- **Morse Code Flashing**: Parses custom messages and flashes an LED in Morse code accordingly.
- **Easy Integration**: Straightforward setup and usage, suitable for beginners and experienced developers alike.

### Getting Started

1. **Clone the Repository**: Clone this repository to your local machine.
2. **Install Libraries**: Ensure you have the required libraries installed. The necessary libraries are `WiFi`, `WebServer`, and `ArduinoJson`.
3. **Configure WiFi**: Replace `"your-ssid"` and `"your-password"` with your WiFi credentials in the `ssid` and `password` variables.
4. **Hardware Setup**: Connect an LED to pin 2 (or modify `ledPin` if using a different pin) of your ESP32 board.
5. **Upload the Sketch**: Upload the provided sketch (`esp32_web_server.ino`) to your ESP32 board using the Arduino IDE or platform of your choice.

### Usage

- Access the `/data` endpoint in your browser or through a tool like cURL to receive a predefined JSON message and see the LED flash.
- Send a POST request to the `/morse` endpoint with a `message` parameter containing the text you want to convert to Morse code. The ESP32 will flash the LED accordingly and respond with a confirmation message.

## Flutter Application

The repository also includes a Flutter application (`flutter_demo_for_using_esp_server`) for interacting with the ESP32 web server.

### Features

- **Fetch Data**: Fetches predefined data from the ESP32 web server.
- **Send Morse Request**: Sends custom messages to the ESP32 web server to be flashed in Morse code.
- **Visual Feedback**: Displays response messages and loading indicators for user feedback.

### Usage

1. Update the IP Address: Obtain the IP address of your ESP32 and update the URL in the Flutter application (`lib/main.dart`) with the correct IP address.
2. Run the Application: Run the Flutter application on your mobile device or emulator.
3. Fetch Data: Press the "Fetch Data" button to fetch predefined data from the ESP32 web server.
4. Send Morse Request: Press the "Send Morse Request" button to send a custom message to be flashed in Morse code by the ESP32.

## Resources

- [Medium Article](https://iamthejahid.medium.com/building-a-web-server-with-esp32-and-fetching-sending-data-in-flutter-9526bf87ea63): Read the detailed tutorial on building the ESP32 web server and integrating it with Flutter.
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_http_server.html): Explore the ESP32 documentation for more information on the HTTP server capabilities.

## Contributions

Contributions to this project are welcome! Feel free to fork this repository, make changes, and submit a pull request. If you encounter any issues or have suggestions for improvements, please open an issue.

