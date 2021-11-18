#include "load_basic_orders.h"
#include <sstream>
#include <fstream>

void load_basic_orders(Database& _database) {
	std::string _name;
	std::vector<std::string> _content;
	std::vector<std::string>filenames;
	std::ifstream filein;
	char buffer[256];
	std::string buffer_string;
	filein.open("rozkazy/config.txt");
	while (filein.getline(buffer,256)) {
		std::stringstream buffer_stream(buffer);
		buffer_stream >> buffer_string;
		filenames.push_back(buffer_string);
	}
	filein.close();
	for (std::vector<std::string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
		filein.open(*it);
		if (filein.getline(buffer, 256)) {
			std::stringstream buffer_stream(buffer);
			std::getline(buffer_stream, _name);
		}
		while (filein.getline(buffer, 256)) {
			std::stringstream buffer_stream(buffer);
			std::getline(buffer_stream, buffer_string, ';');
			_content.push_back(buffer_string);
		}
		filein.close();
		Order new_order(_name, _content);
		_content.clear();
		_database.add_order_to_database(new_order);
	}
}