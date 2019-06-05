#include "Calculator.h"

Calculator::Calculator(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QWidget::setWindowFlags(Qt::FramelessWindowHint);
}

void Calculator::on_closeButton_clicked() {
    QApplication::quit();
}

void Calculator::on_minimizeButton_clicked() {
    showMinimized();
}
 