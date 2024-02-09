#ifndef ADMIN_H
#define ADMIN_H

#include "initials.h"

class Admin
{

protected:
    QString login;
    QString password;

    Initials initials;

public:
    Admin();
    Admin(Admin *admin);
    Admin(QString, QString, Initials);
    ~Admin();

    QString getLogin();
    QString getPassword();

    void setLogin(QString);
    void setPassword(QString);
    void setInitials(Initials);

    Initials getInitials();

};

#endif
