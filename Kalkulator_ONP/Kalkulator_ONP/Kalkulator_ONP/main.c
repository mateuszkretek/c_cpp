/** @file */
#include "parser.h"
#include "calc.h"

#include <stdio.h>

int main() 
{    
    char buffer[501] = { "" };
    launch(buffer);
    char rpn[501] = { "" };

    if (parse(buffer, rpn))
    {
        calculate(rpn);
    }

    system("pause");

    return 0;
}


