#include <QTableWidget>
#include <QStringList>

#include "cardviewform.h"
#include "ui_cardviewform.h"
#include "applicabilitycard.h"

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
    ui->tableWidgetApplicability->setRowCount(applicability.size());
    ui->tableWidgetApplicability->setColumnCount(2);
    QStringList lst;
    lst << " Дата введения " << " Обозначение ";
    ui->tableWidgetApplicability->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetApplicability->setSelectionMode(QAbstractItemView::NoSelection);
    QHeaderView *headerApplicability = ui->tableWidgetApplicability->horizontalHeader();
    headerApplicability->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetApplicability->verticalHeader()->setVisible(false);

    if (!(viewci->getApplicability().isEmpty())){
        for (int i = 0; i < applicability.size();i++){
            ui->tableWidgetApplicability->setItem(i, 0, new QTableWidgetItem(applicability.at(i).getIntroductionDate().toString("dd.MM.yyyy")));
            ui->tableWidgetApplicability->setItem(i, 1, new QTableWidgetItem(applicability.at(i).getDesignation()));
        }
    }

    QItemSelectionModel *selectionModel = ui->tableWidgetApplicability->selectionModel();
    QModelIndex topLeft, bottomRight;
    topLeft = ui->tableWidgetApplicability->model()->index(0, 0, QModelIndex());
    bottomRight = ui->tableWidgetApplicability->model()->index(ui->tableWidgetApplicability->rowCount() - 1,
                                                               ui->tableWidgetApplicability->columnCount() - 1, QModelIndex());
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::NoUpdate);

    //ChangeAccounting (Учет изменений)
    QVector<ChangeAccountingCard> changeAccountingCard = viewci->getChangeAccounting();
    ui->tableWidgetChangeAccounting->setRowCount(changeAccountingCard.length());
    ui->tableWidgetChangeAccounting->setColumnCount(3);
    lst.clear();
    lst << " Изменение " << " N извещения " << " Дата внесения ";
    ui->tableWidgetChangeAccounting->setHorizontalHeaderLabels(lst);
    ui->tableWidgetChangeAccounting->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetChangeAccounting->setSelectionMode(QAbstractItemView::NoSelection);
    QHeaderView *headerChangeAccounting = ui->tableWidgetChangeAccounting->horizontalHeader();
    headerChangeAccounting->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetChangeAccounting->verticalHeader()->setVisible(false);

    if (!(viewci->getChangeAccounting().isEmpty())){
        for (int i = 0; i < changeAccountingCard.size(); i++){
            ui->tableWidgetChangeAccounting->setItem(i, 0, new QTableWidgetItem(changeAccountingCard.at(i).getChange()));
            ui->tableWidgetChangeAccounting->setItem(i, 1, new QTableWidgetItem(QString::number(changeAccountingCard.at(i).getNotificationNumber())));
            ui->tableWidgetChangeAccounting->setItem(i, 2, new QTableWidgetItem(changeAccountingCard.at(i).getDateOfEntry().toString("dd.MM.yyyy")));
        }
    }

    //CopyAccounting (Учет копий)
    QVector<CopyAccounting> copyAccounting = viewci->getCopyAccounting();
    ui->tableWidgetCopyAccounting->setRowCount(copyAccounting.length());
    ui->tableWidgetCopyAccounting->setColumnCount(4);
    lst.clear();
    lst << " N экз. копии " << " Дата поступ. " << " списания " << " замены ";
    ui->tableWidgetCopyAccounting->setHorizontalHeaderLabels(lst);
    ui->tableWidgetCopyAccounting->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetCopyAccounting->setSelectionMode(QAbstractItemView::NoSelection);
    QHeaderView *headerCopyAccounting = ui->tableWidgetCopyAccounting->horizontalHeader();
    headerCopyAccounting->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetCopyAccounting->verticalHeader()->setVisible(false);

    if (!(viewci->getCopyAccounting().isEmpty())){
        for (int i = 0; i < copyAccounting.size(); i++){
            ui->tableWidgetCopyAccounting->setItem(i, 0, new QTableWidgetItem(QString::number(copyAccounting.at(i).getCopyNumberOfCopy())));
            ui->tableWidgetCopyAccounting->setItem(i, 1, new QTableWidgetItem(copyAccounting.at(i).getReceiptDate().toString("dd.MM.yyyy")));
            ui->tableWidgetCopyAccounting->setItem(i, 2, new QTableWidgetItem(copyAccounting.at(i).getDateOfWriteOff().toString("dd.MM.yyyy")));
            ui->tableWidgetCopyAccounting->setItem(i, 3, new QTableWidgetItem(copyAccounting.at(i).getReplacementDate().toString("dd.MM.yyyy")));
        }
    }

    //IssuanceOfCopies (Выдача копий)
    QVector<IssuanceOfCopies> issuanceOfCopies = viewci->getIssuanceOfCopies();
    ui->tableWidgetIssuanceOfCopies->setRowCount(issuanceOfCopies.length());
    ui->tableWidgetIssuanceOfCopies->setColumnCount(4);
    lst.clear();
    lst << " Абоненты " << " Дата выдачи "  << " N экземпляра " << " Списано ";
    ui->tableWidgetIssuanceOfCopies->setHorizontalHeaderLabels(lst);
    ui->tableWidgetIssuanceOfCopies->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetIssuanceOfCopies->setSelectionMode(QAbstractItemView::NoSelection);
    QHeaderView *headerIssuanceOfCopies = ui->tableWidgetIssuanceOfCopies->horizontalHeader();
    headerIssuanceOfCopies->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetIssuanceOfCopies->verticalHeader()->setVisible(false);

    if (!(viewci->getIssuanceOfCopies().isEmpty())){
        for (int i = 0; i < issuanceOfCopies.size(); i++){
            ui->tableWidgetIssuanceOfCopies->setItem(i, 0, new QTableWidgetItem(issuanceOfCopies.at(i).getSubscriber()));
            ui->tableWidgetIssuanceOfCopies->setItem(i, 1, new QTableWidgetItem(issuanceOfCopies.at(i).getDateOfIssue().toString("dd.MM.yyyy")));
            ui->tableWidgetIssuanceOfCopies->setItem(i, 2, new QTableWidgetItem(QString::number(issuanceOfCopies.at(i).getInstanceNumber())));
            ui->tableWidgetIssuanceOfCopies->setItem(i, 3, new QTableWidgetItem(issuanceOfCopies.at(i).getWrittenOff()));
        }
    }
}


CardInformation *CardViewForm::getViewci() const
{

    return viewci;
}


void CardViewForm::setViewci(CardInformation *value)
{
    viewci = value;
}


void CardViewForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape){
        qDebug() << "Esc";

        emit signalCardViewFormToListForm();
    }
}
