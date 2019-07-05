#include "workwithdatabase.h"

WorkWithDatabase::WorkWithDatabase()
{

}

bool WorkWithDatabase::OpenDatabase(QString &path)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    return db.open();
}

void WorkWithDatabase::CloseDatabase()
{
    db.close();
}

bool WorkWithDatabase::CreateNewDatabase()
{
    QString str = "CREATE TABLE IF NOT EXISTS FileLibrary("
                  "serialNumber INTEGER PRIMARY KEY NOT NULL,"
                  "inventoryNumber INTEGER NOT NULL,"
                  "receiptDate TEXT,"
                  "designation TEXT,"
                  "name TEXT,"
                  "comment TEXT,"
                  "a1 INTEGER,"
                  "a2 INTEGER,"
                  "a3 INTEGER,"
                  "a4 INTEGER,"
                  "applicability TEXT,"
                  "changeAccounting TEXT,"
                  "copyAccounting TEXT,"
                  "issuanceOfCopies TEXT);";
    QSqlQuery query(str);
    return query.exec();
}

