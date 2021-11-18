/** @file */

#include <fstream>
#include <iostream>

#include "funkcje.h"

using namespace std;

void zapisz(list*& pHead, readZ wynik)
{
	ofstream fout;
	list* pHelp;
	if (wynik.filetype == "txt")
	{
		fout.open(wynik.filename);
		if (fout.is_open())
		{
			while (pHead)
			{
				fout << pHead->value << endl;
				pHelp = pHead;
				pHead = pHead->pRight;
				delete pHelp;
			}
		}
		fout.close();
	}

	if (wynik.filetype == "bin")
	{
		fout.open(wynik.filename, ios::binary);
		if (fout.is_open())
		{
			while (pHead)
			{
				fout << pHead->value << endl;
				pHelp = pHead;
				pHead = pHead->pRight;
				delete pHelp;
			}
		}

		fout.close();
	}
}