#include <QDate>
#include <QIntValidator>

#include "cardeditform.h"
#include "ui_cardeditform.h"
#include "cardinformation.h"
#include "applicabilityminiform.h"
#include "changeaccountingminiform.h"
#include "copyaccountingminiform.h"

CardEditForm::CardEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardEditForm)
{
    ui->setupUi(this);
    newci = new CardInformation();
    newci->setReceiptDate(QDate::currentDate());
    ui->dateEditReceiptDate->setDate(newci->getReceiptDate());

    cardEditInit();

    QIntValidator *intValidator = new QIntValidator(1, 1000000, this);
    ui->lineEditInventoryNumber->setValidator(intValidator);
}

CardEditForm::CardEditForm(CardInformation *ci, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardEditForm)
{
    ui->setupUi(this);
    newci = new CardInformation(*ci);

    cardEditInit();

    QIntValidator *intValidator = new QIntValidator(1, 1000000, this);
    ui->lineEditInventoryNumber->setValidator(intValidator);
}

CardEditForm::~CardEditForm()
{
    delete ui;
}

void CardEditForm::on_pushButtonSaveCard_clicked()
{
    newci->setInventoryNumber(ui->lineEditInventoryNumber->text().toInt());
    newci->setReceiptDate(ui->dateEditReceiptDate->date());
    newci->setDesignation(ui->lineEditDesignation->text());

    newci->setKitFormat("А1", ui->spinBoxA1->value());
    newci->setKitFormat("А2", ui->spinBoxA2->value());
    newci->setKitFormat("А3", ui->spinBoxA3->value());
    newci->setKitFormat("А4", ui->spinBoxA4->value());

    newci->setName(ui->textEditName->toPlainText());
    newci->setComment(ui->textEditComment->toPlainText());

    emit signalSaveCard(newci);
}

