#include <QDate>

#include "cardeditform.h"
#include "ui_cardeditform.h"
#include "cardinformation.h"

CardEditForm::CardEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardEditForm)
{
    ui->setupUi(this);
    newci = new CardInformation();

    newci->setInventoryNumber(7777);
    newci->setReceiptDate(QDate::currentDate());
    ui->lineEditInventoryNumber->setText(QString::number(newci->getInventoryNumber()));
    ui->dateTimeEditReceipteDate->setDate(newci->getReceiptDate());
}

CardEditForm::~CardEditForm()
{
    delete ui;
}

void CardEditForm::on_pushButtonSaveCard_clicked()
{
    newci->setInventoryNumber(ui->lineEditInventoryNumber->text().toInt());
    newci->setReceiptDate(ui->dateTimeEditReceipteDate->date());
    newci->setDesignation(ui->lineEditDesignation->text());
    newci->setName(ui->lineName->text());
}
