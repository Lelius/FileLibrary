//Применяемость

#ifndef APPLICABILITYCARD_H
#define APPLICABILITYCARD_H

#include <QDate>

class ApplicabilityCard
{
public:
    ApplicabilityCard();
    ApplicabilityCard(const QDate &date,const QString &str);

    QDate getIntroductionDate() const;
    void setIntroductionDate(const QDate &value);

    QString getDesignation() const;
    void setDesignation(const QString &value);

private:
    QDate introductionDate;                 //дата введения
    QString designation;                    //обозначение
};

#endif // APPLICABILITYCARD_H
