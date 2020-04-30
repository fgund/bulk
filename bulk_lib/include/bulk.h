#ifndef BULK_H
#define BULK_H
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include "IObserver.h"

class Bulk
{
public:
	Bulk(int size) :bulk_size(size) {
	}
	~Bulk() {
		if (!commands.empty() && !has_nested) {
			Notify();
		}
	}
	void AddObserver(std::shared_ptr<IObserver> observer) {
		observers.push_back(observer);
	}
	void RemoveObserver(std::shared_ptr<IObserver> observer) {
        auto iter = std::find(observers.begin(),observers.end(),observer);
	    observers.erase(iter);
	}
	void Notify() {
		auto result = PrepareOutput();
		for (auto& o : observers) {
			o->Update(result);
		}
	}
	void Process(std::string&& cmd) {
		if (cmd == "{") {
			has_nested = true;
			++nested_counter;
		}
		else if (cmd == "}") {
			--nested_counter;
		}
		else {
			commands.emplace_back(std::move(cmd));
		}
		if ((commands.size() == bulk_size) && (!has_nested)) {
			Notify();
			commands.clear();
		}
		else if (has_nested && (nested_counter == 0)) {
			Notify();
			has_nested = false;
			commands.clear();
		}
	}
	std::string PrepareOutput() {
		std::string result{ "bulk: " };
		auto it = commands.begin();
		auto end = commands.end();
		for (; it != end; ++it) {
			if (it != commands.begin()) {
				result.append(", ");
			}
			result.append(*it);
		}
		return std::move(result);
	}
private:
	bool has_nested{ false };
	size_t bulk_size;
	int nested_counter{ 0 };
	std::vector<std::shared_ptr<IObserver> > observers;
	std::vector<std::string> commands;
};


#endif //BULK_H
