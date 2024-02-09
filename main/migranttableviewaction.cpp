#include "migranttableviewaction.h"

MigrantTableViewAction::MigrantTableViewAction(QTableView *&tableView, QSqlTableModel *&tableModel, QSqlQueryModel *&queryModel)
{

    this->tableView = tableView;
    this->tableModel = tableModel;
    this->queryModel = queryModel;
    this->myMessageBox = new MyMessageBox;

}

MigrantTableViewAction::~MigrantTableViewAction()
{
    if(this->myMessageBox != nullptr)
        delete this->myMessageBox;
}

void MigrantTableViewAction::setTableView()
{

    tableModel->setTable("migrant");

    MigrantTableViewAction::setSqlTableModelHeadersData();

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableModel->setSort(1, Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);
    tableView->selectRow(0);

    int avarageSize = (tableView->geometry().width() / 6) - 4;

    tableView->setColumnHidden(0, true);
    tableView->setColumnHidden(1, true);
    tableView->setColumnHidden(2, true);
    tableView->setColumnHidden(3, true);

    tableView->setColumnWidth(4, avarageSize);
    tableView->setColumnWidth(5, avarageSize);
    tableView->setColumnWidth(6, avarageSize);
    tableView->setColumnWidth(7, avarageSize);
    tableView->setColumnWidth(8, avarageSize);
    tableView->setColumnWidth(9, avarageSize);

}

void MigrantTableViewAction::setSqlTableModelHeadersData()
{

    tableModel->setHeaderData(0, Qt::Horizontal, ("migrant_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("migrant_center_id"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("migrant_family_id"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("migrant_group_id"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Прізвище"));
    tableModel->setHeaderData(5, Qt::Horizontal, ("Ім'я"));
    tableModel->setHeaderData(6, Qt::Horizontal, ("По батькові"));
    tableModel->setHeaderData(7, Qt::Horizontal, ("Стать"));
    tableModel->setHeaderData(8, Qt::Horizontal, ("Дата реєстрації"));
    tableModel->setHeaderData(9, Qt::Horizontal, ("Поперереднє м.п."));

    int avarageSize = (tableView->geometry().width() / 6) - 4;

    tableView->setColumnWidth(4, avarageSize);
    tableView->setColumnWidth(5, avarageSize);
    tableView->setColumnWidth(6, avarageSize);
    tableView->setColumnWidth(7, avarageSize);
    tableView->setColumnWidth(8, avarageSize);
    tableView->setColumnWidth(9, avarageSize);

}

void MigrantTableViewAction::setSqlQueryModelHeadersData()
{

    queryModel->setHeaderData(0, Qt::Horizontal, ("migrant_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("migrant_center_id"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("migrant_family_id"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("migrant_group_id"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Прізвище"));
    queryModel->setHeaderData(5, Qt::Horizontal, ("Ім'я"));
    queryModel->setHeaderData(6, Qt::Horizontal, ("По батькові"));
    queryModel->setHeaderData(7, Qt::Horizontal, ("Стать"));
    queryModel->setHeaderData(8, Qt::Horizontal, ("Дата реєстрації"));
    queryModel->setHeaderData(9, Qt::Horizontal, ("Поперереднє м.п."));

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);

    tableView->setColumnHidden(0, true);
    tableView->setColumnHidden(1, true);
    tableView->setColumnHidden(2, true);
    tableView->setColumnHidden(3, true);
    tableView->setColumnHidden(10, true);
    tableView->setColumnHidden(11, true);
    tableView->setColumnHidden(12, true);
    tableView->setColumnHidden(13, true);
    tableView->setColumnHidden(14, true);
    tableView->setColumnHidden(14, true);

    int avarageSize = (tableView->geometry().width() / 6) - 4;

    tableView->setColumnWidth(4, avarageSize);
    tableView->setColumnWidth(5, avarageSize);
    tableView->setColumnWidth(6, avarageSize);
    tableView->setColumnWidth(7, avarageSize);
    tableView->setColumnWidth(8, avarageSize);
    tableView->setColumnWidth(9, avarageSize);

}

void MigrantTableViewAction::searchTableViewRecord()
{

    QString sqlQuery;
    sqlQuery = "select *"
               "from migrant inner join personal on migrant_id = personal_migrant_id "
               "where migrant_lastname = '" + migrant.getInitials().lastname + "' or "
               "migrant_firstname = '" + migrant.getInitials().firstname + "' or "
               "migrant_middlename = '" + migrant.getInitials().middlename + "' or "
               "migrant_checkin = '" + migrant.getCheckin() + "' or "
               "migrant_previous_residence = '" + migrant.getPreviousResidence() + "' or "
               "personal_passport = '" + migrant.getPersonal().getPassport() + "';";

    queryModel->setQuery(sqlQuery, QSqlDatabase::database("MyDatabase"));
    tableView->setModel(queryModel);
    MigrantTableViewAction::setSqlQueryModelHeadersData();

}

