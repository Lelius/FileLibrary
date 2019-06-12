#include "exitform.h"
#include "ui_exitform.h"

ExitForm::ExitForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExitForm)
{
    ui->setupUi(this);
}

ExitForm::~ExitForm()
{
    delete ui;
}

void ExitForm::on_pushButtonYes_clicked()
{
    QApplication::exit();
}

void ExitForm::on_pushButtonNo_clicked()
{
    emit noExit(0);
}
