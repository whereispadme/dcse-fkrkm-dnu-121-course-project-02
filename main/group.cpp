#include "group.h"

Group::Group()
{

    this->previousResidence = "";
    this->groupPeopleAmount = 0;

}

Group::Group(Group *group)
{

    this->previousResidence = group->previousResidence;
    this->groupPeopleAmount = group->groupPeopleAmount;

}

Group::Group(QString previousResidence, unsigned int groupPeopleAmount)
{

    this->previousResidence = previousResidence;
    this->groupPeopleAmount = groupPeopleAmount;

}

Group::~Group()
{
}

QString Group::getPreviousResidence()
{
    return this->previousResidence;
}

unsigned int Group::getGroupPeopleAmount()
{
    return this->groupPeopleAmount;
}

void Group::setPreviousResidence(QString previousResidence)
{
    this->previousResidence = previousResidence;
}

void Group::setGroupPeopleAmount(unsigned int groupPeopleAmount)
{
    this->groupPeopleAmount = groupPeopleAmount;
}
