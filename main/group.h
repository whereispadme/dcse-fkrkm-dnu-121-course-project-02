#ifndef GROUP_H
#define GROUP_H

#include <QString>

#pragma once

class Group
{

protected:
    QString previousResidence;
    unsigned int groupPeopleAmount;

public:
    Group();
    Group(Group *);
    Group(QString, unsigned int);
    ~Group();

    QString getPreviousResidence();
    unsigned int getGroupPeopleAmount();

    void setPreviousResidence(QString);
    void setGroupPeopleAmount(unsigned int);

};

#endif
