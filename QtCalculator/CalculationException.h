#pragma once

#include <QException>
#include <QString>

class CalculationException : public QException {
public:
    CalculationException(QString description = "Unknown CalculationException instance");
    virtual QString description() const;
private:
    QString desp;
};

class CalculationLogicError : public CalculationException {
public:
    CalculationLogicError(QString description = "Unknown CalculationLogicError instance");
};

class CalculationRuntimeError : public CalculationException {
public:
    CalculationRuntimeError(QString description = "Unknown CalculationRuntimeError instance");
};
