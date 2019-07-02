#include "applicabilityminiform.h"
#include "ui_applicabilityminiform.h"
#include "applicabilitycard.h"

ApplicabilityMiniForm::ApplicabilityMiniForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicabilityMiniForm)
{
    ui->setupUi(this);
    ui->dateEditIntroductionDate->setDate(QDate::currentDate());
}

ApplicabilityMiniForm::~ApplicabilityMiniForm()
{
    delete ui;
}

void ApplicabilityMiniForm::on_pushButtonBack_clicked()
{
    emit signalApplicabilityMiniFormClose();
}

void ApplicabilityMiniForm::on_pushButtonAdd_clicked()
{
    ApplicabilityCard a;
    a.setIntroductionDate(ui->dateEditIntroductionDate->date());
    a.setDesignation(ui->lineEditDesignation->text());
    emit signalApplicabilityMiniFormAdd(a);
}
