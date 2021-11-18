#include <iostream>
#include <vector>
#include <string>

#include "program.h"
#include "database.h"
#include "load_basic_orders.h"
#include "add_new_order.h"
#include "add_program.h"


int main() {
	std::string buffer;
	Database _database;
	Machine _machine;
	Program _program;
	load_basic_orders(_database);
	std::vector<std::string> content;
	std::cout << "Symulator Maszyny W+ w konfiguracji bitowej 4/6\n\n";
	while (true) {	
		std::cout << "Dostepne opcje:\n";
		std::cout << "[1]: Wyswietlenie bazy rozkazow\n";
		std::cout << "[2]: Wprowadzenie rozkazu\n";
		std::cout << "[3]: Wprowadzenie programu\n";
		std::cout << "[4]: Uruchomienie programu\n";
		std::cout << "[5]: Wyswietlenie stanu maszyny\n";
		std::cout << "[6]: Wyjscie\n\n";
		std::cout << "Wprowadz numer opcji\n";
		std::cin >> buffer;
		system("CLS");
		if (buffer.size() > 1) {
			std::cout<<"opcja nie istnieje\n";
			system("CLS");
			continue;
		}
		switch (buffer[0]) {
		case '1':
			_database.print_orders_list();
			break;
		case '2':
			add_new_order(_database);
			break; 
		case '3':
			add_new_program(content);
			_program.add_program(content);
			_program.analyze(_database, _machine);
			break; 
		case '4':
			_program.run(_machine);
			break;
		case '5':
			_machine.print_machine();
			break;
		case '6':
			break;
		default:
			std::cout << "opcja nie istnieje";
			system("CLS");
			break;
		}
		if (buffer[0] == '6') {
			break;
		}
	}
	return 0;
}