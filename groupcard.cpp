#include "groupcard.h"


GroupCard::GroupCard(QObject *parent) : QObject(parent)
{

}


GroupCard::GroupCard(QMapGroup &mapIn, QObject *parent) : QObject(parent)
{
    setGroupCard(mapIn);
}


GroupCard::GroupCard(const QVector<CardInformation> &ci, QObject *parent) : QObject(parent)
{
    QMapGroup map = getGroupCard();
    for (int i = 0; i < ci.length(); i++){
        map.insert(ci[i].getInventoryNumber(), ci[i]);
    }
    setGroupCard(map);
}





QMap<int, CardInformation> GroupCard::getGroupCard() const
{
    return groupCard;
}

void GroupCard::setGroupCard(QMapGroup &value)
{
    groupCard = value;
}


void GroupCard::clearGroupCard()
{
    QMapGroup map = getGroupCard();
    map.clear();
    setGroupCard(map);
}

bool GroupCard::isEmptyGroupCard()
{
    return getGroupCard().isEmpty();
}


bool GroupCard::containsInGroupCard(int &inventoryNumber)
{
    return getGroupCard().contains(inventoryNumber);
}


bool GroupCard::containsInGroupCard(CardInformation &ci)
{
    return getGroupCard().contains(ci.getInventoryNumber());
}


void GroupCard::addGroupCard(int &inventoryNumber)
{
    WorkWithDatabase wwd;
    CardInformation ci;

    if (!wwd.searchForInventoryNumber(inventoryNumber)){
        qDebug() << "Попытка добавления в группу несуществующей карточки!";
        return;
    }
    else if (containsInGroupCard(inventoryNumber)){
        qDebug() << "Попытка дублирования карточки в группе!";
        return;
    }

    ci = wwd.searchCard(inventoryNumber);
    addGroupCard(ci);
}


void GroupCard::addGroupCard(CardInformation &ci)
{
    WorkWithDatabase wwd;

    if (!wwd.searchForInventoryNumber(ci)){
        qDebug() << "Попытка добавления в группу несуществующей карточки!";
        return;
    }
    else if (containsInGroupCard(ci)){
        qDebug() << "Попытка дублирования карточки в группе!";
        return;
    }

    QMapGroup *map = new QMapGroup(getGroupCard());
    map->insert(ci.getInventoryNumber(), ci);
    setGroupCard(*map);
    delete map;
}

void GroupCard::removeGroupCard(int &inventoryNumber)
{
    QMapGroup *map = new QMapGroup(getGroupCard());
    map->remove(inventoryNumber);
    setGroupCard(*map);
    delete map;
}

void GroupCard::removeGroupCard(CardInformation &ci)
{
    int inventoryNumber = ci.getInventoryNumber();
    removeGroupCard(inventoryNumber);
}
