#ifndef PERSONAL_H
#define PERSONAL_H

#include <QString>

class Personal
{

protected:
    QString passport;
    QString telephone;
    QString birthday;
    QString needs;

public:
    Personal();
    Personal(Personal *);
    Personal(QString, QString, QString, QString);
    ~Personal();

    QString getPassport();
    QString getTelephone();
    QString getBirthday();
    QString getNeeds();

};

#endif
