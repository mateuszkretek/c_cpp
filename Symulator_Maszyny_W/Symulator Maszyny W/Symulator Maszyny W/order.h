#pragma once
#include "signal.h"
#include <string>
#include <vector>

class Order : Signal {
	std::string name;
	std::vector<std::string> content;
	std::vector<void(Order::*)(Machine& machine)> compiled;
public:
	friend class Database;
	friend class Program;
	Order(std::string _name, std::vector<std::string>_content);
	~Order() {};
	void analyze();
	void compile(std::vector<std::string> _cycle);
	void run(Machine& _machine);
};