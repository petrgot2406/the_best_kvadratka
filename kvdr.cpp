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

bool InputABC(Coeffs *abc);
bool SpaceBeforeEndl();
void AnswerOutput(Roots sol);

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

/**
* @brief             ������� ����� �������������
* @param Coeffs *abc �������� ������������
* @return            ������������ ���������� ������
*/

bool InputABC(Coeffs *abc)
{
    assert(&abc->a != NULL);
    assert(&abc->b != NULL);
    assert(&abc->c != NULL);
    int symbol = 0;
    while (scanf("%f %f %f", &abc->a, &abc->b, &abc->c) != 3 || !SpaceBeforeEndl())
    {
        if (getchar() == EOF || getchar() == '\n')
        {
            printf("������������ ������!");
            return false;
        }
        while ((symbol = getchar()) != '\n' || symbol != EOF || symbol == ' ') {}
        printf("������� ��� ���\n");
    }
    return true;
}

/**
* @brief  ������� �������� ������� �������� ����� ������ �����
* @return ������� �������� ����� ������ �����
*/

bool SpaceBeforeEndl()
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

/**
* @brief           ������� ������ ������� ���������
* @param Roots sol ����� ��������� � �� ����������
*/

void AnswerOutput(Roots sol)
{
    switch(sol.nRoots)
    {
        case 0: printf("��� �������");
                break;
        case 1: printf("x = %g", sol.x1);
                break;
        case 2: printf("x1 = %g, x2 = %g", sol.x1, sol.x2);
                break;
        case INF_NUM_OF_ROOTS: printf("����� �����");
                               break;

        default: printf("ERROR: Incorrect number of roots");
                 break;
    }
}
