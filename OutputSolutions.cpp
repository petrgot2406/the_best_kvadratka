/*!
\file
\brief  Файл вывода решений квадратного уравнения
*/

#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "OutputSolutions.h"
#include "SolverQuadro.h"

/**
* @brief           Функция вывода решений уравнения
* @param Roots sol Корни уравнения и их количество
*/

void AnswerOutput(Roots sol)
{
    switch(sol.nRoots)
    {
        case 0: printf("нет решений");
                break;
        case 1: printf("x = %g", sol.x1);
                break;
        case 2: printf("x1 = %g, x2 = %g", sol.x1, sol.x2);
                break;
        case INF_NUM_OF_ROOTS: printf("любое число");
                               break;

        default: txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
                 printf("ERROR: Incorrect number of roots");
                 txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                 break;
    }
}


