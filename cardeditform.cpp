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
}

CardEditForm::CardEditForm(CardInformation *ci, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardEditForm)
{
    ui->setupUi(this);
    newci = new CardInformation(*ci);
}

CardEditForm::~CardEditForm()
{
    delete ui;
    delete newci;
}

void CardEditForm::on_pushButtonSaveCard_clicked()
{
    newci->setInventoryNumber(ui->lineEditInventoryNumber->text().toInt());
    newci->setReceiptDate(ui->dateEditReceiptDate->date());
    newci->setDesignation(ui->lineEditDesignation->text());

    newci->setKitFormat("А1", ui->spinBoxA1->value());
    newci->setKitFormat("А2", ui->spinBoxA2->value());
    newci->setKitFormat("А3", ui->spinBoxA3->value());
    newci->setKitFormat("А4", ui->spinBoxA4->value());

    newci->setName(ui->lineName->text());
    newci->setComment(ui->textEditComment->toPlainText());
}
