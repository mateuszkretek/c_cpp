/** @file */
#pragma once

#include "operations.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>

#pragma fenv_access (on)

void addition(struct element** top)
{
	struct element* buf = (*top)->pt;
	buf->value += (*top)->value;

	free(*top);
	(*top) = buf;

	return;
}

void subtraction(struct element** top)
{
	struct element* buf = (*top)->pt;
	buf->value -= (*top)->value;

	free(*top);
	(*top) = buf;

	return;
}

void multiplication(struct element** top)
{
	struct element* buf = (*top)->pt;
	buf->value *= (*top)->value;
	
	free(*top);
	(*top) = buf;

	return;
}

bool division(struct element** top)
{
	struct element* buf = (*top)->pt;
	buf->value /= (*top)->value;
	
	if (fetestexcept(FE_DIVBYZERO))
	{
		return false;
	}
	
	free(*top);
	(*top) = buf;

	return true;
}

bool power(struct element** top)
{
	struct element* buf = (*top)->pt;

	buf->value = pow(buf->value, (*top)->value);

	if (fetestexcept(FE_INVALID))
	{
		return false;
	}

	else if (fetestexcept(FE_DIVBYZERO))
	{
		return false;
	}

	else if (fetestexcept(FE_OVERFLOW))
	{
		return false;
	}

	else if (fetestexcept(FE_UNDERFLOW))
	{
		return false;
	}

	free(*top);
	(*top) = buf;

	return true;
}

bool logarithm(struct element** top)
{
	struct element* buf = (*top)->pt;

	buf->value = log((*top)->value) / log(buf->value);

	if (fetestexcept(FE_INVALID))
	{
		return false;
	}

	else if (fetestexcept(FE_DIVBYZERO))
	{
		return false;
	}

	free(*top);
	(*top) = buf;

	return true;
}

bool ln(struct element* top)
{
	top->value = log(top->value);

	if (fetestexcept(FE_INVALID))
	{
		return false;
	}

	else if (fetestexcept(FE_DIVBYZERO))
	{
		return false;
	}

	return true;
}

void sinus(struct element* top)
{
	top->value = sin(top->value);
}

void cosinus(struct element* top)
{
	top->value = cos(top->value);
}

void tangens(struct element* top)
{
	top->value = sin(top->value) / cos(top->value);
}