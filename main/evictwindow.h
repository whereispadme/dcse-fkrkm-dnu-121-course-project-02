#ifndef EVICTWINDOW_H
#define EVICTWINDOW_H

#include "center.h"
#include "centertableviewaction.h"
#include "migrant.h"
#include "migranttableviewaction.h"

#include "functions.h"
#include "headers.h"

#include "myvalidator.h"

namespace Ui {
class EvictWindow;
}

class EvictWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EvictWindow(QWidget *parent = nullptr);
    ~EvictWindow();

    void closeEvent(QCloseEvent *event);

    void setEvictWindowConfig();
    void familygroupAddConfig();

    void setSearchParam();

signals:
    void sendSignalToMainWindowCloseEvent();

public slots:
    void getSignalFromMainWindowOpen();

private slots:


    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_passportLineEdit_textEdited(const QString &arg1);

    void on_checkinDateEdit_dateChanged(const QDate &date);

    void on_previousResidenceLineEdit_textEdited(const QString &arg1);

    void on_centerTableView_doubleClicked(const QModelIndex &index);

    void on_migrantTableView_doubleClicked(const QModelIndex &index);

private:
    Ui::EvictWindow *ui;

    Migrant *migrant;

    QSqlTableModel *centerTableModel;
    QSqlQueryModel *centerQueryModel;

    QSqlTableModel *migrantTableModel;
    QSqlQueryModel *migrantQueryModel;

    CenterTableViewAction *centerTableViewAction;
    MigrantTableViewAction *migrantTableViewAction;

    MyValidator *myValidator;
    QString sex;

};

#endif // EVICTWINDOW_H
