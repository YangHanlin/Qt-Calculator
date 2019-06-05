#include "Calculator.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <stdexcept>

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
    /* QFile mainStylesheet("main.qss");
    if (mainStylesheet.open(QFile::ReadOnly)) {
        QString mainStylesheetStr = QLatin1String(mainStylesheet.readAll());
        application.setStyleSheet(mainStylesheetStr);
    } */
	Calculator calculator;
	calculator.show();
	return application.exec();
}
