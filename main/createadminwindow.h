#ifndef CREATEADMINWINDOW_H
#define CREATEADMINWINDOW_H

#include "headers.h"
#include "admin.h"
#include "initials.h"
#include "myvalidator.h"

namespace Ui {
class CreateAdminWindow;
}

class CreateAdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAdminWindow(QWidget *parent = nullptr);
    ~CreateAdminWindow();

    void closeEvent(QCloseEvent *event);

    Admin getAdmin();
    bool getTypeSearch();

    void setCreateAdminWindowConfig();
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
    Ui::CreateAdminWindow *ui;
    Admin admin;

};

#endif // CREATEADMINWINDOW_H
