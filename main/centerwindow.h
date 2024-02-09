#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include "createcenterwindow.h"
#include "editcenterwindow.h"

#include "headers.h"
#include "functions.h"

#include "center.h"
#include "centertableviewaction.h"

namespace Ui {
class CenterWindow;
}

class CenterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CenterWindow(QWidget *parent = nullptr);
    ~CenterWindow();

    void closeEvent(QCloseEvent *event);

    void setCenterWindowConfig();

    void searchAdminTableView();
    void removeAdminTableView();
    void editAdminTableView();
    void resetAdminTableView();
    void setSearchParam();

signals:
    void sendSignalToMainWindowCloseEvent();

public slots:
    void getSignalFromMainWindowOpen();

private slots:

    void getSignalFromCreateCenterWindowCloseEvent();
    void getSignalFromCreateCenterWindowAppyPushButtonClicked();

    void getSignalFromEditCenterWindowCloseEvent();
    void getSignalFromEditCenterWindowAppyPushButtonClicked();

    void on_createCenterPushButton_clicked();

    void on_editCenterPushButton_clicked();

    void on_removeCenterPushButton_clicked();

    void on_resetPushButton_clicked();

private:
    Ui::CenterWindow *ui;
    CreateCenterWindow *createCenterWindow;
    EditCenterWindow *editCenterWindow;

    Center center;

    QSqlTableModel *model;
    QSqlQueryModel *queryModel;
    CenterTableViewAction *centerTableViewAction;

};

#endif
