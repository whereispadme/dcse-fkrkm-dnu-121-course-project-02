#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authwindow.h"
#include "moreinfowindow.h"
#include "settlementwindow.h"
#include "evictwindow.h"
#include "centerwindow.h"
#include "rootapplywindow.h"
#include "adminwindow.h"
#include "reportwindow.h"

#include "headers.h"
#include "functions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMainWindowConfig();
    bool databaseConnect();
    void initializeMembers();

    void saveAdminConfigurationsToDatabase();

    void setSearchParam();

private slots:

    void showEvictWindow();
    void showSettlementWindow();
    void showCenterWindow();
    void showRootApplyWindow();
    void showAdressReportWindow();

    void getSignalFromAuthWindowLoginPushButtonClicked();
    void getSignalFromRootApplyWindowCloseEvent();
    void getSignalFromRootApplyWindowRootApplyPushButtonClicked(QString, QString);
    void getSignalFromAdminWindowCloseEvent();
    void getSignalFromCenterWindowCloseEvent();
    void getSignalFromSettlementWindowCloseEvent();
    void getSignalFromEvictWindowCloseEvent();
    void getSignalFromMoreInfoWindowCloseEvent();
    void getSignalFromReportWindowCloseEvent();

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_passportLineEdit_textEdited(const QString &arg1);

    void on_checkinDateEdit_dateChanged(const QDate &date);

    void on_previousResidenceLineEdit_textEdited(const QString &arg1);

    void on_centerTableView_doubleClicked(const QModelIndex &index);

    void on_migrantTableView_doubleClicked(const QModelIndex &index);

signals:
    void sendSignalToCenterWindowOpen();
    void sendSignalToEvictWindowOpen();
    void sendSignalToSettlementWindowOpen();

private:
    Ui::MainWindow *ui;

    AuthWindow *authWindow;
    MoreInfoWindow *moreInfoWindow;
    SettlementWindow *settlementWindow;
    EvictWindow *evictWindow;
    CenterWindow *centerWindow;
    RootApplyWindow *rootApplyWindow;
    AdminWindow *adminWindow;
    ReportWindow *reportWindow;

    QString mainRootLogin = "rootroot";
    QString mainRootPassword = "rootroot";

    QString currentLogin;
    QString currentPassword;
    QString queryString;

    QSqlDatabase database;
    QSqlQuery *query;
    QSqlRecord record;

    QSqlTableModel *centerTableModel;
    QSqlQueryModel *centerQueryModel;

    QSqlTableModel *migrantTableModel;
    QSqlQueryModel *migrantQueryModel;

    CenterTableViewAction *centerTableViewAction;
    MigrantTableViewAction *migrantTableViewAction;

    bool authStatus = false;

    Migrant *migrant;

    MyValidator *myValidator;
    QString sex;

};

#endif
