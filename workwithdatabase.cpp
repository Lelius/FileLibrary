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

