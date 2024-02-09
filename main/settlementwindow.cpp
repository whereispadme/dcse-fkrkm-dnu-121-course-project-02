#include "settlementwindow.h"
#include "ui_settlementwindow.h"

SettlementWindow::SettlementWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettlementWindow)
{
    ui->setupUi(this);
    setSettlementWindowConfig();

    migrant = new Migrant();
    myValidator = new MyValidator();

    queryModel = new QSqlQueryModel(this);
    model = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));
    model->setTable("center");

    migrantTableViewAction = new MigrantTableViewAction();

    centerTableViewAction = new CenterTableViewAction(ui->centerTableView, model, queryModel);
    centerTableViewAction->setTableView();

    QRegularExpression regex("^\\+[0-9]{3}\\s\\((\\d+)\\)-\\d{3}-\\d{2}-\\d{2}");
    validator = new QRegularExpressionValidator(regex);

}

SettlementWindow::~SettlementWindow()
{

    delete ui;

    delete migrantTableViewAction;

    if (this->centerTableViewAction != nullptr)
        delete centerTableViewAction;

    delete model;
    delete queryModel;

    delete migrant;
    delete validator;
    delete myValidator;

}

void SettlementWindow::closeEvent(QCloseEvent *event)
{
    emit sendSignalToMainWindowCloseEvent();
}

void SettlementWindow::setSettlementWindowConfig()
{

    this->setWindowTitle("Оформлення | Реєстрація");

    iterator = 0;

    ui->typeSetGroupBox->show();
    ui->familyInfoGroupBox->show();
    ui->groupInfoGroupBox->show();
    ui->centerGroupBox->show();

    ui->personInfoGroupBox->setGeometry(10, 200, 451, 251); //10, 200, 451, 251
    ui->personalInfoGroupBox->setGeometry(480, 200, 451, 251); //480, 200, 451, 251
    ui->applyPushButton->setGeometry(10, 770, 911, 24);//10, 770, 911, 24

    ui->familyPeopleAmountLineEdit->clear();
    ui->groupPeopleAmountLineEdit->clear();
    ui->familyPreviousResidenceLineEdit->clear();
    ui->groupPreviousResidenceLineEdit->clear();
    ui->previousPlaceIndLineEdit->clear();
    ui->lastnameLineEdit->clear();
    ui->middlenameLineEdit->clear();
    ui->firstnameLineEdit->clear();
    ui->passportLineEdit->clear();
    ui->telephoneLineEdit->inputMask().clear();
    ui->telephoneLineEdit->clear();
    ui->birthdayDateEdit->setDate(QDate(QDateTime::currentDateTime().toString("yyyy").toInt(), QDateTime::currentDateTime().toString("MM").toInt(), QDateTime::currentDateTime().toString("dd").toInt()));
    ui->needsLineEdit->clear();

    QList<QLineEdit *> listLineEdit;

    listLineEdit.push_back(ui->familyPeopleAmountLineEdit);
    listLineEdit.push_back(ui->groupPeopleAmountLineEdit);
    myValidator->setIntegerLineEditValidator(listLineEdit, 1);

    listLineEdit.push_back(ui->familyPreviousResidenceLineEdit);
    listLineEdit.push_back(ui->groupPreviousResidenceLineEdit);
    listLineEdit.push_back(ui->previousPlaceIndLineEdit);
    listLineEdit.push_back(ui->lastnameLineEdit);
    listLineEdit.push_back(ui->middlenameLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit, 20);

    listLineEdit.push_back(ui->firstnameLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit, 15);

    listLineEdit.push_back(ui->passportLineEdit);
    myValidator->setIntegerLineEditValidator(listLineEdit, 9);

    listLineEdit.push_back(ui->needsLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit);

    ui->familyInfoGroupBox->setEnabled(false);
    ui->groupInfoGroupBox->setEnabled(false);
    ui->personInfoGroupBox->setEnabled(false);
    ui->personalInfoGroupBox->setEnabled(false);
    ui->sexGroupBox->setEnabled(false);

    ui->applyPushButton->setEnabled(true);

    ui->previousPlaceIndLabel->hide();
    ui->previousPlaceIndLineEdit->hide();

}

