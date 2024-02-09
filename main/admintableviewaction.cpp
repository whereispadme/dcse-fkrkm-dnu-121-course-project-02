#include "admintableviewaction.h"

AdminTableViewAction::AdminTableViewAction(QTableView *&tableView, QSqlTableModel *&tableModel, QSqlQueryModel *&queryModel)
{

    this->tableView = tableView;
    this->tableModel = tableModel;
    this->queryModel = queryModel;
    this->myMessageBox = new MyMessageBox;

}

AdminTableViewAction::~AdminTableViewAction()
{

    if(this->myMessageBox != nullptr)
    delete this->myMessageBox;

}

void AdminTableViewAction::setTableView()
{

    tableModel->setTable("admin");

    AdminTableViewAction::setSqlTableModelHeadersData();

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableModel->setSort(1, Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);
    tableView->selectRow(0);

    int avarageSize = (tableView->geometry().width() / 5) - 5;

    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, avarageSize);
    tableView->setColumnWidth(2, avarageSize);
    tableView->setColumnWidth(3, avarageSize);
    tableView->setColumnWidth(4, avarageSize);
    tableView->setColumnWidth(5, avarageSize);

}

void AdminTableViewAction::setSqlTableModelHeadersData()
{

    tableModel->setHeaderData(0, Qt::Horizontal, ("admin_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Логін"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Пароль"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Прізвище"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Ім'я"));
    tableModel->setHeaderData(5, Qt::Horizontal, ("По батькові"));

}

void AdminTableViewAction::setSqlQueryModelHeadersData()
{

    queryModel->setHeaderData(0, Qt::Horizontal, ("admin_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Логін"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Пароль"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Прізвище"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Ім'я"));
    queryModel->setHeaderData(5, Qt::Horizontal, ("По батькові"));

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);

}

void AdminTableViewAction::searchTableViewRecord(int typeSearch)
{

    QString query;

    if(typeSearch == 0)
    {

        query = "select * from admin where admin_login = '%1';";
        query = query.arg(admin.getLogin());

        queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

        tableView->setModel(queryModel);
        AdminTableViewAction::setSqlQueryModelHeadersData();

    }
    else
    {

        query = "select * from admin where admin_lastname = '%1' and admin_firstname = '%2' and admin_middlename = '%3';";
        query = query.arg(admin.getInitials().lastname).arg(admin.getInitials().firstname).arg(admin.getInitials().middlename);

        queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

        tableView->setModel(queryModel);
        AdminTableViewAction::setSqlQueryModelHeadersData();

    }

    (this->queryModel->rowCount() == 0) ? this->myMessageBox->setQMessageBoxInformation("Результат пошуку", "Не було знайдено записів з вказаними параметрами!", QIcon()) :
                                          this->myMessageBox->setQMessageBoxInformation("Результат пошуку", "Було знайдено записів з вказаними параметрами: " + QString::number(this->queryModel->rowCount()) + "!", QIcon());

}

void AdminTableViewAction::createTableViewRecord()
{

    QString query;

    query = "select admin_login from admin where admin_login = '%1';";
    query = query.arg(this->admin.getLogin());

    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    tableView->setModel(queryModel);

    if(queryModel->rowCount() != 0)
    {
        AdminTableViewAction::setTableView();
        this->myMessageBox->setQMessageBoxWarning("Створення нового адміністратору", "Адміністратор з вказаним логіном вже існує!", QIcon());
        return;
    }

    query = ("insert into admin(admin_login, admin_password, admin_lastname, admin_firstname, admin_middlename) values ('%1', '%2', '%3', '%4', '%5');");
    query = query.arg(admin.getLogin()).arg(admin.getPassword()).arg(admin.getInitials().lastname).arg(admin.getInitials().firstname).arg(admin.getInitials().middlename);
    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

    query = ("insert into config (config_posX, config_posY, config_width, config_length) values ('489', '268', '942', '504');");
    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

    tableView->setModel(queryModel);
    AdminTableViewAction::setSqlQueryModelHeadersData();

    AdminTableViewAction::setTableView();

    this->myMessageBox->setQMessageBoxInformation("Створення нового адміністратору", "Адміністратор був успішно створений!", QIcon());

}

void AdminTableViewAction::removeTableViewRecord()
{

    if (setWarningMessageBoxDeleteRecord("Видалення адміністратору") == QMessageBox::Ok) //нажата кнопка Ok
    {
        QVariant myData;
        QModelIndex myIndex;

        myIndex = tableView->model()->index(tableView->currentIndex().row(), 1, QModelIndex());
        myData = tableView->model()->data(myIndex);

        if(myData == this->mainWindowAdminLogin)
        {
            QMessageBox::warning(0, "Увага!", "Даного користувача неможливо видалити, він використовується у реальному часі!");
            return;
        }

        QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

        query->prepare("delete from config where config_admin_id = (select admin_id from admin where admin_id = ':id');");
        query->bindValue(":id", myData);
        query->exec();

        query->prepare("delete from admin where admin_login = :id;");
        query->bindValue(":id", myData);
        query->exec();

        AdminTableViewAction::setTableView();

    }
    else
        return;

}

void AdminTableViewAction::editTableViewRecord()
{

    QString query;

    QVariant myData;
    QModelIndex myIndex;

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 1, QModelIndex());
    myData = tableView->model()->data(myIndex);

    if(myData == this->mainWindowAdminLogin)
    {
        QMessageBox::warning(0, "Увага!", "Даного користувача неможливо редагувати, він використовується у реальному часі!");
        return;
    }

    QStringList adminLoginStringList;
    QSqlQuery *sqlQuery = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

    sqlQuery->prepare("select admin_login from admin;");
    sqlQuery->exec();

    while(sqlQuery->next())
    {
        adminLoginStringList.push_back(sqlQuery->value(0).toString());
    }

    for(int i = 0; i < adminLoginStringList.size(); ++i)
    {

        if(adminLoginStringList[i] == this->admin.getLogin())
        {

            QMessageBox::warning(0, "Увага!", "Користувач з вказаним логіном вже наявний у системі, спробуйте інший логін!");
            return;

        }

    }

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 0, QModelIndex());
    myData = tableView->model()->data(myIndex);

    query = ("update admin set admin_login = '%1', admin_password = '%2', admin_lastname = '%3', admin_firstname = '%4', admin_middlename = '%5' where admin_id = '%6';");
    query = query.arg(admin.getLogin()).arg(admin.getPassword()).arg(admin.getInitials().lastname).arg(admin.getInitials().firstname).arg(admin.getInitials().middlename).arg(myData.toString());
    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

    AdminTableViewAction::setSqlQueryModelHeadersData();
    AdminTableViewAction::setTableView();

}

void AdminTableViewAction::setAdmin(Admin admin)
{
    this->admin = admin;
}

void AdminTableViewAction::setMainWindowAdminLogin(QString mainWindowAdminLogin)
{
    this->mainWindowAdminLogin = mainWindowAdminLogin;
}
