#pragma once
#include "order.h"
#include "database.h"
#include <string>
#include <vector>

class Program {
	std::vector<std::string> content;
	std::vector<Order*> compiled;
public:
	void add_program(std::vector<std::string>& _content);
	void analyze(Database& _database, Machine& _machine);
	void compile(Database& _database, Machine& _machine, std::vector<std::pair<std::string, int>>& _order);
	void run(Machine& _machine);
};