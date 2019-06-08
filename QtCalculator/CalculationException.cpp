#include "CalculationException.h"

#include <QString>

CalculationException::CalculationException(QString description)
    : QException(),
      desp(description) {}

QString CalculationException::description() const {
    return desp;
}

CalculationLogicError::CalculationLogicError(QString description)
    : CalculationException(description) {}

CalculationRuntimeError::CalculationRuntimeError(QString description)
    : CalculationException(description) {}
