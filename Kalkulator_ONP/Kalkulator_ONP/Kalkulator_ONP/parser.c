/** @file */
#pragma once

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void launch(char input[])
{
    printf("Kalkulator ONP\n");
    printf("Wszystkie liczby i znaki powinny byc oddzielone spacja, limit to 250 znakow\n");
    printf("Liczba moze byc zmiennoprzecinkowa, lecz nie może być ujemna, liczby ujemnie należy wpisywać jako 0 - liczba");
    printf("Mozna uzywac stalych (pi) = 3.14 i (e) = 2.72\n");
    printf("Dostepne funkcje: dodawanie '+', odejmnowanie '-', mnozenie '*', dzielenie '/'\n");
    printf("potega/pierwiastek '^' -> zapis 'a ^ b'\n");
    printf("logarytm 'log' -> zapis 'log a b' oznacza logarytm przy podstawie a z b\n");
    printf("logarytm naturalny 'ln'\n");
    printf("sinus 'sin', cosinus 'cos', tangens 'tan', argument jest traktowana jako radiany\n\n");
    printf("podaj wyrazenie i zatwierdz enterem:\n\n");

    fgets(input, 500, stdin);

    return;
}

bool parse(char expression[], char rpn[])
{
    char* token;
    token = strtok(expression, " " "\n");

    if (token == NULL)
    {
        printf("\nNie wpisano dzialania\n\n");
        return false;
    }

    int needed = 0;     //zmienna zliczająca ile liczb potrzeba do wykoniania działania
    int owned = 0;      //zmienna zliczająca ile liczb zostało już wczytanych
    int bracket = 0;    //zmienna zliczjaca ilość nawiasów otwartych i zamkniętych
    struct parser* top = NULL;
    
    if (strstr(token, "sin") != NULL)
    {
        if (token[3])
        {
            printf("\nBlad w zapisie\n\n");
            return false;
        }

        modify_stack(&top, 's', rpn, 4);
        needed += 1;
    }

    else if (strstr(token, "cos") != NULL)
    {
        if (token[3])
        {
            printf("\nBlad w zapisie\n\n");
            return false;
        }

        modify_stack(&top, 'c', rpn, 4);
        needed += 1;
    }

    else if (strstr(token, "tan") != NULL)
    {
        if (token[3])
        {
            printf("\nBlad w zapisie\n\n");
            return false;
        }

        modify_stack(&top, 't', rpn, 4);
        needed += 1;
    }

    else if (strstr(token, "log") != NULL)
    {
        if (token[3])
        {
            printf("\nBlad w zapisie\n\n");
            return false;
        }

        modify_stack(&top, 'l', rpn, 4);
        needed += 2;
    }

    else if (strstr(token, "ln") != NULL)
    {
        if (token[2])
        {
            printf("\nBlad w zapisie\n\n");
            return false;
        }

        modify_stack(&top, 'n', rpn, 4);
        needed += 1;
    }

    else  if (strstr(token, "pi") != NULL)
    {
        if (token[2])
        {
            printf("\nBlad w zapisie\n\n");
            return false;
        }

        strcat(rpn, "3.14 ");
        owned += 1;
    }

    else if (47 < token[0] && token[0] < 58)
    {
        strcat(rpn, token);
        strcat(rpn, " ");
        owned += 1;
    }

    else  if (token[1])
    {
        printf("\nBlad w zapisie\n\n");
        return false;
    }

    else 
    {
        switch (token[0]) 
        {
        case '(': 
            bracket += 1;
            modify_stack(&top, '(', rpn,  5);
            break;
        case 'e': 
            strcat(rpn, "2.72 ");
            owned += 1;
            break;
        default:
            printf("\nBlad w zapisie\n\n");
            return false;
        }
    }
    
    token = strtok(NULL, " " "\n");
    
    while (token != NULL)
    {            
        if (strstr(token, "sin") != NULL)
        {
            if (token[3])
            {
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }

            modify_stack(&top, 's', rpn, 4);
            needed += 1;
        }

        else if (strstr(token, "cos") != NULL)
        {
            if (token[3])
            {
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }

            modify_stack(&top, 'c', rpn, 4);
            needed += 1;
        }

        else if (strstr(token, "tan") != NULL)
        {
            if (token[3])
            {
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }

            modify_stack(&top, 't', rpn, 4);
            needed += 1;
        }

        else if (strstr(token, "log") != NULL)
        {
            if (token[3])
            {
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }

            modify_stack(&top, 'l', rpn, 4);
            needed += 2;
        }

        else if (strstr(token, "ln") != NULL)
        {
            if (token[2])
            {
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }
            modify_stack(&top, 'n', rpn, 4);
            needed += 1;
        }
       
        else  if (strstr(token, "pi") != NULL)
        {
            if (token[2])
            {
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }
            strcat(rpn, "3.14 ");
            owned += 1;
        }

        else if (47 < token[0] && token[0] < 58)
        {
            strcat(rpn, token);
            strcat(rpn, " ");
            owned += 1;
        }

        else if (token[1])
        {
            printf("\nBlad w zapisie\n\n");
            modify_stack(&top, ' ', rpn, -1);
            return false;
        }

        else {
            switch (token[0]) {
            case '(': 
                bracket += 1;
                modify_stack(&top, token[0], rpn, 5);
                break;
            case '+':
            case '-': 
                modify_stack(&top, token[0], rpn, 1);
                needed += 2;
                break;
            case '*':
            case '/': 
                modify_stack(&top, token[0], rpn, 2);
                needed += 2;
                break;
            case '^': 
                modify_stack(&top, token[0], rpn, 3);
                needed += 2;
                break;
            case ')': 
                bracket -= 1;
                modify_stack(&top, ' ', rpn, 0);
                break;
            case 'e': 
                strcat(rpn, "2.72 ");
                owned += 1;
                break;
            default:
                printf("\nBlad w zapisie\n\n");
                modify_stack(&top, ' ', rpn, -1);
                return false;
            }
        }

        if (needed == owned && needed !=0 && owned !=0)
        {
            needed = 0;
            owned = 1;
        }

        token = strtok(NULL, " " "\n");
    }

    modify_stack(&top, ' ', rpn, -1);

    if (bracket != 0) 
    {
        printf("\nBrakujace nawiasy\n\n");
        return false;
    }

    if (!(needed == 0 && owned == 1))
    {
        printf("\nNiezgodna ilosc liczb i znakow\n\n");
        return false;
    }

    printf("\nONP: %s\n\n",rpn);

    return true;
}

