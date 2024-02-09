#ifndef CENTER_H
#define CENTER_H

#include <QString>

class Center
{

protected:
    QString street;
    QString house;
    QString generalPlacesAmount;
    QString availablePlacesAmount;

public:
    Center();
    Center(Center *);
    Center(QString, QString, QString, QString);
    ~Center();

    QString getStreet();
    QString getHouse();
    QString getGeneralPlacesAmount();
    QString getAvailablePlacesAmount();

    void setStreet(QString);
    void setHouse(QString);
    void setGeneralPlacesAmount(QString);
    void setAvailablePlacesAmount(QString);

};

#endif
