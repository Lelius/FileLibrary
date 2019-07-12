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
    bool editCard(CardInformation &ci);
    bool deleteCard(CardInformation &ci);
    QList<CardInformation> searchCard(QMap<QString, QString> &map);
    QVector<CardInformation> searchCardAll();
};

#endif // WORKWITHDATABASE_H
