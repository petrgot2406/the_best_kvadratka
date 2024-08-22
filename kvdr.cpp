#include <stdio.h>
#include <math.h>
#include <TXLib.h>

struct Coeffs {
    float a, b, c;
};

struct Roots {
    float x1, x2;
    int nRoots;
};

struct UnitTest {
    int numtest;
    Coeffs abc;
    Roots sol;
};

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

bool InputABC(Coeffs *abc);
bool SpaceBeforeEndl();
float Discriminant(Coeffs abc);
bool IsClose(float x, float y);
void SolveQuad(Coeffs abc, Roots *sol);
void SolveLinear(float b, float c, int* nRoots, float* x1);
void AnswerOutput(Roots sol);
bool RunTest(UnitTest);
bool RunAllTests(UnitTest test1, UnitTest test2, UnitTest test3,
                 UnitTest test4, UnitTest test5, UnitTest test6,
                 UnitTest test7, UnitTest test8, UnitTest test9,
                 UnitTest test10, UnitTest test11, UnitTest test12);

int main() {
    struct Coeffs abc = {0, 0, 0};
    struct Roots sol = {0, 0, 0};
    struct UnitTest test1 = {1, {0, 0, 0}, {0, 0, INF_NUM_OF_ROOTS}};
    struct UnitTest test2 = {2, {1, 1, 1}, {0, 0, 0}};
    struct UnitTest test3 = {3, {0, 1, 1}, {-1, 0, 1}};
    struct UnitTest test4 = {4, {1, 0, -4}, {-2, 2, 2}};
    struct UnitTest test5 = {5, {1, 1, -12}, {-4, 3, 2}};
    struct UnitTest test6 = {6, {0, 0, 7}, {0, 0, 0}};
    struct UnitTest test7 = {7, {1, 1, -2}, {-2, 1, 2}};
    struct UnitTest test8 = {8, {0, 4, -4}, {1, 0, 1}};
    struct UnitTest test9 = {9, {1, 1, 0}, {-1, 0, 2}};
    struct UnitTest test10 = {10, {1, 0, 0}, {0, 0, 1}};
    struct UnitTest test11 = {11, {1, 1, 0.25}, {-0.5, 0, 1}};
    struct UnitTest test12 = {12, {1, 1, -12}, {-4, 3, 2}};
    if (RunAllTests(test1, test2, test3, test4,
                    test5, test6, test7, test8,
                    test9, test10, test11, test12)) {
        printf("All tests are passed\n");
    }
    printf("Введите a, b, c: ");

    if (!InputABC(&abc)) {
        return 1;
    }
    SolveQuad(abc, &sol);
    AnswerOutput(sol);
    return 0;
}

bool InputABC(Coeffs *abc) {
    assert(&abc->a != NULL);
    assert(&abc->b != NULL);
    assert(&abc->c != NULL);
    int symbol = 0;
    while (scanf("%f %f %f", &abc->a, &abc->b, &abc->c) != 3 || !SpaceBeforeEndl()) {
        if (getchar() == EOF || getchar() == '\n') {
            printf("Недостаточно данных!");
            return false;
        }
        while ((symbol = getchar()) != '\n' || symbol != EOF || symbol == ' ') {}
        printf("Введите ещё раз\n");
    }
    return true;
}

bool SpaceBeforeEndl() {
    int symbol = 0;
    while ((symbol = getchar()) != '\n' && symbol != EOF) {
        if (symbol != ' ') {
            return false;
        }
    }
    return true;
}

float Discriminant(Coeffs abc) {
    return abc.b * abc.b - 4 * abc.a * abc.c;
}

bool IsClose(float x, float y) {
    if (fabs(x - y) < EPS) {
        return true;
    }
    return false;
}

void SolveQuad(Coeffs abc, Roots *sol) {
    assert(&sol->x1 != NULL);
    assert(&sol->x2 != NULL);
    if (IsClose(abc.a, 0)) {
        SolveLinear(abc.b, abc.c, &sol->nRoots, &sol->x1);
    } else {
        float D = 0;
        D = Discriminant(abc);
        if (D < 0) {
            sol->nRoots = 0;
        } else {
            if (IsClose(D, 0)) {
                sol->x1 = - abc.b / (2 * abc.a);
                sol->nRoots = 1;
            } else {
                sol->x1 = (- abc.b - sqrtf(D)) / (2 * abc.a);
                sol->x2 = (- abc.b + sqrtf(D)) / (2 * abc.a);
                sol->nRoots = 2;
            }
        }
    }
}

void SolveLinear(float b, float c, int* nRoots, float* x1) {
    assert(x1 != NULL);
    if (IsClose(b, 0)) {
        if (IsClose(c, 0)) {
            *nRoots = INF_NUM_OF_ROOTS;
        } else {
            *nRoots = 0;
        }
    } else {
        *nRoots = 1;
        *x1 = - c / b;
        if (IsClose(*x1, 0)) {
            *x1 = 0;
        }
    }
}

void AnswerOutput(Roots sol) {
    switch(sol.nRoots) {
        case 0: printf("нет решений");
                break;
        case 1: printf("x = %g", sol.x1);
                break;
        case 2: printf("x1 = %g, x2 = %g", sol.x1, sol.x2);
                break;
        case INF_NUM_OF_ROOTS: printf("любое число");
                               break;

        default: printf("ERROR: Incorrect number of roots");
                 break;
    }
}

bool RunTest(UnitTest test) {
    struct Roots testroots = {0, 0, 0};
    SolveQuad(test.abc, &testroots);
    if (!(abs(testroots.nRoots - test.sol.nRoots) < EPS) or !(fabs(testroots.x1 - test.sol.x1) < EPS) or !(fabs(testroots.x2 - test.sol.x2) < EPS)) {
        printf("ErrorTest %d: a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nRoots = %d\n", test.numtest, test.abc.a, test.abc.b, test.abc.c, testroots.x1, testroots.x2, testroots.nRoots);
        printf("Expected: x1 = %g, x2 = %g, nRoots = %d\n", test.sol.x1, test.sol.x2, test.sol.nRoots);
        return false;
    }
    return true;
}

bool RunAllTests(UnitTest test1, UnitTest test2, UnitTest test3,
                 UnitTest test4, UnitTest test5, UnitTest test6,
                 UnitTest test7, UnitTest test8, UnitTest test9,
                 UnitTest test10, UnitTest test11, UnitTest test12) {
    if (!RunTest(test1)) return false;
    if (!RunTest(test2)) return false;
    if (!RunTest(test3)) return false;
    if (!RunTest(test4)) return false;
    if (!RunTest(test5)) return false;
    if (!RunTest(test6)) return false;
    if (!RunTest(test7)) return false;
    if (!RunTest(test8)) return false;
    if (!RunTest(test9)) return false;
    if (!RunTest(test10)) return false;
    if (!RunTest(test11)) return false;
    if (!RunTest(test12)) return false;
    return true;
}
