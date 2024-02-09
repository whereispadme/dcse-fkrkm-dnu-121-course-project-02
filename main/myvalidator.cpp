#include "myvalidator.h"

MyValidator::MyValidator()
{

    this->validator = nullptr;

}

MyValidator::~MyValidator()
{

    if(this->validator != nullptr)
        delete validator;

}

void MyValidator::setLoginLineEditValidator(QLineEdit *&lineEdit)
{

    QRegularExpression regexLogin("^[a-zA-Z0-9]{6,20}$");
    QValidator *validator = new QRegularExpressionValidator(regexLogin);

    lineEdit->setValidator(validator);

}

void MyValidator::setPasswordLineEditValidator(QLineEdit *&lineEdit)
{

    QRegularExpression regexPassword("^[a-zA-Z0-9]{8,20}$");
    QValidator *validator = new QRegularExpressionValidator(regexPassword);

    lineEdit->setValidator(validator);

}

void MyValidator::setIntegerLineEditValidator(QList<QLineEdit *> &listQLineEdit)
{

    QRegularExpression regexInteger("^[0-9]{10}$");
    QValidator *validator = new QRegularExpressionValidator(regexInteger);

    for(long long i = 0; i < listQLineEdit.size(); ++i)
    {

        listQLineEdit[i]->setValidator(validator);

    }

    listQLineEdit.clear();

}

void MyValidator::setLatinLineEditValidator(QList<QLineEdit *> &listQLineEdit)
{

    QRegularExpression regexLatin("^[a-zA-Z0-9]{20}$");
    regexLatin.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);
    QValidator *validator = new QRegularExpressionValidator(regexLatin);
    validator->setLocale(QLocale::Latin);

    for(long long i = 0; i < listQLineEdit.size(); ++i)
    {

        listQLineEdit[i]->setValidator(validator);

    }

    listQLineEdit.clear();

}

void MyValidator::setCyrillicLineEditValidator(QList<QLineEdit *> &listQLineEdit)
{

    QRegularExpression regexCyrillic ("^[а-яА-яа-яА-яІіЇїЄє]{20}$");
    regexCyrillic.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);
    QValidator *validator  = new QRegularExpressionValidator(regexCyrillic);
    validator->setLocale(QLocale::AnyLanguage);

    for(long long i = 0; i < listQLineEdit.size(); ++i)
    {

        listQLineEdit[i]->setValidator(validator);

    }

    listQLineEdit.clear();

}

void MyValidator::setIntegerLineEditValidator(QList<QLineEdit *> & listQLineEdit, int size)
{

    QRegularExpression regexInteger("^[0-9]{" + QString::number(size) + "}$");
    QValidator *validator = new QRegularExpressionValidator(regexInteger);

    for(long long i = 0; i < listQLineEdit.size(); ++i)
    {

        listQLineEdit[i]->setValidator(validator);

    }

    listQLineEdit.clear();

}

void MyValidator::setCyrillicLineEditValidator(QList<QLineEdit *> &listQLineEdit, int size)
{

    QRegularExpression regexCyrillic ("^[а-яА-яа-яА-яІіЇїЄє]{" + QString::number(size) + "}$");
    regexCyrillic.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);
    QValidator *validator  = new QRegularExpressionValidator(regexCyrillic);
    validator->setLocale(QLocale::AnyLanguage);

    for(long long i = 0; i < listQLineEdit.size(); ++i)
    {

        listQLineEdit[i]->setValidator(validator);

    }

    listQLineEdit.clear();

}
