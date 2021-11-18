/** @file */
#pragma once

#include "struktury.h"
#include <vector>

using namespace std;

/** Funkcja odczytuje argument funkcji main i nazwê pliku wejœciowego
@param argc liczba argumentów
@param argv tablica argumentów
@param[in,out] name nazwa pliku wejściowego
@return zwraca czy argumenty zostały odczytane poprawnie
*/
bool argument(int argc, char* argv[], string& name);

/** Funkcja odczytuje dane z pliku wejœciowego i wywo³uje funkcjê generuj¹c¹ strukturê danych
@param fname nazwa pliku wejœciowego
@param[in,out] exit struktura przechowuj¹ca dane pliku wyjœciowego
@param[in,out] readed zmienna zwracaj¹ca informacjê czy odczyt siê uda³
@return adres korzenia drzewa binarnego operacji
*/
tree* odczyt(string fname, readZ& exit, bool& readed);

/** Funkcja generuje strukturê drzewa
@param[in,out] vecZ wektor przechowuj¹cy dane zbiorów
@param[in,out] vecO wektor przechowuj¹cy dane operacji
@param name nazwa elementu dla którego wywo³ywana jest funkcja
@return adres wêz³a drzewa binarnego operacji, jeœli nazwy nie znaleziono zwraca nullptr
*/
tree* generujDrzewo(vector<readZ>& vecZ, vector<readO>& vecO, char name);

/** Funkcja generuje listê dwukierunkow¹ zawieraj¹c¹ elementy zbioru
@param[in,out] vecZ wektor przechowuj¹cy dane zbiorów
@param name nazwa elementu dla którego wywo³ywana jest funkcja
@return adres pierwszego elementu listy, jeœli nazwy nie znaleziono zwraca nullptr
*/
list* generujListe(vector<readZ>& vecZ, char name);

/** Funkcja odczytuje kolejne elementy zbioru z pliku i wywo³uje funkcjê sortuj¹c¹
@param dane struktura zawieraj¹ca dane zbioru
@return adres pierwszego elementu listy, jesli zbiór jest pusty zwraca nullptr
*/
list* odczytLista(readZ dane);

/** Funkcja sortuje listê dwukierunkow¹ przez scalanie
@param pHead adres pierwszego elementu listy
@return adres posortowanej listy
*/
list* MergeSort(list* pHead);

/** Funkcja rozdziela listê dwukierunkow¹ na dwie podlisty
@param pHead adres pierwszego elementu listy
@param[in,out] pH1 adres pierwszego elementu pierwszej podlisty
@param[in,out] pH2 adres pierwszego elementu drugiej podlisty 
*/
void split(list* pHead, list*& pH1, list*& pH2);

/** Funkcja ³¹czy dwie posortowane listy dwukierunkowe w jedn¹ posortowan¹ listê
@param[in,out] pH1 adres pierwszego elementu pierwszej listy
@param[in,out] pH2 adres pierwszego elementu drugiej listy
@return adres pierwszego elementu listy po³¹czonej listy
*/
list* merge(list*& pH1, list*& pH2);

/** Funkcja wyznacza zbiór bêd¹cy wynikiem operacji dla danego wêz³a drzew binarnego
@param pHead adres wêz³a
@return adres pierwszego elementu listy dwukierunkowej przechowuj¹cej wynik operacji, dla zbioru pustego zwraca nullptr
*/
list* oblicz(tree* pHead);

/** Funkcja wyznacza zbiór bêdacy przeciêciem podanych zbiorów przechowywanych w listach dwukierunkowych
@param[in,out] pH1 adres pierwszego elementu pierwszej listy
@param[in,out] pH2 adres pierwszego elementu drugiej listy
@return adres pierwszego elementu listy dwukierunkowej przechowuj¹cej wynik operacji, dla zbioru pustego zwraca nullptr
*/
list* przeciecie(list*& pH1, list*& pH2);

/** Funkcja wyznacza zbiór bêdacy sum¹ podanych zbiorów przechowywanych w listach dwukierunkowych
@param[in,out] pH1 adres pierwszego elementu pierwszej listy
@param[in,out] pH2 adres pierwszego elementu drugiej listy
@return adres pierwszego elementu listy dwukierunkowej przechowuj¹cej wynik operacji, dla zbioru pustego zwraca nullptr
*/
list* suma(list*& pH1, list*& pH2);

/** Funkcja wyznacza zbiór bêdacy ró¿nic¹ podanych zbiorów przechowywanych w listach dwukierunkowych
@param[in,out] pH1 adres pierwszego elementu pierwszej listy
@param[in,out] pH2 adres pierwszego elementu drugiej listy
@return adres pierwszego elementu listy dwukierunkowej przechowuj¹cej wynik operacji, dla zbioru pustego zwraca nullptr
*/
list* roznica(list*& pH1, list*& pH2);

/** Funkcja wyznacza zbiór bêdacy ro¿nic¹ symetryczn¹ podanych zbiorów przechowywanych w listach dwukierunkowych
@param[in,out] pH1 adres pierwszego elementu pierwszej listy
@param[in,out] pH2 adres pierwszego elementu drugiej listy
@return adres pierwszego elementu listy dwukierunkowej przechowuj¹cej wynik operacji, dla zbioru pustego zwraca nullptr
*/
list* symetryczna(list*& pH1, list*& pH2);

/** Funkcja usuwaj¹ca listê dwukierunkow¹
@param[in,out] pHead adres pierwszego elementu listy
*/
void zniszcz(list*& pHead);

/** Funkcja zapisuj¹ca do pliku wyjœciowego listê dwukierunkow¹
@param[in,out] pHead adres pierwszego elementu listy
@param wynik dane pliku wyjœciowego
*/
void zapisz(list*& pHead, readZ wynik);