void CardEditForm::cardEditInit()
{
    ui->lineEditInventoryNumber->setText(QString::number(newci->getInventoryNumber()));
    ui->dateEditReceiptDate->setDate(newci->getReceiptDate());
    ui->lineEditDesignation->setText(newci->getDesignation());

    ui->spinBoxA1->setValue(newci->getKitFormat("А1"));
    ui->spinBoxA2->setValue(newci->getKitFormat("А2"));
    ui->spinBoxA3->setValue(newci->getKitFormat("А3"));
    ui->spinBoxA4->setValue(newci->getKitFormat("А4"));

    ui->textEditName->setText(newci->getName());
    ui->textEditComment->setText(newci->getComment());

    //Applicability (Применяемость)
    QVector<ApplicabilityCard> applicability = newci->getApplicability();
    ui->tableWidgetApplicability->setRowCount(applicability.size());
    ui->tableWidgetApplicability->setColumnCount(2);
    QStringList lst;
    lst << " Дата введения " << " Обозначение ";
    ui->tableWidgetApplicability->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerApplicability = ui->tableWidgetApplicability->horizontalHeader();
    headerApplicability->setSectionResizeMode(QHeaderView::Stretch);

    if (!(newci->getApplicability().isEmpty())){
        for (int i = 0; i < applicability.size();i++){
            ui->tableWidgetApplicability->setItem(i, 0, new QTableWidgetItem(applicability.at(i).getIntroductionDate().toString("dd.MM.yyyy")));
            ui->tableWidgetApplicability->setItem(i, 1, new QTableWidgetItem(applicability.at(i).getDesignation()));
        }
    }

    //ChangeAccounting (Учет изменений)
    QVector<ChangeAccountingCard> changeAccountingCard = newci->getChangeAccounting();
    ui->tableWidgetChangeAccounting->setRowCount(changeAccountingCard.length());
    ui->tableWidgetChangeAccounting->setColumnCount(3);
    lst.clear();
    lst << " Изменение " << " N извещения " << " Дата внесения ";
    ui->tableWidgetChangeAccounting->setHorizontalHeaderLabels(lst);
    ui->tableWidgetChangeAccounting->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerChangeAccounting = ui->tableWidgetChangeAccounting->horizontalHeader();
    headerChangeAccounting->setSectionResizeMode(QHeaderView::Stretch);

    if (!(newci->getChangeAccounting().isEmpty())){
        for (int i = 0; i < changeAccountingCard.size(); i++){
            ui->tableWidgetChangeAccounting->setItem(i, 0, new QTableWidgetItem(changeAccountingCard.at(i).getChange()));
            ui->tableWidgetChangeAccounting->setItem(i, 1, new QTableWidgetItem(QString::number(changeAccountingCard.at(i).getNotificationNumber())));
            ui->tableWidgetChangeAccounting->setItem(i, 2, new QTableWidgetItem(changeAccountingCard.at(i).getDateOfEntry().toString("dd.MM.yyy")));
        }
    }

    //CopyAccounting (Учет копий)
    QVector<CopyAccounting> copyAccounting = newci->getCopyAccounting();
    ui->tableWidgetCopyAccounting->setRowCount(copyAccounting.length());
    ui->tableWidgetCopyAccounting->setColumnCount(4);
    lst.clear();
    lst << " N экз. копии " << " Дата поступ. " << " списания " << " замены ";
    ui->tableWidgetCopyAccounting->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerCopyAccounting = ui->tableWidgetCopyAccounting->horizontalHeader();
    headerCopyAccounting->setSectionResizeMode(QHeaderView::Stretch);

    if (!(newci->getCopyAccounting().isEmpty())){
        for (int i = 0; i < copyAccounting.size(); i++){
            ui->tableWidgetCopyAccounting->setItem(i, 0, new QTableWidgetItem(QString::number(copyAccounting.at(i).getCopyNumberOfCopy())));
            ui->tableWidgetCopyAccounting->setItem(i, 1, new QTableWidgetItem(copyAccounting.at(i).getReceiptDate().toString("dd.MM.yyyy")));
            ui->tableWidgetCopyAccounting->setItem(i, 2, new QTableWidgetItem(copyAccounting.at(i).getDateOfWriteOff().toString("dd.MM.yyyy")));
            ui->tableWidgetCopyAccounting->setItem(i, 3, new QTableWidgetItem(copyAccounting.at(i).getReplacementDate().toString("dd.MM.yyyy")));
        }
    }

    //IssuanceOfCopies (Выдача копий)
    QVector<IssuanceOfCopies> issuanceOfCopies = newci->getIssuanceOfCopies();
    ui->tableWidgetIssuanceOfCopies->setRowCount(issuanceOfCopies.length());
    ui->tableWidgetIssuanceOfCopies->setColumnCount(4);
    lst.clear();
    lst << " Абоненты " << " Дата выдачи "  << " N экземпляра " << " Списано ";
    ui->tableWidgetIssuanceOfCopies->setHorizontalHeaderLabels(lst);
    ui->tableWidgetApplicability->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *headerIssuanceOfCopies = ui->tableWidgetIssuanceOfCopies->horizontalHeader();
    headerIssuanceOfCopies->setSectionResizeMode(QHeaderView::Stretch);

    if (!(newci->getIssuanceOfCopies().isEmpty())){
        for (int i = 0; i < issuanceOfCopies.size(); i++){
            ui->tableWidgetIssuanceOfCopies->setItem(i, 0, new QTableWidgetItem(issuanceOfCopies.at(i).getSubscriber()));
            ui->tableWidgetIssuanceOfCopies->setItem(i, 1, new QTableWidgetItem(issuanceOfCopies.at(i).getDateOfIssue().toString()));
            ui->tableWidgetIssuanceOfCopies->setItem(i, 2, new QTableWidgetItem(issuanceOfCopies.at(i).getInstanceNumber()));
            ui->tableWidgetIssuanceOfCopies->setItem(i, 3, new QTableWidgetItem(issuanceOfCopies.at(i).getWrittenOff()));
        }
    }
}

void CardEditForm::on_pushButtonApplicabilityAdd_clicked()
{
    newWindow = new QWidget();
    ApplicabilityMiniForm *mini = new ApplicabilityMiniForm();
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(mini);
    newWindow->setLayout(layout);
    newWindow->setWindowModality(Qt::WindowModality::ApplicationModal);

    QPoint point = QCursor::pos();
    newWindow->move(point.x() - newWindow->size().width()/4, point.y() - newWindow->size().height()/4);

    newWindow->show();
    connect(mini, &ApplicabilityMiniForm::signalApplicabilityMiniFormClose, this, &CardEditForm::slotApplicabilityMiniFormClose);
    connect(mini, &ApplicabilityMiniForm::signalApplicabilityMiniFormAdd, this, &CardEditForm::slotApplicabilityMiniFormAdd);
}

