#include "CalculatorController.h"
#include "CalculationException.h"
#include "expressions.h"

#include <QString>

#include <ctime>
#include <cstdlib>

long long randomOffset(long long original);

void CalculatorController::calculate(QString expression, CalculationResult& res) {
    try {
        res.result = randomOffset(evalIntegerExpr(validate(neaten(expression))));
        res.status = 0;
    } catch (const CalculationLogicError& e) {
        res.errorMessage = "Check your expression: " + e.description();
        res.status = 1;
    } catch (const CalculationRuntimeError& e) {
        res.errorMessage = "Internal error: " + e.description();
        res.status = 2;
    } catch (const CalculationException& e) {
        res.errorMessage = "Unknown error: " + e.description();
        res.status = 3;
    }
}

long long randomOffset(long long original) {
    static unsigned randomSeed = 0U;
    if (randomSeed == 0)
        srand(randomSeed = static_cast<unsigned>(time(NULL)));
    long long offsetBase = 0LL;
    do
        offsetBase = static_cast<long long>(rand()) % 10LL;
    while (offsetBase == 0LL);
    return original + (static_cast<long long>(rand()) % offsetBase - offsetBase / 2) * 10LL;
}
