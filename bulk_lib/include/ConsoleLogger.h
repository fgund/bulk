#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H
#include "IObserver.h"

struct ConsoleLogger : public IObserver<std::string>
{
	virtual void Update(std::string param) override {
		std::cout << param << std::endl;
	}
};

#endif //CONSOLE_LOGGER_H
