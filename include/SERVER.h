#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <vector>
#include <ESP8266WiFi.h>   // Use this for WiFi on ESP8266

class Server {
public:
    Server(uint16_t port = 3306);      // Constructor with default port
    void begin();                      // Initialize and start the server
    std::vector<String> getCommand();  // Parse command from incoming requests
    void handleClient();               // Main loop for handling client requests

private:
    WiFiServer apiServer;              // Server instance
    std::vector<String> parseCommand(const String& query); // Helper to parse command
};

#endif // SERVER_H
