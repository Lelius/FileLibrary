//Идентификационная карта

#include "cardinformation.h"

CardInformation::CardInformation()
{
        inventoryNumber = 0;
        receiptDate = QDate::currentDate();
        designation = "";
        name = "";

}

int CardInformation::getInventoryNumber() const
{
    return inventoryNumber;
}

void CardInformation::setInventoryNumber(int value)
{
    inventoryNumber = value;
}

QDate CardInformation::getReceiptDate() const
{
    return receiptDate;
}

void CardInformation::setReceiptDate(const QDate &value)
{
    receiptDate = value;
}

QString CardInformation::getDesignation() const
{
    return designation;
}

void CardInformation::setDesignation(const QString &value)
{
    designation = value;
}

QString CardInformation::getName() const
{
    return name;
}

void CardInformation::setName(const QString &value)
{
    name = value;
}

QMap<QString, int> CardInformation::getSheetFormat() const
{
    return sheetFormat;
}

void CardInformation::setSheetFormat(const QMap<QString, int> &value)
{
    sheetFormat = value;
}

QVector<ApplicabilityCard> CardInformation::getApplicability() const
{
    return applicability;
}

void CardInformation::setApplicability(const QVector<ApplicabilityCard> &value)
{
    applicability = value;
}

QVector<ChangeAccountingCard> CardInformation::getChangeAccounting() const
{
    return changeAccounting;
}

void CardInformation::setChangeAccounting(const QVector<ChangeAccountingCard> &value)
{
    changeAccounting = value;
}

QVector<CopyAccounting> CardInformation::getCopyAccounting() const
{
    return copyAccounting;
}

void CardInformation::setCopyAccounting(const QVector<CopyAccounting> &value)
{
    copyAccounting = value;
}

QVector<IssuanceOfCopies> CardInformation::getIssuanceOfCopies() const
{
    return issuanceOfCopies;
}

void CardInformation::setIssuanceOfCopies(const QVector<IssuanceOfCopies> &value)
{
    issuanceOfCopies = value;
}
