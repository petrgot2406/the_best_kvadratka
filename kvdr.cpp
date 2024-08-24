/*!
\file
\brief ������������ ���� � ��������� �������
������ ���� �������� � ���� ����������� ��������
�������, ������������ � ���������������� ���������
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
    if (RunAllTests())
    {
        printf("All tests are passed\n");
    }
    printf("������� a, b, c: ");

    if (!InputABC(&abc))
    {
        return 1;
    }
    SolveQuad(abc, &sol);
    AnswerOutput(sol);
    return 0;
}
