/*!
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения основных
классов, используемых в демонстрационной программе
*/

#include <math.h>
#include <TXLib.h>

/**
* @brief   Структура коэффициентов
* @param a Главный коэффициент уравнения
* @param b Второй коэффициент уравнения
* @param c Свободный член уравнения
*/

struct Coeffs {
    float a, b, c;
};

/**
* @brief        Структура решений уравнения
* @param x1     Первый корень уравнения
* @param x2     Второй корень уравнения
* @param nRoots Количество корней уравнения
*/

struct Roots {
    float x1, x2;
    int nRoots;
};

/**
* @brief            Структура тестовых коэффициентов и ожидаемых результатов
* @param Coeffs abc Тестовые коэффициенты
* @param Roots sol  Ожидаемые результаты
*/

struct UnitTest {
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
void SolveLinear(float b, float c, int* nRoots, float* x1, float* x2);
void AnswerOutput(Roots sol);
bool RunTest(int numtest, UnitTest test);
bool RunAllTests();

int main() {
    struct Coeffs abc = {0, 0, 0};
    struct Roots sol = {0, 0, 0};
    if (RunAllTests()) {
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

/**
* @brief             Функция ввода коэффициентов
* @param Coeffs *abc Вводимые коэффициенты
* @return            Корректность полученных данных
*/

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

/**
* @brief  Функция проверки наличия пробелов перед концом ввода
* @return Наличие пробелов перед концом ввода
*/

bool SpaceBeforeEndl() {
    int symbol = 0;
    while ((symbol = getchar()) != '\n' && symbol != EOF) {
        if (symbol != ' ') {
            return false;
        }
    }
    return true;
}

/**
* @brief             Функция рассчёта дискриминанта
* @param Coeffs abc  Коэффициенты
* @return            Дискриминант
*/

float Discriminant(Coeffs abc) {
    return abc.b * abc.b - 4 * abc.a * abc.c;
}

/**
* @brief   Функция проверки равенство двух действительных чисел
* @param x Первое действительное число
* @param y Второе действительное число
* @return  Равенство данных чисел
*/

bool IsClose(float x, float y) {
    if (fabs(x - y) < EPS) {
        return true;
    }
    return false;
}

/**
* @brief            Функция решения квадраного уравнения
* @param Coeffs abc Коэффициенты уравнения
* @param Roots *sol Корни уравнения и их количество
*/

void SolveQuad(Coeffs abc, Roots *sol) {
    assert(&sol->x1 != NULL);
    assert(&sol->x2 != NULL);
    if (IsClose(abc.a, 0)) {
        SolveLinear(abc.b, abc.c, &sol->nRoots, &sol->x1, &sol->x2);
    } else {
        float D = 0;
        D = Discriminant(abc);
        if (D < 0) {
            sol->nRoots = 0;
        } else {
            if (IsClose(D, 0)) {
                sol->x1 = - abc.b / (2 * abc.a);
                sol->x2 = - abc.b / (2 * abc.a);
                sol->nRoots = 1;
            } else {
                sol->x1 = (- abc.b - sqrtf(D)) / (2 * abc.a);
                sol->x2 = (- abc.b + sqrtf(D)) / (2 * abc.a);
                sol->nRoots = 2;
            }
        }
    }
}

/**
* @brief         Функция решения линейного уравнения
* @param b       Старший коэффициент уравнения
* @param c       Свободный член уравнения
* @param *nRoots Количество корней уравнения
* @param *x1     Корень уравнения
* @param *x2     Корень уравнения
*/

void SolveLinear(float b, float c, int* nRoots, float* x1, float* x2) {
    assert(nRoots != NULL);
    assert(x1 != NULL);
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
        *x2 = - c / b;
        if (IsClose(*x1, 0)) {
            *x1 = 0;
            *x2 = 0;
        }
    }
}

/**
* @brief           Функция вывода решений уравнения
* @param Roots sol Корни уравнения и их количество
*/

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

/**
* @brief               Функция прохождения теста
* @param i             Номер теста
* @param UnitTest test Тестовые коэффициенты и ожидаемые значения
* @return              Успешность прохождения теста
*/

bool RunTest(int i, UnitTest test) {
    bool succ = true;
    struct Roots testroots = {0, 0, 0};
    SolveQuad(test.abc, &testroots);
    if (abs(testroots.nRoots - test.sol.nRoots) < EPS) {
        switch(testroots.nRoots) {
            case INF_NUM_OF_ROOTS: if (IsClose(testroots.x1, 0) && IsClose(testroots.x2, 0)) {
                                        return true;
                                   } else {
                                        succ = false;
                                   }
            case 0: if (IsClose(testroots.x1, 0) && IsClose(testroots.x2, 0)) {
                        return true;
                    } else {
                        succ =  false;
                    }
            case 1: if ((fabs(testroots.x1 - test.sol.x1) < EPS) && (fabs(testroots.x2 - test.sol.x2) < EPS)) {
                        return true;
                    } else {
                        succ = false;
                    }
            case 2: if (((fabs(testroots.x1 - test.sol.x1) < EPS) && (fabs(testroots.x2 - test.sol.x2) < EPS)) || ((fabs(testroots.x1 - test.sol.x2) < EPS) && (fabs(testroots.x2 - test.sol.x1) < EPS))) {
                        return true;
                    } else {
                        succ = false;
                    }
            default: printf("Error: Coeffs are incorrect\n");
                     succ = false;
                     break;
        }
    } else {
        succ = false;
    }
    if (!succ) {
        printf("ErrorTest %d: a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nRoots = %d\n", i + 1, test.abc.a, test.abc.b, test.abc.c, testroots.x1, testroots.x2, testroots.nRoots);
        printf("Expected: x1 = %g, x2 = %g, nRoots = %d\n", test.sol.x1, test.sol.x2, test.sol.nRoots);
        return false;
    }
    return false;
}

/**
* @brief  Функция прохождения всех тестов
* @return Успешность прохождения всех тестов
*/

bool RunAllTests() {
    const int numtests = 11;
    struct UnitTest test[numtests] = {{{0, 0, 0}, {0, 0, INF_NUM_OF_ROOTS}},
                                      {{1, 1, 1}, {0, 0, 0}},
                                      {{0, 1, 1}, {-1, -1, 1}},
                                      {{1, 0, -4}, {-2, 2, 2}},
                                      {{1, 1, -12}, {-4, 3, 2}},
                                      {{0, 0, 7}, {0, 0, 0}},
                                      {{1, 1, -2}, {-2, 1, 2}},
                                      {{0, 4, -4}, {1, 1, 1}},
                                      {{1, 0, 0}, {0, 0, 1}},
                                      {{1, 1, 0.25}, {-0.5, -0.5, 1}},
                                      {{1, 1, -12}, {3, -4, 2}}};
    for (int i = 0; i < numtests; i++) {
        if (!RunTest(i, test[i])) {
            return false;
        }
    }
    return true;
}
