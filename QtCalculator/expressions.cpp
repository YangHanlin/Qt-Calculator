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
    " (", " +", " -", " !", " n", "  ",
    "+(", "++", "+-", "+!", "+n",
    "-(", "-+", "--", "-!", "-n",
    "*(", "*+", "*-", "*!", "*n",
    "/(", "/+", "/-", "/!", "/n",
    "%(", "%+", "%-", "%!", "%n",
    "&(", "&+", "&-", "&!", "&n",
    "|(", "|+", "|-", "|!", "|n",
    "!(", "!+", "!-", "!!", "!n",
    "((", "(+", "(-", "(!", "(n",
    ")+", ")-", ")*", ")/", ")%", "))", ") ",
    "n+", "n-", "n*", "n/", "n%", "n&", "n|", "n!", "n)", "nn", "n "
};

const QMap<QChar, QString> friendlyDescriptions = {
    {'+', "operators"},
    {'-', "operators"},
    {'*', "operators"},
    {'/', "operators"},
    {'%', "operators"},
    {'&', "operators"},
    {'|', "operators"},
    {'!', "operators"},
    {'(', "brackets"},
    {')', "brackets"},
    {'n', "numbers"}
};

long long operate(long long a, QChar op, long long b);

long long evalIntegerExpr(QString expr) {
    if (expr.isEmpty()) // not elegant?
        return 0LL;
    QStack<QChar> operators;
    QStack<long long> operands;
    long long currentOperand = 0;
    bool insideOperand = false, rightAssociative = false;
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
            rightAssociative = !insideOperand; // because (here) unary operators are all left-associative operators (and vice versa)
            insideOperand = false;
        }
        QMap<QChar, int>::ConstIterator currentOutIterator = outOfStackPriority.find(currentCharacter);
        if (currentOutIterator == outOfStackPriority.end())
            throw CalculationRuntimeError("Unexpected token \'" + static_cast<QString>(currentCharacter) + "\'");
        if (!operators.empty()) {
            QMap<QChar, int>::ConstIterator currentInIterator = inStackPriority.find(operators.top());
            while (currentOutIterator.value() < currentInIterator.value() || (currentOutIterator.value() == currentInIterator.value() && !rightAssociative)) {
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
    int bracketValue = 0;
    QString combination = "  ";
    for (QString::ConstIterator iter = expr.begin(); iter != expr.end(); ++iter) {
        if (*iter == '(')
            ++bracketValue;
        else if (*iter == ')')
            --bracketValue;
        if (bracketValue < 0)
            throw CalculationLogicError("Unmatched brackets");
        QChar addition = '\0';
        if (iter->isDigit())
            addition = 'n';
        else if (*iter == 'n')
            throw CalculationLogicError("Invalid token \'n\'");
        else
            addition = *iter;
        if (!validCombinations.contains(combination.remove(0, 1).append(addition))) {
            QMap<QChar, QString>::ConstIterator foundIter0 = friendlyDescriptions.find(combination[0]);
            if (foundIter0 == friendlyDescriptions.end()) {
                if (combination[0] == ' ')
                    throw CalculationLogicError("Invalid token \'" + static_cast<QString>(combination[1]) + "\' at the beginning");
                else
                    throw CalculationLogicError("Invalid token \'" + static_cast<QString>(combination[0]) + "\'");
            }
            QMap<QChar, QString>::ConstIterator foundIter1 = friendlyDescriptions.find(combination[1]);
            if (foundIter1 == friendlyDescriptions.end())
                throw CalculationLogicError("Invalid token \'" + static_cast<QString>(combination[1]) + "\'");
            throw CalculationLogicError("Invalid combination of " + foundIter0.value() + " and " + foundIter1.value());
        }
    }
    if (bracketValue != 0)
        throw CalculationLogicError("Unmatched brackets");
    if (!validCombinations.contains(combination.remove(0, 1).append(' ')))
        throw CalculationLogicError("Invalid token \'" + combination[0] + "\' in the end");
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
