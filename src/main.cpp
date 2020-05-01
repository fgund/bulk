#include <iostream>
#include "bulk.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

int main(int argc, char *argv[])
{
	int bulk_size{ 0 };

	if (argc == 2) {
		bulk_size = std::atoi(argv[1]);
	}
	else{
		std::cout << "Bulk size was not set.\n";
		std::cout << "Please start the program like this: bulk arg"<< "\n";
		return 1;
	}
	
	Bulk bulk_unit(bulk_size);
	auto console_logger = std::make_shared<ConsoleLogger>();
	auto file_logger = std::make_shared<FileLogger>();
	bulk_unit.GetResultNotifier().AddObserver(console_logger);
	bulk_unit.GetResultNotifier().AddObserver(file_logger);
	bulk_unit.GetTimeNotifier().AddObserver(file_logger);
	std::string input;
	while (true) {
		std::getline(std::cin, input);
		if (std::cin.eof()) {
			break;
		}
		bulk_unit.Process(std::move(input));
	}
	return 0;
}