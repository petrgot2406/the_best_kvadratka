/*!
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения основных
классов, используемых в демонстрационной программе
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"
#include "UTests.h"
#include "Input.h"
#include "OutputSolutions.h"

int main()
{
    struct Coeffs abc = {};
    struct Roots sol = {};
    printf("Введите 1, чтобы запустить тесты\n");
    printf("Введите 2, чтобы решить квадратное уравнение\n");
    int selection = 0;
    scanf("%d", &selection);
    switch(selection)
    {
        case 1: if (RunAllTests())
                {
                    txSetConsoleAttr (FOREGROUND_GREEN | BACKGROUND_BLACK);
                    printf("All tests are passed\n");
                    txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                    break;
                } else
                {
                    return EXIT_FAILURE;
                }
        case 2: if (!InputABC(&abc))
                {
                    return EXIT_FAILURE;
                } else
                {
                    SolveQuad(abc, &sol);
                    AnswerOutput(sol);
                    break;
                }
        default: txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
                 printf("Ошибка ввода данных\n");
                 txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                 return EXIT_FAILURE;
    }
    return 0;
}
