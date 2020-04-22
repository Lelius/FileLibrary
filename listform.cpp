#include <algorithm>

#include "listform.h"
#include "ui_listform.h"
#include "cardinformation.h"
#include "workwithdatabase.h"
#include "mainwindow.h"


struct sort_InventoryNumberUp {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (x.getInventoryNumber() < y.getInventoryNumber());
    }
} sortInventoryNumberUp;


struct sort_InventoryNumberDown {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (x.getInventoryNumber() > y.getInventoryNumber());
    }
} sortInventoryNumberDown;


struct sort_ListByDesignationUp {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (QString::compare(x.getDesignation(), y.getDesignation(), Qt::CaseInsensitive) < 0);
    }
} sortListByDesignationUp;


struct sort_ListByDesignationDown {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (QString::compare(x.getDesignation(), y.getDesignation(), Qt::CaseInsensitive) > 0);
    }
} sortListByDesignationDown;


struct sort_ListByNameUp {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (QString::compare(x.getName(), y.getName(), Qt::CaseInsensitive) < 0);
    }
} sortListByNameUp;


struct sort_ListByNameDown {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (QString::compare(x.getName(), y.getName(), Qt::CaseInsensitive) > 0);
    }
} sortListByNameDown;


struct sort_ListByReceiptDateUp {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (x.getReceiptDate() < y.getReceiptDate());
    }
} sortListByReceiptDateUp;


struct sort_ListByReceiptDateDown {
    bool operator() (const CardInformation &x, const CardInformation &y){
        return (x.getReceiptDate() > y.getReceiptDate());
    }
} sortListByReceiptDateDown;



ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);

    sortMethod = INVENTORY_NUMBER_ASC;

    slotListInit();
}


ListForm::ListForm(QVector<CardInformation> &sci, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi((this));

    sortMethod = INVENTORY_NUMBER_ASC;
    listInit(sci);
}


ListForm::~ListForm()
{
    delete ui;
}


void ListForm::slotListInit()
{
    listInit();
}


void ListForm::listInit()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    if (!db.isOpen()){
        qDebug() << "База данных отсутствует";
        return;
    }

    cci.clear();
    ui->tableWidgetList->clear();

    WorkWithDatabase wwd;
    cci = wwd.searchCardAll();

    cci = sortList(cci);

    ui->labelListFileName->clear();
    QFileInfo *fileInfo = new QFileInfo(db.databaseName());
    ui->labelListFileName->setText(fileInfo->fileName());
    delete fileInfo;

    ui->tableWidgetList->setRowCount(cci.length());
    ui->tableWidgetList->setColumnCount(4);

    QStringList list;
    list.clear();
    list << "Инвентарный номер" << "Обозначение" << "Наименование" << "Дата поступления";
    ui->tableWidgetList->setHorizontalHeaderLabels(list);
    QHeaderView *header = ui->tableWidgetList->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setStyleSheet("color: rgb(0, 0, 127);");
    QFont font = header->font();
    font.setPointSize(ui->labelList->fontInfo().pointSize());
    header->setFont(font);

    ui->tableWidgetList->verticalHeader()->hide();
    ui->tableWidgetList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetList->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < cci.length(); ++i){
        ui->tableWidgetList->setItem(i, 0, new QTableWidgetItem(QString::number(cci.at(i).getInventoryNumber())));
        ui->tableWidgetList->setItem(i, 1, new QTableWidgetItem(cci.at(i).getDesignation()));
        ui->tableWidgetList->setItem(i, 2, new QTableWidgetItem(cci.at(i).getName()));
        ui->tableWidgetList->setItem(i, 3, new QTableWidgetItem(cci.at(i).getReceiptDate().toString("dd.MM.yyyy")));
    }

    connect(header, &QHeaderView::sectionClicked, this, &ListForm::slotHeaderSectionClicked, Qt::UniqueConnection);
}


void ListForm::listInit(QVector<CardInformation> &sci)
{
    cci.clear();
    ui->tableWidgetList->clear();

    cci = sci;

    cci = sortList(cci);

    ui->labelListFileName->clear();
    ui->labelListFileName->setText("Результат поиска");

    ui->tableWidgetList->setRowCount(cci.length());
    ui->tableWidgetList->setColumnCount(4);

    QStringList list;
    list.clear();
    list << "Инвентарный номер" << "Обозначение" << "Наименование" << "Дата поступления";
    ui->tableWidgetList->setHorizontalHeaderLabels(list);
    QHeaderView *header = ui->tableWidgetList->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setStyleSheet("color: rgb(0, 0, 127);");
    QFont font = header->font();
    font.setPointSize(ui->labelList->fontInfo().pointSize());
    header->setFont(font);

    ui->tableWidgetList->verticalHeader()->hide();
    ui->tableWidgetList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetList->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < cci.length(); ++i){
        ui->tableWidgetList->setItem(i, 0, new QTableWidgetItem(QString::number(cci.at(i).getInventoryNumber())));
        ui->tableWidgetList->setItem(i, 1, new QTableWidgetItem(cci.at(i).getDesignation()));
        ui->tableWidgetList->setItem(i, 2, new QTableWidgetItem(cci.at(i).getName()));
        ui->tableWidgetList->setItem(i, 3, new QTableWidgetItem(cci.at(i).getReceiptDate().toString("dd.MM.yyyy")));
    }

    connect(header, &QHeaderView::sectionClicked, this, &ListForm::slotHeaderSectionClicked, Qt::UniqueConnection);
}


