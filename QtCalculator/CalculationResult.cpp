#include "CalculationResult.h"

CalculationResult::CalculationResult(int status, long long result, QString errorMessage)
    : status(status),
      result(result),
      errorMessage(errorMessage) {}
