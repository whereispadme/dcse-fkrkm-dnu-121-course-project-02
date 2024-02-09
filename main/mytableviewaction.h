#ifndef MYTABLEVIEWACTION_H
#define MYTABLEVIEWACTION_H

#include "headers.h"

class MyTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    virtual ~MyTableViewAction() = default;

    virtual void setTableView() = 0;
    virtual void setSqlTableModelHeadersData() = 0;
    virtual void setSqlQueryModelHeadersData() = 0;

    virtual void searchTableViewRecord(int) = 0;
    virtual void createTableViewRecord() = 0;
    virtual void removeTableViewRecord() = 0;
    virtual void editTableViewRecord() = 0;

};

#endif
