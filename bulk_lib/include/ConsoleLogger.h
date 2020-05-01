#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H
#include "IObserver.h"

struct ConsoleLogger : public IObserver
{
	virtual void Update(std::string param, timepoint time) override {
		std::cout << param << std::endl;
	}
};

#endif //CONSOLE_LOGGER_H
