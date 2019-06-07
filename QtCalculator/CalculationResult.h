#pragma once

#include <QString>

struct CalculationResult {
    int status;
    long long result;
    QString errorMessage;

    CalculationResult(int status = 0, long long result = 0LL, QString errorMessage = "");
};
