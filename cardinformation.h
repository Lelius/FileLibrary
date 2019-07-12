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
    CardInformation(const CardInformation &ci);

    int getInventoryNumber() const;
    void setInventoryNumber(int value);

    QDate getReceiptDate() const;
    void setReceiptDate(const QDate &value);

    QString getDesignation() const;
    void setDesignation(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    int getKitFormat(const QString &str) const;
    void setKitFormat(const QString &str, const int &value);

    QVector<ApplicabilityCard> getApplicability() const;
    void setApplicability(const QVector<ApplicabilityCard> &value);

    QVector<ChangeAccountingCard> getChangeAccounting() const;
    void setChangeAccounting(const QVector<ChangeAccountingCard> &value);

    QVector<CopyAccounting> getCopyAccounting() const;
    void setCopyAccounting(const QVector<CopyAccounting> &value);

    QVector<IssuanceOfCopies> getIssuanceOfCopies() const;
    void setIssuanceOfCopies(const QVector<IssuanceOfCopies> &value);

    QString getComment() const;
    void setComment(const QString &value);

private:
    int inventoryNumber;                            //инвентарный номер
    QDate receiptDate;                              //дата поступления
    QString designation;                            //обозначение
    QString name;                                   //наименование
    QString comment;                                //комментарий
    QMap<QString, int> kitFormat;                   //формат и количество листов
    QVector<ApplicabilityCard> applicability;       //применяемость
    QVector<ChangeAccountingCard> changeAccounting; //учет изменений
    QVector<CopyAccounting> copyAccounting;         //учет копий
    QVector<IssuanceOfCopies> issuanceOfCopies;     //выдача копий
};

#endif // CARDINFORMATION_H
