#include "listform.h"
#include "ui_listform.h"
#include "cardinformation.h"
#include "workwithdatabase.h"

ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);
    slotListInit();
}

ListForm::~ListForm()
{
    delete ui;
}

void ListForm::slotListInit()
{
    QVector<CardInformation> cci;
    WorkWithDatabase wwd;

    cci = wwd.searchCardAll();
    QSqlDatabase db = QSqlDatabase::database("FL");
    if (!db.isOpen()){
        qDebug() << "База данных отсутствует";
        return;
    }

    ui->labelListFileName->clear();
    QFileInfo *fileInfo = new QFileInfo(db.databaseName());
    ui->labelListFileName->setText(fileInfo->fileName());

    ui->tableWidgetList->setRowCount(cci.length());
    ui->tableWidgetList->setColumnCount(4);

    QStringList list;
    list << "Инвентарный номер" << "Обозначение" << "Наименование" << "Дата поступления";
    ui->tableWidgetList->setHorizontalHeaderLabels(list);
    QHeaderView *header = ui->tableWidgetList->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
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

void ListForm::slotDelCard()
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
    WorkWithDatabase wwd;
    wwd.removeDatabase();
    ui->tableWidgetList->clear();
    ui->tableWidgetList->setRowCount(0);
    ui->tableWidgetList->setColumnCount(0);
    ui->labelListFileName->clear();
}

void ListForm::on_tableWidgetList_cellActivated(int row, int column)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item = ui->tableWidgetList->item(row, 0);
    int inventoryNumber = item->text().toInt();
    qDebug() << inventoryNumber;
}
