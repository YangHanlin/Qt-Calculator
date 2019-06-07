#include "Calculator.h"
#include "util.h"

#include <QMouseEvent>
#include <QStyle>
#include <QMap>
#include <QPushButton>

QPoint originalPos;
QMap<int, QPushButton*> keyToButton;

Calculator::Calculator(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QWidget::setWindowFlags(Qt::FramelessWindowHint);
    initKeyToButton(keyToButton);
}

void Calculator::initWidgets() {
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

void Calculator::keyPressEvent(QKeyEvent* event) {
    int k = event->key();
    QMap<int, QPushButton*>::iterator it = keyToButton.find(k);
    if (it != keyToButton.end()) {
        setAppearAsPressed(it.value(), true);
        it.value()->click();
    }
}

void Calculator::keyReleaseEvent(QKeyEvent* event) {
    int k = event->key();
    QMap<int, QPushButton*>::iterator it = keyToButton.find(k);
    if (it != keyToButton.end())
        setAppearAsPressed(it.value(), false);
}

void Calculator::on_closeButton_clicked() {
    QApplication::quit();
}

void Calculator::on_minimizeButton_clicked() {
    showMinimized();
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
 