#include "listform.h"
#include "ui_listform.h"
#include "cardinformation.h"
#include "workwithdatabase.h"
#include "mainwindow.h"


ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);

    sortMethod = DATE_DES;

    slotListInit();
}


ListForm::~ListForm()
{
    delete ui;
}


void ListForm::slotListInit()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    if (!db.isOpen()){
        qDebug() << "База данных отсутствует";
        return;
    }

    QVector<CardInformation> cci;
    WorkWithDatabase wwd;
    cci = wwd.searchCardAll();

    cci = sortList(cci);

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

    int x = 1;

    if (sortMethod == DATE_ASC){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (cci[i].getReceiptDate() > cci[i + 1].getReceiptDate()){
                    QDate v = cci[i].getReceiptDate();
                    cci[i].setReceiptDate(cci[i + 1].getReceiptDate());
                    cci[i + 1].setReceiptDate(v);
                    x = 1;
                }
            }
        }
    }

    else if (sortMethod == DATE_DES){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (cci[i].getReceiptDate() < cci[i + 1].getReceiptDate()){
                    QDate v = cci[i].getReceiptDate();
                    cci[i].setReceiptDate(cci[i + 1].getReceiptDate());
                    cci[i + 1].setReceiptDate(v);
                    x = 1;
                }
            }
        }
    }

    return cci;
}


QVector<CardInformation> ListForm::sortListByName(QVector<CardInformation> cci){

    int x = 1;

    if (sortMethod == NAME_ASC){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (QString::compare(cci[i].getName(), cci[i + 1].getName(), Qt::CaseInsensitive) > 0){
                    QString v = cci[i].getName();
                    cci[i].setName(cci[i + 1].getName());
                    cci[i + 1].setName(v);
                    x = 1;
                }
            }
        }
    }
    else if (sortMethod == NAME_DES){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (QString::compare(cci[i].getName(), cci[i + 1].getName(), Qt::CaseInsensitive) < 0){
                    QString v = cci[i].getName();
                    cci[i].setName(cci[i + 1].getName());
                    cci[i + 1].setName(v);
                    x = 1;
                }
            }
        }
    }

    return cci;
}


QVector<CardInformation> ListForm::sortListByDesignation(QVector<CardInformation> cci){

    int x = 1;

    if (sortMethod == DESIGNATION_ASC){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (QString::compare(cci[i].getDesignation(), cci[i + 1].getDesignation(), Qt::CaseInsensitive) > 0){
                    QString v = cci[i].getDesignation();
                    cci[i].setDesignation(cci[i + 1].getDesignation());
                    cci[i + 1].setDesignation(v);
                    x = 1;
                }
            }
        }
    }
    else if (sortMethod == DESIGNATION_DES){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (QString::compare(cci[i].getDesignation(), cci[i + 1].getDesignation(), Qt::CaseInsensitive) < 0){
                    QString v = cci[i].getDesignation();
                    cci[i].setDesignation(cci[i + 1].getDesignation());
                    cci[i + 1].setDesignation(v);
                    x = 1;
                }
            }
        }
    }

    return cci;
}


QVector<CardInformation> ListForm::sortListByInventoryNumber(QVector<CardInformation> cci){

    int x = 1;

    if (sortMethod == INVENTORY_NUMBER_ASC){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (cci[i].getInventoryNumber() > cci[i + 1].getInventoryNumber()){
                    int v = cci[i].getInventoryNumber();
                    cci[i].setInventoryNumber(cci[i + 1].getInventoryNumber());
                    cci[i + 1].setInventoryNumber(v);
                    x = 1;
                }
            }
        }
    }

    else if (sortMethod == INVENTORY_NUMBER_DES){
        while (x == 1){
            x = 0;
            for (int i = 0; i < cci.length() - 1; ++i){
                if (cci[i].getInventoryNumber() < cci[i + 1].getInventoryNumber()){
                    int v = cci[i].getInventoryNumber();
                    cci[i].setInventoryNumber(cci[i + 1].getInventoryNumber());
                    cci[i + 1].setInventoryNumber(v);
                    x = 1;
                }
            }
        }
    }

    return cci;
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
