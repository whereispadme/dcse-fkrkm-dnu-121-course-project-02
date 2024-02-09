#include "center.h"

Center::Center()
{

    this->street = "";
    this->house = "";
    this->generalPlacesAmount = "";
    this->availablePlacesAmount = "";

}

Center::Center(Center *center)
{

    this->street = center->street;
    this->house = center->house;
    this->generalPlacesAmount = center->generalPlacesAmount;
    this->availablePlacesAmount = center->availablePlacesAmount;

}

Center::Center(QString street, QString house, QString generalPlacesAmount, QString availablePlacesAmount)
{

    this->street = street;
    this->house = house;
    this->generalPlacesAmount = generalPlacesAmount;
    this->availablePlacesAmount = availablePlacesAmount;
}

Center::~Center()
{
}

QString Center::getStreet()
{
    return this->street;
}

QString Center::getHouse()
{
    return this->house;
}

QString Center::getGeneralPlacesAmount()
{
    return this->generalPlacesAmount;
}

QString Center::getAvailablePlacesAmount()
{
    return this->availablePlacesAmount;
}

void Center::setStreet(QString street)
{
    this->street = street;
}

void Center::setHouse(QString house)
{
    this->house = house;
}

void Center::setGeneralPlacesAmount(QString generalPlacesAmount)
{
    this->generalPlacesAmount = generalPlacesAmount;
}

void Center::setAvailablePlacesAmount(QString availablePlacesAmount)
{
    this->availablePlacesAmount = availablePlacesAmount;
}
