#include "add_new_order.h"
#include "read_order_txt.h"
#include <iostream>
#include <thread>
#include <chrono>

void add_new_order(Database& _database) {
	std::string buffer;
	std::string _name;
	std::vector<std::string> _content;
	bool success = false;
	while (!success) {
		std::cout << "Wybierz sposob wprowadzenia rozkazu:\n";
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
				read_order_txt(_name, _content);
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
	try {
		Order new_order(_name, _content);
		_database.add_order_to_database(new_order);
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		return;
	}
}