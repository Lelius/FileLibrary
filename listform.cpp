#include "listform.h"
#include "ui_listform.h"
#include "cardinformation.h"
#include "workwithdatabase.h"

ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);
    listInit();
}

ListForm::~ListForm()
{
    delete ui;
}

void ListForm::listInit()
{
    QVector<CardInformation> cci;
    WorkWithDatabase wwd;
    QList<QString> list;

    cci = wwd.searchCardAll();
    if (cci.isEmpty())
        return;
    list << "Инвентарный номер" << "Обозначение" << "Наименование" << "Дата поступления";

}
