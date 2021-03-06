#include "secondsearchform.h"
#include "ui_secondsearchform.h"

SecondSearchForm::SecondSearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondSearchForm)
{
    ui->setupUi(this);
}

SecondSearchForm::~SecondSearchForm()
{
    delete ui;
}

void SecondSearchForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();
}
