#include "Calculator.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <stdexcept>

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	Calculator calculator;
	calculator.show();
	return application.exec();
}
