#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H
#include <fstream>
#include "IObserver.h"

struct FileLogger : public IObserver
{
	virtual void Update(std::string param, timepoint time) override {
		std::string filename = "bulk" + std::to_string(time.time_since_epoch().count()) + ".log";
		std::ofstream file(filename);
		if (file.is_open())
		{
			file << param;
			file.close();
		}
	}
};

#endif //FILE_LOGGER_H
