#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include "ui_Calculator.h"

class Calculator : public QMainWindow {

	Q_OBJECT

public:
	Calculator(QWidget *parent = Q_NULLPTR);
    void initWidgets();

signals:
    void fetchCaptionStr(QString& target);
    void fetchAboutInfoStr(QString& target);
    void fetchOriginalButtonStyle(QString& target);
    void fetchPressedButtonStyle(QString& target);

private slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();

private:
	Ui::CalculatorClass ui;
    QString aboutInfoStr;
    QString captionStr;
    QString originalButtonStyle;
    QString pressedButtonStyle;
};
