# ESP8266 SQL-Like Database Project

This project is an implementation of a SQL-like database on the ESP8266, allowing basic SQL-style commands to create, manage, and query databases and tables. The data is stored on an SD card, and a WebSocket-based network interface is used to communicate with the database, providing a MySQL-like experience.

## Features

- **Basic SQL Commands**:
  - `SHOW DATABASES` - Lists all available databases.
  - `CREATE DATABASE <name>` - Creates a new database.
  - `USE <database>` - Selects an active database.
  - `CREATE TABLE <table name>(...)` - Creates a new table within the active database.
  - `INSERT INTO <table name>(parameters)` - Inserts values into a specified table.
  - `SELECT`, `WHERE`, `DROP DATABASE`, `DROP TABLE` - Additional manipulation commands.
  
- **Storage**:
  - Data is stored on an SD card, allowing persistent storage similar to MySQL tables.
  - Each database and table is represented as a file on the SD card.

- **Network Communication**:
  - The ESP8266 listens for database commands over a WebSocket interface at `192.168.1.100:3306`.
  - Basic API structure for commands (`/database?cmd=SHOW DATABASES`, `/database?cmd=CREATE DATABASE <name>`).
  - **Note**: Initial version has no login functionality.

## Project Structure

- `src/Database.h` and `src/Database.cpp`: Core database logic, including SQL command parsing and data handling.
- `src/Server.h` and `src/Server.cpp`: WebSocket server logic to receive and execute commands.
- `data/`: SD card storage simulation folder (for Arduino IDE).
- `README.md`: Project overview and documentation.

## Setup and Installation

1. **Hardware Requirements**:
   - ESP8266 module
   - SD card module for data storage

2. **Software Requirements**:
   - Arduino IDE (for initial setup)
   - WebSocket and SD libraries for ESP8266
   - **Future**: Plan to transition to ESP-IDF or Lua

3. **Wiring**:
   - Connect SD card module to ESP8266 according to your pin configuration.
   - Connect ESP8266 to Wi-Fi.

4. **Flashing the Code**:
   - Clone this repository and open it in Arduino IDE.
   - Set the IP address in the `Server` class (`192.168.1.100:3306` or change as needed).
   - Compile and upload the code to your ESP8266.

## Usage

1. **Connect to the WebSocket**:
   - Open a WebSocket connection to `ws://192.168.1.100:3306`.
   
2. **Send Commands**:
   - Once connected, send basic SQL commands (listed under **Features**).
   - For example:
     - `SHOW DATABASES`
     - `CREATE DATABASE test_db`
     - `USE test_db`
     - `CREATE TABLE users(id INT, name TEXT)`
     - `INSERT INTO users VALUES (1, "Alice")`

3. **View and Manage Data**:
   - Data is saved to the SD card. Check files directly on the SD card for persistence.

## Future Plans

- **Authentication**: Add login functionality with username/password.
- **JSON Support**: Implement MongoDB-like structure using JSON for flexible storage.
- **Additional Commands**: Extend with more SQL commands and query options.

## License

This project is licensed under the MIT License.

