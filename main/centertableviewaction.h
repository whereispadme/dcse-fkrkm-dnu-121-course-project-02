#ifndef CENTERTABLEVIEWACTION_H
#define CENTERTABLEVIEWACTION_H

#include "mytableviewaction.h"
#include "mymessagebox.h"
#include "center.h"

#include "headers.h"
#include "functions.h"

class CenterTableViewAction : MyTableViewAction
{

protected:
    Center center;
    MyMessageBox *myMessageBox;

public:
    CenterTableViewAction(QTableView *&, QSqlTableModel *&, QSqlQueryModel *&);
    ~CenterTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void searchTableViewRecord(int);
    void createTableViewRecord();
    void removeTableViewRecord();
    void editTableViewRecord();

    void setTableViewAvailablePlaces(int);

    void setCenter(Center);

};

#endif
