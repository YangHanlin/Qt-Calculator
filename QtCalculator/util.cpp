#include "util.h"

#include <QPushButton>
#include <QVariant>
#include <QStyle>

void setAppearAsPressed(QPushButton* button, bool appearAsPressed) {
    button->setProperty("appearAsPressed", appearAsPressed);
    button->style()->unpolish(button);
    button->style()->polish(button);
}
