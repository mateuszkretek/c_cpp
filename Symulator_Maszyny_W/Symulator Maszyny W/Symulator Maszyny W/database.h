#pragma once
#include "order.h"
#include <map>

class Database {
	std::map<int,Order> orders;
public:
	friend class Program;
	void print_orders_list();
	void add_order_to_database(Order& new_order);
};