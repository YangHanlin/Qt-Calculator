#include "CalculatorSettings.h"

#include <QString>
#include <QDateTime>

const QString defaultAuthor = "Yang Hanlin";
const QString defaultProgramName = "Calculator";
const QString defaultProgramVersion = "0.0";
const QString defaultOriginalButtonStyle = "background-color: #3c4144\n";
const QString defaultPressedButtonStyle = "background-color: #232627\n";

CalculatorSettings::CalculatorSettings()
    : author(defaultAuthor),
      programName(defaultProgramName),
      programVersion(defaultProgramVersion),
      originalButtonStyle(defaultOriginalButtonStyle),
      pressedButtonStyle(defaultPressedButtonStyle)
{}

void CalculatorSettings::onProgramNameRequested(QString& target) const {
    target = programName;
}

void CalculatorSettings::onAboutInfoStrRequested(QString& target) const {
    target = programName + " v" + programVersion + " - Copyright (C) " + QDateTime::currentDateTime().toString("yyyy") + " " + author + ".";
}

void CalculatorSettings::onOriginalButtonStyleRequested(QString& target) const {
    target = originalButtonStyle;
}

void CalculatorSettings::onPressedButtonStyleRequested(QString& target) const {
    target = pressedButtonStyle;
}
