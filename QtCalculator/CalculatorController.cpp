#include "CalculatorController.h"
#include "CalculationException.h"
#include "expressions.h"

#include <QString>

void CalculatorController::calculate(QString expression, CalculationResult& res) {
    try {
        res.result = evalIntegerExpr(validate(neaten(expression)));
        res.status = 0;
    } catch (const CalculationException& e) {
        res.errorMessage = "Please check your expression: " + e.description();
        res.status = 1;
    }
}
