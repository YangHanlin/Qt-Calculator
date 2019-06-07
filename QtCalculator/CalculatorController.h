#pragma once

#include "CalculationResult.h"

#include <QObject>
#include <QString>

class CalculatorController : public QObject {

    Q_OBJECT

public slots:
    void calculate(QString expression, CalculationResult& res);
};
