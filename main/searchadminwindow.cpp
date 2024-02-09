#include "searchadminwindow.h"
#include "ui_searchadminwindow.h"

SearchAdminWindow::SearchAdminWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SearchAdminWindow)
{
    ui->setupUi(this);
    setSearchAdminWindowConfig();
}

SearchAdminWindow::~SearchAdminWindow()
{
    delete ui;
}

void SearchAdminWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToAdminWindowCloseEvent();

}

Admin SearchAdminWindow::getAdmin()
{

    Initials *initials = new Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text());

    admin.setLogin(ui->loginLineEdit->text());
    admin.setInitials(initials);

    delete initials;

    return admin;

}

bool SearchAdminWindow::getTypeSearch()
{

    if(ui->loginRadioButton->isChecked())
    {
        return 0;
    }
    if(ui->initialsRadioButton->isChecked())
    {
        return 1;
    }

}

void SearchAdminWindow::setSearchAdminWindowConfig()
{

    this->setWindowTitle("Пошук адміністратора");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window |  Qt::WindowCloseButtonHint);

    ui->loginGroupBox->setEnabled(false);
    ui->initialsGroupBox->setEnabled(false);

    ui->applyPushButton->setEnabled(false);

    QList<QLineEdit *> listLineEdit;

    listLineEdit.push_back(ui->lastnameLineEdit);
    listLineEdit.push_back(ui->firstnameLineEdit);
    listLineEdit.push_back(ui->middlenameLineEdit);

    MyValidator *myValidator = new MyValidator();
    myValidator->setCyrillicLineEditValidator(listLineEdit);

    myValidator->setLoginLineEditValidator(ui->loginLineEdit);

    delete myValidator;

}

void SearchAdminWindow::checkCorrectInput(bool radioButton)
{

    if(radioButton == 0)
    {
        if(ui->loginLineEdit->text().isEmpty()){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
        if((ui->loginLineEdit->text().size() <= 5 || ui->loginLineEdit->text().size() >= 21)){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    }
    else
    {
        if(ui->lastnameLineEdit->text().isEmpty() || ui->firstnameLineEdit->text().isEmpty() || ui->middlenameLineEdit->text().isEmpty()){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
        if(ui->lastnameLineEdit->text().size() >= 21 || ui->firstnameLineEdit->text().size() >= 16 || ui->middlenameLineEdit->text().size() >= 21){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    }

}

void SearchAdminWindow::on_initialsRadioButton_clicked()
{

    ui->initialsGroupBox->setEnabled(true);
    ui->lastnameLineEdit->setFocus();
    ui->loginGroupBox->setEnabled(false);
    checkCorrectInput(1);

}

void SearchAdminWindow::on_loginRadioButton_clicked()
{

    ui->initialsGroupBox->setEnabled(false);
    ui->loginGroupBox->setEnabled(true);
    ui->loginLineEdit->setFocus();
    checkCorrectInput(0);

}

void SearchAdminWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput(0);
}

void SearchAdminWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput(1);
}

void SearchAdminWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
     checkCorrectInput(1);
}

void SearchAdminWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
     checkCorrectInput(1);
}


void SearchAdminWindow::on_applyPushButton_clicked()
{
    emit sendSignalToAdminWindowApplyPushButtonClicked();
}