void SettlementWindow::setLineEditStyleSheets()
{

    ui->familyPeopleAmountLineEdit->setStyleSheet("#familyPeopleAmountLineEdit { color: rgb(115, 115, 115); } #familyPeopleAmountLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #familyPeopleAmountLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->groupPeopleAmountLineEdit->setStyleSheet("#groupPeopleAmountLineEdit { color: rgb(115, 115, 115); } #groupPeopleAmountLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #groupPeopleAmountLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->familyPreviousResidenceLineEdit->setStyleSheet("#familyPreviousResidenceLineEdit { color: rgb(115, 115, 115); } #familyPreviousResidenceLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #familyPreviousResidenceLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->groupPreviousResidenceLineEdit->setStyleSheet("#groupPreviousResidenceLineEdit { color: rgb(115, 115, 115); } #groupPreviousResidenceLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #groupPreviousResidenceLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->previousPlaceIndLineEdit->setStyleSheet("#previousPlaceIndLineEdit { color: rgb(115, 115, 115); } #previousPlaceIndLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #previousPlaceIndLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->lastnameLineEdit->setStyleSheet("#lastnameLineEdit { color: rgb(115, 115, 115); } #lastnameLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #lastnameLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->middlenameLineEdit->setStyleSheet("#middlenameLineEdit { color: rgb(115, 115, 115); } #middlenameLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #middlenameLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->firstnameLineEdit->setStyleSheet("#firstnameLineEdit { color: rgb(115, 115, 115); } #firstnameLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #firstnameLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->passportLineEdit->setStyleSheet("#passportLineEdit { color: rgb(115, 115, 115); } #passportLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #passportLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->telephoneLineEdit->setStyleSheet("#telephoneLineEdit { color: rgb(115, 115, 115); } #telephoneLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #telephoneLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");
    ui->needsLineEdit->setStyleSheet("#needsLineEdit { color: rgb(115, 115, 115); } #needsLineEdit:hover { border: 1px solid rgb(64, 71, 88); } #needsLineEdit:focus { border: 1px solid rgb(255, 67, 254); }");

}

void SettlementWindow::familygroupAddConfig()
{

    this->setGeometry(this->geometry().x(), this->geometry().y(), 933, 300);

    ui->typeSetGroupBox->setVisible(false);
    ui->familyInfoGroupBox->setVisible(false);
    ui->groupInfoGroupBox->setVisible(false);

    ui->personInfoGroupBox->setGeometry(10, 10, 451, 251); //10, 200, 451, 251
    ui->personalInfoGroupBox->setGeometry(480, 10, 441, 251); //480, 200, 451, 251
    ui->applyPushButton->setGeometry(10, 270, 911, 24);//10, 770, 911, 24

    ui->lastnameLineEdit->clear();
    ui->firstnameLineEdit->clear();
    ui->middlenameLineEdit->clear();
    ui->passportLineEdit->clear();
    ui->telephoneLineEdit->clear();

    ui->birthdayDateEdit->setDate(QDate(QDateTime::currentDateTime().toString("yyyy").toInt(), QDateTime::currentDateTime().toString("MM").toInt(), QDateTime::currentDateTime().toString("dd").toInt()));
    ui->needsLineEdit->clear();

    checkCorrectInput();
    this->show();

    ui->lastnameLineEdit->setFocus();

}

void SettlementWindow::personInfoCheckCorrectInput()
{

    if (ui->lastnameLineEdit->text().isEmpty() || ui->firstnameLineEdit->text().isEmpty() || ui->middlenameLineEdit->text().isEmpty()) { ui->applyPushButton->setEnabled(false); return; }
    else { ui->applyPushButton->setEnabled(true); }
    if (ui->lastnameLineEdit->text().size() >= 21 || ui->firstnameLineEdit->text().size() >= 16 || ui->middlenameLineEdit->text().size() >= 21) { ui->applyPushButton->setEnabled(false); return; }
    else { ui->applyPushButton->setEnabled(true); }

    if ((ui->maleRadioButton->isChecked() == false && ui->femaleRadioButton->isChecked() == false)) { ui->applyPushButton->setEnabled(false); return; }
    else { ui->applyPushButton->setEnabled(true); }

    if (ui->passportLineEdit->text().isEmpty() || ui->telephoneLineEdit->text().isEmpty() || ui->needsLineEdit->text().isEmpty()) { ui->applyPushButton->setEnabled(false); return; }
    else { ui->applyPushButton->setEnabled(true); }
    if (ui->passportLineEdit->text().size() != 9 || ui->telephoneLineEdit->text().size() != 18) { ui->applyPushButton->setEnabled(false); return; }
    else { ui->applyPushButton->setEnabled(true); }

}

void SettlementWindow::checkCorrectInput()
{

    if (ui->singleRadioButton->isChecked())
    {
        if (ui->previousPlaceIndLineEdit->text().isEmpty()) { ui->applyPushButton->setEnabled(false); return; }
        else { ui->applyPushButton->setEnabled(true); }
        personInfoCheckCorrectInput();
    }

    if (ui->familyRadioButton->isChecked())
    {
        if (ui->familyPeopleAmountLineEdit->text().isEmpty() || ui->familyPreviousResidenceLineEdit->text().isEmpty() || ui->familyPeopleAmountLineEdit->text().toInt() == 0) { ui->applyPushButton->setEnabled(false); return; }
        else { ui->applyPushButton->setEnabled(true); }
        personInfoCheckCorrectInput();
    }

    if (ui->groupRadioButton->isChecked())
    {
        if (ui->groupPeopleAmountLineEdit->text().isEmpty() || ui->groupPreviousResidenceLineEdit->text().isEmpty() || ui->groupPeopleAmountLineEdit->text().toInt() == 0) { ui->applyPushButton->setEnabled(false); return; }
        else { ui->applyPushButton->setEnabled(true); }
        personInfoCheckCorrectInput();
    }

}

void SettlementWindow::setCorrectLineEditStyleSheet(QLineEdit *&lineEdit)
{

    (lineEdit->text().isEmpty()) ? lineEdit->setStyleSheet("QLineEdit { color: rgb(115, 115, 115); } #lineEdit:hover { border: 1px solid rgb(64, 71, 88); } #lineEdit:focus { border: 1px solid rgb(255, 67, 254); }") : lineEdit->setStyleSheet("#lineEdit { color: white; } #lineEdit:hover { border: 1px solid rgb(64, 71, 88); } #lineEdit:focus { border: 1px solid rgb(255, 67, 254); }");

}

void SettlementWindow::on_singleRadioButton_clicked()
{

    ui->familyInfoGroupBox->setEnabled(false);
    ui->groupInfoGroupBox->setEnabled(false);
    ui->personInfoGroupBox->setEnabled(true);
    ui->personalInfoGroupBox->setEnabled(true);
    ui->sexGroupBox->setEnabled(true);
    ui->lastnameLineEdit->setFocus();

    ui->previousPlaceIndLabel->show();
    ui->previousPlaceIndLineEdit->show();

    this->size = ui->familyPeopleAmountLineEdit->text().toUInt();
    this->centerTableViewAction->setTableViewAvailablePlaces(1);
    checkCorrectInput();

}

void SettlementWindow::on_familyRadioButton_clicked()
{

    familyGroupStatus = true;
    ui->familyInfoGroupBox->setEnabled(true);
    ui->groupInfoGroupBox->setEnabled(false);
    ui->personInfoGroupBox->setEnabled(true);
    ui->personalInfoGroupBox->setEnabled(true);
    ui->sexGroupBox->setEnabled(true);
    ui->familyPreviousResidenceLineEdit->setFocus();

    ui->previousPlaceIndLabel->hide();
    ui->previousPlaceIndLineEdit->hide();
    checkCorrectInput();

}

void SettlementWindow::on_groupRadioButton_clicked()
{

    familyGroupStatus = true;
    ui->familyInfoGroupBox->setEnabled(false);
    ui->groupInfoGroupBox->setEnabled(true);
    ui->personInfoGroupBox->setEnabled(true);
    ui->personalInfoGroupBox->setEnabled(true);
    ui->sexGroupBox->setEnabled(true);
    ui->groupPreviousResidenceLineEdit->setFocus();

    ui->previousPlaceIndLabel->hide();
    ui->previousPlaceIndLineEdit->hide();
    checkCorrectInput();

}

void SettlementWindow::on_familyPreviousResidenceLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->familyPreviousResidenceLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_familyPeopleAmountLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->familyPeopleAmountLineEdit);
    checkCorrectInput();
    this->size = ui->familyPeopleAmountLineEdit->text().toUInt();
    this->centerTableViewAction->setTableViewAvailablePlaces(size);
}

