#include "listform.h"
#include "ui_listform.h"

ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);
}

ListForm::~ListForm()
{
    delete ui;
}
