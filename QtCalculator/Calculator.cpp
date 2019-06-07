#include "Calculator.h"

#include <QMouseEvent>

QPoint originalPos;

Calculator::Calculator(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QWidget::setWindowFlags(Qt::FramelessWindowHint);
}

void Calculator::initWidgets() {
    QString captionStr;
    emit fetchCaptionStr(captionStr);
    ui.captionLabel->setText(captionStr);
    ui.expressionLineEdit->setText("");
    ui.resultLabel->setText("0");
    emit fetchAboutInfoStr(aboutInfoStr);
    ui.messageLabel->setText(aboutInfoStr);
}

void Calculator::mousePressEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton)
        originalPos = event->pos();
}

void Calculator::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton)
        move(pos() + event->pos() - originalPos);
}

void Calculator::on_closeButton_clicked() {
    QApplication::quit();
}

void Calculator::on_minimizeButton_clicked() {
    showMinimized();
}
 