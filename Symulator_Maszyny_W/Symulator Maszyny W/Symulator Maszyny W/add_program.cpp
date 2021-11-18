#include "add_program.h"
#include "read_program_txt.h"
#include <iostream>
#include <thread>
#include <chrono>

void add_new_program(std::vector<std::string>& _content) {
	std::string buffer;
	std::string _name;
	bool success = false;
	//std::vector<std::string> _content;
	while (!success) {
		std::cout << "Wybierz sposob wprowadzenia programu:\n";
		std::cout << "[1]: Plik .txt\n";
		//std::cout << "[2]: Wiersz polecen\n";
		std::cout << "[3]: Anuluj\n\n";
		std::cin >> buffer;
		if (buffer.size() > 1) {
			std::cout << "opcja nie istnieje\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			system("CLS");
			continue;
		}
		switch (buffer[0]) {
		case '1':
			try {
				read_program_txt(_content);
				success = true;
			}
			catch (std::exception& e) {
				std::cerr << e.what();
			}
			break;
			//case '2':
			//	failure = read_order_console(_name, _content);
			//	break;
		case '3':
			return;
			break;
		default:
			std::cout << "opcja nie istnieje\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			system("CLS");
			break;
		}
	}
}