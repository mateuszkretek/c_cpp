/** @file */
#pragma once

#include "struct.h"
#include <stdbool.h>

/** Funkcja przyjmuje cstring z zapisanym wyrażeniem w ONP i wywołuje funkcje obliczające oraz budujące stos
@param rpn cstring z wyrażeniem zapisanym w ONP
@return zwraca true jeżeli obliczenia się powiodły, lub false jeśli wystąpił błąd
*/
bool calculate(char rpn[]);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami i dokłada element na początek
@param top adres wskaźnika na szczyt stosu
@param value wartość która ma zostać dołożona na szczyt
*/
void push_element(struct element** top, double value);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu i usuwa cały stos
@param top adres wskaźnika na szczyt stosu
*/
void destroy_stack(struct element** top);