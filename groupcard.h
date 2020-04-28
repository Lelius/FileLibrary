#ifndef GROUPCARD_H
#define GROUPCARD_H

#include <QObject>
#include <QMap>

#include "cardinformation.h"
#include "workwithdatabase.h"

class GroupCard : public QObject
{
    Q_OBJECT
public:

    typedef QMap<int, CardInformation> QMapGroup;

    explicit GroupCard(QObject *parent = nullptr);
    explicit GroupCard(QMapGroup &mapIn, QObject *parent = nullptr);
    explicit GroupCard(QVector<CardInformation> const &ci, QObject *parent = nullptr);

    QMap<int, CardInformation> getGroupCard() const;
    void setGroupCard(QMapGroup &value);

    void clearGroupCard();
    bool isEmptyGroupCard();
    bool containsInGroupCard(int &);
    bool containsInGroupCard(CardInformation &);
    void addGroupCard(int &);
    void addGroupCard(CardInformation &);
    void removeGroupCard(int &);
    void removeGroupCard(CardInformation &);

private:

    QMapGroup groupCard;
};

#endif // GROUPCARD_H
