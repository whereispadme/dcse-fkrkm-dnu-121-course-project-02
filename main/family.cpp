#include "family.h"

Family::Family()
{

    this->previousResidence = "";
    this->familyPeopleAmount = 0;

}

Family::Family(Family *family)
{

    this->previousResidence = family->previousResidence;
    this->familyPeopleAmount = family->familyPeopleAmount;

}

Family::Family(QString previousResidence, unsigned int familyPeopleAmount)
{

    this->previousResidence = previousResidence;
    this->familyPeopleAmount = familyPeopleAmount;

}

Family::~Family()
{
}

QString Family::getPreviousResidence()
{

    return this->previousResidence;

}

unsigned int Family::getFamilyPeopleAmount()
{

    return this->familyPeopleAmount;

}

void Family::setPreviousResidence(QString previousResidence)
{
    this->previousResidence = previousResidence;
}

void Family::setFamilyPeopleAmount(unsigned int familyPeopleAmount)
{
    this->familyPeopleAmount = familyPeopleAmount;
}
