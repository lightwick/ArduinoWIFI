#include <SPI.h>
#include <WiFiS3.h>

const char* ssid = "YJ";
const char* password = "01090784811";
const char* server = "192.168.0.104";
const int portNumber = 8000;

int lastButtonState = HIGH; // Variable for the last button state
const int buttonPin = 2; // Pin where the button is connected

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor

  // Connect to WiFi
  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);

  // Check if the button state has changed
  if (currentButtonState != lastButtonState) {
    sendButtonState(currentButtonState == LOW ? 1 : 0); // Send 1 if pressed, 0 if released
    lastButtonState = currentButtonState; // Update the last button state
  }

  delay(500); // Adjust the delay as needed
}

void sendButtonState(int state) {
  WiFiClient client;

  if (client.connect(server, portNumber)) {
    Serial.println("Connected to server");

    // Make a HTTP POST request
    client.println("POST /arduino/receive/ HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Content-Type: application/x-www-form-urlencoded");
    String postData = "state=" + String(state);
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.print(postData);

    // Check response
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }
}