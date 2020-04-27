#include "groupcard.h"


GroupCard::GroupCard(QObject *parent) : QObject(parent)
{
    setGroupCard(new QMap<int, CardInformation>);
}


GroupCard::GroupCard(QMap<int, CardInformation> &mapIn, QObject *parent) : QObject(parent)
{
    setGroupCard(mapIn);
}


GroupCard::GroupCard(const QVector<CardInformation> &ci, QObject *parent) : QObject(parent)
{
    QMap<int, CardInformation> map = getGroupCard();
    for (int i = 0; i < ci.length(); i++){
        map.insert(ci[i].getInventoryNumber(), ci[i]);
    }
    setGroupCard(map);
}





QMap<int, CardInformation> GroupCard::getGroupCard() const
{
    return groupCard;
}

void GroupCard::setGroupCard(QMap<int, CardInformation> &value)
{
    groupCard = value;
}


void GroupCard::clearGroupCard()
{
    QMap<int, CardInformation> map = getGroupCard();
    map.clear();
    setGroupCard(map);
}


bool GroupCard::containsInGroupCard(int) //NEXT: продолжить здесь
{

}


bool GroupCard::containsInGroupCard(CardInformation)
{

}


void GroupCard::addGroupCard(int inventoryNumber)
{

}


void GroupCard::addGroupCard(CardInformation ci)
{

}
