#ifndef SQL_H
#define SQL_H

#include <Arduino.h>
#include <vector>

class SQL {
public:
    // Constructor
    SQL();

    // Destructor
    ~SQL();

    // Method to handle SQL command input
    void cmd(std::vector<String>& command);

private:
    // Any private members or helper methods can be added here
};

#endif // SQL_H
