#include "workwithdatabase.h"

WorkWithDatabase::WorkWithDatabase()
{

}

bool WorkWithDatabase::OpenDatabase(QString &path)
{

    *db = QSqlDatabase::addDatabase("QSQLITE", "FL");
    db->setDatabaseName(path);
    if (!db->open()){
        qDebug() << db->lastError().text();
        qDebug() << "Не открылась база данных!";
        return false;
    }
    return true;
}

void WorkWithDatabase::CloseDatabase()
{
    db->close();
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
                  "format1 INTEGER,"
                  "format2 INTEGER,"
                  "format3 INTEGER,"
                  "format4 INTEGER,"
                  "applicability TEXT,"
                  "changeAccounting TEXT,"
                  "copyAccounting TEXT,"
                  "issuanceOfCopies TEXT);";

    QSqlQuery query(*db);

    if (!query.exec()){
        qDebug() << query.lastError().text();
        qDebug() << "Таблицу не удалось создать или она уже создана.";
        return false;
    }
    return true;
}

bool WorkWithDatabase::InsertNewCard(CardInformation &ci)
{
    QSqlQuery query(*db);

    query.prepare("INSERT INTO FileLibrary (inventoryNumber, receiptDate, designation,"
                  "name, comment, format1, format2, format3, format4, applicability, changeAccounting,"
                  "copyAccounting, issuanceOfCopies) VALUES (:inventoryNumber, :receiptDate, :designation,"
                  ":name, :comment, :format1, :format2, :format3, :format4, :applicability, :changeAccounting,"
                  ":copyAccounting, :issuanceOfCopies);");

    query.bindValue(":inventoryNumber",ci.getInventoryNumber());
    query.bindValue(":receiptDate", ci.getReceiptDate().toString());
    query.bindValue(":designation", ci.getDesignation());
    query.bindValue(":name", ci.getName());
    query.bindValue(":comment", ci.getComment());
    query.bindValue(":format1", ci.getKitFormat("А1"));
    query.bindValue(":format2", ci.getKitFormat("А2"));
    query.bindValue(":format3", ci.getKitFormat("А3"));
    query.bindValue(":format4", ci.getKitFormat("А4"));
    query.bindValue(":applicability", "applicability" + QString::number(ci.getInventoryNumber()));
    query.bindValue(":changeAccounting", "changeAccounting" + QString::number(ci.getInventoryNumber()));
    query.bindValue(":copyAccounting", "copyAccounting" + QString::number(ci.getInventoryNumber()));
    query.bindValue(":issuanceOfCopies", "issuanceOfCopies" + QString::number(ci.getInventoryNumber()));

    if (!query.exec()){
        qDebug() << query.lastError().text();
        qDebug() << "Вставка в таблицу не удалась!";
        return false;
    }

    return true;
}

bool WorkWithDatabase::EditCard(CardInformation &ci)
{
    QSqlQuery query(*db);

    query.prepare("UPDATE FileLibrary "
                  "SET inventoryNumber = :inventoryNumber, "
                  "receiptDate = :receiptDate, designation = :designation, "
                  "name = :name, comment = :comment, format1 = :format1, "
                  "format2 = :format2, format3 = :format3, format4 = :format4, "
                  "applicability = :applicability, changeAccounting = :changeAccounting, "
                  "copyAccounting = :copyAccounting, issuanceOfCopies = :issuanceOfCopies "
                  "WHERE inventoryNumber = '" + QString::number(ci.getInventoryNumber()) + "';");

    query.bindValue(":inventoryNumber",ci.getInventoryNumber());
    query.bindValue(":receiptDate", ci.getReceiptDate().toString());
    query.bindValue(":designation", ci.getDesignation());
    query.bindValue(":name", ci.getName());
    query.bindValue(":comment", ci.getComment());
    query.bindValue(":format1", ci.getKitFormat("А1"));
    query.bindValue(":format2", ci.getKitFormat("А2"));
    query.bindValue(":format3", ci.getKitFormat("А3"));
    query.bindValue(":format4", ci.getKitFormat("А4"));
    query.bindValue(":applicability", "applicability" + QString::number(ci.getInventoryNumber()));
    query.bindValue(":changeAccounting", "changeAccounting" + QString::number(ci.getInventoryNumber()));
    query.bindValue(":copyAccounting", "copyAccounting" + QString::number(ci.getInventoryNumber()));
    query.bindValue(":issuanceOfCopies", "issuanceOfCopies" + QString::number(ci.getInventoryNumber()));

    if (!query.exec()){
        qDebug() << query.lastError().text();
        qDebug() << "Замена в таблице не удалась!";
        return false;
    }

    return true;
}

bool WorkWithDatabase::DeleteCard(CardInformation &ci)
{
    QSqlQuery query(*db);

    query.prepare("DELETE FROM FileLibrary WHERE inventoryNumber = :inventoryNumber;");

    query.bindValue(":inventoryNumber", ci.getInventoryNumber());

    if (!query.exec()){
        qDebug() << query.lastError().text();
        qDebug() << "Удаление строки в таблице не удалось!";
        return false;
    }

    return true;
}