void modify_stack(struct parser** top, char sign, char rpn[], int priority)
{

    if ((*top) == NULL)
    {
        push_stack(top, sign, priority);
        return;
    }
        

    if (priority == -1)
    {
        while ((*top) != NULL)
        {
            pop_stack(top, rpn);
        }
        
        return;
    }

    if (priority == 0)
    {
        while ((*top) != NULL && (*top)->priority != 0)
        {
            pop_stack(top, rpn);
        }

        if ((*top) != NULL) 
        {
            pop_stack(top, rpn);
        }

        return;
    }

    if (priority > (*top)->priority)
    {
        if (priority == 5)
        {
            push_stack(top, sign, 0);
            return;
        }

        push_stack(top, sign, priority);
        return;
    }

    if (priority <= (*top)->priority)
    {
        while ((*top) != 0 && priority <= (*top)->priority)
        {
            pop_stack(top, rpn);
        }
        push_stack(top, sign, priority);

        return;
    }

    return;
}

void push_stack(struct parser** top, char sign, int priority) 
{
    struct parser* buf = (struct parser*)malloc(sizeof(struct parser));

    buf->operation = sign;
    buf->priority = priority;
    buf->pt = (*top);
    (*top) = buf;

    return;
}

void pop_stack(struct parser** top, char rpn[]) 
{
    struct parser* buf = (*top)->pt;
    switch ((*top)->operation) {
    case '+':
        strcat(rpn, "+ ");
        break;
    case '-':
        strcat(rpn, "- ");
        break;
    case '*':
        strcat(rpn, "* ");
        break;
    case '/':
        strcat(rpn, "/ ");
        break;
    case '^':
        strcat(rpn, "^ ");
        break;
    case 's': 
        strcat(rpn, "sin ");
        break;
    case 'c': 
        strcat(rpn, "cos ");
        break;
    case 't': 
        strcat(rpn, "tan ");
        break;
    case 'l': 
        strcat(rpn, "log ");
        break;
    case 'n': 
        strcat(rpn, "ln ");
        break;
    default: 
        break;
    }

    free(*top);
    (*top) = buf;

    return;
}