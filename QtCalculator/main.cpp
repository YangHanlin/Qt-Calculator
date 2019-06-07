#include "Calculator.h"
#include "CalculatorSettings.h"

#include <QtWidgets/QApplication>
#include <QString>
#include <QObject>

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	Calculator calculator;
    CalculatorSettings calculatorSettings;
    QObject::connect(&calculator, SIGNAL(fetchAboutInfoStr(QString&)), &calculatorSettings, SLOT(onAboutInfoStrRequested(QString&)));
    calculator.initWidgets();
	calculator.show();
	return application.exec();
}
