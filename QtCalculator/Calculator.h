#pragma once

#include "CalculationResult.h"

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
    void fetchCalculationResult(QString expression, CalculationResult& res);

private slots:
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();
    void on_num0Button_clicked();
    void on_num1Button_clicked();
    void on_num2Button_clicked();
    void on_num3Button_clicked();
    void on_num4Button_clicked();
    void on_num5Button_clicked();
    void on_num6Button_clicked();
    void on_num7Button_clicked();
    void on_num8Button_clicked();
    void on_num9Button_clicked();
    void on_opPlusButton_clicked();
    void on_opMinusButton_clicked();
    void on_opMultiplyButton_clicked();
    void on_opDivideButton_clicked();
    void on_opAndButton_clicked();
    void on_opOrButton_clicked();
    void on_opNotButton_clicked();
    void on_opLeftBracketButton_clicked();
    void on_opRightBracketButton_clicked();
    void on_opEqualButton_clicked();
    void on_actionBkspButton_clicked();
    void on_actionClearButton_clicked();
    void on_expressionLineEdit_textChanged(const QString& text);

private:
	Ui::CalculatorClass ui;
    QString aboutInfoStr;
    QString captionStr;
    QPushButton* lastPressedButton;
    int status;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    void initKeyToButton(QMap<int, QPushButton*>& target);
    void expressionInsert(QString s);
};
