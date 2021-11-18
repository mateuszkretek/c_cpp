#include "read_order_txt.h"
#include <iostream>
#include <fstream>
#include <sstream>

void read_order_txt(std::string& _name, std::vector<std::string>& _content)
{
	std::string filename;
	std::cout << "Podaj nazwe pliku\n";
	std::cin >> filename;
	std::ifstream filein;
	filein.open(filename);
	if (!filein) {
		throw std::exception("pliku nie udalo sie otworzyc\n\n");
	}
	char buffer[256];
	if (filein.getline(buffer, 256)) {
		std::stringstream buffer_stream(buffer);
		std::getline(buffer_stream, _name);
	}
	std::string buffer_string;
	while (filein.getline(buffer, 256)) {
		std::stringstream buffer_stream(buffer);
		std::getline(buffer_stream, buffer_string, ';');
		_content.push_back(buffer_string);
	}
}