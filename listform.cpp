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
    QStringList list;

    cci = wwd.searchCardAll();
    if (cci.isEmpty()){
        qDebug() << "База данных пуста или отсутствует";
        return;
    }
    qDebug() << cci.length();
    ui->tableWidgetList->setRowCount(cci.length());
    ui->tableWidgetList->setColumnCount(4);
    list << "Инвентарный номер" << "Обозначение" << "Наименование" << "Дата поступления";
    ui->tableWidgetList->setHorizontalHeaderLabels(list);
    QHeaderView *header = ui->tableWidgetList->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}
