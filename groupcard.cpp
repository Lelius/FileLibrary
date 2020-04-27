#include "groupcard.h"


GroupCard::GroupCard(QObject *parent) : QObject(parent)
{
    setGroupCard(new QMap<int, CardInformation>);
}


GroupCard::GroupCard(const QMap<int, CardInformation> &mapIn, QObject *parent) : QObject(parent)
{
    QMap<int, CardInformation> *map = new QMap<int, CardInformation>;
    QMap<int, CardInformation>::const_iterator i = mapIn.constBegin();
    while (i != mapIn.constEnd()){
        map->insert(i.key(), i.value());
        i++;
    }
    setGroupCard(map);
}


GroupCard::GroupCard(const QVector<CardInformation> &ci, QObject *parent) : QObject(parent)
{
    QMap<int, CardInformation> *map = new QMap<int, CardInformation>;
    for (int i = 0; i < ci.length(); i++){
        map->insert(ci[i].getInventoryNumber(), ci[i]);
    }
    setGroupCard(map);
}





QMap<int, CardInformation> *GroupCard::getGroupCard() const
{
    return groupCard;
}

void GroupCard::setGroupCard(QMap<int, CardInformation> *value)
{
    groupCard = value;
}
