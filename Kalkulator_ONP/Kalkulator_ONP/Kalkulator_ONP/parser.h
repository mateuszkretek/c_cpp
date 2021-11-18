/** @file */
#pragma once

#include "struct.h"
#include <stdbool.h>

/** Funkcja wyświetla instrukcję do programu i odczytuje wyrażenie arytmetyczne do podanego cstring'a
@param input cstring do którego wczytane zostanie wyrażenie
*/
void launch(char input[]);

/** Funkcja przyjmuje cstring z wyrażeniem arytmetycznym i tłumaczy je na wyrażenie w ONP które umieszcza w innym cstring'u
@param expression cstring z wyrażeniem arytmetycznym
@param rpn cstring w którym zostanie umieszczone przetłumaczone wyrażenie
@return zwraca true jeżeli operacja się powiodła, lub false jeśli wystąpił błąd
*/
bool parse(char expression[], char rpn[]);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z operatorami i modyfikuje go w zależności od przyjetych parametrów
@param top adres wskaźnika na szczyt stosu
@param sign znak który powinien być umieszczony na szczycie stosu
@param rpn cstring w którym zostanie umieszczone przetłumaczone wyrażenie
@param priority priorytet danego operatora wpływający na modyfikację stosu
*/
void modify_stack(struct parser** top, char sign, char rpn[], int priority);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z operatorami i dodaje element na szczyt
@param top adres wskaźnika na szczyt stosu
@param sign znak który powinien być umieszczony na szczycie stosu
@param priority priorytet danego operatora wpływający na modyfikację stosu
*/
void push_stack(struct parser** top, char sign, int priority);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z operatorami usuwa element po czym umieszcza go w cstring'u z przetłumaczonym wyrażeniem
@param top adres wskaźnika na szczyt stosu
@param rpn cstring w którym zostanie umieszczone przetłumaczone wyrażenie
*/
void pop_stack(struct parser** top, char rpn[]);