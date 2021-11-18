#include "order.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <exception>

Order::Order(std::string _name, std::vector<std::string> _content) :
	name(_name),
	content(_content) {
	this->analyze();
}

void Order::analyze() {
	bool success = true;
	std::vector<std::string>::iterator it = content.begin();
	std::size_t first_cycle = it->find("czyt wys wei il");
	if (first_cycle == std::string::npos) {
		throw std::exception("blad pierszego taktu\n\n");
	}
	std::regex if_M_S_taken("wys|wyak|as");
	std::regex if_M_A_taken("wyad|wyl|sa");
	std::regex if_wys("wys");
	std::regex if_wyak("wyak");
	std::regex if_as("as");
	std::regex if_wyad("wyad");
	std::regex if_wyl("wyl");
	std::regex if_sa("sa");
	int counter = 0;
	for (it; it != content.end(); ++it) {
		if (std::regex_search((*it), if_M_S_taken)) {
			if (std::regex_search((*it), if_wys)) {
				++counter;
			}
			if (std::regex_search((*it), if_wyak)) {
				++counter;
			}
			if (std::regex_search((*it), if_as)) {
				++counter;
			}
			if (counter > 1) {
				throw std::exception("kolizja na magistrali S\n\n");
			}
		}
		counter = 0;
		if (std::regex_search((*it), if_M_A_taken)) {
			if (std::regex_search((*it), if_wyad)) {
				++counter;
			}
			if (std::regex_search((*it), if_wyl)) {
				++counter;
			}
			if (std::regex_search((*it), if_sa)) {
				++counter;
			}
			if (counter > 1) {
				throw std::exception("kolizja na magistrali S\n\n");
			}
		}
		counter = 0;
	}
	it = content.begin();
	std::string buffer;
	std::vector<std::string> cycle;
	for (it; it != content.end(); ++it) {
		std::stringstream str_split(*it);
		while (std::getline(str_split, buffer, ' ')) {
			cycle.push_back(buffer);
		}
	}
	this->compile(cycle);
}

void Order::compile(std::vector<std::string> _cycle) {
	for (std::vector<std::string>::iterator it = _cycle.begin(); it != _cycle.end(); ++it) {
		if ((*it)[0] == 'w') {
			if ((*it)[1] == 'e') {
				if (!it->compare("wes")) {
					compiled.push_back(&Order::wes);
				}
				else if (!it->compare("wei")) {
					compiled.push_back(&Order::wei);
				}
				else if (!it->compare("wea")) {
					compiled.push_back(&Order::wea);
				}
				else if (!it->compare("wel")) {
					compiled.push_back(&Order::wel);
				}
				else if (!it->compare("weja")) {
					compiled.push_back(&Order::weja);
				}
				else if (!it->compare("weak")) {
					compiled.push_back(&Order::weak);
				}
				else {
					throw std::exception("blad kompilacji sygnal nie istnieje\n\n");
				}
			}
			else if ((*it)[1] == 'y') {
				if (!it->compare("wys")) {
					compiled.push_back(&Order::wys);
				}
				else if (!it->compare("wyad")) {
					compiled.push_back(&Order::wyad);
				}
				else if (!it->compare("wyl")) {
					compiled.push_back(&Order::wyl);
				}
				else if (!it->compare("wyak")) {
					compiled.push_back(&Order::wyak);
				}
				else {
					throw std::exception("blad kompilacji sygnal nie istnieje\n\n");
				}
			}
			else {
				throw std::exception("blad kompilacji sygnal nie istnieje\n\n");
			}
		}
		else {
			if (!it->compare("czyt")) {
				compiled.push_back(&Order::czyt);
			}
			else if (!it->compare("pisz")) {
				compiled.push_back(&Order::pisz);
			}
			else if (!it->compare("il")) {
				compiled.push_back(&Order::il);
			}
			else if (!it->compare("dod")) {
				compiled.push_back(&Order::dod);
			}
			else if (!it->compare("ode")) {
				compiled.push_back(&Order::ode);
			}
			else if (!it->compare("przep")) {
				compiled.push_back(&Order::przep);
			}
			else if (!it->compare("as")) {
				compiled.push_back(&Order::as);
			}
			else if (!it->compare("sa")) {
				compiled.push_back(&Order::sa);
			}
			else {
				throw std::exception("blad kompilacji sygnal nie istnieje\n\n");
			}
		}		
	}
}

void Order::run(Machine& _machine) {
	for (std::vector<void(Order::*)(Machine& machine)>::iterator it = compiled.begin(); it != compiled.end(); ++it) {
		(this->**it)(_machine);
	}
}