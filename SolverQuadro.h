/*!
\file
\brief Заголовочный файл решения уравнения
*/

#ifndef SOLVERQUADRO_H
#define SOLVERQUADRO_H

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

/**
* @brief   Структура коэффициентов
*/

struct Coeffs {
    float a; ///< Главный коэффициент уравнения
    float b; ///< Второй коэффициент уравнения
    float c; ///< Свободный член уравнения
};

/**
* @brief        Структура решений уравнения
*/

struct Roots
{
    float x1;   ///< Первый корень уравнения
    float x2;   ///< Второй корень уравнения
    int nRoots; ///< Количество корней уравнения
};

/**
* @brief            Структура тестовых коэффициентов и ожидаемых результатов
*/

struct UnitTest
{
    Coeffs abc; ///< Тестовые коэффициенты
    Roots sol;  ///< Ожидаемые результаты
};

bool IsClose(float x, float y);
float Discriminant(Coeffs abc);
void SolveLinear(float b, float c, int* nRoots, float* x1, float* x2);
void SolveQuad(Coeffs abc, Roots *sol);

#endif
