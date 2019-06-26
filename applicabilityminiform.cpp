#include "applicabilityminiform.h"
#include "ui_applicabilityminiform.h"

ApplicabilityMiniForm::ApplicabilityMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicabilityMiniForm)
{
    ui->setupUi(this);
}

ApplicabilityMiniForm::~ApplicabilityMiniForm()
{
    delete ui;
}
