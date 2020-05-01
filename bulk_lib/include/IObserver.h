#ifndef IOBSERVER_H
#define IOBSERVER_H
#include <string>
#include <chrono>

struct IObserver
{
	using timepoint = std::chrono::system_clock::time_point;
    IObserver() = default;
	virtual void Update(std::string param, timepoint time) = 0;
};


#endif //IOBSERVER_H
