#pragma once

#include <QObject>
#include <QString>

class CalculatorSettings : public QObject {

    Q_OBJECT

public:
    CalculatorSettings();

public slots:
    void onAboutInfoStrRequested(QString& target) const;

private:
    QString author;
    QString programName;
    QString programVersion;
};
