#ifndef SEARCHADMINWINDOW_H
#define SEARCHADMINWINDOW_H

#include "headers.h"
#include "admin.h"
#include "initials.h"
#include "myvalidator.h"

namespace Ui {
class SearchAdminWindow;
}

class SearchAdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchAdminWindow(QWidget *parent = nullptr);
    ~SearchAdminWindow();

    void closeEvent(QCloseEvent *event);

    Admin getAdmin();
    bool getTypeSearch();

    void setSearchAdminWindowConfig();
    void checkCorrectInput(bool);

signals:
    void sendSignalToAdminWindowCloseEvent();
    void sendSignalToAdminWindowApplyPushButtonClicked();

private slots:
    void on_initialsRadioButton_clicked();

    void on_loginRadioButton_clicked();

    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_applyPushButton_clicked();

private:
    Ui::SearchAdminWindow *ui;
    Admin admin;

};

#endif
