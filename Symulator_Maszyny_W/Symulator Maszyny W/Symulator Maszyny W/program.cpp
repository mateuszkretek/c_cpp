#include "program.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <exception>

void Program::add_program(std::vector<std::string>& _content) {
	this->content.clear();
	this->content = _content;
}

void Program::analyze(Database& _database, Machine& _machine) {
	std::regex rst("rst");
	std::regex rpa("rpa");
	std::regex stop("stop");
	std::vector<std::pair<std::string, int>> orders;
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> arguments;
	std::pair<std::string, std::pair<std::string, std::string>> buffer_pair;
	for (std::vector<std::string>::iterator it = content.begin(); it != content.end(); ++it) {
		std::stringstream sstr(*it);
		if (std::regex_search(*it, rst)) {
			buffer_pair.second.first = "rst";
			std::getline(sstr, buffer_pair.first, ':');
			sstr >> buffer_pair.second.second;
			std::getline(sstr, buffer_pair.second.second, ' ');
			buffer_pair.second.second.clear();
			std::getline(sstr, buffer_pair.second.second);
			arguments.push_back(buffer_pair);
		}
		else if (std::regex_search(*it, rpa)) {
			buffer_pair.second.first = "rpa";
			std::getline(sstr, buffer_pair.first, ':');
			buffer_pair.second.second = '0';
			arguments.push_back(buffer_pair);
		}
		else if (std::regex_search(*it, stop)) {
			buffer_pair.first = "stop";
			std::getline(sstr, buffer_pair.second.first);
			buffer_pair.second.second = '0';
			arguments.push_back(buffer_pair);
		}
		else {
			buffer_pair.first = "order";
			std::getline(sstr, buffer_pair.second.first, ' ');
			std::getline(sstr, buffer_pair.second.second);
			arguments.push_back(buffer_pair);
		}
	}
	for (int i = 0; i < arguments.size(); ++i) {
		if (arguments[i].first == "order") {
			for (int j = 0; j < arguments.size(); ++j) {
				if (arguments[i].second.second == arguments[j].first) {
					orders.push_back(std::pair<std::string, int>(arguments[i].second.first, j));
				}
			}
		}
		else if (std::regex_search(arguments[i].second.first, rst)) {
			orders.push_back(std::pair<std::string, int>(arguments[i].second.first, std::stoi(arguments[i].second.second)));
		}
		else if (std::regex_search(arguments[i].second.first, rpa)) {
			orders.push_back(std::pair<std::string, int>(arguments[i].second.first, 0));
		}
		else if (std::regex_search(arguments[i].first, stop)) {
			orders.push_back(std::pair<std::string, int>(arguments[i].second.first, 0));
		}
	}
	this->compile(_database, _machine, orders);
}

void Program::compile(Database& _database, Machine& _machine, std::vector<std::pair<std::string,int>>& _order) {
	bool order_found = false;
	std::map<int, int> PO_content;
	std::regex rst("rst");
	std::regex rpa("rpa");
	std::regex stop("stop");
	for (std::vector<std::pair<std::string, int>>::iterator it = _order.begin(); it != _order.end(); ++it) {
		if (std::regex_search(it->first, rst) or std::regex_search(it->first, rpa)) {
			order_found = true;
			PO_content.insert(std::pair<int, int>(PO_content.size(), it->second));
		}
		else for (std::map<int, Order>::iterator it2 = _database.orders.begin(); it2 != _database.orders.end(); ++it2) {
			std::size_t search_order_name = it->first.find(it2->second.name);
			if (search_order_name != std::string::npos) {
				compiled.push_back(&it2->second);
				order_found = true;
				PO_content.insert(std::pair<int, int>(PO_content.size(), it2->first * 64 + it->second));
			}
		}
		if (!order_found) {
			throw std::exception("rozkaz nie istnieje\n\n");
		}
	}
	_machine.overwrite_PO(PO_content);
	_machine.print_PO();
}

void Program::run(Machine& _machine) {
	for (std::vector<Order*>::iterator it = compiled.begin(); it != compiled.end(); ++it) {
		(*it)->run(_machine);
	}
	_machine.print_PO();
	std::cout << std::endl;
}