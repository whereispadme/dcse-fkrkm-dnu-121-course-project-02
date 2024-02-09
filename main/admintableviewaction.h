#ifndef ADMINTABLEVIEWACTION_H
#define ADMINTABLEVIEWACTION_H

#include "mytableviewaction.h"
#include "admin.h"
#include "mymessagebox.h"

#include "headers.h"
#include "functions.h"

class AdminTableViewAction : public MyTableViewAction
{

protected:
    MyMessageBox *myMessageBox;
    Admin admin;
    QString mainWindowAdminLogin;

public:
    AdminTableViewAction(QTableView *&, QSqlTableModel *&, QSqlQueryModel *&);
    ~AdminTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void searchTableViewRecord(int);
    void createTableViewRecord();
    void removeTableViewRecord();
    void editTableViewRecord();

    void setAdmin(Admin);
    void setMainWindowAdminLogin(QString);

};

#endif
