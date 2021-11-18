/** @file */

#include <fstream>

#include "funkcje.h"

using namespace std;

list* oblicz(tree* pHead)
{
	list* pHelp = nullptr;
	list* lH1 = nullptr;
	list* lH2 = nullptr;
	
	if (pHead->tLeft)
	{
		lH1 = oblicz(pHead->tLeft);
	}
	else
	{
		lH1 = pHead->lLeft;
	}

	if (pHead->tRight)
	{
		lH2 = oblicz(pHead->tRight);
	}
	else
	{
		lH2 = pHead->lRight;
	}

	switch (pHead->operation)
		{
		case '*':
			pHelp = przeciecie(lH1, lH2);
			delete pHead;
			return pHelp;
			break;

		case '+':
			pHelp = suma(lH1, lH2);
			delete pHead;
			return pHelp;
			break;

		case '\\':
			pHelp = roznica(lH1, lH2);
			delete pHead;
			return pHelp;
			break;

		case '-':
			pHelp = symetryczna(lH1, lH2);
			delete pHead;
			return pHelp;
			break;

		default:
			return nullptr;
			break;
		}
}

list* przeciecie(list*& pH1, list*& pH2)
{
	if (!pH1)
	{
		zniszcz(pH2);
		return pH1;
	}
	
	if (!pH2)
	{	
		zniszcz(pH1);
		return pH2;
	}
	
	list* pHead = nullptr;
	list* pHelp = nullptr;

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHelp = pH1;
			pH1 = pH1->pRight;
			delete pHelp;
			pHelp = nullptr;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHelp = pH2;
			pH2 = pH2->pRight;
			delete pHelp;
			pHelp = nullptr;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHead = pH1;
			pH1 = pH1->pRight;
			pHelp = pH2;
			pH2 = pH2->pRight;
			delete pHelp;
			pHelp = pHead;
			pHelp->pRight = nullptr;
			break;
		}
	}

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHelp->pRight = pH1;
			pH1 = pH1->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHelp->pRight = pH2;
			pH2 = pH2->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pH1 = pH1->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = pH2;
			pH2 = pH2->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}
	}

	return pHead;
}

list* suma(list*& pH1, list*& pH2)
{
	if (!pH1)
	{
		return pH2;
	}

	if (!pH2)
	{
		return pH1;
	}

	list* pHead = nullptr;
	list* pHelp = nullptr;

	if (pH1->value < pH2->value)
	{
		pHead = pH1;
		pHelp = pHead;
		pH1 = pH1->pRight;
		pHelp->pRight = nullptr;
	}

	else
	{
		if (pH1->value > pH2->value)
		{
			pHead = pH2;
			pHelp = pHead;
			pH2 = pH2->pRight;
			pHelp->pRight = nullptr;
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
			pHelp->pRight = nullptr;
		}
	}

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pH1 = pH1->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))	
		{
			pHelp->pRight = pH2;
			pH2->pLeft = pHelp;
			pH2 = pH2->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pH1 = pH1->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = pH2;
			pH2 = pH2->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}
	}

	return pHead;
}

list* roznica(list*& pH1, list*& pH2)
{
	if (!pH1 || !pH2)
	{
		zniszcz(pH2);
		return pH1;
	}

	list* pHead = nullptr;
	list* pHelp = nullptr;

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHead = pH1;
			pH1 = pH1->pRight;
			pHelp = pHead;
			pHelp->pRight = nullptr;
			break;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHelp = pH2;
			pH2 = pH2->pRight;
			delete pHelp;
			pHelp = nullptr;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp = pH1;
			pH1 = pH1->pRight;
			delete pHelp;
			pHelp = pH2;
			pH2 = pH2->pRight;
			delete pHelp;
			pHelp = nullptr;
		}
	}

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pH1 = pH1->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHelp->pRight = pH2;
			pH2 = pH2->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp->pRight = pH1;
			pH1 = pH1->pRight;
			delete pHelp->pRight;
			pHelp->pRight = pH2;
			pH2 = pH2->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}
	}

	return pHead;
}

list* symetryczna(list*& pH1, list*& pH2)
{
	if (!pH1)
	{
		return pH2;
	}

	if (!pH2)
	{
		return pH1;
	}
	
	list* pHead = nullptr;
	list* pHelp = nullptr;

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHead = pH1;
			pHelp = pHead;
			pH1 = pH1->pRight;
			pHelp->pRight = nullptr;
			break;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHead = pH2;
			pHelp = pHead;
			pH2 = pH2->pRight;
			pHelp->pRight = nullptr;
			break;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp = pH1;
			pH1 = pH1->pRight;
			delete pHelp;
			pHelp = pH2;
			pH2 = pH2->pRight;
			delete pHelp;
			pHelp = nullptr;
		}
	}

	while (pH1 || pH2)
	{
		if (pH1 && (!pH2 || pH1->value < pH2->value))
		{
			pHelp->pRight = pH1;
			pH1->pLeft = pHelp;
			pH1 = pH1->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH2 && (!pH1 || pH1->value > pH2->value))
		{
			pHelp->pRight = pH2;
			pH2->pLeft = pHelp;
			pH2 = pH2->pRight;
			pHelp = pHelp->pRight;
			pHelp->pRight = nullptr;
		}

		if (pH1 && pH2 && pH1->value == pH2->value)
		{
			pHelp->pRight = pH1;
			pH1 = pH1->pRight;
			delete pHelp->pRight;
			pHelp->pRight = pH2;
			pH2 = pH2->pRight;
			delete pHelp->pRight;
			pHelp->pRight = nullptr;
		}
	}

	return pHead;
}

void zniszcz(list*& pHead)
{
	list* pHelp = nullptr;

	while (pHead)
	{
		pHelp = pHead;
		pHead = pHead->pRight;
		delete pHelp;
	}
}