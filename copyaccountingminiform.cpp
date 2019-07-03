#include "copyaccountingminiform.h"
#include "ui_copyaccountingminiform.h"

CopyAccountingMiniForm::CopyAccountingMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopyAccountingMiniForm)
{
    ui->setupUi(this);

    viewDateEditReceiptDate = false;
    viewDateEditDateOfWriteOff = false;
    viewDateEditReplacementDate = false;

    toShowDateEdit();
}

CopyAccountingMiniForm::~CopyAccountingMiniForm()
{
    delete ui;
}

void CopyAccountingMiniForm::on_pushButtonBack_clicked()
{
    emit signalCopyAccounteMiniFormClose();
}

void CopyAccountingMiniForm::toShowDateEdit()
{
    viewDateEditReceiptDate ? ui->dateEditReceiptDate->show() : ui->dateEditReceiptDate->hide();
    viewDateEditDateOfWriteOff ? ui->dateEditDateOfWriteOff->show() : ui->dateEditDateOfWriteOff->hide();
    viewDateEditReplacementDate ? ui->dateEditReplacementDate->show() : ui->dateEditReplacementDate->hide();
}

void CopyAccountingMiniForm::on_pushButtonReceiptDate_clicked()
{
    viewDateEditReceiptDate ? viewDateEditReceiptDate = false : viewDateEditReceiptDate = true;
    toShowDateEdit();
}

void CopyAccountingMiniForm::on_pushButtonDateOfWriteOff_clicked()
{
    viewDateEditDateOfWriteOff ? viewDateEditDateOfWriteOff = false : viewDateEditDateOfWriteOff = true;
    toShowDateEdit();
}

void CopyAccountingMiniForm::on_pushButtonReplacementDate_clicked()
{
    viewDateEditReplacementDate ? viewDateEditReplacementDate = false : viewDateEditReplacementDate = true;
    toShowDateEdit();
}
