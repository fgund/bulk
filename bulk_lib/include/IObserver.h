#ifndef IOBSERVER_H
#define IOBSERVER_H
#include <string>

struct IObserver
{
	virtual void Update(std::string param) = 0;
};


#endif //IOBSERVER_H
