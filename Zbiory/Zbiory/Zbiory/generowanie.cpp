/** @file */

#include <fstream>

#include "funkcje.h"

using namespace std;



tree* generujDrzewo(vector<readZ>& vecZ, vector<readO>& vecO, char name)
{
	tree* pHead = nullptr;
	tree* tH1 = nullptr;
	tree* tH2 = nullptr;
	list* lH1 = nullptr;
	list* lH2 = nullptr;

	for (int i = 0; i <vecO.size(); i++)	//przeszukiwanie wektora operacji pod k¹tem nazwy operacji podanej w argumencie
	{
		if (name == vecO[i].name)
		{
			tH1 = generujDrzewo(vecZ, vecO, vecO[i].left);	//wywo³anie funkcji dla lewego potomka
			
			if (!tH1)
			{
				lH1 = generujListe(vecZ, vecO[i].left);		//je¿eli lewym potomkiem nie jest wêze³ to jest nim lista
			}
			
			tH2 = generujDrzewo(vecZ, vecO, vecO[i].right);	//wywo³anie funkcji dla prawego potomka
			
			if (!tH2)
			{
				lH2 = generujListe(vecZ, vecO[i].right);	// je¿eli prawym potomkiem nie jest wêze³ to jest nim lista
			}
			
			pHead = new tree{ name,vecO[i].operation,tH1,tH2,lH1,lH2 };	//wygenerowanie wêz³a wraz ze wskaŸnikami na potomków
			return pHead;
		}
	}
	
	return pHead;
}

list* generujListe(vector<readZ>& vecZ, char name)
{
	list* pHead = nullptr;
	for (int i = 0; i < vecZ.size(); i++)	// przeszukiwanie wektora zbiorów pod k¹tem nazwy zbioru podanej w argumencie
	{
		if (name == vecZ[i].name)
		{
			pHead = odczytLista(vecZ[i]);	//odczyt elementów zbioru z pliku			
			return pHead;
		}
	}

	return pHead;
}

list* odczytLista(readZ dane)
{
	list* pHead = nullptr;
	ifstream fin;
	int value;

	if (dane.filetype == "txt")
	{
		fin.open(dane.filename);
		while (fin >> value)
		{
			pHead = new list{ value,nullptr,pHead };
			if (pHead->pRight)
			{
				pHead->pRight->pLeft = pHead;
			}
		}
		fin.close();
		pHead = MergeSort(pHead);	//sortowanie odczytanej listy
		return pHead;
	}

	if (dane.filetype == "bin")
	{
		fin.open(dane.filename, ios::binary);
		while (fin >> value)
		{
			pHead = new list{ value,nullptr,pHead };
			if (pHead->pRight)
			{
				pHead->pRight->pLeft = pHead;
			}
		}
		fin.close();
		pHead = MergeSort(pHead);	//sortowanie odczytanej listy
		return pHead;
	}

	return pHead;
}

list* MergeSort(list* pHead)
{
	if (pHead && pHead->pRight)	// jeœli do funkcji trafi lista jednoelementowa lub pusta algorytm siê nie wykona
	{
		list* pH1 = nullptr;
		list* pH2 = nullptr;
		split(pHead, pH1, pH2);
		pH1 = MergeSort(pH1);
		pH2 = MergeSort(pH2);
		pHead = merge(pH1, pH2);
	}
	return pHead;
}

void split(list* pHead, list*& pH1, list*& pH2)	// funkcja pobiera pierwszy element z listy i na zmiane przydziela go do podlist
{
	pH1 = pHead;
	pHead = pHead->pRight;
	pH1->pRight = nullptr;
	pH2 = pHead;
	pHead = pHead->pRight;
	pH2->pRight = nullptr;

	list* pHelp1 = pH1;
	list* pHelp2 = pH2;
	while (pHead)
	{
		pHelp1->pRight = pHead;
		pHelp1 = pHelp1->pRight;
		pHead = pHead->pRight;
		pHelp1->pRight = nullptr;
		pHelp2->pRight = pHead;
		pHelp2 = pHelp2->pRight;
		if (pHead)
		{
			pHead = pHead->pRight;
			pHelp2->pRight = nullptr;
		}
	}
}

list* merge(list*& pH1, list*& pH2)	// zgdonie z warunkiem w funkcji MergeSort, do funkcji merge trafia zawsze co najmniej jedno elementowa lista
{
	list* pHead = nullptr;
	list* pHelp = nullptr;

	if (pH1->value < pH2->value)
	{
		pHead = pH1;
		pHelp = pHead;
		pH1 = pH1->pRight;
	}

	else
	{
		if (pH1->value > pH2->value)
		{
			pHead = pH2;
			pHelp = pHead;
			pH2 = pH2->pRight;
		}

		else if (pH1->value == pH2->value)
		{
			pHead = pH1;
			pH1 = pH1->pRight;
			pHead->pRight = nullptr;
			pHelp = pH2;
			pH2 = pH2->pRight;
			delete pHelp;
			pHelp = pHead;
		}
	}

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pHelp = pHelp->pRight;
			pH1 = pH1->pRight;
			pHelp->pRight = nullptr;
			continue;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHelp->pRight = pH2;
			pH2->pLeft = pHelp;
			pHelp = pH2;
			pH2 = pH2->pRight;
			pHelp->pRight = nullptr;
			continue;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pHelp = pH1;
			pH1 = pH2;
			pH2 = pH2->pRight;
			delete pH1;
			pH1 = pHelp->pRight;
			pHelp->pRight = nullptr;
		}
	}

	return pHead;
}