/** @file */
#pragma once

#include "calc.h"
#include "operations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool calculate(char rpn[])
{
	char* token;
	token = strtok(rpn, " " "\n");

	struct element* top = NULL;

	push_element(&top, strtod(token, NULL));

	while (token != NULL)
	{

		if (47 < token[0] && token[0] < 58)
		{
			push_element(&top, strtod(token, NULL));
		}

		else if (token[0] == 'l')
		{
			if (strstr(token, "log") != NULL)
			{
				if (!logarithm(&top))
				{
					destroy_stack(&top);
					printf("Blad matematyczny\n\n");
					return false;
				}
			}

			else
			{
				if (!ln(top)) 
				{
					destroy_stack(&top);
					printf("Blad matematyczny\n\n");
					return false;
				}
			}
		}

		else
		{
			switch (token[0])
			{
			case '+':
				addition(&top);
				break;
			case '-':
				subtraction(&top);
				break;
			case'*':
				multiplication(&top);
				break;
			case '/':
			{
				if (division(&top))
				{
					break;
				}
				else
				{
					destroy_stack(&top);
					printf("Blad matematyczny\n\n");
					return false;
				}
			}
			case '^':
			{
				if (power(&top))
				{
					break;
				}
				else
				{
					destroy_stack(&top);
					printf("Blad matematyczny\n\n");
					return false;
				}
			}
			case 's':
				sinus(top);
				break;
			case 'c':
				cosinus(top);
				break;
			case 't':
				tangens(top);
				break;
			default:
				break;
			}
		}

		token = strtok(NULL, " " "\n");
	}

	printf("Wynik: %g\n\n",top->value);

	return true;
}


void push_element(struct element** top, double value)
{
	struct element* buf = (struct element*)malloc(sizeof(struct element));

	buf->value = value;
	buf->pt = (*top);
	(*top) = buf;

	return;
}

void destroy_stack(struct element** top)
{
	struct element* buf = NULL;
	while ((*top) != NULL)
	{
		buf = (*top)->pt;
		free(*top);
		*top = buf;
	}
	return;
}