void SettlementWindow::on_groupPreviousResidenceLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->groupPreviousResidenceLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_groupPeopleAmountLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->groupPeopleAmountLineEdit);
    checkCorrectInput();
    this->size = ui->groupPeopleAmountLineEdit->text().toUInt();
    this->centerTableViewAction->setTableViewAvailablePlaces(size);
}

void SettlementWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->lastnameLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->firstnameLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->middlenameLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_maleRadioButton_clicked()
{
    checkCorrectInput();
}

void SettlementWindow::on_femaleRadioButton_clicked()
{
    checkCorrectInput();
}

void SettlementWindow::getSignalFromMainWindow()
{

    this->centerTableViewAction->setTableView();

}

void SettlementWindow::on_passportLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->passportLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_telephoneLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->telephoneLineEdit);
    if(ui->telephoneLineEdit->text().size() == 1)
    {
        ui->telephoneLineEdit->setValidator(validator);
        ui->telephoneLineEdit->setInputMask("+38(000)-00-00-000");
    }
    checkCorrectInput();

}

void SettlementWindow::on_needsLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->needsLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_previousPlaceIndLineEdit_textEdited(const QString &arg1)
{
    setCorrectLineEditStyleSheet(ui->previousPlaceIndLineEdit);
    checkCorrectInput();
}

