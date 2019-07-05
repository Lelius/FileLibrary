#ifndef WORKWITHDATABASE_H
#define WORKWITHDATABASE_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "cardinformation.h"

class WorkWithDatabase
{
public:
    WorkWithDatabase();

    bool OpenDatabase(QString &str);
    void CloseDatabase();
    bool CreateNewDatabase();
    bool CreateBuckupCurrentDatabase();
    bool OpenBuckupDatabase(QString &str);
    bool InsertNewCard(CardInformation &ci);
    bool EditCard(CardInformation &ci);
    bool DeleteCard(CardInformation &ci);
    QList<CardInformation> SearchCard(QMap<QString, QString> &map);

private:
    QSqlDatabase db;
};

#endif // WORKWITHDATABASE_H
