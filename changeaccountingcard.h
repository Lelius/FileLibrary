//Учет изменений

#ifndef CHANGEACCOUNTINGCARD_H
#define CHANGEACCOUNTINGCARD_H

#include <QString>
#include <QDate>

class ChangeAccountingCard
{
public:
    ChangeAccountingCard();
    ChangeAccountingCard(const QString &str,const int n,const QDate &date);

    QString getChange() const;
    void setChange(const QString &value);

    int getNotificationNumber() const;
    void setNotificationNumber(int value);

    QDate getDateOfEntry() const;
    void setDateOfEntry(const QDate &value);

private:
    QString change;                 //изменение
    int notificationNumber;         //номер извещения
    QDate dateOfEntry;              //дата внесения
};

#endif // CHANGEACCOUNTINGCARD_H
