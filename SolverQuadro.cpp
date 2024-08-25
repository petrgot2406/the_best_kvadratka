#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"

/**
* @brief   ������� �������� ��������� ���� �������������� �����
* @param x ������ �������������� �����
* @param y ������ �������������� �����
* @return  ��������� ������ �����
*/

bool IsClose(float x, float y)
{
    if (fabs(x - y) < EPS)
    {
        return true;
    }
    return false;
}

/**
* @brief             ������� �������� �������������
* @param Coeffs abc  ������������
* @return            ������������
*/

float Discriminant(Coeffs abc)
{
    return abc.b * abc.b - 4 * abc.a * abc.c;
}

/**
* @brief         ������� ������� ��������� ���������
* @param b       ������� ����������� ���������
* @param c       ��������� ���� ���������
* @param *nRoots ���������� ������ ���������
* @param *x1     ������ ���������
* @param *x2     ������ ���������
*/

void SolveLinear(float b, float c, int* nRoots, float* x1, float* x2)
{
    assert(nRoots != NULL);
    assert(x1 != NULL);
    assert(x1 != NULL);

    if (IsClose(b, 0))
    {
        if (IsClose(c, 0))
        {
            *nRoots = INF_NUM_OF_ROOTS;
        } else
        {
            *nRoots = 0;
        }
    } else
    {
        *nRoots = 1;
        *x1 = - c / b;
        *x2 = - c / b;
        if (IsClose(*x1, 0))
        {
            *x1 = 0;
            *x2 = 0;
        }
    }
}

/**
* @brief            ������� ������� ���������� ���������
* @param Coeffs abc ������������ ���������
* @param Roots *sol ����� ��������� � �� ����������
*/

void SolveQuad(Coeffs abc, Roots *sol)
{
    assert(&sol->x1 != NULL);
    assert(&sol->x2 != NULL);
    if (IsClose(abc.a, 0))
    {
        SolveLinear(abc.b, abc.c, &sol->nRoots, &sol->x1, &sol->x2);
    } else
    {
        float D = 0;
        D = Discriminant(abc);
        if (D < 0)
        {
            sol->nRoots = 0;
        } else
        {
            if (IsClose(D, 0))
            {
                sol->x1 = - abc.b / (2 * abc.a);
                sol->x2 = - abc.b / (2 * abc.a);
                sol->nRoots = 1;
            } else
            {
                sol->x1 = (- abc.b - sqrtf(D)) / (2 * abc.a);
                sol->x2 = (- abc.b + sqrtf(D)) / (2 * abc.a);
                sol->nRoots = 2;
            }
        }
    }
}
