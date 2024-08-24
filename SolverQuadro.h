#ifndef SOLVERQUADRO_H
#define SOLVERQUADRO_H

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

/**
* @brief   Структура коэффициентов
* @param a Главный коэффициент уравнения
* @param b Второй коэффициент уравнения
* @param c Свободный член уравнения
*/

struct Coeffs {
    float a, b, c;
};

/**
* @brief        Структура решений уравнения
* @param x1     Первый корень уравнения
* @param x2     Второй корень уравнения
* @param nRoots Количество корней уравнения
*/

struct Roots
{
    float x1, x2;
    int nRoots;
};

/**
* @brief            Структура тестовых коэффициентов и ожидаемых результатов
* @param Coeffs abc Тестовые коэффициенты
* @param Roots sol  Ожидаемые результаты
*/

struct UnitTest
{
    Coeffs abc;
    Roots sol;
};

bool IsClose(float x, float y);
float Discriminant(Coeffs abc);
void SolveLinear(float b, float c, int* nRoots, float* x1, float* x2);
void SolveQuad(Coeffs abc, Roots *sol);

#endif
