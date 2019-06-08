#pragma once

#include <QString>

long long evalIntegerExpr(QString expr);
QString& neaten(QString& expr);
const QString& validate(const QString& expr);