void SettlementWindow::on_applyPushButton_clicked()
{

    if (ui->singleRadioButton->isChecked())
    {

        QVariant myData;
        QModelIndex myIndex;

        myIndex = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
        myData = ui->centerTableView->model()->data(myIndex);

        QString sex;

        if (ui->maleRadioButton->isChecked()) sex = "Чоловіча";
        if (ui->femaleRadioButton->isChecked()) sex = "Жіноча";

        Personal personal(ui->passportLineEdit->text(), ui->telephoneLineEdit->text(), ui->birthdayDateEdit->text(), ui->needsLineEdit->text());
        Initials initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text());

        migrant = new Migrant(personal, initials, sex, QDateTime::currentDateTime().toString("yyyy-MM-dd"), ui->previousPlaceIndLineEdit->text());

        migrantTableViewAction = new MigrantTableViewAction();
        migrantTableViewAction->createSingleTableViewRecord(*migrant, myData);

        MyMessageBox message;
        message.setQMessageBoxInformation("Поселення/Реєстрація", "Особа була успішно зареєстрована!", QIcon());

        this->setSettlementWindowConfig();
        ui->personInfoGroupBox->setEnabled(true);
        ui->personalInfoGroupBox->setEnabled(true);
        ui->lastnameLineEdit->setFocus();
        ui->singleRadioButton->setChecked(true);

        this->centerTableViewAction->setTableView();
        ui->telephoneLineEdit->clear();
        ui->telephoneLineEdit->setText("");
        ui->telephoneLineEdit->setPlaceholderText("+38(096)-52-33-873");
        ui->sexGroupBox->setEnabled(true);
        this->show();
        checkCorrectInput();
        ui->previousPlaceIndLabel->show();
        ui->previousPlaceIndLineEdit->show();
        setLineEditStyleSheets();

    }

    if (ui->familyRadioButton->isChecked())
    {

        QString query;
        QModelIndex myIndex;

        QSqlQuery *sqlQuery = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

        if (iterator == 0)
        {

            myIndex = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
            center_id_data = ui->centerTableView->model()->data(myIndex);

            sqlQuery->prepare("update center set center_available_places = (center_available_places - " + QString::number(size) + ") where center_id = " + center_id_data.toString() + ";");
            sqlQuery->exec();

            query = "insert into family(family_previous_residence, family_people_amount) values ('%1','%2');";
            query = query.arg(ui->familyPreviousResidenceLineEdit->text()).
                          arg(ui->familyPeopleAmountLineEdit->text());
            queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

            query = "select max(family_id) from family;";
            queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
            ui->centerTableView->setModel(queryModel);
            family_id_data = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
            family_id_data = ui->centerTableView->model()->data(myIndex);

            centerTableViewAction->setTableView();
            this->centerTableViewAction->setTableViewAvailablePlaces(size);

        }

        QString sex;

        if (ui->maleRadioButton->isChecked()) sex = "Чоловіча";
        if (ui->femaleRadioButton->isChecked()) sex = "Жіноча";

        sqlQuery->prepare("SET SQL_SAFE_UPDATES = 0;");
        sqlQuery->exec();

        sqlQuery->prepare("SET GLOBAL FOREIGN_KEY_CHECKS=0;");
        sqlQuery->exec();

        sqlQuery->prepare("insert into migrant(migrant_center_id, migrant_family_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence) "
            "values (:center_id, :family_id, :lastname, :firstname, :middlename, :sex, :checkin, :previous_residence);");
        sqlQuery->bindValue(":center_id", center_id_data);
        sqlQuery->bindValue(":family_id", family_id_data.toString());
        sqlQuery->bindValue(":lastname", ui->lastnameLineEdit->text());
        sqlQuery->bindValue(":firstname", ui->firstnameLineEdit->text());
        sqlQuery->bindValue(":middlename", ui->middlenameLineEdit->text());
        sqlQuery->bindValue(":sex", sex);
        sqlQuery->bindValue(":checkin", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
        sqlQuery->bindValue(":previous_residence", ui->familyPreviousResidenceLineEdit->text());
        sqlQuery->exec();

        sqlQuery->prepare("insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values(:passport, :telephone, :birthday, :needs);");
        sqlQuery->bindValue(":passport", ui->passportLineEdit->text());
        sqlQuery->bindValue(":telephone", ui->telephoneLineEdit->text());
        sqlQuery->bindValue(":birthday", ui->birthdayDateEdit->text());
        sqlQuery->bindValue(":needs", ui->needsLineEdit->text());
        sqlQuery->exec();

        this->show();

        if (iterator == size - 1)
        {
            MyMessageBox message;
            message.setQMessageBoxInformation("Поселення/Реєстрація", "Сім'я з " + QString::number(size) + " чоловік була успішно зареєстрована! Продовжіть заповнення або повертайтеся до головного меню!", QIcon());
            this->setSettlementWindowConfig();
            this->setGeometry(this->geometry().x(), this->geometry().y(), 933, 799);
            ui->singleRadioButton->setChecked(true);
            ui->personInfoGroupBox->setEnabled(true);
            ui->personalInfoGroupBox->setEnabled(true);
            ui->sexGroupBox->setEnabled(true);
            ui->lastnameLineEdit->setFocus();
            checkCorrectInput();
            this->show();
            setLineEditStyleSheets();
        }
        else
        {
            MyMessageBox message;
            message.setQMessageBoxInformation("Поселення/Реєстрація", "Особа " + QString::number(iterator + 1) + " була успішно зареєстрована! Заповніть будь ласка " + QString::number(iterator + 2) + " особу!", QIcon());
            this->familygroupAddConfig();
            ui->personInfoGroupBox->setEnabled(true);
            ui->personalInfoGroupBox->setEnabled(true);
            ui->lastnameLineEdit->setFocus();
            checkCorrectInput();
            this->show();
            setLineEditStyleSheets();

            iterator++;

        }

    }

    if (ui->groupRadioButton->isChecked())
    {

        QString query;
        QModelIndex myIndex;

        QSqlQuery *sqlQuery = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

        if (iterator == 0)
        {

            myIndex = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
            center_id_data = ui->centerTableView->model()->data(myIndex);

            sqlQuery->prepare("update center set center_available_places = (center_available_places - " + QString::number(size) + ") where center_id = " + center_id_data.toString() + ";");
            sqlQuery->exec();

            query = "insert into _group(group_previous_residence, group_people_amount) values ('%1','%2');";
            query = query.arg(ui->groupPreviousResidenceLineEdit->text()).
                          arg(ui->groupPeopleAmountLineEdit->text());
            queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

            query = "select max(group_id) from _group;";
            queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
            ui->centerTableView->setModel(queryModel);

            group_id_data = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
            group_id_data = ui->centerTableView->model()->data(myIndex);

            centerTableViewAction->setTableView();
            this->centerTableViewAction->setTableViewAvailablePlaces(size);

        }

        QString sex;

        if (ui->maleRadioButton->isChecked()) sex = "Чоловіча";
        if (ui->femaleRadioButton->isChecked()) sex = "Жіноча";

        sqlQuery->prepare("SET SQL_SAFE_UPDATES = 0;");
        sqlQuery->exec();

        sqlQuery->prepare("SET GLOBAL FOREIGN_KEY_CHECKS=0;");
        sqlQuery->exec();

        sqlQuery->prepare("insert into migrant(migrant_center_id, migrant_group_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence) "
            "values (:center_id, :group_id, :lastname, :firstname, :middlename, :sex, :checkin, :previous_residence);");
        sqlQuery->bindValue(":center_id", center_id_data);
        sqlQuery->bindValue(":group_id", group_id_data.toString());
        sqlQuery->bindValue(":lastname", ui->lastnameLineEdit->text());
        sqlQuery->bindValue(":firstname", ui->firstnameLineEdit->text());
        sqlQuery->bindValue(":middlename", ui->middlenameLineEdit->text());
        sqlQuery->bindValue(":sex", sex);
        sqlQuery->bindValue(":checkin", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
        sqlQuery->bindValue(":previous_residence", ui->groupPreviousResidenceLineEdit->text());
        sqlQuery->exec();

        sqlQuery->prepare("insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values(:passport, :telephone, :birthday, :needs);");
        sqlQuery->bindValue(":passport", ui->passportLineEdit->text());
        sqlQuery->bindValue(":telephone", ui->telephoneLineEdit->text());
        sqlQuery->bindValue(":birthday", ui->birthdayDateEdit->text());
        sqlQuery->bindValue(":needs", ui->needsLineEdit->text());
        sqlQuery->exec();

        this->show();

        if (iterator == size - 1)
        {
            MyMessageBox message;
            message.setQMessageBoxInformation("Поселення/Реєстрація", "Група з " + QString::number(size) + " чоловік була успішно зареєстрована! Продовжіть заповнення або повертайтеся до головного меню!", QIcon());
            this->setSettlementWindowConfig();
            this->setGeometry(this->geometry().x(), this->geometry().y(), 933, 799);
            ui->singleRadioButton->setChecked(true);
            ui->personInfoGroupBox->setEnabled(true);
            ui->personalInfoGroupBox->setEnabled(true);
            ui->sexGroupBox->setEnabled(true);
            ui->lastnameLineEdit->setFocus();
            checkCorrectInput();
            this->show();
            setLineEditStyleSheets();
        }
        else
        {
            MyMessageBox message;
            message.setQMessageBoxInformation("Поселення/Реєстрація", "Особа " + QString::number(iterator + 1) + " була успішно зареєстрована! Заповніть будь ласка " + QString::number(iterator + 2) + " особу!", QIcon());
            this->familygroupAddConfig();
            ui->personInfoGroupBox->setEnabled(true);
            ui->personalInfoGroupBox->setEnabled(true);
            ui->lastnameLineEdit->setFocus();
            checkCorrectInput();
            this->show();
            setLineEditStyleSheets();

            iterator++;

        }

    }

}
