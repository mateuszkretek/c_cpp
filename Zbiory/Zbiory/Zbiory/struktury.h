/** @file */
#pragma once

#include <string>

using namespace std;

/** Element listy dwukierunkowej */
struct list
{
	int value;			///< Wartoœæ elementu je¿eli nalezy do zbioru
	list* pLeft;		///< WskaŸnik na poprzedni element
	list* pRight;		///< WskaŸnik na nastêpny element
};

/** Element drzewa binarnego */
struct tree
{
	char name;			///< Nazwa zbioru
	char operation;		///< Znak  operacji do wykonania dla wêz³a
	tree* tLeft;		///< WskaŸnik na lewego potomka
	tree* tRight;		///< WskaŸnik na prawego potomka
	list* lLeft;		///< WskaŸnik na zbiór
	list* lRight;		///< WskaŸnik na zbiór
};

/** Struktura przechowuj¹ca dane zbiorów i wyniku */
struct readZ
{
	char name;			///< Nazwa zbioru
	string filename;	///< Nazwa pliku w którym znajduje siê zawartoœæ zbioru
	string filetype;	///< Typ pliku w którym znajduje siê zawartoœæ zbioru
};

/** Struktura przechowuj¹ca dane kolejnych operacji */
struct readO
{
	char name;			///< Nazwa zbioru
	char operation;		///< Znak operacji do wykonania
	char left;			///< Nazwa pierwszego elementu dzia³ania
	char right;			///< Nazwa drugiego elementu dzia³ania
};

