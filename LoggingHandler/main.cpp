#include "LoggingHandler.h"

int main(int argc, char **argv) {

	LOG(MESSAGE) << "TEST" << 123 << "test";
	LOG(WARNING) << "TEST" << 123 << "test";
	LOG(ERROR) << "TEST" << 123 << "test";

	system("pause");
	exit(0);
}

