#include "createadminwindow.h"
#include "ui_createadminwindow.h"

CreateAdminWindow::CreateAdminWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CreateAdminWindow)
{
    ui->setupUi(this);
    setCreateAdminWindowConfig();
}

CreateAdminWindow::~CreateAdminWindow()
{
    delete ui;
}

void CreateAdminWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToAdminWindowCloseEvent();

}

Admin CreateAdminWindow::getAdmin()
{

    Initials *initials = new Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text());
    admin.setLogin(ui->loginLineEdit->text());
    admin.setPassword(ui->passwordLineEdit->text());
    admin.setInitials(initials);
    delete initials;

    setCreateAdminWindowConfig();

    return admin;

}

void CreateAdminWindow::setCreateAdminWindowConfig()
{

    this->setWindowTitle("Створення адміністратора");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window |  Qt::WindowCloseButtonHint);

    ui->loginLineEdit->setFocus();
    ui->loginLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->lastnameLineEdit->clear();
    ui->firstnameLineEdit->clear();
    ui->middlenameLineEdit->clear();

    ui->applyPushButton->setEnabled(false);

    QList<QLineEdit *> listLineEdit;

    listLineEdit.push_back(ui->lastnameLineEdit);
    listLineEdit.push_back(ui->firstnameLineEdit);
    listLineEdit.push_back(ui->middlenameLineEdit);

    MyValidator *myValidator = new MyValidator();
    myValidator->setCyrillicLineEditValidator(listLineEdit);

    myValidator->setLoginLineEditValidator(ui->loginLineEdit);
    myValidator->setPasswordLineEditValidator(ui->passwordLineEdit);

    delete myValidator;

}

void CreateAdminWindow::checkCorrectInput()
{

    if(ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty()){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    if((ui->loginLineEdit->text().size() <= 5 || ui->loginLineEdit->text().size() >= 21) || (ui->passwordLineEdit->text().size() <= 7 || ui->passwordLineEdit->text().size() >= 21)){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }

    if(ui->lastnameLineEdit->text().isEmpty() || ui->firstnameLineEdit->text().isEmpty() || ui->middlenameLineEdit->text().isEmpty()){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    if(ui->lastnameLineEdit->text().size() >= 21 || ui->firstnameLineEdit->text().size() >= 16 || ui->middlenameLineEdit->text().size() >= 21){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
}

void CreateAdminWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void CreateAdminWindow::on_passwordLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void CreateAdminWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void CreateAdminWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void CreateAdminWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}


void CreateAdminWindow::on_applyPushButton_clicked()
{
    emit sendSignalToAdminWindowApplyPushButtonClicked();
}

