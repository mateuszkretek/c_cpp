
#include <fstream>
#include <sstream>
#include <iostream>
#include "file.h"

FileIn::FileIn(const std::string& filename, const data_type& param) :
	filename(filename),
	param(param) {
}

bool FileIn::read_txt(std::vector<std::vector<long double>>& data, const char& delim) const {
	std::vector<long double> input;
	std::ifstream istr;
	istr.open(filename);
	if (!istr) return false;
	char buf[64];
	while (istr.getline(buf, sizeof(buf))) {
		std::stringstream sstr(buf);
		sstr.getline(buf, sizeof(buf), delim);
		long double a = strtold(buf, NULL);
		sstr.getline(buf, sizeof(buf), delim);
		long double b = strtold(buf, NULL);
		if (param == data_type::WGS) {
			input.insert(input.end(), { a,b,0.0,0.0 });
			data.push_back(input);
		}
		else {
			input.insert(input.end(), { 0.0,0.0,a,b });
			data.push_back(input);
		}
	input.clear();
	}
	return true;
}


bool FileIn::read_bin(std::vector<std::vector<long double>>& data, const char& delim) const {
	std::vector<long double> input;
	std::ifstream istr;
	istr.open(filename, std::ios::binary | std::ios::in);
	if (!istr) return false;
	char buf[64];
	while (istr.getline(buf, sizeof(buf))) {
		std::stringstream sstr(buf);
		sstr.getline(buf, sizeof(buf), delim);
		long double a = strtold(buf, NULL);
		sstr.getline(buf, sizeof(buf), delim);
		long double b = strtold(buf, NULL);
		if (param == data_type::WGS) {
			input.insert(input.end(), { a,b,0.0,0.0 });
			data.push_back(input);
		}
		else {
			input.insert(input.end(), { 0.0,0.0,a,b });
			data.push_back(input);
		}
		input.clear();
	}
	return true;
}

bool FileIn::read_csv(std::vector<std::vector<long double>>& data) const {
	std::vector<long double> input;
	std::ifstream istr;
	istr.open(filename);
	if (!istr) return false;
	char buf[64];
	istr.getline(buf, sizeof(buf));
	while (istr.getline(buf, sizeof(buf))) {
		std::stringstream sstr(buf);
		sstr.getline(buf, sizeof(buf), ',');
		long double a = strtold(buf, NULL);
		sstr.getline(buf, sizeof(buf), ',');
		long double b = strtold(buf, NULL);
		if (param == data_type::WGS) {
			input.insert(input.end(), { a,b,0.0,0.0 });
			data.push_back(input);
		}
		else {
			input.insert(input.end(), { 0.0,0.0,a,b });
			data.push_back(input);
		}
		input.clear();
	}
	return true;
}

FileOut::FileOut(const std::string& filename) : filename(filename) {
}

bool FileOut::print_txt(std::vector<std::vector<long double>>& data, const char& delim) const {
	std::ofstream ostr;
	ostr.open(filename);
	if (!ostr) return false;
	for (int i = 0; i < data.size(); ++i) {
		ostr << std::fixed << data[i][0] << delim << std::fixed << data[i][1] << delim << std::fixed << data[i][2] << delim << std::fixed << data[i][3] << std::endl;
	}
	ostr.close();
	return true;
}

bool FileOut::print_bin(std::vector<std::vector<long double>>& data, const char& delim) const {
	std::ofstream ostr;
	ostr.open(filename, std::ios::binary | std::ios::out);
	if (!ostr) return false;
	for (int i = 0; i < data.size(); ++i) {
		ostr << std::fixed << data[i][0] << delim << std::fixed << data[i][1] << delim << std::fixed << data[i][2] << delim << std::fixed << data[i][3] << std::endl;
	}
	ostr.close();
	return true;
}

bool FileOut::print_csv(std::vector<std::vector<long double>>& data) const {
	std::ofstream ostr;
	ostr.open(filename);
	if (!ostr) return false;
	ostr << "B[deg],L[deg],N[m],E[m]\n";
	for (int i = 0; i < data.size(); ++i) {
		ostr << std::fixed << data[i][0] << "," << std::fixed << data[i][1] << "," << std::fixed << data[i][2] << "," << std::fixed << data[i][3] << std::endl;
	}
	ostr.close();
	return true;
}

bool FileOut::print_gpx(std::vector<std::vector<long double>>& data) const {
	std::ofstream ostr;
	ostr.open(filename);
	if (!ostr) return false;
	ostr << "<?xml verison=\"1.0\" encoding=\"UTF-8\" stndalone=\"no\" ?>\n";
	ostr << "<gpx creator=\"konwerter_wspolrzednych\" version\"1.1\">\n";
	for (int i = 0; i < data.size(); ++i) {
		ostr << "<trkpt lat=\"" << std::fixed << data[i][0] << "\" lon=\"" << std::fixed << data[i][1] << "\"></trk>\n";
	}
	ostr << "</gpx>";
	ostr.close();
	return true;
}
