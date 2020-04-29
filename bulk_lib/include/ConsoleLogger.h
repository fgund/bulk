#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H
#include <string>

struct ConsoleLogger : public IObserver
{
	virtual void Update(std::string param)override {
		std::cout << param << std::endl;
	}
};

#endif //CONSOLE_LOGGER_H
