#include "CalculatorController.h"

// Expression.cpp -- START

#include <string>
#include <map>
#include <set>
#include <stack>
#include <stdexcept>

using std::string;
using std::map;
using std::set;
using std::stack;
using std::exception;
using std::logic_error;
using std::runtime_error;

const map<char, int> inStackPriority = {
    {'+', 2}, {'-', 2},
    {'*', 3}, {'/', 3}, {'%', 3},
    {'(', 1}, {')', 4}
};

const map<char, int> outOfStackPriority = {
    {'+', 2}, {'-', 2},
    {'*', 3}, {'/', 3}, {'%', 3},
    {'(', 4}, {')', 1}
};

const set<string> validOperatorCombinations = {
    " (", " +", " -",
    "+(",
    "-(",
    "*(",
    "/(",
    "%(",
    "()", "((", "(+", "(-",
    ")+", ")-", ")*", ")/", ")%", "))", ") "
};

void neaten(string& expr);
void validate(const string& expr);
long long operate(long long a, char op, long long b);

long long evalIntegerExpr(string expr) {
    neaten(expr);
    try {
        validate(expr);
    } catch (const exception& e) {
        throw;
    }
    stack<char> operators;
    stack<long long> operands;
    long long currentOperand = 0;
    bool insideOperand = false;
    char lastOperator = '\0';
    for (string::iterator iter = expr.begin(); iter != expr.end(); ++iter) {
        char currentCharacter = *iter;
        if (isdigit(currentCharacter)) {
            currentOperand = currentOperand * 10 + (currentCharacter - '0');
            insideOperand = true;
            continue;
        }
        if (currentCharacter != '(' && lastOperator != ')') {
            operands.push(currentOperand);
            currentOperand = 0;
            insideOperand = false;
        }
        map<char, int>::const_iterator currentOutIterator = outOfStackPriority.find(currentCharacter);
        if (currentOutIterator == outOfStackPriority.end()) {
            char errMsg[] = "Invalid token \'?\'";
            errMsg[15] = currentCharacter;
            throw logic_error(errMsg);
        }
        if (!operators.empty()) {
            map<char, int>::const_iterator currentInIterator = inStackPriority.find(operators.top());
            while (currentOutIterator->second <= currentInIterator->second) {
                char op = operators.top();
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
        char op = operators.top();
        operands.push(operate(a, op, b));
        operators.pop();
    }
    return operands.top();
}

void neaten(string& expr) {
    for (string::iterator iter = expr.begin(); iter != expr.end(); ) {
        if (isspace(*iter))
            iter = expr.erase(iter);
        else
            ++iter;
    }
    return;
}

void validate(const string& expr) {
    if (expr.empty())
        throw logic_error("Empty expression");
    int bracketValue = 0;
    if (!isdigit(expr.front())) {
        char combination[] = " ?";
        combination[1] = expr.front();
        if (validOperatorCombinations.find(combination) == validOperatorCombinations.end()) {
            char errMsg[] = "Invalid token \'?\' at this position";
            errMsg[15] = expr.front();
            throw logic_error(errMsg);
        }
        if (expr.front() == '(')
            ++bracketValue;
        else if (expr.front() == ')')
            --bracketValue;
        if (bracketValue < 0)
            throw logic_error("Unmatched brackets");
    }
    for (string::const_iterator iter = expr.begin() + 1; iter != expr.end(); ++iter) {
        if (isdigit(*iter))
            continue;
        if (*iter == '(')
            ++bracketValue;
        else if (*iter == ')')
            --bracketValue;
        if (bracketValue < 0)
            throw logic_error("Unmatched brackets");
        if (isdigit(*(iter - 1)))
            continue;
        char combination[] = "??";
        combination[0] = *(iter - 1);
        combination[1] = *iter;
        if (validOperatorCombinations.find(combination) == validOperatorCombinations.end()) {
            char errMsg[] = "Invalid operator combination \'??\'";
            errMsg[30] = *(iter - 1);
            errMsg[31] = *iter;
            throw logic_error(errMsg);
        }
    }
    if (!isdigit(expr.back())) {
        char combination[] = "? ";
        combination[0] = expr.back();
        if (validOperatorCombinations.find(combination) == validOperatorCombinations.end()) {
            char errMsg[] = "Invalid token \'?\' at this position";
            errMsg[15] = expr.back();
            throw logic_error(errMsg);
        }
    }
    if (bracketValue != 0)
        throw logic_error("Unmatched brackets");
    return;
}

long long operate(long long a, char op, long long b) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw logic_error("Cannot divide by 0");
        return a / b;
    case '%':
        if (b == 0)
            throw logic_error("Cannot divide by 0");
        return a % b;
    default:
        char errMsg[] = "Unexpected operator \'?\' in calculation";
        errMsg[21] = op;
        throw runtime_error(errMsg);
    }
}

// END

void CalculatorController::calculate(QString expression, CalculationResult& res) {
    try {
        res.result = evalIntegerExpr(expression.toStdString());
        res.status = 0;
    } catch (const exception& e) {
        res.errorMessage = e.what();
        res.status = 1;
    }
}
