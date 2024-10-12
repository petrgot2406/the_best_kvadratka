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
    printf("Input 1 to run tests\n");
    printf("Input 2 to solve quadratic equation\n");
    printf("Input 3 to exit the program\n");
    int selection = 0;
    scanf("%d", &selection);
    switch(selection)
    {
        case 1: if (RunAllTests())
                {
                    txSetConsoleAttr (FOREGROUND_GREEN | BACKGROUND_BLACK);
                    printf("All tests are passed\n");
                    txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                    main();
                    break;
                } else
                {
                    return EXIT_FAILURE;
                    main();
                }
        case 2: if (!InputABC(&abc))
                {
                    return EXIT_FAILURE;
                    main();
                } else
                {
                    SolveQuad(abc, &sol);
                    AnswerOutput(sol);
                    main();
                    break;
                }
        case 3: return 0;
        default: txSetConsoleAttr (FOREGROUND_RED | BACKGROUND_BLACK);
                 printf("Data entry error\n");
                 txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
                 main();
                 break;
    }
    return 0;
}
