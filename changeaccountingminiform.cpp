#include "changeaccountingminiform.h"
#include "ui_changeaccountingminiform.h"

ChangeAccountingMiniForm::ChangeAccountingMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeAccountingMiniForm)
{
    ui->setupUi(this);
    ui->dateEditDateOfEntry->setDate(QDate::currentDate());

    QIntValidator *intValidator = new QIntValidator(1, 1000000, this);
    ui->lineEditNotificationNumber->setValidator(intValidator);
}

ChangeAccountingMiniForm::~ChangeAccountingMiniForm()
{
    delete ui;
}

void ChangeAccountingMiniForm::on_pushButtonAdd_clicked()
{
    ChangeAccountingCard arg;

    arg.setChange(ui->lineEditChange->text());
    arg.setNotificationNumber(ui->lineEditNotificationNumber->text().toInt());
    arg.setDateOfEntry(ui->dateEditDateOfEntry->date());

    emit signalChangeAccountingMiniFormAdd(arg);
}

void ChangeAccountingMiniForm::on_pushButtonBack_clicked()
{
    emit signalChangeAccountingMiniFormClose();
}


void ChangeAccountingMiniForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        on_pushButtonBack_clicked();
    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        on_pushButtonAdd_clicked();
}
