#include "issuanceofcopiesminiform.h"
#include "ui_issuanceofcopiesminiform.h"

IssuanceOfCopiesMiniForm::IssuanceOfCopiesMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IssuanceOfCopiesMiniForm)
{
    ui->setupUi(this);

    QIntValidator *intValidator = new QIntValidator(1, 1000000, this);
    ui->lineEditInstanceNumber->setValidator(intValidator);

    ui->dateEditDateOfIssue->setDate(QDate::currentDate());
}

IssuanceOfCopiesMiniForm::~IssuanceOfCopiesMiniForm()
{
    delete ui;
}

void IssuanceOfCopiesMiniForm::on_pushButtonAdd_clicked()
{
    IssuanceOfCopies iss;
    iss.setSubscriber(ui->lineEditSubscriber->text());
    iss.setDateOfIssue(ui->dateEditDateOfIssue->date());
    iss.setInstanceNumber(ui->lineEditInstanceNumber->text().toInt());
    iss.setWrittenOff(ui->lineEditWrittenOff->text());

    emit signalIssuanceOfCopiesMiniFormAdd(iss);
}

void IssuanceOfCopiesMiniForm::on_pushButtonBack_clicked()
{
    emit signalIssuanceOfCopiesMiniFormClose();
}
