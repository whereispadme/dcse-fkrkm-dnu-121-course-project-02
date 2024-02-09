#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include "headers.h"
#include "functions.h"
#include "myvalidator.h"

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

    void closeEvent(QCloseEvent *event);
    void setAuthWindowConfig();

    QString getCurrentLogin();
    QString getCurrentPassword();

signals:
    void sendSignalToMainWindowLoginPushButtonClicked();

private slots:
    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_loginPushButton_clicked();

    void on_visibleIconPushButton_clicked();

    void on_hiddenIconPushButton_clicked();

private:
    Ui::AuthWindow *ui;

    QString currentLogin;
    QString currentPassword;

    MyValidator *myValidator;

};

#endif
