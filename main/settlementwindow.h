#ifndef SETTLEMENTWINDOW_H
#define SETTLEMENTWINDOW_H

#include "functions.h"
#include "headers.h"

#include "migranttableviewaction.h"
#include "centertableviewaction.h"

#include "center.h"
#include "family.h"
#include "group.h"
#include "migrant.h"
#include "personal.h"

#include "myvalidator.h"
#include "mymessagebox.h"

namespace Ui {
class SettlementWindow;
}

class SettlementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettlementWindow(QWidget *parent = nullptr);
    ~SettlementWindow();

    void closeEvent(QCloseEvent *event);

    void setSettlementWindowConfig();
    void familygroupAddConfig();

    void personInfoCheckCorrectInput();
    void checkCorrectInput();

    void setCorrectLineEditStyleSheet(QLineEdit *&);

    void getSignalFromMainWindow();

    void setLineEditStyleSheets();

signals:
    void sendSignalToMainWindowCloseEvent();

private slots:
    void on_singleRadioButton_clicked();

    void on_familyRadioButton_clicked();

    void on_groupRadioButton_clicked();

    void on_familyPreviousResidenceLineEdit_textEdited(const QString &arg1);

    void on_familyPeopleAmountLineEdit_textEdited(const QString &arg1);

    void on_groupPreviousResidenceLineEdit_textEdited(const QString &arg1);

    void on_groupPeopleAmountLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_passportLineEdit_textEdited(const QString &arg1);

    void on_telephoneLineEdit_textEdited(const QString &arg1);

    void on_needsLineEdit_textEdited(const QString &arg1);

    void on_previousPlaceIndLineEdit_textEdited(const QString &arg1);

    void on_applyPushButton_clicked();

    void on_maleRadioButton_clicked();

    void on_femaleRadioButton_clicked();

private:
    Ui::SettlementWindow *ui;

    MigrantTableViewAction *migrantTableViewAction;
    CenterTableViewAction *centerTableViewAction;

    QSqlTableModel *model;
    QSqlQueryModel *queryModel;

    Migrant *migrant;
    QVariant family_id_data;
    QVariant center_id_data;
    QVariant group_id_data;

    vector<Migrant> vectorMigrant;

    QValidator *validator;
    MyValidator *myValidator;

    unsigned int size;
    unsigned int iterator = 0;

    bool familyGroupStatus = false;

};

#endif
