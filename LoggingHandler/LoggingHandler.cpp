#include "LoggingHandler.h"

LoggingHandler::LoggingHandler(LOG_TYPE type) {
	this->current_log = type;
}

LoggingHandler::~LoggingHandler() {
	switch (current_log)
	{
	case LoggingHandler::Message:
		this->logMessage(this->current_message.c_str());
		break;
	case LoggingHandler::Warning:
		this->logWarning(this->current_message.c_str());
		break;
	case LoggingHandler::Error:
		this->logError(this->current_message.c_str());
		break;
	}
}

void LoggingHandler::logError(const char *message)
{
	this->toFile(message, "ERROR");
	throw;
	//exit(-1);
}
#if (Debug)
void LoggingHandler::logMessage(const char *message)
{
	this->toFile(message, "MESSAGE");
}
void LoggingHandler::logWarning(const char *message)
{
	this->toFile(message, "WARNING");
}
#else
void LoggingHandler::logMessage(const char *message) {}
void LoggingHandler::logWarning(const char *message) {}
#endif

// Save the message log in the file
void LoggingHandler::toFile(const char *message, const char *log_type)
{
	static std::string last_log = "";
	if (message == last_log) {
		return;
	}
	last_log = message;
	try
	{
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%T", &tstruct);
		printf(buf);
		printf(">>");
		printf(log_type);
		printf("::");
		printf(message);
		printf("\n");
		std::ofstream logs("logs.txt", std::ios::app);
		if (logs.is_open())
		{
			logs << buf;
			logs << ">>";
			logs << log_type << "::";
			logs << message;
			logs << "\n";
			logs.close();
		}
		else
		{
			printf("Failed save the log. ");
			printf(log_type);
			printf("\n");
		}
	}
	catch (...)
	{
		printf("Failed to save the file.");
	}
}
