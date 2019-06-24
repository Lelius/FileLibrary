//Идентификационная карта

#include "cardinformation.h"
#include "applicabilitycard.h"

CardInformation::CardInformation()
{
    setInventoryNumber(0);
    setReceiptDate(QDate());
    setDesignation("");
    setName("");
    setComment("");

    setKitFormat("А1", 0);
    setKitFormat("А2", 0);
    setKitFormat("А3", 0);
    setKitFormat("А4", 0);
}

CardInformation::CardInformation(CardInformation &ci)
{
    setInventoryNumber(ci.getInventoryNumber());
    setReceiptDate(ci.getReceiptDate());
    setDesignation(ci.getDesignation());
    setName(ci.getName());
    setComment(ci.getComment());

    setKitFormat("А1", ci.getKitFormat("А1"));
    setKitFormat("А2", ci.getKitFormat("А2"));
    setKitFormat("А3", ci.getKitFormat("А3"));
    setKitFormat("А4", ci.getKitFormat("А4"));

    for (int i = 0; i < ci.applicability.length(); i++){
        applicability.push_back(ci.applicability[i]);
    }
    for (int i = 0; i < ci.changeAccounting.length(); i++){
        changeAccounting.push_back(ci.changeAccounting[i]);
    }
    for (int i = 0; i < ci.copyAccounting.length(); i++){
        copyAccounting.push_back(ci.copyAccounting[i]);
    }
    for (int i = 0; i < ci.issuanceOfCopies.length(); i++){
        issuanceOfCopies.push_back(ci.issuanceOfCopies[i]);
    }
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
    if (value.isValid())
        receiptDate = value;
    else{
        receiptDate = QDate();
    }
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

int CardInformation::getKitFormat(const QString &str) const
{
    return kitFormat.value(str, 0);
}

void CardInformation::setKitFormat(const QString &str, const int &value)
{
    kitFormat.insert(str, value);
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

QString CardInformation::getComment() const
{
    return comment;
}

void CardInformation::setComment(const QString &value)
{
    comment = value;
}
