#include <Arduino.h>
#include <vector>
#include <SD.h>
#include <ESP8266WiFi.h>    // WiFi library for ESP8266
#include "SQL.h"             // Include your SQL class
#include "Server.h"          // Include your Server class

SQL sql;
Server server(3306);  // Initialize the server to listen on port 3306

void setup() {
    Serial.begin(9600);  // Start Serial for debugging
    wifi("Airtel_Zeus", "TheBestWifi");
    server.begin();
}

// Function to handle WiFi connection
void wifi(const char* SSID, const char* PASSWORD) {
    WiFi.begin(SSID, PASSWORD);
    int8_t connectingCounter = 0;
    const int8_t maxRetries = 20;  // Maximum retries (20 seconds)

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED && connectingCounter < maxRetries) {
        delay(1000);
        Serial.print(".");
        connectingCounter++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected successfully!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi within 20 seconds.");
    }
}

// Function to print free heap memory for debugging
void RAM() {
    Serial.println("Free Heap: " + String(ESP.getFreeHeap()) + " bytes");
}

void loop() {
    server.handleClient();  // Continuously handle incoming client requests
    RAM();  // Print free RAM every second
    delay(1000);
}
