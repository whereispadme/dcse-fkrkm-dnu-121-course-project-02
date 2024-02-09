#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "searchadminwindow.h"
#include "createadminwindow.h"
#include "editadminwindow.h"

#include "headers.h"
#include "functions.h"

#include "admin.h"
#include "config.h"
#include "admintableviewaction.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    void closeEvent(QCloseEvent *event);

    void setAdminWindowConfig();

    void searchAdminTableView();
    void removeAdminTableView();
    void editAdminTableView();
    void resetAdminTableView();

    void setCurrentAdminLogin(QString);

signals:
    void sendSignalToMainWindowCloseEvent();

private slots:

    void getSignalFromSearchAdminWindowCloseEvent();
    void getSignalFromSearchAdminWindowAppyPushButtonClicked();

    void getSignalFromCreateAdminWindowCloseEvent();
    void getSignalFromCreateAdminWindowAppyPushButtonClicked();

    void getSignalFromEditAdminWindowCloseEvent();
    void getSignalFromEditAdminWindowAppyPushButtonClicked();

    void on_searchAdminPushButton_clicked();

    void on_createAdminPushButton_clicked();

    void on_removeAdminPushButton_clicked();

    void on_editAdminPushButton_clicked();

    void on_resetPushButton_clicked();

private:
    Ui::AdminWindow *ui;
    SearchAdminWindow *searchAdminWindow;
    CreateAdminWindow *createAdminWindow;
    EditAdminWindow *editAdminWindow;

    Admin admin;
    Config config;

    QSqlTableModel *model;
    QSqlQueryModel *queryModel;
    AdminTableViewAction *adminTableViewAction;

    QString currentAdminLogin;

};

#endif
