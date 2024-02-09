#include "evictwindow.h"
#include "ui_evictwindow.h"

EvictWindow::EvictWindow(QWidget *parent) : QWidget(parent), ui(new Ui::EvictWindow)
{

    ui->setupUi(this);
    setEvictWindowConfig();

    migrant = new Migrant();
    myValidator = new MyValidator();

    centerTableModel = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));;
    centerQueryModel = new QSqlQueryModel(this);;
    centerTableModel->setTable("center");

    migrantTableModel = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));;
    migrantQueryModel = new QSqlQueryModel(this);;
    migrantTableModel->setTable("migrant");

    centerTableViewAction = new CenterTableViewAction(ui->centerTableView, centerTableModel, centerQueryModel);
    migrantTableViewAction = new MigrantTableViewAction(ui->migrantTableView, migrantTableModel, migrantQueryModel);

    centerTableViewAction->setTableView();

    ui->checkinDateEdit->setDate(QDate(QDateTime::currentDateTime().toString("yyyy").toInt(), QDateTime::currentDateTime().toString("MM").toInt(), QDateTime::currentDateTime().toString("dd").toInt()));

}

EvictWindow::~EvictWindow()
{

    delete ui;

    delete migrant;

    delete centerTableModel;
    delete centerQueryModel;

    delete migrantTableModel;
    delete migrantQueryModel;

    delete centerTableViewAction;
    delete migrantTableViewAction;

    delete myValidator;

}

void EvictWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToMainWindowCloseEvent();

}

void EvictWindow::setEvictWindowConfig()
{

    this->setWindowTitle("Виселення");

    QList<QLineEdit *> listLineEdit;

    listLineEdit.push_back(ui->lastnameLineEdit);
    listLineEdit.push_back(ui->middlenameLineEdit);
    listLineEdit.push_back(ui->previousResidenceLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit, 20);

    listLineEdit.push_back(ui->firstnameLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit, 15);

    listLineEdit.push_back(ui->passportLineEdit);
    myValidator->setIntegerLineEditValidator(listLineEdit, 9);

    ui->lastnameLineEdit->setFocus();

}

void EvictWindow::setSearchParam()
{

    migrant = new Migrant(Personal(ui->passportLineEdit->text(), QString(), QString(), QString()), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), sex, ui->checkinDateEdit->text(), ui->previousResidenceLineEdit->text());
    migrantTableViewAction->setMigrant(*migrant);
    migrantTableViewAction->searchTableViewRecord();

}

void EvictWindow::getSignalFromMainWindowOpen()
{

    if(this->centerTableViewAction != nullptr)
        this->centerTableViewAction->setTableView();

}

void EvictWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void EvictWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void EvictWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void EvictWindow::on_passportLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void EvictWindow::on_checkinDateEdit_dateChanged(const QDate &date)
{
    setSearchParam();
}

void EvictWindow::on_previousResidenceLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void EvictWindow::on_centerTableView_doubleClicked(const QModelIndex &index)
{

    QModelIndex myIndex = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
    QVariant center_id = ui->centerTableView->model()->data(myIndex);

    QString query = "select migrant.migrant_id, migrant.migrant_center_id, migrant.migrant_family_id, migrant.migrant_group_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex, "
                    "migrant.migrant_checkin, migrant.migrant_previous_residence "
                    "from migrant where migrant_center_id = " + center_id.toString() + ";";

    this->migrantQueryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    ui->migrantTableView->setModel(migrantQueryModel);
    migrantTableViewAction->setSqlQueryModelHeadersData();

}

