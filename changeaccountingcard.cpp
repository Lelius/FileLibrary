//Учет изменений

#include "changeaccountingcard.h"

ChangeAccountingCard::ChangeAccountingCard()
{
    setChange("");
    setNotificationNumber(0);
    setDateOfEntry(QDate());
}

ChangeAccountingCard::ChangeAccountingCard(const QString &str, const int n, const QDate &date)
{
    setChange(str);
    setNotificationNumber(n);
    setDateOfEntry(date);
}

QString ChangeAccountingCard::getChange() const
{
    return change;
}

void ChangeAccountingCard::setChange(const QString &value)
{
    change = value;
}

int ChangeAccountingCard::getNotificationNumber() const
{
    return notificationNumber;
}

void ChangeAccountingCard::setNotificationNumber(int value)
{
    notificationNumber = value;
}

QDate ChangeAccountingCard::getDateOfEntry() const
{
    return dateOfEntry;
}

void ChangeAccountingCard::setDateOfEntry(const QDate &value)
{
    dateOfEntry = value;
}
