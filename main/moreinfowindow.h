#ifndef MOREINFOWINDOW_H
#define MOREINFOWINDOW_H

#include "migrant.h"
#include "migranttableviewaction.h"
#include "centertableviewaction.h"

#include "headers.h"
#include "functions.h"

namespace Ui {
class MoreInfoWindow;
}

class MoreInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MoreInfoWindow(QWidget *parent = nullptr);
    ~MoreInfoWindow();

    void closeEvent(QCloseEvent *event);

    void setMigrantId(int, int, int);
    void setFamilyGroupTableViewHeadersData();


signals:
    void sendSignalToMainWindowCloseEvent();

private:
    Ui::MoreInfoWindow *ui;

    Migrant *migrant;

    QSqlQueryModel *personalQueryModel;
    QSqlQueryModel *familyGroupQueryModel;

    int migrant_id;

};

#endif
