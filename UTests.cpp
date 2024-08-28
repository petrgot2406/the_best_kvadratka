/*!
\file
\brief Файл прохождения тестов
*/


#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"
#include "UTests.h"

/**
* @brief               Функция прохождения теста
* @param i             Номер теста
* @param UnitTest test Тестовые коэффициенты и ожидаемые значения
* @return              Успешность прохождения теста
*/

bool RunTest(int i, UnitTest test)
{
    bool succ = true;
    struct Roots testroots = {0, 0, 0};
    SolveQuad(test.abc, &testroots);
    if (abs(testroots.nRoots - test.sol.nRoots) < EPS)
    {
        switch(testroots.nRoots)
        {
            case INF_NUM_OF_ROOTS: if (IsClose(testroots.x1, 0) && IsClose(testroots.x2, 0))
                                   {
                                        txSetConsoleAttr (FOREGROUND_GREEN | BACKGROUND_BLACK);
                                        printf("Test %d is passed\n", i + 1);
                                        txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                                        return true;
                                   } else
                                   {
                                        succ = false;
                                   }
            case 0: if (IsClose(testroots.x1, 0) && IsClose(testroots.x2, 0))
                    {
                        txSetConsoleAttr (FOREGROUND_GREEN | BACKGROUND_BLACK);
                        printf("Test %d is passed\n", i + 1);
                        txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                        return true;
                    } else
                    {
                        succ =  false;
                    }
            case 1: if ((fabs(testroots.x1 - test.sol.x1) < EPS) && (fabs(testroots.x2 - test.sol.x2) < EPS))
                    {
                        txSetConsoleAttr (FOREGROUND_GREEN | BACKGROUND_BLACK);
                        printf("Test %d is passed\n", i + 1);
                        txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                        return true;
                    } else
                    {
                        succ = false;
                    }
            case 2: if (((fabs(testroots.x1 - test.sol.x1) < EPS) && (fabs(testroots.x2 - test.sol.x2) < EPS))
                          || ((fabs(testroots.x1 - test.sol.x2) < EPS) && (fabs(testroots.x2 - test.sol.x1) < EPS)))
                    {
                        txSetConsoleAttr (FOREGROUND_GREEN | BACKGROUND_BLACK);
                        printf("Test %d is passed\n", i + 1);
                        txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                        return true;
                    } else
                    {
                        succ = false;
                    }
            default: printf("Error: Coeffs are incorrect\n");
                     succ = false;
                     break;
        }
    } else
    {
        succ = false;
    }
    if (!succ)
    {
        txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
        printf("ErrorTest %d: a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nRoots = %d\n",
               i + 1, test.abc.a, test.abc.b, test.abc.c, testroots.x1, testroots.x2, testroots.nRoots);
        printf("Expected: x1 = %g, x2 = %g, nRoots = %d\n", test.sol.x1, test.sol.x2, test.sol.nRoots);
        txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
        return false;
    }
    return false;
}

/**
* @brief  Функция прохождения всех тестов
* @return Успешность прохождения всех тестов
*/

bool RunAllTests(void)
{
    bool totalsuccess = true;
    struct UnitTest test[] = {
        {{0, 0, 0}, {0, 0, INF_NUM_OF_ROOTS}},
        {{1, 1, 1}, {0, 0, 0}},
        {{0, 1, 1}, {-1, -1, 1}},
        {{1, 0, -4}, {-2, 2, 2}},
        {{1, 1, -12}, {-4, 3, 2}},
        {{0, 0, 7}, {0, 0, 0}},
        {{1, 1, -2}, {-2, 1, 2}},
        {{0, 4, -4}, {1, 1, 1}},
        {{1, 0, 0}, {0, 0, 1}},
        {{1, 1, 0.25}, {-0.5, -0.5, 1}},
        {{1, 1, -12}, {3, -4, 2}}
    };
    const int numtests = sizeof(test) / sizeof(test[0]);

    for (int i = 0; i < numtests; i++)
    {
        if (!RunTest(i, test[i]))
        {
            totalsuccess = false;
        }
    }
    if (totalsuccess)
    {
        return true;
    }
    return false;
}
