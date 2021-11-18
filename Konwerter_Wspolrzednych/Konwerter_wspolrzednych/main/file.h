/** @file */
#pragma once
#include <vector>
#include <string>


/// klasa służaca jako paramatr określający dane wejściowe
enum class data_type { 
	WGS,	///< wartość jesli system wprowadzanych danych to WGS84
	PL		///< wartość jesli system wprowadzanych danych to PL2000
};

/// klasa odpowiadająca za odczyt z pliku
class FileIn {
protected:
	std::string filename;	///< nazwa pliku, który ma zostać odczytany
	data_type param;		///< parametr okreslający w jakim systemie podane są dane wejściowe w pliku WGS84 lub PL2000
public:

	FileIn(const std::string& filename, const data_type& param);
	
	/** \brief Odczyt z pliku txt
	  * \param data wektor do którego zostaną wczytane wartości
	  * \param delim separator którym oddzielone są kolejne wartości
	  * \return funkcja zwraca true jeśli odczyt się powiódł lub false, jeżeli nie
	  * 
	  * Funkcja odczytuje do wektora kolejne wartości współrzędnych punktów do konwersji.
	*/
	bool read_txt(std::vector<std::vector<long double>>& data, const char& delim) const;
	
	/** \brief Odczyt z pliku bin
	  * \param data wektor do którego zostaną wczytane wartości
	  * \param delim separator którym oddzielone są kolejne wartości
	  * \return funkcja zwraca true jeśli odczyt się powiódł lub false, jeżeli nie
	  *
	  * Funkcja odczytuje do wektora kolejne wartości współrzędnych punktów do konwersji.
	*/
	bool read_bin(std::vector<std::vector<long double>>& data, const char& delim) const;
	
	/** \brief Odczyt z pliku csv
	  * \param data wektor do którego zostaną wczytane wartości
	  * \return funkcja zwraca true jeśli odczyt się powiódł lub false, jeżeli nie
	  *
	  * Funkcja odczytuje z do wektora kolejne wartości współrzędnych punktów do konwersji.
	*/
	bool read_csv(std::vector<std::vector<long double>>& data) const;
};

/// klasa odpowadająca za zapis do pliku
class FileOut {
protected:
	std::string filename;	///< nazwa pliku, do którego mają zostac zapisane dane
public:

	FileOut(const std::string& filename);
	
	/** \brief Zapis do pliku txt 
	  * \param data wektor z którego zostaną pobrane wartości do zapisu
	  * \param delim separator którym zostaną oddzielone poszczególne wartości
	  * \return funkcja zwraca true jeśli zapis się powiódł lub false, jeżeli nie
	  *
	  * Funkcja odczytuje z wektora kolejne wartości i zapisuje je do pliku.
	*/
	bool print_txt(std::vector<std::vector<long double>>& data, const char& delim) const;
	
	/** \brief Zapis do pliku bin
	  * \param data wektor z którego zostaną pobrane wartości do zapisu
	  * \param delim separator którym zostaną oddzielone poszczególne wartości
	  * \return funkcja zwraca true jeśli zapis się powiódł lub false, jeżeli nie
	  *
	  * Funkcja odczytuje z wektora kolejne wartości i zapisuje je do pliku.
	*/
	bool print_bin(std::vector<std::vector<long double>>& data, const char& delim) const;
	
	/** \brief Zapis do pliku csv
	  * \param data wektor z którego zostaną pobrane wartości do zapisu
	  * \return funkcja zwraca true jeśli zapis się powiódł lub false, jeżeli nie
	  *
	  * Funkcja odczytuje z wektora kolejne wartości i zapisuje je do pliku.
	*/
	bool print_csv(std::vector<std::vector<long double>>& data) const;
	
	/** \brief Zapis do pliku gpx
	  * \param data wektor z którego zostaną pobrane wartości do zapisu
	  * \return funkcja zwraca true jeśli odczyt się powiódł lub false, jeżeli nie
	  *
	  * Funkcja odczytuje z wektora kolejne wartości i zapisuje je do pliku.
	  * Zapisywane są jednak jedynie wartości podanane w systemie WGS-84.
	*/
	bool print_gpx(std::vector<std::vector<long double>>& data) const;
};