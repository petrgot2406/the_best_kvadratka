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

bool InputABC(Coeffs *abc);
bool SpaceBeforeEndl();
void AnswerOutput(Roots sol);

int main()
{
    struct Coeffs abc = {0, 0, 0};
    struct Roots sol = {0, 0, 0};
    if (RunAllTests())
    {
        printf("All tests are passed\n");
    }
    printf("Введите a, b, c: ");

    if (!InputABC(&abc))
    {
        return 1;
    }
    SolveQuad(abc, &sol);
    AnswerOutput(sol);
    return 0;
}

/**
* @brief             Функция ввода коэффициентов
* @param Coeffs *abc Вводимые коэффициенты
* @return            Корректность полученных данных
*/

bool InputABC(Coeffs *abc)
{
    assert(&abc->a != NULL);
    assert(&abc->b != NULL);
    assert(&abc->c != NULL);
    int symbol = 0;
    while (scanf("%f %f %f", &abc->a, &abc->b, &abc->c) != 3 || !SpaceBeforeEndl())
    {
        if (getchar() == EOF || getchar() == '\n')
        {
            printf("Недостаточно данных!");
            return false;
        }
        while ((symbol = getchar()) != '\n' || symbol != EOF || symbol == ' ') {}
        printf("Введите ещё раз\n");
    }
    return true;
}

/**
* @brief  Функция проверки наличия пробелов перед концом ввода
* @return Наличие пробелов перед концом ввода
*/

bool SpaceBeforeEndl()
{
    int symbol = 0;
    while ((symbol = getchar()) != '\n' && symbol != EOF)
    {
        if (symbol != ' ')
        {
            return false;
        }
    }
    return true;
}

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

        default: printf("ERROR: Incorrect number of roots");
                 break;
    }
}
