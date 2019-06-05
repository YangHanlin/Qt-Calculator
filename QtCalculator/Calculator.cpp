#include "Calculator.h"

Calculator::Calculator(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QWidget::setWindowFlags(Qt::FramelessWindowHint);
}
 