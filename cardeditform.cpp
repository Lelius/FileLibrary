#include "cardeditform.h"
#include "ui_cardeditform.h"
#include "cardinformation.h"

CardEditForm::CardEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardEditForm)
{
    ui->setupUi(this);

    CardInformation *cardInformation = new CardInformation();


}

CardEditForm::~CardEditForm()
{
    delete ui;
}
