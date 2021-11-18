/** @file */

#include <fstream>
#include <iostream>

#include "funkcje.h"

using namespace std;

bool argument(int argc, char* argv[], string& name)		// sprawdzanie poprawnoœci argumentu programu
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			++i;
			if (i < argc)
			{
				name.assign(argv[i]);
			}
		}
	}
	if (name.length() == 0)		// jeœli nie podano nazwy pliku wejœciowego
	{
		cout << "Nieprawidlowy argument wywolania programu" << endl;
		cout << "Prawidlowy przelacznik wywolania:" << endl;
		cout << "-i <plik wejsciowy z danymi>" << endl;
		cout << "Plik powinien miec rozszerzenie .txt" << endl << endl;
		cout << "Przykladowy sposob wywolania programu:" << endl;
		cout << "Program.exe -i input.txt" << endl;
		return false;
	}
	return true;
}

tree* odczyt(string fname, readZ& exit, bool& readed)
{
	ifstream fin(fname);

	if (!fin.is_open())		//czy plik otwarty
	{
		cout << "Nie udalo sie otworzyc pliku wejsciowego." << endl;
		readed = false;
		return nullptr;
	}

	if (fin.peek() == EOF)	//czy plik nie jest pusty
	{
		cout << "Plik wejsciowy jest pusty" << endl;
		readed = false;
		return nullptr;
	}

	tree* pHead;
	string name;
	string filename;
	string filetype;
	char temp;
	char left;
	char right;
	char element = {};
	vector <readZ> vecZ;
	vector <readO> vecO;

	while (fin >> name)
	{
		if (name == "WEJSCIE:")
		{
			while (fin >> name)
			{
				if (name == "OPERACJE:")	//czy nale¿y przejœæ do odczytu operacji
				{
					break;
				}
				
				if (fin >> temp >> filename >> filetype)
				{
					element = name[0];
					
					for (int i = 0; i < vecZ.size();i++)
					{
						if (element == vecZ[i].name)	// czy nie nastêpuje powtórzenie nazwy zbioru
						{
							cout << "Blad w pliku wejsciowym" << endl;
							readed = false;
							return nullptr;
						}
					}
					
					vecZ.push_back({ element, filename, filetype });
				}
			}

			while (fin >> name)
			{
				if (name == "WYJSCIE:")	//czy nale¿y przejœæ do odczytu danych pliku wyjœciowego
				{
					break;
				}

				if (fin >> temp >> left >> temp >> right)
				{
					element = name[0];
					
					if (element == left || element == right || left == right)	// czy w linii operacji nie wystêpuj¹ powtórzenia
					{
						cout << "Blad w pliku wejsciowym" << endl;
						readed = false;
						return nullptr;
					}
					
					switch(temp)	//czy pomiêdzy zbiorami znajduje sie poprawny znak
					{
					case '+':
					case '*':
					case '\\':
					case '-':
						break;
					default:
						cout << "Blad w pliku wejsciowym" << endl;
						readed = false;
						return nullptr;
					}

					for (int i = 0; i < vecZ.size(); i++)
					{
						if (element == vecZ[i].name)	//czy nie nastêpuje zdublowanie nazwy zbioru i operacji
						{
							cout << "Blad w pliku wejsciowym" << endl;
							readed = false;
							return nullptr;
						}
					}
					
					for (int i = 0; i < vecO.size(); i++)	
					{
						if (element == vecO[i].name || left == vecO[i].left || left == vecO[i].right || right == vecO[i].left || right == vecO[i].right)	//czy nie powtarza sie nazwa operacji, lub czy nazwy zbiorów nie powtarzaj¹ siê miêdzy sob¹
						{
							cout << "Blad w pliku wejsciowym" << endl;
							readed = false;
							return nullptr;
						}
					}
					
					vecO.push_back({ element,temp,left,right });
				}
			}

			if (fin >> filename >> filetype >> temp >> name)
			{
				exit = { element,filename,filetype };
				break;
			}
		}
	}

	if (fin.fail())	// czy plik odczyta³ sie poprawnie
	{
		cout << "Blad w pliku wejsciowym" << endl;
		readed = false;
		return nullptr;
	}

	fin.close();

	pHead = generujDrzewo(vecZ, vecO, exit.name);	//generowanie struktury danych programu
	return pHead;
}