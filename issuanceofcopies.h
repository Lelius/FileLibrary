//Выдача копий

#ifndef ISSUANCEOFCOPIES_H
#define ISSUANCEOFCOPIES_H

#include <QString>
#include <QDate>

class IssuanceOfCopies
{
public:
    IssuanceOfCopies();
    IssuanceOfCopies(const QString &, const QDate &, const int, const QString &);

    QString getSubscriber() const;
    void setSubscriber(const QString &value);

    QDate getDateOfIssue() const;
    void setDateOfIssue(const QDate &value);

    int getInstanceNumber() const;
    void setInstanceNumber(int value);

    QString getWrittenOff() const;
    void setWrittenOff(const QString &value);

private:
    QString subscriber;         //абонент
    QDate dateOfIssue;          //дата выдачи
    int instanceNumber;         //номер экземпляра
    QString writtenOff;         //списано
};

#endif // ISSUANCEOFCOPIES_H
