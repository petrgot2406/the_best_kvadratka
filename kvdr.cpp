#include <stdio.h>
#include <math.h>
#include <TXLib.h>

const float EPS = 1e-9f;
const int INF_NUM_OF_ROOTS = -1;

float Discriminant(float a, float b, float c);
bool IsClose(float x, float y);
void SolveQuad(float a, float b, float c, int* colvo, float* x1, float* x2);
void LinUravn(float b, float c, int* colvo, float* x1);
void AnswerOutput(int* colvo, float* x1, float* x2);

int main() {
    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int colvo = 0;
    printf("Введите a, b, c: ");
    scanf("%f %f %f", &a, &b, &c);
    SolveQuad(a, b, c, &colvo, &x1, &x2);
    AnswerOutput(&colvo, &x1, &x2);
    return 0;
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
    if (IsClose(a, 0)) {
        LinUravn(b, c, colvo, x1);
    } else {
        float D = 0;
        D = Discriminant(a, b, c);
        if (D < 0) {
            *colvo = 0;
        } else {
            if (IsClose(D, 0)) {
                *colvo = 1;
                *x1 = - b / (2 * a);
            } else {
                *colvo = 2;
                *x1 = (- b - sqrtf(D)) / (2 * a);
                *x2 = (- b + sqrtf(D)) / (2 * a);
                printf("%g, %g\n", *x1, *x2);
            }
        }
    }
}

void LinUravn(float b, float c, int* colvo, float* x1) {
    if (IsClose(b, 0)) {
        if (IsClose(c, 0)) {
            *colvo = INF_NUM_OF_ROOTS;
        } else {
            *colvo = 0;
        }
    } else {
        *colvo = 1;
        *x1 = - c / b;
    }
}

void AnswerOutput(int* colvo, float* x1, float* x2) {
    switch(*colvo) {
        case 0: printf("нет решений");
                break;
        case 1: printf("x = %g", *x1);
                break;
        case 2: printf("x1 = %g, x2 = %g", *x1, *x2);
                break;
        case INF_NUM_OF_ROOTS: printf("любое число");
                               break;
    }
}
