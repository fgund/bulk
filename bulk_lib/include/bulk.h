#ifndef BULK_H
#define BULK_H
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <chrono>
#include <iostream>
#include "IObserver.h"
#include "IObservable.h"
class Bulk
{
public:
	Bulk(int size) :bulk_size(size) {
	}
	~Bulk() {
		if (!commands.empty() && !has_nested) {
			NotifyResult();
		}
	}
	void NotifyResult() {
		result_notifier.Notify(PrepareOutput());
	}
	void NotifyTime() {
		time_notifier.Notify(std::chrono::system_clock::now());
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
			if (commands.empty()) {
				NotifyTime();
			}
			commands.emplace_back(std::move(cmd));
		}
		if ((commands.size() == bulk_size) && (!has_nested)) {
			NotifyResult();
			commands.clear();
		}
		else if (has_nested && (nested_counter == 0)) {
			NotifyResult();
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
	auto& GetResultNotifier() {
		return result_notifier;
	}
	auto& GetTimeNotifier() {
		return time_notifier;
	}
private:
	bool has_nested{ false };
	size_t bulk_size;
	int nested_counter{ 0 };
	IObservable<std::string> result_notifier;
	IObservable<std::chrono::system_clock::time_point> time_notifier;
	std::vector<std::string> commands;
};


#endif //BULK_H
