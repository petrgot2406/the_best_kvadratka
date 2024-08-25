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
    printf("������� 1, ����� ��������� �����\n");
    printf("������� 2, ����� ������ ���������� ���������\n");
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
        default: printf("������ ����� ������\n");
                 return 1;
    }
    return 0;
}
