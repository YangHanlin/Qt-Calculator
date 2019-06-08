#include "CalculatorController.h"
#include "CalculationException.h"
#include "expressions.h"

#include <QString>

void CalculatorController::calculate(QString expression, CalculationResult& res) {
    try {
        neaten(expression);
        validate(expression);
        res.result = evalIntegerExpr(expression);
        res.status = 0;
    } catch (const CalculationException& e) {
        res.errorMessage = e.description();
        res.status = 1;
    }
}
