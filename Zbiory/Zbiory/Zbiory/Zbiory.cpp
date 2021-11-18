/** @file */

#include <iostream>

#include "funkcje.h"

using namespace std;

int main(int argc, char* argv[])
{
   string input = "sumaprzeciecie.txt";
   bool readed = true;
   
   if (argument(argc, argv, input)) //sprawdzenie poprawno�ci argument�w uruchomienia
   {
        readZ exit = {};
        tree* pHead = nullptr;
        list* pExit = nullptr;
        pHead = odczyt(input, exit,readed); //odczyt i generowanie struktury
        if (pHead)  // je�eli odczytany zbi�r nie jest pusty
        {
           pExit = oblicz(pHead);   //obliczenie operacji
        }
        if (readed) //je�eli odczyt si� uda�
        {
            zapisz(pExit, exit);    //zapis do pliku
        }
   }

    return 0;
}


