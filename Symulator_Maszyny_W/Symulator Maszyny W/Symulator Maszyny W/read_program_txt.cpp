#include "read_program_txt.h"
#include <fstream>
#include <sstream>
#include <iostream>

void read_program_txt(std::vector<std::string>& _content) {
	std::string filename;
	std::cout << "Podaj nazwe pliku\n";
	std::cin >> filename;
	std::ifstream filein;
	filein.open(filename);
	if (!filein) {
		throw std::exception("pliku nie udalo sie otworzyc\n\n");
	}
	char buffer[256];
	std::string buffer_string;
	while (filein.getline(buffer, 256)) {
		std::stringstream buffer_stream(buffer);
		std::getline(buffer_stream, buffer_string, ';');
		_content.push_back(buffer_string);
	}
}