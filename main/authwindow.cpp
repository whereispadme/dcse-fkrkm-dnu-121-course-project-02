#include "authwindow.h"
#include "ui_authwindow.h"

AuthWindow::AuthWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AuthWindow)
{

    ui->setupUi(this);
    myValidator = new MyValidator();

    setAuthWindowConfig();

}

AuthWindow::~AuthWindow()
{

    delete ui;
    delete myValidator;

}

void AuthWindow::closeEvent(QCloseEvent *event)
{

    QApplication::exit();

}

void AuthWindow::setAuthWindowConfig()
{

    this->setWindowTitle("Авторизація");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::WindowCloseButtonHint);

    myValidator->setLoginLineEditValidator(ui->loginLineEdit);
    myValidator->setPasswordLineEditValidator(ui->passwordLineEdit);

    ui->loginLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->loginPushButton->setEnabled(false);

    ui->visibleIconPushButton->setIcon(QIcon(":/icons/visible_eye.png"));
    ui->hiddenIconPushButton->setIcon(QIcon(":/icons/hide_eye.png"));
    ui->visibleIconPushButton->setGeometry(384, 46, 21, 31);
    ui->hiddenIconPushButton->setGeometry(384, 46, 21, 31);
    ui->visibleIconPushButton->show();
    ui->hiddenIconPushButton->hide();

    ui->loginLineEdit->setFocus();

}

QString AuthWindow::getCurrentLogin()
{
    return this->currentLogin;
}

QString AuthWindow::getCurrentPassword()
{
    return this->currentPassword;
}

void AuthWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkAuthorizationCorrectInput(ui->loginLineEdit, ui->passwordLineEdit, ui->loginPushButton);
    this->currentLogin = arg1;
}

void AuthWindow::on_passwordLineEdit_textEdited(const QString &arg1)
{
    checkAuthorizationCorrectInput(ui->loginLineEdit, ui->passwordLineEdit, ui->loginPushButton);
    this->currentPassword = arg1;
}

void AuthWindow::on_checkBox_stateChanged(int arg1)
{

    if(ui->checkBox->isChecked())
    {
       ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
       ui->visibleIconPushButton->hide();
       ui->hiddenIconPushButton->show();
    }
    else
    {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->visibleIconPushButton->show();
        ui->hiddenIconPushButton->hide();
    }

}

void AuthWindow::on_visibleIconPushButton_clicked()
{

    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    ui->visibleIconPushButton->hide();
    ui->hiddenIconPushButton->show();

    ui->checkBox->setChecked(true);

}

void AuthWindow::on_hiddenIconPushButton_clicked()
{

    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->hiddenIconPushButton->hide();
    ui->visibleIconPushButton->show();

    ui->checkBox->setChecked(false);

}

void AuthWindow::on_loginPushButton_clicked()
{
    emit sendSignalToMainWindowLoginPushButtonClicked();
}
