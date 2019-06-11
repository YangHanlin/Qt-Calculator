// FIXME: There are some bugs

#include "expressions.h"
#include "CalculationException.h"

#include <QString>
#include <QChar>
#include <QMap>
#include <QSet>
#include <QStack>

#include <QDebug> // TODO: Delete this on release

const QMap<QChar, int> inStackPriority = {
    {'+', 3}, {'-', 3},
    {'*', 4}, {'/', 4}, {'%', 4},
    {'&', 2}, {'|', 1}, {'!', 5},
    {'(', 0}, {')', 6}
};

const QMap<QChar, int> outOfStackPriority = {
    {'+', 3}, {'-', 3},
    {'*', 4}, {'/', 4}, {'%', 4},
    {'&', 2}, {'|', 1}, {'!', 5},
    {'(', 6}, {')', 0}
};

const QSet<QString> validCombinations = {
    " (", " +", " -", " !", " 0",
    "+(", "++", "+-", "+!", "+0",
    "-(", "-+", "--", "-!", "-0",
    "*(", "*+", "*-", "*!", "*0",
    "/(", "/+", "/-", "/!", "/0",
    "%(", "%+", "%-", "%!", "%0",
    "&(", "&+", "&-", "&!", "&0",
    "|(", "|+", "|-", "|!", "|0",
    "!(", "!+", "!-", "!!", "!0",
    "((", "(+", "(-", "(!", "(0",
    ")+", ")-", ")*", ")/", ")%", "))", ") ",
    "0+", "0-", "0*", "0/", "0%", "0&", "0|", "0!", "0)", "0 "
};

long long operate(long long a, QChar op, long long b);

long long evalIntegerExpr(QString expr) {
    QStack<QChar> operators;
    QStack<long long> operands;
    long long currentOperand = 0;
    bool insideOperand = false;
    QChar lastOperator = '\0';
    for (QString::Iterator iter = expr.begin(); iter != expr.end(); ++iter) {
        QChar currentCharacter = *iter;
        if (currentCharacter.isDigit()) {
            currentOperand = currentOperand * 10 + currentCharacter.digitValue();
            insideOperand = true;
            continue;
        }
        if (currentCharacter != '(' && lastOperator != ')') {
            operands.push(currentOperand);
            currentOperand = 0;
            insideOperand = false;
        }
        QMap<QChar, int>::ConstIterator currentOutIterator = outOfStackPriority.find(currentCharacter);
        if (currentOutIterator == outOfStackPriority.end())
            throw CalculationLogicError("Invalid token \'" + static_cast<QString>(currentCharacter) + "\'");
        if (!operators.empty()) {
            QMap<QChar, int>::ConstIterator currentInIterator = inStackPriority.find(operators.top());
            while (currentOutIterator.value() <= currentInIterator.value()) {
                QChar op = operators.top();
                operators.pop();
                if (op == '(' && currentCharacter == ')')
                    break;
                long long b = operands.top();
                operands.pop();
                long long a = operands.top();
                operands.pop();
                operands.push(operate(a, op, b));
                if (operators.empty())
                    break;
                else
                    currentInIterator = inStackPriority.find(operators.top());
            }
        }
        if (currentCharacter != ')')
            operators.push(currentCharacter);
        lastOperator = currentCharacter;
    }
    if (insideOperand) {
        operands.push(currentOperand);
        currentOperand = 0;
        insideOperand = false;
    }
    while (!operators.empty()) {
        long long b = operands.top();
        operands.pop();
        long long a = operands.top();
        operands.pop();
        QChar op = operators.top();
        operands.push(operate(a, op, b));
        operators.pop();
    }
    return operands.top();
}

QString& neaten(QString& expr) {
    for (QString::size_type i = 0; i < expr.size(); )
        if (expr.at(i).isSpace())
            expr.remove(i, 1);
        else
            ++i;
    for (QString::size_type i = 0; i < expr.size(); ++i)
        if (i + 1 < expr.size() &&
            ((expr.at(i) == '&' && expr.at(i + 1) == '&') ||
            (expr.at(i) == '|' && expr.at(i + 1) == '|')))
            expr.remove(i, 1);
    return expr;
}

const QString& validate(const QString& expr) {
    if (expr.isEmpty())
        throw CalculationLogicError("Empty expression");
    int bracketValue = 0;
    if (!expr.front().isDigit()) {
        QString combination = " " + static_cast<QString>(expr.front());
        if (validCombinations.find(combination) == validCombinations.end())
            throw CalculationLogicError("Invalid token \'" + static_cast<QString>(combination[1]) + "\' at this position");
        if (expr.front() == '(')
            ++bracketValue;
        else if (expr.front() == ')')
            --bracketValue;
        if (bracketValue < 0)
            throw CalculationLogicError("Unmatched brackets");
    }
    for (QString::ConstIterator iter = expr.begin() + 1; iter != expr.end(); ++iter) {
        if (iter->isDigit())
            continue;
        if (*iter == '(')
            ++bracketValue;
        else if (*iter == ')')
            --bracketValue;
        if (bracketValue < 0)
            throw CalculationLogicError("Unmatched brackets");
        if ((iter - 1)->isDigit())
            continue;
        QString combination = static_cast<QString>(*(iter - 1)) + *iter;
        if (validCombinations.find(combination) == validCombinations.end())
            throw CalculationLogicError("Invalid operator combination \'" + combination + "\'");
    }
    if (!expr.back().isDigit()) {
        QString combination = static_cast<QString>(expr.back()) + " ";
        if (validCombinations.find(combination) == validCombinations.end())
            throw CalculationLogicError("Invalid token \'" + static_cast<QString>(combination[0]) + "\' at this position");
    }
    if (bracketValue != 0)
        throw CalculationLogicError("Unmatched brackets");
    return expr;
}

long long operate(long long a, QChar op, long long b) {
    switch (op.toLatin1()) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw CalculationLogicError("Cannot divide by 0");
        return a / b;
    case '%':
        if (b == 0)
            throw CalculationLogicError("Cannot divide by 0");
        return a % b;
    case '&':
        return a && b;
    case '|':
        return a || b;
    case '!':
        return !b;
    default:
        throw CalculationRuntimeError("Unexpected operator \'" + static_cast<QString>(op) + "\' in calculation");
    }
}
