#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "your-ssid";
const char* password = "your-password";

const int ledPin = 2;

WebServer server(80);

void flashLED(int times = 1);
void handleData();
void handleMorse();

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  flashLED(2);

  pinMode(ledPin, OUTPUT);

  server.on("/data", HTTP_GET, handleData);
  server.on("/morse", HTTP_POST, handleMorse);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleData() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["message"] = "Hello from ESP32";
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  server.sendHeader("Content-Type", "application/json");
  server.send(200, "application/json", jsonString);
  flashLED();
}

void handleMorse() {
  String message = server.arg("message");
  Serial.println("Received message: " + message);
  
  for (int i = 0; i < message.length(); i++) {
    char c = tolower(message.charAt(i));
    if (c == ' ') {
      delay(3000); // Gap between words
    } else {
      flashCharacter(c);
      delay(1000); // Gap between letters
    }
  }
  server.send(200, "text/plain", "LED flashed in Morse code");
}

void flashCharacter(char c) {
  switch (c) {
    case 'a': flashMorse(".-"); break;
    case 'b': flashMorse("-..."); break;
    case 'c': flashMorse("-.-."); break;
    case 'd': flashMorse("-.."); break;
    case 'e': flashMorse("."); break;
    case 'f': flashMorse("..-."); break;
    case 'g': flashMorse("--."); break;
    case 'h': flashMorse("...."); break;
    case 'i': flashMorse(".."); break;
    case 'j': flashMorse(".---"); break;
    case 'k': flashMorse("-.-"); break;
    case 'l': flashMorse(".-.."); break;
    case 'm': flashMorse("--"); break;
    case 'n': flashMorse("-."); break;
    case 'o': flashMorse("---"); break;
    case 'p': flashMorse(".--."); break;
    case 'q': flashMorse("--.-"); break;
    case 'r': flashMorse(".-."); break;
    case 's': flashMorse("..."); break;
    case 't': flashMorse("-"); break;
    case 'u': flashMorse("..-"); break;
    case 'v': flashMorse("...-"); break;
    case 'w': flashMorse(".--"); break;
    case 'x': flashMorse("-..-"); break;
    case 'y': flashMorse("-.--"); break;
    case 'z': flashMorse("--.."); break;
    default: break; // For unsupported characters, do nothing
  }
}


void flashMorse(String morseCode) {
  for (int i = 0; i < morseCode.length(); i++) {
    if (morseCode.charAt(i) == '.') {
      digitalWrite(ledPin, HIGH);
      delay(250); // Dot duration
    } else if (morseCode.charAt(i) == '-') {
      digitalWrite(ledPin, HIGH);
      delay(750); // Dash duration
    }
    digitalWrite(ledPin, LOW);
    delay(250); // Inter-element gap
  }
}

void flashLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}