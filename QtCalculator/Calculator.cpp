#include "Calculator.h"
#include "util.h"
#include "CalculationResult.h"

#include <QMouseEvent>
#include <QStyle>
#include <QMap>
#include <QPushButton>

// #include <QDebug>

QPoint originalPos;
QMap<int, QPushButton*> keyToButton;

Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent),
      lastPressedButton(Q_NULLPTR),
      status(0) {
	ui.setupUi(this);
	QWidget::setWindowFlags(Qt::FramelessWindowHint);
    initKeyToButton(keyToButton);
}

void Calculator::initWidgets() {
    emit fetchCaptionStr(captionStr);
    ui.captionLabel->setText(captionStr);
    on_actionClearButton_clicked();
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

void Calculator::keyPressEvent(QKeyEvent* event) {
    int k = event->key();
    QMap<int, QPushButton*>::iterator it = keyToButton.find(k);
    if (it != keyToButton.end()) {
        setAppearAsPressed(it.value(), true);
        lastPressedButton = it.value();
        it.value()->click();
    }
}

void Calculator::keyReleaseEvent(QKeyEvent* event) {
    int k = 0;
    k = event->key();
    QMap<int, QPushButton*>::iterator it = keyToButton.find(k);
    if (it != keyToButton.end())
        setAppearAsPressed(it.value(), false);
    if (lastPressedButton != Q_NULLPTR)
        setAppearAsPressed(lastPressedButton, false);
}

void Calculator::on_closeButton_clicked() {
    QApplication::quit();
}

void Calculator::on_minimizeButton_clicked() {
    showMinimized();
}

void Calculator::on_num0Button_clicked() {
    expressionInsert("0");
}

void Calculator::on_num1Button_clicked() {
    expressionInsert("1");
}

void Calculator::on_num2Button_clicked() {
    expressionInsert("2");
}

void Calculator::on_num3Button_clicked() {
    expressionInsert("3");
}

void Calculator::on_num4Button_clicked() {
    expressionInsert("4");
}

void Calculator::on_num5Button_clicked() {
    expressionInsert("5");
}

void Calculator::on_num6Button_clicked() {
    expressionInsert("6");
}

void Calculator::on_num7Button_clicked() {
    expressionInsert("7");
}

void Calculator::on_num8Button_clicked() {
    expressionInsert("8");
}

void Calculator::on_num9Button_clicked() {
    expressionInsert("9");
}

void Calculator::on_opPlusButton_clicked() {
    expressionInsert("+");
}

void Calculator::on_opMinusButton_clicked() {
    expressionInsert("-");
}

void Calculator::on_opMultiplyButton_clicked() {
    expressionInsert("*");
}

void Calculator::on_opDivideButton_clicked() {
    expressionInsert("/");
}

void Calculator::on_opAndButton_clicked() {
    expressionInsert("&&");
}

void Calculator::on_opOrButton_clicked() {
    expressionInsert("||");
}

void Calculator::on_opNotButton_clicked() {
    expressionInsert("!");
}

void Calculator::on_opLeftBracketButton_clicked() {
    expressionInsert("(");
}

void Calculator::on_opRightBracketButton_clicked() {
    expressionInsert(")");
}

void Calculator::on_opEqualButton_clicked() {
    if (ui.expressionLineEdit->text().isEmpty())
        return;
    CalculationResult res;
    emit fetchCalculationResult(ui.expressionLineEdit->text(), res);
    if (res.status == 0) {
        ui.resultLabel->setText(QString::number(res.result));
    } else {
        ui.resultLabel->setText("Error");
        ui.messageLabel->setText(res.errorMessage);
        status = 1;
    }
}

void Calculator::on_actionBkspButton_clicked() {
    int currentCursorPosition = ui.expressionLineEdit->cursorPosition();
    if (currentCursorPosition > 0) {
        ui.expressionLineEdit->setText(ui.expressionLineEdit->text().remove(currentCursorPosition - 1, 1));
        ui.expressionLineEdit->setCursorPosition(currentCursorPosition - 1);
    }
}

void Calculator::on_actionClearButton_clicked() {
    ui.expressionLineEdit->setText("");
    ui.resultLabel->setText("0");
}

void Calculator::on_expressionLineEdit_textChanged(const QString& text) {
    if (status != 0) {
        ui.resultLabel->setText("0");
        ui.messageLabel->setText(aboutInfoStr);
        status = 0;
    }
    int currentCursorPosition = ui.expressionLineEdit->cursorPosition();
    if (currentCursorPosition > 0 && ui.expressionLineEdit->text().at(currentCursorPosition - 1) == '=') {
        ui.expressionLineEdit->setText(ui.expressionLineEdit->text().remove(currentCursorPosition - 1, 1));
        ui.expressionLineEdit->setCursorPosition(currentCursorPosition - 1);
        ui.opEqualButton->click();
    }
}

void Calculator::initKeyToButton(QMap<int, QPushButton*>& target) {
    target.insert(Qt::Key_0,            ui.num0Button);
    target.insert(Qt::Key_1,            ui.num1Button);
    target.insert(Qt::Key_2,            ui.num2Button);
    target.insert(Qt::Key_3,            ui.num3Button);
    target.insert(Qt::Key_4,            ui.num4Button);
    target.insert(Qt::Key_5,            ui.num5Button);
    target.insert(Qt::Key_6,            ui.num6Button);
    target.insert(Qt::Key_7,            ui.num7Button);
    target.insert(Qt::Key_8,            ui.num8Button);
    target.insert(Qt::Key_9,            ui.num9Button);
    target.insert(Qt::Key_Plus,         ui.opPlusButton);
    target.insert(Qt::Key_Minus,        ui.opMinusButton);
    target.insert(Qt::Key_Asterisk,     ui.opMultiplyButton);
    target.insert(Qt::Key_Slash,        ui.opDivideButton);
    target.insert(Qt::Key_Ampersand,    ui.opAndButton);
    target.insert(Qt::Key_Bar,          ui.opOrButton);
    target.insert(Qt::Key_Exclam,       ui.opNotButton);
    target.insert(Qt::Key_ParenLeft,    ui.opLeftBracketButton);
    target.insert(Qt::Key_ParenRight,   ui.opRightBracketButton);
    target.insert(Qt::Key_Equal,        ui.opEqualButton);
    target.insert(Qt::Key_Enter,        ui.opEqualButton);
    target.insert(Qt::Key_Return,       ui.opEqualButton);
    target.insert(Qt::Key_Backspace,    ui.actionBkspButton);
    target.insert(Qt::Key_Escape,       ui.actionClearButton);
}

void Calculator::expressionInsert(QString s) {
    int currentCursorPosition = ui.expressionLineEdit->cursorPosition();
    ui.expressionLineEdit->setText(ui.expressionLineEdit->text().insert(currentCursorPosition, s));
    ui.expressionLineEdit->setCursorPosition(currentCursorPosition + s.length());
}
 