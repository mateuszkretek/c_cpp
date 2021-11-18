#include <iostream>
#include "file.h"
#include "converter.h"

int main() {
	std::vector<std::vector<long double>> data;
	Converter converter;
	bool error = false;
	while (true) {
		std::cout << "Podaj system danych wejsciowych: WGS84(1) lub PL2000(2).\n";
		data_type param;
		std::string buf;
		std::cin >> buf;
		if (buf == "1")
			param = data_type::WGS;
		else if (buf == "2")
			param = data_type::PL;
		else
			continue;
		std::cout << "\nKazda wspolrzedna powinna byc podana w stopniach dla systemu WGS84 lub w metrach dla systemu PL2000";
		std::cout << "\nPodaj nazwe pliku z danymi (obslugiwane rozszerzenia: *.txt *.bin, *.csv).\n";
		std::cin >> buf;
		data.clear();
		FileIn input(buf, param);
		buf.erase(0, buf.length() - 3);
		switch (buf[0]) {
		case 't':
			std::cout << "podaj znak ktorym rozdzielone sa wartosci\n";
			std::cin >> buf;
			error = !input.read_txt(data, buf[0]);
			break;
		case 'b':
			std::cout << "podaj znak ktorym rozdzielone sa wartosci\n";
			std::cin >> buf;
			error = !input.read_bin(data, buf[0]);
			break;
		case 'c':
			error = !input.read_csv(data);
			break;
		default:
			error = true;
			break;
		}
		if (!error) {
			if (param == data_type::WGS)
				for (int i = 0; i < data.size(); ++i) {
					converter.PL2000(data[i][0], data[i][1], data[i][2], data[i][3]);
				}
			else
				for (int i = 0; i < sizeof(data); ++i) {
					converter.WGS84(data[i][2], data[i][3], data[i][0], data[i][1]);
				}
			std::cout << "\nPodaj nazwe pliku do ktorego ma zostac zapisany wynik.\n";
			std::cout << "Obslugiwane formaty: *.txt, *.bin, *.csv, *.gpx\n";
			std::cout << "Do pliku *.gpx zostana wypisane jedynie wartosci w systemie WGS84\n";
			std::cin >> buf;
			FileOut output(buf);
			buf.erase(0, buf.length() - 3);
			switch (buf[0]) {
			case 't':
				std::cout << "\nPodaj znak ktorym rozdzielone sa wartosci\n";
				std::cin >> buf;
				error = !output.print_txt(data, buf[0]);
				break;
			case 'b':
				std::cout << "\nPodaj znak ktorym rozdzielone sa wartosci\n";
				std::cin >> buf;
				error = !output.print_bin(data, buf[0]);
				break;
			case 'c':
				error = !output.print_csv(data);
				break;
			case 'g':
				error = !output.print_gpx(data);
				break;
			default:
				error = true;
				break;
			}
			if (error)
				std::cout << "Pliku nie udalo sie utworzyc\n";
			std::cout << "\nCzy chcesz wprowadzic kolejne dane?";
			std::cout << "\nWpisz (T) jesli tak, lub (N) jesli nie\n";
			std::cin >> buf;
			if (buf == "T")
				system("CLS");
			else
				break;
		}
		else
			std::cout << "\nbledna nazwa pliku\n";
		error = false;
	}
	return 0;
}


