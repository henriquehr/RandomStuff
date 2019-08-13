#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

// Log types
#define ERROR        "ERROR" // Error, for RELEASE and DEBUG builds, will quit after the message
#define WARNING      "WARNING" // Warning, for RELEASE and DEBUG builds
#define MESSAGE      "MESSAGE" // Message, only for DEBUG build
#define SYSTEM       "SYSTEM" // System information, fps, cpu, ram usage etc
#define ONLY_PRINT   "PRINT" // Message always printed on console, not saved to file, only for DEBUG build
#define PRINT        "PRINT" // Message always printed on console, not saved to file, only for DEBUG build

// TODO Fix this?
#if (DEBUG)
    // DEBUG will log everything
    #define LOG(t) Logging(t, __FUNCTION__, __FILE__, __LINE__)
    #define LOG_NO_INFO(t) Logging(t)
#else
    // RELEASE will log only WARNING and ERROR
    #define LOG(t) if(t==ERROR || t==WARNING)Logging(t, __FUNCTION__, __FILE__, __LINE__)
    #define LOG_NO_INFO(t) if(t==ERROR || t==WARNING)Logging(t)

#endif

class Logging {
private:
    const char *file_name = "logs.txt";
    std::ostringstream current_message; // Log message
    const char *current_type; // type of the log
    const bool add_info; // print or hide line number, file, function name
    const char *current_function; // function name
    const char *current_file; // file name
    const int current_line; // line number

public:
    Logging(const char *t, const char *function, const char *file, const int line);
    Logging(const char *t);
    ~Logging();

    template <typename T>
    inline Logging& operator<<(const T &msg) {
        this->current_message << msg;
        return *this;
    }

private:
    // if the message is repeated quit to avoid spam
    bool checkRepeated();
    // Format the message and add date info
    std::string formatMessage();
    // Print the message log in the console
    void toConsole(std::string msg);
    // Save the message log in the file
    void toFile(std::string msg);
};
#endif // !LOGGING_H