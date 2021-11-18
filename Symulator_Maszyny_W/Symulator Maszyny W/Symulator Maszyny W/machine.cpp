#include "machine.h"
#include <iostream>

Machine::Machine() {
	S = 0;
	M_S = 0;
	A = 0;
	M_A = 0;
	JAL = 0;
	AK = 0;
	KOD = 0;
	AD = 0;
	L = 0;
}

void Machine::print_machine() {
	std::cout << "\nRejestry: \n";
	std::cout << "S: " << S << std::endl;
	std::cout << "A: " << A << std::endl;
	std::cout << "AK: " << AK << std::endl;
	std::cout << "KOD: " << KOD << std::endl;
	std::cout << "AD: " << AD << std::endl;
	std::cout << "L: " << L << std::endl;
	std::cout << "\nPamiec: \n";
	for (auto it=PO.begin(); it != PO.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

void Machine::print_PO() {
	for (auto it = PO.begin(); it != PO.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

void Machine::overwrite_PO(std::map<int, int>& _insert_PO) {
	PO.clear();
	for (std::map<int, int>::iterator it = _insert_PO.begin(); it != _insert_PO.end(); ++it) {
		PO.insert(*it);
	}
}
