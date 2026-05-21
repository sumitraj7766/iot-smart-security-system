```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

#define PIR_PIN D5
#define IR_PIN D6
#define LED_PIN D1

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Firebase URL
String firebaseURL = "https://iot-security-system-41309-default-rtdb.firebaseio.com/smart_security.json";

// Create Web Server
ESP8266WebServer server(80);

// Status Variables
String motionStatus = "No Motion";
String objectStatus = "Clear";
String ledStatus = "OFF";
String doorStatus = "CLOSED";

// Firebase Timer
unsigned long lastFirebaseUpdate = 0;

// =======================
// WEB DASHBOARD FUNCTION
// =======================
void handleRoot() {

  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='2'>";

  html += "<style>";
  html += "body{font-family:Arial;background:#f4f6f8;text-align:center;}";
  html += "h1{margin-top:30px;}";
  html += ".card{background:white;width:300px;margin:20px auto;padding:20px;border-radius:12px;box-shadow:0 0 10px #ccc;font-size:22px;}";
  html += "</style>";

  html += "</head><body>";

  html += "<h1>IoT Smart Security Dashboard</h1>";

  html += "<div class='card'>Motion: " + motionStatus + "</div>";
  html += "<div class='card'>Object: " + objectStatus + "</div>";
  html += "<div class='card'>LED: " + ledStatus + "</div>";
  html += "<div class='card'>Door: " + doorStatus + "</div>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

// =======================
// FIREBASE FUNCTION
// =======================
void sendToFirebase() {

  if (WiFi.status() == WL_CONNECTED) {

    std::unique_ptr<BearSSL::WiFiClientSecure> client(
      new BearSSL::WiFiClientSecure
    );

    client->setInsecure();

    HTTPClient https;

    https.begin(*client, firebaseURL);

    https.addHeader("Content-Type", "application/json");

    // JSON Data
    String data = "{";

    data += "\"motion\":\"" + motionStatus + "\",";
    data += "\"object\":\"" + objectStatus + "\",";
    data += "\"led\":\"" + ledStatus + "\",";
    data += "\"door\":\"" + doorStatus + "\"";

    data += "}";

    int httpCode = https.PUT(data);

    Serial.print("Firebase Response: ");
    Serial.println(httpCode);

    String response = https.getString();
    Serial.println(response);

    https.end();
  }
}

// =======================
// SETUP
// =======================
void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // WiFi Connect
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  // Print IP Address
  Serial.print("Open Dashboard: http://");
  Serial.println(WiFi.localIP());

  // Start Web Server
  server.on("/", handleRoot);

  server.begin();

  Serial.println("Web Server Started");
}

// =======================
// LOOP
// =======================
void loop() {

  // Handle Web Requests
  server.handleClient();

  // Read Sensors
  int motion = digitalRead(PIR_PIN);
  int objectDetected = digitalRead(IR_PIN);

  // Motion Logic
  if (motion == HIGH) {

    digitalWrite(LED_PIN, HIGH);

    motionStatus = "Motion Detected";
    ledStatus = "ON";
    doorStatus = "OPEN";

  } else {

    digitalWrite(LED_PIN, LOW);

    motionStatus = "No Motion";
    ledStatus = "OFF";
    doorStatus = "CLOSED";
  }

  // IR Sensor Logic
  if (objectDetected == LOW) {

    objectStatus = "Object Detected";

  } else {

    objectStatus = "Clear";
  }

  // Update Firebase Every 2 Seconds
  if (millis() - lastFirebaseUpdate >= 2000) {

    sendToFirebase();

    lastFirebaseUpdate = millis();
  }
}
```
