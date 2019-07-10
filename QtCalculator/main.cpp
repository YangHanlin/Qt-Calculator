#include "Calculator.h"
#include "CalculatorSettings.h"
#include "CalculatorController.h"

#include <QtWidgets/QApplication>
#include <QString>
#include <QObject>

int main(int argc, char *argv[]) {
    QCoreApplication::addLibraryPath("./");
    QApplication application(argc, argv);
    Calculator calculator;
    CalculatorSettings calculatorSettings;
    CalculatorController calculatorController;
    QObject::connect(&calculator, SIGNAL(fetchCaptionStr(QString&)),
                     &calculatorSettings, SLOT(onProgramNameRequested(QString&)));
    QObject::connect(&calculator, SIGNAL(fetchAboutInfoStr(QString&)),
                     &calculatorSettings, SLOT(onAboutInfoStrRequested(QString&)));
    QObject::connect(&calculator, SIGNAL(fetchCalculationResult(QString, CalculationResult&)),
                     &calculatorController, SLOT(calculate(QString, CalculationResult&)));
    calculator.initWidgets();
    calculator.show();
    return application.exec();
}
