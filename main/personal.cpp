#include "personal.h"

Personal::Personal()
{

    this->passport = "";
    this->telephone = "";
    this->birthday = "";
    this->needs = "";

}

Personal::Personal(Personal *personal)
{

    this->passport = personal->passport;
    this->telephone = personal->telephone;
    this->birthday = personal->birthday;
    this->needs = personal->needs;

}

Personal::Personal(QString passport, QString telephone, QString birthday, QString needs)
{

    this->passport = passport;
    this->telephone = telephone;
    this->birthday = birthday;
    this->needs = needs;

}

Personal::~Personal()
{
}

QString Personal::getPassport()
{
    return this->passport;
}

QString Personal::getTelephone()
{
    return this->telephone;
}

QString Personal::getBirthday()
{
    return this->birthday;
}

QString Personal::getNeeds()
{
    return this->needs;
}
