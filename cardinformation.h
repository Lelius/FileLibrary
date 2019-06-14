//Идентификационная карта

#ifndef CARDINFORMATION_H
#define CARDINFORMATION_H

#include <QDate>
#include <QMap>
#include <QVector>

#include "applicabilitycard.h"
#include "changeaccountingcard.h"
#include "copyaccounting.h"
#include "issuanceofcopies.h"

class CardInformation
{
public:
    CardInformation();

    int getInventoryNumber() const;
    void setInventoryNumber(int value);

    QDate getReceiptDate() const;
    void setReceiptDate(const QDate &value);

    QString getDesignation() const;
    void setDesignation(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QMap<QString, int> getSheetFormat() const;
    void setSheetFormat(const QMap<QString, int> &value);

    QVector<ApplicabilityCard> getApplicability() const;
    void setApplicability(const QVector<ApplicabilityCard> &value);

    QVector<ChangeAccountingCard> getChangeAccounting() const;
    void setChangeAccounting(const QVector<ChangeAccountingCard> &value);

    QVector<CopyAccounting> getCopyAccounting() const;
    void setCopyAccounting(const QVector<CopyAccounting> &value);

    QVector<IssuanceOfCopies> getIssuanceOfCopies() const;
    void setIssuanceOfCopies(const QVector<IssuanceOfCopies> &value);

private:
    int inventoryNumber;                            //инвентарный номер
    QDate receiptDate;                              //дата поступления
    QString designation;                            //обозначение
    QString name;                                   //наименование
    QMap<QString, int> sheetFormat;                 //формат и количество листов
    QVector<ApplicabilityCard> applicability;       //применяемость
    QVector<ChangeAccountingCard> changeAccounting; //учет изменений
    QVector<CopyAccounting> copyAccounting;         //учет копий
    QVector<IssuanceOfCopies> issuanceOfCopies;     //выдача копий
};

#endif // CARDINFORMATION_H
