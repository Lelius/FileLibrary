//Учет копий

#ifndef COPYACCOUNTING_H
#define COPYACCOUNTING_H

#include <QDate>

class CopyAccounting
{
public:
    CopyAccounting();
    CopyAccounting(const int n,const QDate &receipt, const QDate &dowo, const QDate &replacment);

    int getCopyNumberOfCopy() const;
    void setCopyNumberOfCopy(int value);

    QDate getReceiptDate() const;
    void setReceiptDate(const QDate &value);

    QDate getDateOfWriteOff() const;
    void setDateOfWriteOff(const QDate &value);

    QDate getReplacementDate() const;
    void setReplacementDate(const QDate &value);

private:
    int copyNumberOfCopy;                   //номер экземпляра копии
    QDate receiptDate;                      //дата поступления
    QDate dateOfWriteOff;                   //дата списания
    QDate replacementDate;                  //дата замены
};

#endif // COPYACCOUNTING_H
