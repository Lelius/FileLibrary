#ifndef GROUPCARD_H
#define GROUPCARD_H

#include <QObject>
#include <QMap>

#include "cardinformation.h"

class GroupCard : public QObject
{
    Q_OBJECT
public:
    explicit GroupCard(QObject *parent = nullptr);
    explicit GroupCard(QMap<int, CardInformation> &mapIn, QObject *parent = nullptr);
    explicit GroupCard(QVector<CardInformation> const &ci, QObject *parent = nullptr);

    QMap<int, CardInformation> getGroupCard() const;
    void setGroupCard(QMap<int, CardInformation> &value);

    void clearGroupCard();
    bool containsInGroupCard(int);
    bool containsInGroupCard(CardInformation);
    void addGroupCard(int);
    void addGroupCard(CardInformation);

private:

    QMap<int, CardInformation> groupCard;
};

#endif // GROUPCARD_H
