/*!
\file
\brief Файл ввода коэффициентов
*/

#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"
#include "Input.h"

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

    printf("Введите a, b, c: ");
    int symbol = 0;
    while (scanf("%f %f %f", &abc->a, &abc->b, &abc->c) != 3 || !CheckSpaceBeforeEndl())
    {
        if (getchar() == EOF || getchar() == '\n')
        {
            txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
            printf("Недостаточно данных!\n");
            txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
            return false;
        }
        while ((symbol = getchar()) != '\n' || symbol != EOF) {}
        printf("Введите ещё раз\n");
    }
    return true;
}

/**
* @brief  Функция проверки наличия пробелов перед концом ввода
* @return Наличие пробелов перед концом ввода
*/

bool CheckSpaceBeforeEndl()
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
