#include "CalculatorController.h"
#include "CalculationException.h"
#include "expressions.h"

#include <QString>

void CalculatorController::calculate(QString expression, CalculationResult& res) {
    try {
        res.result = evalIntegerExpr(validate(neaten(expression)));
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
