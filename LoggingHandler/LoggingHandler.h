
#ifndef LOGGINGHANDLER_H
#define LOGGINGHANDLER_H

#include <fstream>
#include <iostream>
#include <ctime>

#define LOG(type) LoggingHandler(type)

#define ERROR LoggingHandler::LOG_TYPE::Error
#define WARNING LoggingHandler::LOG_TYPE::Warning
#define MESSAGE LoggingHandler::LOG_TYPE::Message

class LoggingHandler
{
public:
	enum LOG_TYPE
	{
		Message = 0,
		Warning,
		Error
	};

	LoggingHandler(LOG_TYPE type);
	~LoggingHandler();

	void logError(const char *message);
	void logMessage(const char *message);
	void logWarning(const char *message);

	// operator << for *char
	template <typename T>
	typename std::enable_if<!std::is_fundamental<T>::value, LoggingHandler&>::type
		operator<<(T msg) {
		this->current_message.append((msg));
		return *this;
	}
	// operator << for int, float, double...
	template <typename T>
	typename std::enable_if<std::is_fundamental<T>::value, LoggingHandler&>::type
		operator<<(T msg) {
		this->current_message.append(std::to_string(msg));
		return *this;
	}

private:

	LOG_TYPE current_log;
	std::string current_message;

	// Save the message log in the file
	void toFile(const char *message, const char *log_type);
};
#endif // LOGGINGHANDLER_H
