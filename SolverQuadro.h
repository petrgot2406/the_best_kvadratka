#ifndef SOLVERQUADRO_H
#define SOLVERQUADRO_H

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

/**
* @brief   ��������� �������������
* @param a ������� ����������� ���������
* @param b ������ ����������� ���������
* @param c ��������� ���� ���������
*/

struct Coeffs {
    float a, b, c;
};

/**
* @brief        ��������� ������� ���������
* @param x1     ������ ������ ���������
* @param x2     ������ ������ ���������
* @param nRoots ���������� ������ ���������
*/

struct Roots
{
    float x1, x2;
    int nRoots;
};

/**
* @brief            ��������� �������� ������������� � ��������� �����������
* @param Coeffs abc �������� ������������
* @param Roots sol  ��������� ����������
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
