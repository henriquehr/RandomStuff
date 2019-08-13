#include "Logging.h"

Logging::Logging(const char *t, const char *function, const char *file, const int line)
  : current_message(""), current_type(t), add_info(true), current_function(function), 
  current_file(file), current_line(line) {}

Logging::Logging(const char *t)
  : current_message(""), current_type(t), add_info(false), current_function(""), 
  current_file(""), current_line(-1) {}

Logging::~Logging() {
#if (DEBUG)
    if (this->checkRepeated()) {
        return;
    }
#endif
    std::string msg = this->formatMessage();
#if (DEBUG)
    this->toConsole(msg); // RELEASE have no console
    if (this->current_type == PRINT) { // PRINT should not save to log file
        return;
    }
#endif
    this->toFile(msg);
    if (this->current_type == ERROR) {
        exit(-1); // TODO Handle crash
    }
}

inline bool Logging::checkRepeated() {
    const std::string message = this->current_message.str();
    static std::string last_log = "";
    if (this->current_type == PRINT) { // PRINT should not store the last log message, it should "ONLY PRINT"
        return false;
    }
    if (message == last_log) { // if the message is repeated quit to avoid spam
        return true;
    }
    last_log = message;
    return false;
}

// Format the message and add date info
inline std::string Logging::formatMessage() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::gmtime(&t);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d.%T") 
      << "GMT>>" << this->current_type << "::" << this->current_message.str();

    if (this->add_info) {
        ss << " [" 
          << "FILE:" << this->current_file << ":" << this->current_line
          << " - FUNCTION:" << this->current_function 
          << "]";

    }
    ss << "\n";
    return ss.str();
}

// Print the message log in the console
inline void Logging::toConsole(std::string msg) {
    std::cout << msg;
}

// Save the message log in the file
inline void Logging::toFile(std::string msg) {
    std::ofstream logs(this->file_name, std::ios::app);
    if (logs.is_open()) {
        logs << msg;
        logs.close();
    } else {
        std::cout << "Failed to save the log. " << msg << "\n";
    }
}
