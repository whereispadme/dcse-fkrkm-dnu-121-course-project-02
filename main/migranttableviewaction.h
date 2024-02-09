#ifndef MIGRANTTABLEVIEWACTION_H
#define MIGRANTTABLEVIEWACTION_H

#include "mytableviewaction.h"
#include "mymessagebox.h"
#include "migrant.h"

#include "headers.h"
#include "functions.h"

class MigrantTableViewAction : MyTableViewAction
{

protected:
    Migrant migrant;
    MyMessageBox *myMessageBox = nullptr;

public:
    MigrantTableViewAction() {};
    MigrantTableViewAction(QTableView *&, QSqlTableModel *&, QSqlQueryModel *&);
    ~MigrantTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void searchTableViewRecord();
    void searchTableViewRecord(int);

    void createTableViewRecord();

    void createSingleTableViewRecord(Migrant migrant, QVariant myData);
    void createSingleTableViewRecordFamily(Migrant migrant, QVariant myData, int family_id);
    void createSingleTableViewRecordGroup(Migrant migrant, QVariant myData, int group_id);

    void removeTableViewRecord();
    void editTableViewRecord();

    void setMigrant(Migrant);

};


#endif
