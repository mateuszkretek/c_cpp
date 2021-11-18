#include "database.h"
#include <iostream>

void Database::print_orders_list() {
	std::cout << std::endl;
	for (std::map<int,Order>::iterator it = orders.begin(); it != orders.end(); ++it) {
		std::cout << it->first << ": " << it->second.name << std::endl;
	}
	std::cout << std::endl;
}

void Database::add_order_to_database(Order& new_order)
{
	orders.insert(std::pair<int, Order>(orders.size(), new_order));
}
