#pragma once
#include <map>

class Machine {
	std::map<int, int> PO;
	int S;
	int M_S;
	int A;
	int M_A;
	int JAL;
	int AK;
	int KOD;
	int AD;
	int L;
public:
	Machine();
	friend class Signal;
	void print_machine();
	void print_PO();
	void overwrite_PO(std::map<int, int>& _insert_PO);
};