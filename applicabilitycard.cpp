//Применяемость

#include "applicabilitycard.h"

ApplicabilityCard::ApplicabilityCard()
{
    introductionDate.setDate(0, 0, 0);
    designation = "";
}

ApplicabilityCard::ApplicabilityCard(const QDate &date,const QString &str)
{
    setIntroductionDate(date);
    setDesignation(str);
}

QDate ApplicabilityCard::getIntroductionDate() const
{
    return introductionDate;
}

void ApplicabilityCard::setIntroductionDate(const QDate &value)
{
    introductionDate = value;
}

QString ApplicabilityCard::getDesignation() const
{
    return designation;
}

void ApplicabilityCard::setDesignation(const QString &value)
{
    designation = value;
}
