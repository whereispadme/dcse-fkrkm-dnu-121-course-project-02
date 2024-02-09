#ifndef MIGRANT_H
#define MIGRANT_H

#include "initials.h"

#include "center.h"
#include "family.h"
#include "group.h"
#include "personal.h"

class Migrant
{

protected:
    Personal personal;
    Initials initials;

    QString sex;
    QString checkin;
    QString previousResidence;

    QString centerAdress;

public:
    Migrant();
    Migrant(Personal, Initials, QString, QString, QString);
    ~Migrant();

    Personal getPersonal();
    Initials getInitials();

    QString getSex();
    QString getCheckin();
    QString getPreviousResidence();

};

#endif
