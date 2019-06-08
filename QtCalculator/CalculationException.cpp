#include "CalculationException.h"

#include <QString>

CalculationException::CalculationException(QString description)
    : QException(),
      desp(description) {}

const char* CalculationException::what() const {
    return desp.toStdString().c_str();
}

QString CalculationException::description() const {
    return desp;
}

CalculationLogicError::CalculationLogicError(QString description)
    : CalculationException(description) {}
