#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QApplication>

#include <QFile>
#include <QString>

#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include <QStyleFactory>

void setApplicationConfig();
void setMainStylesheet(QString, QApplication &);

void setWarningMessageBoxAuth();
int setWarningMessageBoxDeleteRecord(QString);

void checkAuthorizationCorrectInput(QLineEdit *&, QLineEdit *&, QPushButton *&);

#endif
