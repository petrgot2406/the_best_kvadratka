/*!
\file
\brief  ���� ������ ������� ����������� ���������
*/

#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "OutputSolutions.h"
#include "SolverQuadro.h"

/**
* @brief           ������� ������ ������� ���������
* @param Roots sol ����� ��������� � �� ����������
*/

void AnswerOutput(Roots sol)
{
    switch(sol.nRoots)
    {
        case 0: printf("��� �������\n");
                break;
        case 1: printf("x = %g\n", sol.x1);
                break;
        case 2: printf("x1 = %g, x2 = %g\n", sol.x1, sol.x2);
                break;
        case INF_NUM_OF_ROOTS: printf("����� �����\n");
                               break;

        default: txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
                 printf("ERROR: Incorrect number of roots\n");
                 txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                 break;
    }
}


