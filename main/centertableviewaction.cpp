#include "centertableviewaction.h"

CenterTableViewAction::CenterTableViewAction(QTableView *&tableView, QSqlTableModel *&tableModel, QSqlQueryModel *&queryModel)
{

    this->tableView = tableView;
    this->tableModel = tableModel;
    this->queryModel = queryModel;
    this->myMessageBox = new MyMessageBox;

}

CenterTableViewAction::~CenterTableViewAction()
{
    delete this->myMessageBox;
}

void CenterTableViewAction::setTableView()
{

    tableModel->setTable("center");

    CenterTableViewAction::setSqlTableModelHeadersData();

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableModel->setSort(1, Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);
    tableView->selectRow(0);

    int avarageSize = (tableView->geometry().width() / 4) - 6;

    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, avarageSize);
    tableView->setColumnWidth(2, avarageSize);
    tableView->setColumnWidth(3, avarageSize);
    tableView->setColumnWidth(4, avarageSize);

}

void CenterTableViewAction::setSqlTableModelHeadersData()
{

    tableModel->setHeaderData(0, Qt::Horizontal, ("center_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Вулиця"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Будинок"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Загальна кіл-сть місць"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Доступна кіл-сть місць"));

}

void CenterTableViewAction::setSqlQueryModelHeadersData()
{

    queryModel->setHeaderData(0, Qt::Horizontal, ("center_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Вулиця"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Будинок"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Загальна кіл-сть місць"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Доступна кіл-сть місць"));

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);

}

void CenterTableViewAction::searchTableViewRecord(int isCheckedAvailablePlaces)
{

    if(isCheckedAvailablePlaces == 1)
    {

        QString sqlQuery;
        sqlQuery = "select *"
                   "from center"
                   "where center_street = '" + center.getStreet() + "' or "
                   "center_house = '" + center.getHouse() + "' or "
                   "center_available_places != 0;";


        queryModel->setQuery(sqlQuery, QSqlDatabase::database("MyDatabase"));
        tableView->setModel(queryModel);
        CenterTableViewAction::setSqlQueryModelHeadersData();

    }
    else
    {

        QString sqlQuery;
        sqlQuery = "select *"
                   "from center"
                   "where center_street = '" + center.getStreet() + "' or "
                   "center_house = '" + center.getHouse() + "';";


        queryModel->setQuery(sqlQuery, QSqlDatabase::database("MyDatabase"));
        tableView->setModel(queryModel);
        CenterTableViewAction::setSqlQueryModelHeadersData();

    }

}

void CenterTableViewAction::createTableViewRecord()
{

    QString query;

    query = "select * from center where center_street = '%1' and center_house = '%2';";
    query = query.arg(this->center.getStreet()).arg(this->center.getHouse());

    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    tableView->setModel(queryModel);

    if(queryModel->rowCount() != 0)
    {
        CenterTableViewAction::setTableView();
        this->myMessageBox->setQMessageBoxWarning("Створення нового центру", "Центр за цією адресою вже наявний у системі!", QIcon());
        return;
    }

    query = ("insert into center(center_street, center_house, center_general_places, center_available_places) values ('%1', '%2', '%3', '%4');");
    query = query.arg(center.getStreet()).arg(center.getHouse()).arg(center.getGeneralPlacesAmount()).arg(center.getAvailablePlacesAmount());
    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

    tableView->setModel(queryModel);
    CenterTableViewAction::setSqlQueryModelHeadersData();

    CenterTableViewAction::setTableView();

    this->myMessageBox->setQMessageBoxInformation("Створення нового центру", "Центр був успішно створений!", QIcon());

}

void CenterTableViewAction::removeTableViewRecord()
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

        CenterTableViewAction::setTableView();

    }
    else
        return;

}

void CenterTableViewAction::editTableViewRecord()
{

    QString query;

    QVariant myData;
    QVariant street;
    QVariant house;
    QVariant generalPlacesAmount;
    QVariant availablePlacesAmount;
    QModelIndex myIndex;

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 0, QModelIndex());
    myData = tableView->model()->data(myIndex);

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 1, QModelIndex());
    street = tableView->model()->data(myIndex);

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 2, QModelIndex());
    house = tableView->model()->data(myIndex);

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 3, QModelIndex());
    generalPlacesAmount = tableView->model()->data(myIndex);

    myIndex = tableView->model()->index(tableView->currentIndex().row(), 4, QModelIndex());
    availablePlacesAmount = tableView->model()->data(myIndex);

    if(generalPlacesAmount.toInt() > availablePlacesAmount.toInt() && street.toString() == this->center.getStreet() && house.toString() == this->center.getHouse())
    {

        query = "update center set center_street = '%1', center_house = '%2', center_general_places = '%3', center_available_places = '%4' where center_id = '%5';";
        query = query.arg(center.getStreet()).arg(center.getHouse()).arg(center.getGeneralPlacesAmount()).arg(center.getGeneralPlacesAmount().toInt() - (generalPlacesAmount.toInt() - availablePlacesAmount.toInt())).arg(myData.toString());
        queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

        CenterTableViewAction::setSqlQueryModelHeadersData();
        CenterTableViewAction::setTableView();

        return;

    }
    else
    {
        QMessageBox::warning(0, "Увага!", "Неможливо редагувати адресу центру, у якому є зареєстровані переселенці: " + QString::number(generalPlacesAmount.toInt() - availablePlacesAmount.toInt()) + "!");
        return;
    }

    if((generalPlacesAmount.toInt() > availablePlacesAmount.toInt()) && !(street.toString() == this->center.getStreet() && house.toString() == this->center.getHouse()));
    {

    }

    if(this->center.getGeneralPlacesAmount().toInt() < (generalPlacesAmount.toInt() - availablePlacesAmount.toInt()))
    {
        QMessageBox::warning(0, "Увага!", "Неможливо зменшити кількість місць таким чином, що їх буде менше, ніж усього заселених людей, в даному випадку: " + QString::number(generalPlacesAmount.toInt() - availablePlacesAmount.toInt()) + "!");
        return;
    }

    query = "select * from center where center_street = '%1' and center_house = '%2' and center_general_places = '%3';";
    query = query.arg(this->center.getStreet()).arg(this->center.getHouse()).arg(this->center.getGeneralPlacesAmount());

    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    tableView->setModel(queryModel);

    if(queryModel->rowCount() != 0)
    {
        CenterTableViewAction::setTableView();
        this->myMessageBox->setQMessageBoxWarning("Редагування центру", "Центр з вказаними параметрами вже наявний у системі!", QIcon());
        return;
    }

    query = "update center set center_street = '%1', center_house = '%2', center_general_places = '%3', center_available_places = '%4' where center_id = '%5';";
    query = query.arg(center.getStreet()).arg(center.getHouse()).arg(center.getGeneralPlacesAmount()).arg(center.getGeneralPlacesAmount().toInt() - (generalPlacesAmount.toInt() - availablePlacesAmount.toInt())).arg(myData.toString());
    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));

    CenterTableViewAction::setSqlQueryModelHeadersData();
    CenterTableViewAction::setTableView();

}

void CenterTableViewAction::setTableViewAvailablePlaces(int size)
{

    QString query;

    query = "select * from center where center_available_places >= '%1';";
    query = query.arg(size);

    queryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    tableView->setModel(queryModel);

    CenterTableViewAction::setSqlQueryModelHeadersData();

}

void CenterTableViewAction::setCenter(Center center)
{

    this->center = center;

}
