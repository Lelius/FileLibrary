//Выдача копий

#include "issuanceofcopies.h"

IssuanceOfCopies::IssuanceOfCopies()
{
    setSubscriber("");
    setDateOfIssue(QDate());
    setInstanceNumber(0);
    setWrittenOff("");
}

IssuanceOfCopies::IssuanceOfCopies(const QString &sub, const QDate &d, const int n, const QString &wrOff)
{
    setSubscriber(sub);
    setDateOfIssue(d);
    setInstanceNumber(n);
    setWrittenOff(wrOff);
}

QString IssuanceOfCopies::getSubscriber() const
{
    return subscriber;
}

void IssuanceOfCopies::setSubscriber(const QString &value)
{
    subscriber = value;
}

QDate IssuanceOfCopies::getDateOfIssue() const
{
    return dateOfIssue;
}

void IssuanceOfCopies::setDateOfIssue(const QDate &value)
{
    dateOfIssue = value;
}

int IssuanceOfCopies::getInstanceNumber() const
{
    return instanceNumber;
}

void IssuanceOfCopies::setInstanceNumber(int value)
{
    instanceNumber = value;
}

QString IssuanceOfCopies::getWrittenOff() const
{
    return writtenOff;
}

void IssuanceOfCopies::setWrittenOff(const QString &value)
{
    writtenOff = value;
}
