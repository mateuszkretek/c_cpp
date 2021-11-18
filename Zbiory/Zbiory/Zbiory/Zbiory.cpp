/** @file */

#include <iostream>

#include "funkcje.h"

using namespace std;

int main(int argc, char* argv[])
{
   string input = "sumaprzeciecie.txt";
   bool readed = true;
   
   if (argument(argc, argv, input)) //sprawdzenie poprawnoœci argumentów uruchomienia
   {
        readZ exit = {};
        tree* pHead = nullptr;
        list* pExit = nullptr;
        pHead = odczyt(input, exit,readed); //odczyt i generowanie struktury
        if (pHead)  // je¿eli odczytany zbiór nie jest pusty
        {
           pExit = oblicz(pHead);   //obliczenie operacji
        }
        if (readed) //je¿eli odczyt siê uda³
        {
            zapisz(pExit, exit);    //zapis do pliku
        }
   }

    return 0;
}


