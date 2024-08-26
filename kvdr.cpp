/*!
\file
\brief ������������ ���� � ��������� �������
������ ���� �������� � ���� ����������� ��������
�������, ������������ � ���������������� ���������
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"
#include "UTests.h"
#include "Input.h"
#include "OutputSolutions.h"

int main()
{
    struct Coeffs abc = {};
    struct Roots sol = {};
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
                    return EXIT_FAILURE;
                }
        case 2: if (!InputABC(&abc))
                {
                    return EXIT_FAILURE;
                } else
                {
                    SolveQuad(abc, &sol);
                    AnswerOutput(sol);
                    break;
                }
        default: printf("������ ����� ������\n");
                 return EXIT_FAILURE;
    }
    return 0;
}
