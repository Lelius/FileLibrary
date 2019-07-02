#include "copyaccountingminiform.h"
#include "ui_copyaccountingminiform.h"

CopyAccountingMiniForm::CopyAccountingMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopyAccountingMiniForm)
{
    ui->setupUi(this);
}

CopyAccountingMiniForm::~CopyAccountingMiniForm()
{
    delete ui;
}
