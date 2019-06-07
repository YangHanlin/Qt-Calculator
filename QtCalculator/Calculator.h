#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QMap>
#include <QPushButton>
#include "ui_Calculator.h"

class Calculator : public QMainWindow {

	Q_OBJECT

public:
	Calculator(QWidget *parent = Q_NULLPTR);
    void initWidgets();

signals:
    void fetchCaptionStr(QString& target);
    void fetchAboutInfoStr(QString& target);

private slots:
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();

private:
	Ui::CalculatorClass ui;
    QString aboutInfoStr;
    QString captionStr;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event); // With bug! (should not judge by key())

    void initKeyToButton(QMap<int, QPushButton*>& target);
};
