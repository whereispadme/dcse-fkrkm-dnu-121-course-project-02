#ifndef EDITADMINWINDOW_H
#define EDITADMINWINDOW_H

#include "headers.h"
#include "admin.h"
#include "initials.h"
#include "myvalidator.h"

namespace Ui {
class EditAdminWindow;
}

class EditAdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditAdminWindow(QWidget *parent = nullptr);
    ~EditAdminWindow();

    void closeEvent(QCloseEvent *event);

    Admin getAdmin();
    bool getTypeSearch();

    void setEditAdminWindowConfig();
    void checkCorrectInput();

signals:
    void sendSignalToAdminWindowCloseEvent();
    void sendSignalToAdminWindowApplyPushButtonClicked();

private slots:

    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_applyPushButton_clicked();

private:
    Ui::EditAdminWindow *ui;
    Admin *admin = nullptr;

};

#endif // EDITADMINWINDOW_H
