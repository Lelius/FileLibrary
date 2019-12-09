#include "exitform.h"
#include "ui_exitform.h"
#include "workwithconfigfile.h"

ExitForm::ExitForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExitForm)
{
    ui->setupUi(this);
    QTimer::singleShot(0, ui->pushButtonNo, SLOT(setFocus()));
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


void ExitForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        emit noExit(0);
    else if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
             && ui->pushButtonYes->hasFocus() == true) {
        QApplication::quit();
    }
    else if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
             && ui->pushButtonNo->hasFocus() == true)
        emit noExit(0);
}
