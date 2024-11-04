#include <ESP8266mDNS.h>        // Include the mDNS library
#include <ESP8266WiFi.h>

// Set pin definitions for the WEMOS D1 Mini
#define PIN_BATTERY_LEVEL A0
#define PIN_INTERNAL_LED 2
#define PIN_HAPTIC_LEFT D1
#define PIN_HAPTIC_RIGHT D2

// ADC Configuration
#define ADCResolution 1023.0
#define ADCVoltageMax 1.0

// Server Configuration
#if defined(PORT)
static WiFiServer server(PORT);
#else
#error "Missing -DPORT option in platformio.ini"
#endif

// Haptic Feedback Configuration
#if defined(USE_PNP)
#define HAPTIC_ON LOW
#define HAPTIC_OFF HIGH
#else
#define HAPTIC_ON HIGH
#define HAPTIC_OFF LOW
#endif

// Battery Shield Configuration
#define BATTERY_SHIELD_R1 100.0
#define BATTERY_SHIELD_R2 220.0
#define BATTERY_SHIELD_RESISTANCE 180.0
#define ADCMultiplier ((BATTERY_SHIELD_R1 + BATTERY_SHIELD_R2 + BATTERY_SHIELD_RESISTANCE) / BATTERY_SHIELD_R1)

// Function to get battery level
float getBatteryLevel() {
  float voltage = (analogRead(PIN_BATTERY_LEVEL) * ADCVoltageMax / ADCResolution) * ADCMultiplier;
  float level = 0.0f;

  // Estimate battery level based on voltage ranges
  if (voltage > 3.975f) {
      level = (voltage - 2.920f) * 0.8f;
  } else if (voltage > 3.678f) {
      level = (voltage - 3.300f) * 1.25f;
  } else if (voltage > 3.489f) {
      level = (voltage - 3.400f) * 1.7f;
  } else if (voltage > 3.360f) {
      level = (voltage - 3.300f) * 0.8f;
  } else {
      level = (voltage - 3.200f) * 0.3f;
  }

  // Cut off the last 5% (3.36V) and clamp level between 0 and 1
  level = max(min((level - 0.05f) / 0.95f, 1.0f), 0.0f);
  return level;
}

// Setup function
void setup() {
  // Initialize pins
  pinMode(PIN_INTERNAL_LED, OUTPUT);
  pinMode(PIN_HAPTIC_LEFT, OUTPUT);
  pinMode(PIN_HAPTIC_RIGHT, OUTPUT);
  pinMode(PIN_BATTERY_LEVEL, INPUT);

  // Set initial state of haptic feedback
  digitalWrite(PIN_HAPTIC_LEFT, HAPTIC_OFF);
  digitalWrite(PIN_HAPTIC_RIGHT, HAPTIC_OFF);

  // Initialize serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  #if defined(WIFI_CREDS_SSID) && defined(WIFI_CREDS_PASSWD)
    WiFi.begin(WIFI_CREDS_SSID, WIFI_CREDS_PASSWD); // Connect to Wi-Fi
  #else
    #error "Missing -DWIFI_CREDS_SSID and -DWIFI_CREDS_PASSWD options in platformio.ini"
  #endif

  // Wait for Wi-Fi connection
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(100);
    digitalWrite(PIN_INTERNAL_LED, LOW);
    Serial.print(".");
    delay(100);
    digitalWrite(PIN_INTERNAL_LED, HIGH);
  }

  // Print IP address and start server
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();

  // Start the mDNS responder for patstrap.local
  if (!MDNS.begin("patstrap")) {
    Serial.println("Error setting up mDNS responder!");
  }
  MDNS.addService("http", "tcp", 80);
  Serial.println("mDNS responder started");

  // Feedback to indicate successful setup
  digitalWrite(PIN_HAPTIC_LEFT, HAPTIC_ON);
  digitalWrite(PIN_HAPTIC_RIGHT, HAPTIC_ON);
  delay(500);
  digitalWrite(PIN_HAPTIC_LEFT, HAPTIC_OFF);
  digitalWrite(PIN_HAPTIC_RIGHT, HAPTIC_OFF);
}

// Main loop
void loop() {
  MDNS.update();

  // Blink internal LED as a heartbeat
  digitalWrite(PIN_INTERNAL_LED, HIGH);
  delay(500);
  digitalWrite(PIN_INTERNAL_LED, LOW);
  delay(500);

  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Client Connected");

    unsigned long previousMillis = millis();

    while (client.connected()) {
      unsigned long currentMillis = millis();

      // Process received bytes
      while (client.available() > 0) {
        char data = client.read();
        unsigned int haptic_right_level = (data & 0x0F) << 4;
        unsigned int haptic_left_level = data & 0xF0;

        // Complete the haptic level to full range
        haptic_right_level |= haptic_right_level >> 4;
        haptic_left_level |= haptic_left_level >> 4;

        // Generate PWM signal for haptic feedback
        analogWrite(PIN_HAPTIC_LEFT, HAPTIC_OFF ? haptic_left_level : 0xFF - haptic_left_level);
        analogWrite(PIN_HAPTIC_RIGHT, HAPTIC_OFF ? haptic_right_level : 0xFF - haptic_right_level);
      }

      // Send keep-alive packet with averaged battery value
      if (currentMillis - previousMillis >= 1000) {
        // Send keep_alive package every second
        #if defined(USE_BATTERY)
        client.print((char)round(max(min(getBatteryLevel() * 100.0f, 100.0f), 0.0f)));
        #else
        client.print((char)255);  // Indicate no battery information
        #endif

        previousMillis = currentMillis;
        client.flush();
      }
    }

    client.stop();
    Serial.println("Client disconnected");    
  }
}
