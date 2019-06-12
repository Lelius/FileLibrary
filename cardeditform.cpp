#include "cardeditform.h"
#include "ui_cardeditform.h"

CardEditForm::CardEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardEditForm)
{
    ui->setupUi(this);
}

CardEditForm::~CardEditForm()
{
    delete ui;
}
