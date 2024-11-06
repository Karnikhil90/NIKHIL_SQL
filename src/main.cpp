#include <Arduino.h>
#include <vector>

class SQL {
public:
    // Method to handle SQL command input (non-const to allow modification)
    void cmd(std::vector<String>& command) {
        Serial.printf("Command received...\n");
        // Iterate through command vector and print each part
        for (const auto& part : command) {
            Serial.println(part);  // Replace with actual command handling logic
        }
        command.clear();  
    }
};

SQL sql;

// Task handle for the secondary core task
TaskHandle_t CommandTask;

// Function that will run on the secondary core
void runCommandTask(void *parameter) {
    while (true) {
        // Example SQL command to be run every 2 seconds
        std::vector<String> exampleCommand = {"CREATE", "DATABASE", "test_db"};
        sql.cmd(exampleCommand);

        // Delay for 2 seconds
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);  // Start Serial for debugging

    // Create a task on Core 1 (secondary core) to run the SQL commands
    xTaskCreatePinnedToCore(
        runCommandTask,    // Task function
        "SQL Command Task", // Name of the task
        10000,             // Stack size (in bytes)
        NULL,              // Parameter for the task
        1,                 // Priority of the task
        &CommandTask,      // Task handle
        1                  // Core ID (1 for secondary core)
    );
}

void RAM() {
    Serial.println("Free Heap: " + String(ESP.getFreeHeap()) + " bytes");
}

void loop() {
    // Main core (Core 0) handles the RAM monitoring
    RAM();
    delay(1000);  // Delay as needed for main loop
}