void ListForm::slotHeaderSectionClicked(int logicalIndex){

    if (logicalIndex == 0){
        if (sortMethod == INVENTORY_NUMBER_ASC)
            sortMethod = INVENTORY_NUMBER_DES;
        else
            sortMethod = INVENTORY_NUMBER_ASC;
    }
    else if (logicalIndex == 1){
        if (sortMethod == DESIGNATION_ASC)
            sortMethod = DESIGNATION_DES;
        else
            sortMethod = DESIGNATION_ASC;
    }
    else if (logicalIndex == 2){
        if (sortMethod == NAME_ASC)
            sortMethod = NAME_DES;
        else
            sortMethod = NAME_ASC;
    }
    else if (logicalIndex == 3){
        if (sortMethod == DATE_ASC)
            sortMethod = DATE_DES;
        else
            sortMethod = DATE_ASC;
    }
    else
        sortMethod = INVENTORY_NUMBER_ASC;

    reinitList();
}


void ListForm::reinitList(){

    cci = sortList(cci);

    ui->tableWidgetList->clearContents();

    ui->tableWidgetList->verticalHeader()->hide();
    ui->tableWidgetList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetList->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < cci.length(); ++i){
        ui->tableWidgetList->setItem(i, 0, new QTableWidgetItem(QString::number(cci.at(i).getInventoryNumber())));
        ui->tableWidgetList->setItem(i, 1, new QTableWidgetItem(cci.at(i).getDesignation()));
        ui->tableWidgetList->setItem(i, 2, new QTableWidgetItem(cci.at(i).getName()));
        ui->tableWidgetList->setItem(i, 3, new QTableWidgetItem(cci.at(i).getReceiptDate().toString("dd.MM.yyyy")));
    }
}


QVector<CardInformation> ListForm::sortList(QVector<CardInformation> cci){

    if (sortMethod == INVENTORY_NUMBER_ASC || sortMethod == INVENTORY_NUMBER_DES)
        return sortListByInventoryNumber(cci);
    else if (sortMethod == DESIGNATION_ASC || sortMethod == DESIGNATION_DES)
        return sortListByDesignation(cci);
    else if (sortMethod == NAME_ASC || sortMethod == NAME_DES)
        return sortListByName(cci);
    else if (sortMethod == DATE_ASC || sortMethod == DATE_DES)
        return sortListByReceiptDate(cci);

    return cci;
}


QVector<CardInformation> ListForm::sortListByReceiptDate(QVector<CardInformation> cci){

    if (sortMethod == DATE_ASC){
        std::sort(cci.begin(), cci.end(), sortListByReceiptDateUp);
    }

    else if (sortMethod == DATE_DES){
        std::sort(cci.begin(), cci.end(), sortListByReceiptDateDown);
    }

    return cci;
}


QVector<CardInformation> ListForm::sortListByName(QVector<CardInformation> cci){

    if (sortMethod == NAME_ASC){
        std::sort(cci.begin(), cci.end(), sortListByNameUp);
    }
    else if (sortMethod == NAME_DES){
        std::sort(cci.begin(), cci.end(), sortListByNameDown);
    }

    return cci;
}


QVector<CardInformation> ListForm::sortListByDesignation(QVector<CardInformation> cci){

    if (sortMethod == DESIGNATION_ASC){
        std::sort(cci.begin(), cci.end(), sortListByDesignationUp);
    }
    else if (sortMethod == DESIGNATION_DES){
        std::sort(cci.begin(), cci.end(), sortListByDesignationDown);
    }

    return cci;
}


QVector<CardInformation> ListForm::sortListByInventoryNumber(QVector<CardInformation> cci){

    if (sortMethod == INVENTORY_NUMBER_ASC){
        std::sort(cci.begin(), cci.end(), sortInventoryNumberUp);
    }

    else if (sortMethod == INVENTORY_NUMBER_DES){
        std::sort(cci.begin(), cci.end(), sortInventoryNumberDown);
    }

    return cci;
}


void ListForm::slotListDelCard()
{
    WorkWithDatabase wwd;

    QList<QTableWidgetSelectionRange> listSelected;
    listSelected = ui->tableWidgetList->selectedRanges();

    if (listSelected.size() != 0){
        foreach(QTableWidgetSelectionRange r, listSelected){
            for (int i = r.topRow(); i <= r.bottomRow(); ++i){
                CardInformation ci;
                QTableWidgetItem *it = ui->tableWidgetList->item(i, 0);
                ci.setInventoryNumber(it->text().toInt());
                wwd.deleteCard(ci);
            }
        }

    }
    slotListInit();
}


void ListForm::slotCloseFileLibrary()
{
    emit signalChangeStackWidget(0);

    WorkWithDatabase wwd;
    wwd.removeDatabase();
    ui->tableWidgetList->clear();
    ui->tableWidgetList->setRowCount(0);
    ui->tableWidgetList->setColumnCount(0);
    ui->labelListFileName->clear();

    emit signalSetActionsEnabled(false);
}


void ListForm::on_tableWidgetList_cellActivated(int row, int column)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item = ui->tableWidgetList->item(row, 0);
    int inventoryNumber = item->text().toInt();
    qDebug() << inventoryNumber;

    WorkWithDatabase wwd;
    CardInformation ci = wwd.searchCard(inventoryNumber);
    emit signalViewSelectedCard(ci);
}


int ListForm::getSelectedInventoryNumber()
{
    WorkWithDatabase wwd;

    QList<QTableWidgetSelectionRange> listSelected;
    listSelected = ui->tableWidgetList->selectedRanges();

    if (listSelected.size() != 0){
        int inventoryNumber = 1;
        foreach(QTableWidgetSelectionRange r, listSelected){
            for (int i = r.topRow(); i <= r.bottomRow(); ++i){
                QTableWidgetItem *it = ui->tableWidgetList->item(i, 0);
                inventoryNumber = it->text().toInt();
            }
        }
        return inventoryNumber;
    }

    return wwd.searchMaxInventoryNumber();
}
