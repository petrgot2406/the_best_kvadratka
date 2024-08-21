#include <stdio.h>
#include <math.h>
#include <TXLib.h>

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

void InputABC(float *a, float *b, float *c);
bool SpaceBeforeEndl();
float Discriminant(float a, float b, float c);
bool IsClose(float x, float y);
void SolveQuad(float a, float b, float c, int* colvo, float* x1, float* x2);
void SolveLinear(float b, float c, int* colvo, float* x1);
void AnswerOutput(int colvo, float x1, float x2);
bool RunTest(int numtest, float a, float b, float c, float x1exp, float x2exp, int colvoexp);
bool RunAllTests();

int main() {
    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int colvo = 0;
    if (RunAllTests() == true) {
        printf("All tests are passed\n");
    }
    printf("Введите a, b, c: ");
    InputABC(&a, &b, &c);
    SolveQuad(a, b, c, &colvo, &x1, &x2);
    AnswerOutput(colvo, x1, x2);
    return 0;
}

void InputABC(float *a, float *b, float *c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    while (scanf("%f %f %f", a, b, c) != 3 || !SpaceBeforeEndl()) {
        while (getchar() != '\n') {}
        printf("Введите ещё раз\n");
    }
}

bool SpaceBeforeEndl() {
    while (getchar() != '\n') {
        if (getchar() != ' ') {
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

bool RunTest(int numtest, float a, float b, float c, float x1exp, float x2exp, int colvoexp) {
    float x1 = 0, x2 = 0;
    int colvo = 0;
    SolveQuad(a, b, c, &colvo, &x1, &x2);
    if ((abs(colvo - colvoexp) >= EPS) or (fabs(x1 - x1exp) >= EPS) or (fabs(x2 - x2exp) >= EPS)) {
        printf("ErrorTest %d: a = %g, b = %g, c = %g, x1 = %g, x2 = %g, colvo = %d\n", numtest, a, b, c, x1, x2, colvo);
        printf("Expected: x1 = %g, x2 = %g, colvo = %d\n", x1exp, x2exp, colvoexp);
        return false;
    }
    return true;
}

bool RunAllTests() {
    if (!RunTest(1, 0, 0, 0, 0, 0, INF_NUM_OF_ROOTS)) return false;

    if (!RunTest(2, 1, 1, 1, 0, 0, 0)) return false;

    if (!RunTest(3, 0, 1, 1, -1, 0, 1)) return false;

    if (!RunTest(4, 1, 0, -4, -2, 2, 2)) return false;

    if (!RunTest(5, 1, 1, -12, -4, 3, 2)) return false;

    if (!RunTest(6, 0, 0, 7, 0, 0, 0)) return false;

    if (!RunTest(7, 1, 1, -2, -2, 1, 2)) return false;

    if (!RunTest(8, 0, 4, -4, 1, 0, 1)) return false;

    if (!RunTest(9, 1, 1, 0, -1, 0, 2)) return false;

    if (!RunTest(10, 1, 0, 0, 0, 0, 1)) return false;

    return true;
}
