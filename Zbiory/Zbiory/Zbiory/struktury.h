/** @file */
#pragma once

#include <string>

using namespace std;

/** Element listy dwukierunkowej */
struct list
{
	int value;			///< Warto�� elementu je�eli nalezy do zbioru
	list* pLeft;		///< Wska�nik na poprzedni element
	list* pRight;		///< Wska�nik na nast�pny element
};

/** Element drzewa binarnego */
struct tree
{
	char name;			///< Nazwa zbioru
	char operation;		///< Znak  operacji do wykonania dla w�z�a
	tree* tLeft;		///< Wska�nik na lewego potomka
	tree* tRight;		///< Wska�nik na prawego potomka
	list* lLeft;		///< Wska�nik na zbi�r
	list* lRight;		///< Wska�nik na zbi�r
};

/** Struktura przechowuj�ca dane zbior�w i wyniku */
struct readZ
{
	char name;			///< Nazwa zbioru
	string filename;	///< Nazwa pliku w kt�rym znajduje si� zawarto�� zbioru
	string filetype;	///< Typ pliku w kt�rym znajduje si� zawarto�� zbioru
};

/** Struktura przechowuj�ca dane kolejnych operacji */
struct readO
{
	char name;			///< Nazwa zbioru
	char operation;		///< Znak operacji do wykonania
	char left;			///< Nazwa pierwszego elementu dzia�ania
	char right;			///< Nazwa drugiego elementu dzia�ania
};