//реакция на нажатие кнопки
void CardEditForm::slotApplicabilityMiniFormClose()
{
    CardEditForm::newWindow->close();
}

//реакция на нажатие кнопки
void CardEditForm::slotApplicabilityMiniFormAdd(ApplicabilityCard &a)
{
    QVector<ApplicabilityCard> v = newci->getApplicability();
    v.push_back(a);
    newci->setApplicability(v);

    slotApplicabilityMiniFormClose();

    cardEditInit();
}

void CardEditForm::on_lineEditInventoryNumber_textChanged(const QString &arg1)
{
    newci->setInventoryNumber(arg1.toInt());
}

void CardEditForm::on_dateEditReceiptDate_dateChanged(const QDate &date)
{
    newci->setReceiptDate(date);
}

void CardEditForm::on_lineEditDesignation_textChanged(const QString &arg1)
{
    newci->setDesignation(arg1);
}

void CardEditForm::on_textEditName_textChanged()
{
    newci->setName(ui->textEditName->toPlainText());
}

void CardEditForm::on_textEditComment_textChanged()
{
    newci->setComment(ui->textEditComment->toPlainText());
}

void CardEditForm::on_spinBoxA1_valueChanged(int arg1)
{
    newci->setKitFormat("А1", arg1);
}

void CardEditForm::on_spinBoxA2_valueChanged(int arg1)
{
    newci->setKitFormat("А2", arg1);
}

void CardEditForm::on_spinBoxA3_valueChanged(int arg1)
{
    newci->setKitFormat("А3", arg1);
}

void CardEditForm::on_spinBoxA4_valueChanged(int arg1)
{
    newci->setKitFormat("А4", arg1);
}

//-----------------------------------------------------------------
void CardEditForm::on_pushButtonChangeAccountingAdd_clicked()
{
    newWindow = new QWidget();
    ChangeAccountingMiniForm *mini = new ChangeAccountingMiniForm();
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(mini);
    newWindow->setLayout(layout);
    newWindow->setWindowModality(Qt::WindowModality::ApplicationModal);

    QPoint point = QCursor::pos();
    newWindow->move(point.x() - newWindow->size().width()/4, point.y() - newWindow->size().height()/4);

    newWindow->show();

    connect(mini, &ChangeAccountingMiniForm::signalChangeAccountingMiniFormAdd, this, &CardEditForm::slotChangeAccountingMiniFormAdd);
    connect(mini, &ChangeAccountingMiniForm::signalChangeAccountingMiniFormClose, this, &CardEditForm::slotChangeAccountingMiniFormClose);
}

void CardEditForm::slotChangeAccountingMiniFormAdd(ChangeAccountingCard &arg)
{
    QVector<ChangeAccountingCard> v = newci->getChangeAccounting();
    v.push_back(arg);
    newci->setChangeAccounting(v);

    slotChangeAccountingMiniFormClose();

    cardEditInit();
}

void CardEditForm::slotChangeAccountingMiniFormClose()
{
    newWindow->close();
}

//----------------------------------------------------------------------
void CardEditForm::on_pushButtonCopyAccountingAdd_clicked()
{
    newWindow = new QWidget();
    CopyAccountingMiniForm *mini = new CopyAccountingMiniForm();
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(mini);
    newWindow->setLayout(layout);
    newWindow->setWindowModality(Qt::WindowModality::ApplicationModal);

    QPoint point = QCursor::pos();
    newWindow->move(point.x() - newWindow->size().width()/4, point.y() - newWindow->size().height()/4);

    newWindow->show();

    connect(mini, &CopyAccountingMiniForm::signalCopyAccounteMiniFormClose, this, &CardEditForm::slotCopyAccountingMiniFormClose);
    connect(mini, &CopyAccountingMiniForm::signalCopyAccountMiniFormAdd, this, &CardEditForm::slotCopyAccountingMiniFormAdd);
}

void CardEditForm::slotCopyAccountingMiniFormAdd(CopyAccounting &arg)
{
    QVector<CopyAccounting> v = newci->getCopyAccounting();
    v.push_back(arg);
    newci->setCopyAccounting(v);

    slotCopyAccountingMiniFormClose();

    cardEditInit();
}

void CardEditForm::slotCopyAccountingMiniFormClose()
{
    newWindow->close();
}
