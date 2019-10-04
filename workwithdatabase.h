#ifndef WORKWITHDATABASE_H
#define WORKWITHDATABASE_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtDebug>
#include <QVector>
#include <QList>


#include "cardinformation.h"

class WorkWithDatabase
{
public:
    WorkWithDatabase();

    bool openDatabase(QString &str);
    void removeDatabase();
    bool createNewDatabase();
    bool createBuckupCurrentDatabase();
    bool openBuckupDatabase(QString &str);
    bool insertNewCard(CardInformation &ci);
    bool insertNewCardTablesMiniForm(CardInformation &ci);
    bool editCard(CardInformation &ci);
    bool deleteCard(CardInformation &ci);
    bool deleteCard(int inventoryNumber);
    void deleteCardTablesMiniForm(CardInformation &ci);
    bool searchForInventoryNumber(int inventoryNumber);
    bool searchForInventoryNumber(CardInformation &ci);
    CardInformation searchCard(int inventoryNumber);
    QVector<CardInformation> searchCardAll();
    int searchMaxInventoryNumber();
};

#endif // WORKWITHDATABASE_H
