/*!
\file
\brief ���� ����� �������������
*/

#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "SolverQuadro.h"
#include "Input.h"

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

    printf("������� a, b, c: ");
    int symbol = 0;
    while (scanf("%f %f %f", &abc->a, &abc->b, &abc->c) != 3 || !CheckSpaceBeforeEndl())
    {
        if (getchar() == EOF || getchar() == '\n')
        {
            txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
            printf("������������ ������!\n");
            txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
            return false;
        }
        while ((symbol = getchar()) != '\n' || symbol != EOF) {}
        printf("������� ��� ���\n");
    }
    return true;
}

/**
* @brief  ������� �������� ������� �������� ����� ������ �����
* @return ������� �������� ����� ������ �����
*/

bool CheckSpaceBeforeEndl()
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
