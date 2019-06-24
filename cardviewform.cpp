#include "cardviewform.h"
#include "ui_cardviewform.h"

CardViewForm::CardViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardViewForm)
{
    ui->setupUi(this);
    viewci = new CardInformation();
}

CardViewForm::CardViewForm(CardInformation *ci, QWidget *parent) :
    QWidget (parent),
    ui(new Ui::CardViewForm)
{
    ui->setupUi(this);
    viewci = new CardInformation(*ci);

    ui->labelInventoryNumberValue->setText(QString::number(viewci->getInventoryNumber()));
    ui->labelReceiptDateValue->setText(viewci->getReceiptDate().toString());
    ui->labelDesignationValue->setText(viewci->getDesignation());

    ui->labelKitA1Value->setText(QString::number(viewci->getKitFormat("А1")));
    ui->labelKitA2Value->setText(QString::number(viewci->getKitFormat("А2")));
    ui->labelKitA3Value->setText(QString::number(viewci->getKitFormat("А3")));
    ui->labelKitA4Value->setText(QString::number(viewci->getKitFormat("А4")));

    ui->textBrowserNameValue->setText(viewci->getName());
    ui->textBrowserCommentValue->setText(viewci->getComment());
}

CardViewForm::~CardViewForm()
{
    delete ui;
}
