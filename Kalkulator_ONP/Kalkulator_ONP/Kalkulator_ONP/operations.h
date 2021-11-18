/** @file */
#pragma once

#include "struct.h"
#include <stdbool.h>

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami i wykonuje dodawanie
@param top adres wskaźnika na szczyt stosu
*/
void addition(struct element** top);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami i wykonuje odejmowanie
@param top adres wskaźnika na szczyt stosu
*/
void subtraction(struct element** top);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami i wykonuje mnożenie
@param top adres wskaźnika na szczyt stosu
*/
void multiplication(struct element** top); //mnożenie

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami i wykonuje dzielenie
@param top adres wskaźnika na szczyt stosu
@return zwraca true jeżeli operacja się powiodła, lub false jeśli wystąpił błąd
*/
bool division(struct element** top);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami i wykonuje potęgowanie lub pierwiastowanie
@param top adres wskaźnika na szczyt stosu
@return zwraca true jeżeli operacja się powiodła, lub false jeśli wystąpił błąd
*/
bool power(struct element** top);

/** Funkcja przyjmuje adres wskaźnika na szczyt stosu z liczbami oblicza logarytm
@param top adres wskaźnika na szczyt stosu
@return zwraca true jeżeli operacja się powiodła, lub false jeśli wystąpił błąd
*/
bool logarithm(struct element** top);

/** Funkcja przyjmuje wskaźnik na szczyt stosu z liczbami i oblicza logarytm naturalny
@param top wskaźnik na szczyt stosu
@return zwraca true jeżeli operacja się powiodła, lub false jeśli wystąpił błąd
*/
bool ln(struct element* top);

/** Funkcja przyjmuje wskaźnik na szczyt stosu z liczbami i oblicza sinus
@param top wskaźnik na szczyt stosu
*/
void sinus(struct element* top);

/** Funkcja przyjmuje wskaźnik na szczyt stosu z liczbami i oblicza cosinus
@param top wskaźnik na szczyt stosu
*/
void cosinus(struct element* top);

/** Funkcja przyjmuje wskaźnik na szczyt stosu z liczbami i oblicza tangens
@param top wskaźnik na szczyt stosu
*/
void tangens(struct element* top);