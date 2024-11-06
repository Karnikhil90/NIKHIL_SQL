#include "SERVER.h"

// Constructor initializes WiFiServer on the specified port
Server::Server(uint16_t port) : apiServer(port) {}

// Start the WiFiServer
void Server::begin() {
    apiServer.begin();
    Serial.println("Server started on port 3306");
}

// Handle client connections and parse commands
void Server::handleClient() {
    WiFiClient client = apiServer.available();  // Listen for incoming clients

    if (client) {
        Serial.println("New client connected");

        // Wait until the client sends some data
        while (client.connected() && !client.available()) {
            delay(10);
        }

        // Read the request
        String request = client.readStringUntil('\r');
        Serial.print("Request: ");
        Serial.println(request);

        // Check if this is a GET request with a command
        if (request.startsWith("GET ")) {
            int cmdIndex = request.indexOf("cmd=");
            if (cmdIndex != -1) {
                // Parse the command query
                String query = request.substring(cmdIndex + 4);  // Start after "cmd="
                query.trim();

                // Parse the command into a vector of strings
                std::vector<String> command = parseCommand(query);

                // Process command (for example, print each part)
                Serial.println("Parsed command:");
                for (const auto& part : command) {
                    Serial.println(part);
                }

                // Send response to client
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/plain");
                client.println();
                client.println("Command received and processed.");
            } else {
                client.println("HTTP/1.1 400 Bad Request");
                client.println("Content-Type: text/plain");
                client.println();
                client.println("No command found in the request.");
            }
        }

        // Close the connection
        client.stop();
        Serial.println("Client disconnected");
    }
}

// Parse the command query into a vector of strings
std::vector<String> Server::parseCommand(const String& query) {
    std::vector<String> command;
    int start = 0;
    int end = query.indexOf('%');  // Parse based on '%'

    while (end != -1) {
        command.push_back(query.substring(start, end));
        start = end + 1;
        end = query.indexOf('%', start);
    }

    // Add the last part if exists
    if (start < query.length()) {
        command.push_back(query.substring(start));
    }

    return command;
}
