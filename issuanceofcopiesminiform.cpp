#include "issuanceofcopiesminiform.h"
#include "ui_issuanceofcopiesminiform.h"

IssuanceOfCopiesMiniForm::IssuanceOfCopiesMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IssuanceOfCopiesMiniForm)
{
    ui->setupUi(this);
}

IssuanceOfCopiesMiniForm::~IssuanceOfCopiesMiniForm()
{
    delete ui;
}
