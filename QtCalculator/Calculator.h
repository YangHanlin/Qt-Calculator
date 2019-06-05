#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"

class Calculator : public QMainWindow {

	Q_OBJECT

public:
	Calculator(QWidget *parent = Q_NULLPTR);

private slots:
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();

private:
	Ui::CalculatorClass ui;
};
