#pragma once

#include <QObject>
#include <QString>

class CalculatorSettings : public QObject {

    Q_OBJECT

public:
    CalculatorSettings();

public slots:
    void onProgramNameRequested(QString& target) const;
    void onAboutInfoStrRequested(QString& target) const;
    void onOriginalButtonStyleRequested(QString& target) const;
    void onPressedButtonStyleRequested(QString& target) const;

private:
    QString author;
    QString programName;
    QString programVersion;
    QString originalButtonStyle;
    QString pressedButtonStyle;
};
