/*!
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения основных
классов, используемых в демонстрационной программе
*/


#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"
#include "UTests.h"
#include "Input.h"
#include "OutputSolutions.h"

int main()
{
    struct Coeffs abc = {0, 0, 0};
    struct Roots sol = {0, 0, 0};
    printf("Введите 1, чтобы запустить тесты\n");
    printf("Введите 2, чтобы решить квадратное уравнение\n");
    int selection = 0;
    scanf("%d", &selection);
    switch(selection)
    {
        case 1: if (RunAllTests())
                {
                    printf("All tests are passed\n");
                    break;
                } else
                {
                    return 1;
                }
        case 2: if (!InputABC(&abc))
                {
                    return 1;
                } else
                {
                    SolveQuad(abc, &sol);
                    AnswerOutput(sol);
                    break;
                }
        default: printf("Ошибка ввода данных\n");
                 return 1;
    }
    return 0;
}
