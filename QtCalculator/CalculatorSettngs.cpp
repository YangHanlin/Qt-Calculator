#include "CalculatorSettings.h"

#include <QString>
#include <QDateTime>

const QString defaultAuthor = "Yang Hanlin";
const QString defaultProgramName = "Calculator";
const QString defaultProgramVersion = "1.0-rc2";

CalculatorSettings::CalculatorSettings()
    : author(defaultAuthor),
      programName(defaultProgramName),
      programVersion(defaultProgramVersion) {}

void CalculatorSettings::onProgramNameRequested(QString& target) const {
    target = programName;
}

void CalculatorSettings::onAboutInfoStrRequested(QString& target) const {
    target = programName + " v" + programVersion + " - Copyright (C) " + QDateTime::currentDateTime().toString("yyyy") + " " + author + ".";
}
