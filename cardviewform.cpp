#include <QTableWidget>
#include <QStringList>

#include "cardviewform.h"
#include "ui_cardviewform.h"

CardViewForm::CardViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardViewForm)
{
    ui->setupUi(this);
    viewci = new CardInformation();
    cardViewInit();
}

CardViewForm::CardViewForm(CardInformation *ci, QWidget *parent) :
    QWidget (parent),
    ui(new Ui::CardViewForm)
{
    ui->setupUi(this);
    viewci = new CardInformation(*ci);
    cardViewInit();
}

CardViewForm::~CardViewForm()
{
    delete ui;
}

void CardViewForm::cardViewInit()
{
    ui->labelInventoryNumberValue->setText(QString::number(viewci->getInventoryNumber()));
    ui->labelReceiptDateValue->setText(viewci->getReceiptDate().toString("dd.MM.yyyy"));
    ui->labelDesignationValue->setText(viewci->getDesignation());

    ui->labelKitA1Value->setText(QString::number(viewci->getKitFormat("А1")));
    ui->labelKitA2Value->setText(QString::number(viewci->getKitFormat("А2")));
    ui->labelKitA3Value->setText(QString::number(viewci->getKitFormat("А3")));
    ui->labelKitA4Value->setText(QString::number(viewci->getKitFormat("А4")));

    ui->textBrowserNameValue->setText(viewci->getName());
    ui->textBrowserCommentValue->setText(viewci->getComment());

    //Applicability (Применяемость)
    QVector<ApplicabilityCard> applicability = viewci->getApplicability();
    ui->tableWidgetApplicability->setRowCount(applicability.length());
    ui->tableWidgetApplicability->setColumnCount(2);
    QStringList lst;
    lst << " Дата введения " << " Обозначение ";
    ui->tableWidgetApplicability->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerApplicability = ui->tableWidgetApplicability->horizontalHeader();
    headerApplicability->setSectionResizeMode(QHeaderView::Stretch);

    //ChangeAccounting (Учет изменений)
    QVector<ChangeAccountingCard> changeAccountingCard = viewci->getChangeAccounting();
    ui->tableWidgetChangeAccounting->setRowCount(changeAccountingCard.length());
    ui->tableWidgetChangeAccounting->setColumnCount(3);
    lst.clear();
    lst << " Изменение " << " N извещения " << " Дата внесения ";
    ui->tableWidgetChangeAccounting->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerChangeAccounting = ui->tableWidgetChangeAccounting->horizontalHeader();
    headerChangeAccounting->setSectionResizeMode(QHeaderView::Stretch);

    //CopyAccounting (Учет копий)
    QVector<CopyAccounting> copyAccounting = viewci->getCopyAccounting();
    ui->tableWidgetCopyAccounting->setRowCount(copyAccounting.length());
    ui->tableWidgetCopyAccounting->setColumnCount(4);
    lst.clear();
    lst << " N экз. копии " << " Дата поступ. " << " списания " << " замены ";
    ui->tableWidgetCopyAccounting->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerCopyAccounting = ui->tableWidgetCopyAccounting->horizontalHeader();
    headerCopyAccounting->setSectionResizeMode(QHeaderView::Stretch);

    //IssuanceOfCopies (Выдача копий)
    QVector<IssuanceOfCopies> issuanceOfCopies = viewci->getIssuanceOfCopies();
    ui->tableWidgetIssuanceOfCopies->setRowCount(issuanceOfCopies.length());
    ui->tableWidgetIssuanceOfCopies->setColumnCount(4);
    lst.clear();
    lst << " Абоненты " << " Дата выдачи "  << " N экземпляра " << " Списано ";
    ui->tableWidgetIssuanceOfCopies->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerIssuanceOfCopies = ui->tableWidgetIssuanceOfCopies->horizontalHeader();
    headerIssuanceOfCopies->setSectionResizeMode(QHeaderView::Stretch);
}