void EvictWindow::on_migrantTableView_doubleClicked(const QModelIndex &index)
{

    QString queryString;
    QModelIndex myIndex;

    QVariant migrant_id;
    QVariant center_id;
    QVariant family_id;
    QVariant group_id;

    myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 0, QModelIndex());
    migrant_id = ui->migrantTableView->model()->data(myIndex);

    myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 1, QModelIndex());
    center_id = ui->migrantTableView->model()->data(myIndex);

    myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 2, QModelIndex());
    family_id = ui->migrantTableView->model()->data(myIndex);

    myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 3, QModelIndex());
    group_id = ui->migrantTableView->model()->data(myIndex);

    qDebug() << migrant_id;

    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon());
    msgBox.setWindowTitle("Підтвердіть видалення!");
    msgBox.setInformativeText("Ок - виселити усю родину\nCancel - виселити тільки цю особу");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setDefaultButton(QMessageBox::Ok);

    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

    query->prepare("SET SQL_SAFE_UPDATES = 0;");
    query->exec();

    query->prepare("SET GLOBAL FOREIGN_KEY_CHECKS = 0;");
    query->exec();

    int currentIndexCenter = ui->centerTableView->currentIndex().row();

    if(family_id.toString() == "0" && group_id.toString() == "0")
    {

        msgBox.setText("Ця особа не має зв'язків! Виселити?");
        msgBox.setInformativeText("Ок - виселити \nCancel - скасувати");

        if(msgBox.exec() == QMessageBox::Ok)
        {

            query->prepare("delete from personal where personal_migrant_id = :id;");
            query->bindValue(":id", migrant_id);
            query->exec();

            query->prepare("delete from migrant where migrant_id = :id;");
            query->bindValue(":id", migrant_id);
            query->exec();

            query->prepare("update center set center_available_places = (center_available_places + 1) where center_id = :id;");
            query->bindValue(":id", center_id);
            query->exec();

            queryString = "select migrant.migrant_id, migrant.migrant_center_id, migrant.migrant_family_id, migrant.migrant_group_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex, "
                            "migrant.migrant_checkin, migrant.migrant_previous_residence "
                            "from migrant where migrant_center_id = " + center_id.toString() + ";";

            this->migrantQueryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));
            ui->migrantTableView->setModel(migrantQueryModel);
            migrantTableViewAction->setSqlQueryModelHeadersData();
            centerTableViewAction->setTableView();
            ui->centerTableView->selectRow(currentIndexCenter);
            return;

        }

        return;

    }

    if(family_id.toString() != "0")
    {

        msgBox.setText("Увага! Ця особа належить до родини!");
        msgBox.setInformativeText("Ок - виселити \nCancel - скасувати");

        if(msgBox.exec() == QMessageBox::Ok)
        {

            query->prepare("SET SQL_SAFE_UPDATES = 0;");
            query->exec();

            query->prepare("SET GLOBAL FOREIGN_KEY_CHECKS = 0;");
            query->exec();

            query->prepare("update family set family_people_amount = (family_people_amount - 1) where family_id = :id");
            query->bindValue(":id", family_id);
            query->exec();

            query->prepare("delete from personal where personal_migrant_id = :id;");
            query->bindValue(":id", migrant_id);
            query->exec();

            query->prepare("delete from migrant where migrant_id = :id;");
            query->bindValue(":id", migrant_id);
            query->exec();

            query->prepare("update center set center_available_places = (center_available_places + 1) where center_id = :id;");
            query->bindValue(":id", center_id);
            query->exec();

            queryString = "select migrant.migrant_id, migrant.migrant_center_id, migrant.migrant_family_id, migrant.migrant_group_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex, "
                            "migrant.migrant_checkin, migrant.migrant_previous_residence "
                            "from migrant where migrant_center_id = " + center_id.toString() + ";";

            query->prepare("delete from family where family_people_amount = 0;");
            query->exec();

            this->migrantQueryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));
            ui->migrantTableView->setModel(migrantQueryModel);
            migrantTableViewAction->setSqlQueryModelHeadersData();
            centerTableViewAction->setTableView();
            ui->centerTableView->selectRow(currentIndexCenter);
            return;

        }
        else
        {
            return;

        }

        return;

    }

    if(group_id.toString() != "0")
    {

        msgBox.setText("Увага! Ця особа належить до групи!");
        msgBox.setInformativeText("Ок - виселити \nCancel - скасувати");

        if(msgBox.exec() == QMessageBox::Ok)
        {

            query->prepare("SET SQL_SAFE_UPDATES = 0;");
            query->exec();

            query->prepare("SET GLOBAL FOREIGN_KEY_CHECKS = 0;");
            query->exec();

            query->prepare("update _group set group_people_amount = (group_people_amount - 1) where group_id = :id");
            query->bindValue(":id", group_id);
            query->exec();

            query->prepare("delete from personal where personal_migrant_id = :id;");
            query->bindValue(":id", migrant_id);
            query->exec();

            query->prepare("delete from migrant where migrant_id = :id;");
            query->bindValue(":id", migrant_id);
            query->exec();

            query->prepare("update center set center_available_places = (center_available_places + 1) where center_id = :id;");
            query->bindValue(":id", center_id);
            query->exec();

            queryString = "select migrant.migrant_id, migrant.migrant_center_id, migrant.migrant_family_id, migrant.migrant_group_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex, "
                            "migrant.migrant_checkin, migrant.migrant_previous_residence "
                            "from migrant where migrant_center_id = " + center_id.toString() + ";";

            query->prepare("delete from _group where group_people_amount = 0;");
            query->exec();

            this->migrantQueryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));
            ui->migrantTableView->setModel(migrantQueryModel);
            migrantTableViewAction->setSqlQueryModelHeadersData();
            centerTableViewAction->setTableView();
            ui->centerTableView->selectRow(currentIndexCenter);
            return;

        }
        else
        {

            return;

        }

    }

}
