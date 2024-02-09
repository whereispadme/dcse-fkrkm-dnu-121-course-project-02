#ifndef MYVALIDATOR_H
#define MYVALIDATOR_H

#include <QList>
#include <QLineEdit>

#include <QValidator>
#include <QRegularExpression>

class MyValidator
{

protected:
    QValidator *validator;

public:
    MyValidator();
    ~MyValidator();

    void setLoginLineEditValidator(QLineEdit *&);
    void setPasswordLineEditValidator(QLineEdit *&);

    void setIntegerLineEditValidator(QList<QLineEdit *> &);
    void setLatinLineEditValidator(QList<QLineEdit *> &);
    void setCyrillicLineEditValidator(QList<QLineEdit *> &);

    void setIntegerLineEditValidator(QList<QLineEdit *> &, int);
    void setCyrillicLineEditValidator(QList<QLineEdit *> &, int);

};

#endif
