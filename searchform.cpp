#include "searchform.h"
#include "ui_searchform.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);

    ui->lineEditSearchText->setText("");
    sci.clear();
}


SearchForm::~SearchForm()
{
    delete ui;
}


void SearchForm::on_pushButtonSearch_clicked()
{
    if (ui->lineEditSearchText->text() == "")
        return;

    QSqlDatabase db = QSqlDatabase::database("FL");
    if (!db.isOpen()){
        qDebug() << "База данных отсутствует";
        return;
    }

    *searchString = ui->lineEditSearchText->text();

}
