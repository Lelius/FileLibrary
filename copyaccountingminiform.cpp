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

    QIntValidator *intValidator = new QIntValidator(1, 1000000, this);
    ui->lineEditCopyNumberOfCopy->setValidator(intValidator);

    toShowDateEdit();

    ui->dateEditReceiptDate->setDate(QDate::currentDate());
    ui->dateEditDateOfWriteOff->setDate(QDate::currentDate());
    ui->dateEditReplacementDate->setDate(QDate::currentDate());
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

void CopyAccountingMiniForm::on_pushButtonAdd_clicked()
{
    CopyAccounting copyAccounting;

    copyAccounting.setCopyNumberOfCopy(ui->lineEditCopyNumberOfCopy->text().toInt());
    if (viewDateEditReceiptDate)
        copyAccounting.setReceiptDate(ui->dateEditReceiptDate->date().isNull() ? QDate() : ui->dateEditReceiptDate->date());
    if (viewDateEditDateOfWriteOff)
        copyAccounting.setDateOfWriteOff(ui->dateEditDateOfWriteOff->date().isNull() ? QDate() : ui->dateEditDateOfWriteOff->date());
    if (viewDateEditReplacementDate)
        copyAccounting.setReplacementDate(ui->dateEditReplacementDate->date().isNull() ? QDate() : ui->dateEditReplacementDate->date());

    emit signalCopyAccountMiniFormAdd(copyAccounting);
}


void CopyAccountingMiniForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        on_pushButtonBack_clicked();
    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        on_pushButtonAdd_clicked();
}
