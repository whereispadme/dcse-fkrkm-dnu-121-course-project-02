#include "admin.h"

Admin::Admin()
{

    this->login = "";
    this->password = "";

}

Admin::Admin(Admin *admin)
{

    this->login = admin->login;
    this->password = admin->password;

    this->initials = admin->initials;

}

Admin::Admin(QString login, QString password, Initials initials)
{

    this->login = login;
    this->password = password;

    this->initials = initials;

}

Admin::~Admin()
{
}

QString Admin::getLogin()
{
    return this->login;
}

QString Admin::getPassword()
{
    return this->password;
}

void Admin::setLogin(QString login)
{
    this->login = login;
}

void Admin::setPassword(QString password)
{
    this->password = password;
}

void Admin::setInitials(Initials initials)
{
    this->initials = initials;
}

Initials Admin::getInitials()
{
    return this->initials;
}
