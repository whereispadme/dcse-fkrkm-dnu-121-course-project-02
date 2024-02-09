#include "migrant.h"

Migrant::Migrant()
{

    this->initials.lastname = "";
    this->initials.firstname = "";
    this->initials.middlename = "";

    this->sex = "";
    this->checkin = "";
    this->previousResidence = "";

}

Migrant::Migrant(Personal personal, Initials initials, QString sex, QString checkin, QString previousResidence)
{

    this->personal = personal;
    this->initials = initials;

    this->sex = sex;
    this->checkin = checkin;
    this->previousResidence = previousResidence;

}

Migrant::~Migrant()
{

}

Personal Migrant::getPersonal()
{
    return this->personal;
}

Initials Migrant::getInitials()
{
    return this->initials;
}

QString Migrant::getSex()
{
    return this->sex;
}

QString Migrant::getCheckin()
{
    return this->checkin;
}

QString Migrant::getPreviousResidence()
{
    return this->previousResidence;
}
