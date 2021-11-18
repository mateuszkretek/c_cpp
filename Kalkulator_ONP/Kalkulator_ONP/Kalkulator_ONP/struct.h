/** @file */
#pragma once

/** Element stosu liczb */
struct element {
	double value;			///< Liczba umieszczona na stosie
	struct element* pt;		///< Wskaźnik na poprzedni element
};

/** Element stosu operatorów */
struct parser {
	char operation;			///< Operator umieszczony na stosie
	int priority;			///< Priorytet operatora
	struct parser* pt;		///< Wskaźnik nan poprzedni element
};