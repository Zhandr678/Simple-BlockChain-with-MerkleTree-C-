#include "timeParser.h"

std::string parse_timestamp(std::time_t t)
{
	struct tm* local = std::localtime(&t);
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
	std::string timestamp = buffer;
	return timestamp;
}