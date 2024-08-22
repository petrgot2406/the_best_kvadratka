#include <stdio.h>
#include <math.h>
#include <TXLib.h>

struct UnitTest {
    int numtest;
    float a, b, c;
    float x1exp, x2exp;
    int colvoexp;
};

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

void InputABC(float* a, float* b, float* c, bool* NoDate);
bool SpaceBeforeEndl();
float Discriminant(float a, float b, float c);
bool IsClose(float x, float y);
void SolveQuad(float a, float b, float c, int* colvo, float* x1, float* x2);
void SolveLinear(float b, float c, int* colvo, float* x1);
void AnswerOutput(int colvo, float x1, float x2);
bool RunTest(UnitTest* test);
bool RunAllTests(UnitTest* test1, UnitTest* test2, UnitTest* test3, UnitTest* test4, UnitTest* test5, UnitTest* test6, UnitTest* test7, UnitTest* test8, UnitTest* test9, UnitTest* test10);

int main() {
    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int colvo = 0;
    bool NoDate = false;
    struct UnitTest test1 = {1, 0, 0, 0, 0, 0, INF_NUM_OF_ROOTS};
    struct UnitTest test2 = {2, 1, 1, 1, 0, 0, 0};
    struct UnitTest test3 = {3, 0, 1, 1, -1, 0, 1};
    struct UnitTest test4 = {4, 1, 0, -4, -2, 2, 2};
    struct UnitTest test5 = {5, 1, 1, -12, -4, 3, 2};
    struct UnitTest test6 = {6, 0, 0, 7, 0, 0, 0};
    struct UnitTest test7 = {7, 1, 1, -2, -2, 1, 2};
    struct UnitTest test8 = {8, 0, 4, -4, 1, 0, 1};
    struct UnitTest test9 = {9, 1, 1, 0, -1, 0, 2};
    struct UnitTest test10 = {10, 1, 0, 0, 0, 0, 1};
    if (RunAllTests(&test1, &test2, &test3, &test4, &test5, &test6, &test7, &test8, &test9, &test10)) {
        printf("All tests are passed\n");
    }
    printf("Введите a, b, c: ");

    InputABC(&a, &b, &c, &NoDate);
    if (NoDate) {
        return 1;
    }
    SolveQuad(a, b, c, &colvo, &x1, &x2);
    AnswerOutput(colvo, x1, x2);
    return 0;
}

void InputABC(float* a, float* b, float* c, bool* NoDate) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    int symbol = 0;
    while (scanf("%f %f %f", a, b, c) != 3 || !SpaceBeforeEndl()) {
        if (getchar() == EOF || getchar() == '\n') {
            printf("Недостаточно данных!");
            *NoDate = true;
            break;
        }
        while ((symbol = getchar()) != '\n' || symbol != EOF || symbol == ' ') {}
        printf("Введите ещё раз\n");
    }
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

float Discriminant(float a, float b, float c) {
    return b * b - 4 * a * c;
}

bool IsClose(float x, float y) {
    if (fabs(x - y) < EPS) {
        return true;
    }
    return false;
}

void SolveQuad(float a, float b, float c, int* colvo, float* x1, float* x2) {
    assert(x1 != NULL);
    assert(x2 != NULL);
    if (IsClose(a, 0)) {
        SolveLinear(b, c, colvo, x1);
    } else {
        float D = 0;
        D = Discriminant(a, b, c);
        if (D < 0) {
            *colvo = 0;
        } else {
            if (IsClose(D, 0)) {
                *x1 = - b / (2 * a);
                *colvo = 1;
            } else {
                *x1 = (- b - sqrtf(D)) / (2 * a);
                *x2 = (- b + sqrtf(D)) / (2 * a);
                *colvo = 2;
            }
        }
    }
}

void SolveLinear(float b, float c, int* colvo, float* x1) {
    assert(x1 != NULL);
    if (IsClose(b, 0)) {
        if (IsClose(c, 0)) {
            *colvo = INF_NUM_OF_ROOTS;
        } else {
            *colvo = 0;
        }
    } else {
        *colvo = 1;
        *x1 = - c / b;
        if (IsClose(*x1, 0)) {
            *x1 = 0;
        }
    }
}

void AnswerOutput(int colvo, float x1, float x2) {
    switch(colvo) {
        case 0: printf("нет решений");
                break;
        case 1: printf("x = %g", x1);
                break;
        case 2: printf("x1 = %g, x2 = %g", x1, x2);
                break;
        case INF_NUM_OF_ROOTS: printf("любое число");
                               break;

        default: printf("ERROR: Incorrect number of roots");
                 break;
    }
}

bool RunTest(UnitTest* test) {
    float x1 = 0, x2 = 0;
    int colvo = 0;
    SolveQuad(test->a, test->b, test->c, &colvo, &x1, &x2);
    if (!(abs(colvo - test->colvoexp) < EPS) or !(fabs(x1 - test->x1exp) < EPS) or !(fabs(x2 - test->x2exp) < EPS)) {
        printf("ErrorTest %d: a = %g, b = %g, c = %g, x1 = %g, x2 = %g, colvo = %d\n", test->numtest, test->a, test->b, test->c, x1, x2, colvo);
        printf("Expected: x1 = %g, x2 = %g, colvo = %d\n", test->x1exp, test->x2exp, test->colvoexp);
        return false;
    }
    return true;
}

bool RunAllTests(UnitTest* test1, UnitTest* test2, UnitTest* test3, UnitTest* test4, UnitTest* test5, UnitTest* test6, UnitTest* test7, UnitTest* test8, UnitTest* test9, UnitTest* test10) {
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
    return true;
}
