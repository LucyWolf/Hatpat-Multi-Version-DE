// Board-specific configurations
#include <WiFi.h>
#include <ESPmDNS.h>

// Set pin definitions for the XIAO ESP32C3
#define PIN_BATTERY_LEVEL 2 // D0 / A0
#define PIN_HAPTIC_LEFT D1  // Set to D1
#define PIN_HAPTIC_RIGHT D2 // Set to D2
#define PIN_INTERNAL_LED 9 // Set D9 as internal LED pin

// ADC settings for ESP32
#define ADCResolution 4096.0 // 12-bit resolution for ESP32
#define ADCVoltageMax 3.3

// Haptic motor control logic
#if defined(USE_PNP)
#define HAPTIC_ON LOW
#define HAPTIC_OFF HIGH
#else
#define HAPTIC_ON HIGH
#define HAPTIC_OFF LOW
#endif

// Server setup
static WiFiServer server(PORT);

// Battery measurement configuration
#define BATTERY_SHIELD_R1 180.0  // 180 kΩ
#define BATTERY_SHIELD_R2 180.0  // 180 kΩ
#define ADCMultiplier (BATTERY_SHIELD_R1 + BATTERY_SHIELD_R2) / BATTERY_SHIELD_R1 // Multiplier is 2

// Function to get battery voltage
float getBatteryVoltage() {
    uint32_t Vbatt = 0;
    for(int i = 0; i < 16; i++) {
        Vbatt += analogRead(PIN_BATTERY_LEVEL); // ADC reading
    }
    float Vbattf = Vbatt / 16 / 1000.0; // Average and convert to volts
    return Vbattf * ADCMultiplier; // Multiply by ADC multiplier
}

// Function to calculate battery level
float getBatteryLevel() {
    float voltage = ((float)analogRead(PIN_BATTERY_LEVEL)) * ADCVoltageMax / ADCResolution * ADCMultiplier;
    float level = 0.0f;

    if (voltage > 3.975f)
        level = (voltage - 2.920f) * 0.8f;
    else if (voltage > 3.678f)
        level = (voltage - 3.300f) * 1.25f;
    else if (voltage > 3.489f)
        level = (voltage - 3.400f) * 1.7f;
    else if (voltage > 3.360f)
        level = (voltage - 3.300f) * 0.8f;
    else
        level = (voltage - 3.200f) * 0.3f;

    level = (level - 0.05f) / 0.95f;
    level = max(min(level, 1.0f), 0.0f);

    return level;
}

// Function to test the motors
void testMotors() {
    Serial.println("Testing both motors...");
    ledcWrite(0, 255);  // Full power to left motor
    ledcWrite(1, 255);  // Full power to right motor
    delay(1000);        // 1 second
    ledcWrite(0, 0);    // Turn off left motor
    ledcWrite(1, 0);    // Turn off right motor
    Serial.println("Motor test complete.");
}

// Setup function
void setup() {
    pinMode(PIN_INTERNAL_LED, OUTPUT);
    digitalWrite(PIN_INTERNAL_LED, LOW);

    pinMode(PIN_HAPTIC_LEFT, OUTPUT);
    pinMode(PIN_HAPTIC_RIGHT, OUTPUT);
    pinMode(PIN_BATTERY_LEVEL, INPUT);

    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_CREDS_SSID, WIFI_CREDS_PASSWD);

    Serial.println("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        digitalWrite(PIN_INTERNAL_LED, !digitalRead(PIN_INTERNAL_LED));
    }

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();

    if (!MDNS.begin("patstrap")) {
        Serial.println("Error setting up MDNS responder!");
    }
    MDNS.addService("http", "tcp", 80);
    Serial.println("mDNS responder started");

    // Setup PWM for motor control
    ledcSetup(0, 5000, 8);
    ledcAttachPin(PIN_HAPTIC_LEFT, 0);
    ledcSetup(1, 5000, 8);
    ledcAttachPin(PIN_HAPTIC_RIGHT, 1);

    testMotors();
}

// Main loop
void loop() {
    delay(500);
    digitalWrite(PIN_INTERNAL_LED, HIGH);
    delay(500);
    digitalWrite(PIN_INTERNAL_LED, LOW);

    // Battery Level Reporting
    Serial.print("Battery Voltage: ");
    Serial.print(getBatteryVoltage());
    Serial.print(" V, Battery Level: ");
    Serial.print(getBatteryLevel() * 100);
    Serial.println(" %");

    WiFiClient client = server.available();
    if (client) {
        Serial.println("Client Connected");
        unsigned long previousMillis = millis();

        while (client.connected()) {
            while (client.available() > 0) {
                char data = client.read();
                unsigned int haptic_right_level = (data & 0x0F) << 4;
                unsigned int haptic_left_level = data & 0xF0;

                Serial.print("Haptic Left Level: ");
                Serial.println(haptic_left_level);
                Serial.print("Haptic Right Level: ");
                Serial.println(haptic_right_level);

                haptic_right_level |= haptic_right_level >> 4;
                haptic_left_level |= haptic_left_level >> 4;

                analogWrite(PIN_HAPTIC_LEFT, HAPTIC_OFF ? haptic_left_level : 0xFF - haptic_left_level);
                analogWrite(PIN_HAPTIC_RIGHT, HAPTIC_OFF ? haptic_right_level : 0xFF - haptic_right_level);
            }

            if (millis() - previousMillis >= 1000) {
                client.print((char)round(max(min(getBatteryLevel() * 100.0f, 100.0f), 0.0f)));
                previousMillis = millis();
                client.flush();
            }
        }

        client.stop();
        Serial.println("Client disconnected");
    }
}
