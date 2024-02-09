#ifndef FAMILY_H
#define FAMILY_H

#include <QString>

class Family
{

protected:
    QString previousResidence;
    unsigned int familyPeopleAmount;

public:
    Family();
    Family(Family *);
    Family(QString, unsigned int);
    ~Family();

    QString getPreviousResidence();
    unsigned int getFamilyPeopleAmount();

    void setPreviousResidence(QString previousResidence);
    void setFamilyPeopleAmount(unsigned int familyPeopleAmount);

};

#endif
