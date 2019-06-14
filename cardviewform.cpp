#include "cardviewform.h"
#include "ui_cardviewform.h"

CardViewForm::CardViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardViewForm)
{
    ui->setupUi(this);
}

CardViewForm::~CardViewForm()
{
    delete ui;
}
