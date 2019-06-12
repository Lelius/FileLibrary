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
