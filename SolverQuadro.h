#ifndef SOLVERQUADRO_H
#define SOLVERQUADRO_H

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

struct Coeffs
{
    float a;
    float b;
    float c;
};

struct Roots
{
    float x1;
    float x2;
    int nRoots;
};

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
