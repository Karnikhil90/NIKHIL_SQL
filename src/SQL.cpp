#include "SQL.h"

void SQL::cmd(std::vector<String>& command) {
    Serial.println("Command received...");
    // Iterate through command vector and print each part
    for (const auto& part : command) {
        Serial.println(part);  // Replace with actual command handling logic
    }
    command.clear();  
}
