//Учет копий

#include "copyaccounting.h"

CopyAccounting::CopyAccounting()
{
    setCopyNumberOfCopy(0);
    setReceiptDate(QDate());
    setDateOfWriteOff(QDate());
    setReplacementDate(QDate());
}

CopyAccounting::CopyAccounting(const int n, const QDate &receipt, const QDate &dowo, const QDate &replacment)
{
    setCopyNumberOfCopy(n);
    setReceiptDate(receipt);
    setDateOfWriteOff(dowo);
    setReplacementDate(replacment);
}

int CopyAccounting::getCopyNumberOfCopy() const
{
    return copyNumberOfCopy;
}

void CopyAccounting::setCopyNumberOfCopy(int value)
{
    copyNumberOfCopy = value;
}

QDate CopyAccounting::getReceiptDate() const
{
    return receiptDate;
}

void CopyAccounting::setReceiptDate(const QDate &value)
{
    receiptDate = value;
}

QDate CopyAccounting::getDateOfWriteOff() const
{
    return dateOfWriteOff;
}

void CopyAccounting::setDateOfWriteOff(const QDate &value)
{
    dateOfWriteOff = value;
}

QDate CopyAccounting::getReplacementDate() const
{
    return replacementDate;
}

void CopyAccounting::setReplacementDate(const QDate &value)
{
    replacementDate = value;
}