void MigrantTableViewAction::searchTableViewRecord(int)
{
}

void MigrantTableViewAction::createTableViewRecord()
{
}

void MigrantTableViewAction::createSingleTableViewRecord(Migrant migrant, QVariant myData)
{

    queryModel = new QSqlQueryModel();

    QString queryString = "insert into migrant(migrant_center_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence) values ('%1', '%2', '%3', '%4', '%5', '%6', '%7');";
    queryString = queryString.
            arg(myData.toString()).
            arg(migrant.getInitials().lastname).
            arg(migrant.getInitials().firstname).
            arg(migrant.getInitials().middlename).
            arg(migrant.getSex()).
            arg(migrant.getCheckin()).
            arg(migrant.getPreviousResidence());

    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    queryString = "insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values('%1', '%2', '%3', '%4');";
    queryString = queryString.
            arg(migrant.getPersonal().getPassport()).
            arg(migrant.getPersonal().getTelephone()).
            arg(migrant.getPersonal().getBirthday()).
            arg(migrant.getPersonal().getNeeds());

    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    queryString = "update center set center_available_places = (center_available_places - 1) where center_id = '%1';";
    queryString = queryString.arg(myData.toString());
    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    delete queryModel;

}

void MigrantTableViewAction::createSingleTableViewRecordFamily(Migrant migrant, QVariant myData, int family_id)
{

    queryModel = new QSqlQueryModel();

    QString queryString = "insert into migrant(migrant_center_id, migrant_family_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence) values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');";
    queryString = queryString.
            arg(myData.toString()).
            arg(QString::number(family_id)).
            arg(migrant.getInitials().lastname).
            arg(migrant.getInitials().firstname).
            arg(migrant.getInitials().middlename).
            arg(migrant.getSex()).
            arg(migrant.getCheckin()).
            arg(migrant.getPreviousResidence());

    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    queryString = "insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values('%1', '%2', '%3', '%4');";
    queryString = queryString.
            arg(migrant.getPersonal().getPassport()).
            arg(migrant.getPersonal().getTelephone()).
            arg(migrant.getPersonal().getBirthday()).
            arg(migrant.getPersonal().getNeeds());

    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    queryString = "update center set center_available_places = (center_available_places - 1);";
    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    delete queryModel;

}

void MigrantTableViewAction::createSingleTableViewRecordGroup(Migrant migrant, QVariant myData, int group_id)
{

    queryModel = new QSqlQueryModel();

    QString queryString = "insert into migrant(migrant_center_id, migrant_group_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence) values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');";
    queryString = queryString.
            arg(myData.toString()).
            arg(QString::number(group_id)).
            arg(migrant.getInitials().lastname).
            arg(migrant.getInitials().firstname).
            arg(migrant.getInitials().middlename).
            arg(migrant.getSex()).
            arg(migrant.getCheckin()).
            arg(migrant.getPreviousResidence());

    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    queryString = "insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values('%1', '%2', '%3', '%4');";
    queryString = queryString.
            arg(migrant.getPersonal().getPassport()).
            arg(migrant.getPersonal().getTelephone()).
            arg(migrant.getPersonal().getBirthday()).
            arg(migrant.getPersonal().getNeeds());

    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    queryString = "update center set center_available_places = (center_available_places - 1);";
    queryModel->setQuery(queryString, QSqlDatabase::database("MyDatabase"));

    delete queryModel;

}

void MigrantTableViewAction::removeTableViewRecord()
{

    if (setWarningMessageBoxDeleteRecord("Видалення центру переселенців") == QMessageBox::Ok) //нажата кнопка Ok
    {
        QVariant myData;
        QVariant myData1;
        QVariant myData2;
        QModelIndex myIndex;

        myIndex = tableView->model()->index(tableView->currentIndex().row(), 0, QModelIndex());
        myData = tableView->model()->data(myIndex);

        myIndex = tableView->model()->index(tableView->currentIndex().row(), 3, QModelIndex());
        myData1 = tableView->model()->data(myIndex);

        myIndex = tableView->model()->index(tableView->currentIndex().row(), 4, QModelIndex());
        myData2 = tableView->model()->data(myIndex);

        if(myData1.toInt() > myData2.toInt())
        {
            QMessageBox::warning(0, "Увага!", "Неможливо видалити центр у якому наявні переселенці!");
            return;
        }

        QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

        query->prepare("delete from center where center_id = :id;");
        query->bindValue(":id", myData);
        query->exec();

        MigrantTableViewAction::setTableView();

    }
    else
        return;

}

void MigrantTableViewAction::editTableViewRecord()
{
}

void MigrantTableViewAction::setMigrant(Migrant migrant)
{

    this->migrant = migrant;

}
