#ifndef TEST_LOGGER_H
#define TEST_LOGGER_H
#include <string>
#include <vector>
#include "IObserver.h"
struct TestLogger : public IObserver
{
    virtual void Update(std::string param, timepoint time) override {
        bulks.emplace_back(param);
    }
    const std::vector<std::string>& GetBulks(){
        return bulks;
    }
private:
    std::vector<std::string> bulks;
};

#endif //TEST_LOGGER_H
