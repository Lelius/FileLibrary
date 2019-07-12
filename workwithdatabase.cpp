#include "workwithdatabase.h"

#include <QVector>


WorkWithDatabase::WorkWithDatabase()
{

}

bool WorkWithDatabase::openDatabase(QString &path)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "FL");
    db.setDatabaseName(path);
    QSqlQuery query(db);

    if (!db.open()){
        qDebug() << db.lastError().text();
        qDebug() << "Не открылась база данных!";
        return false;
    }

    qDebug() << "Новая база открыта";

    return true;
}

void WorkWithDatabase::removeDatabase()
{
    QSqlDatabase::removeDatabase("FL");
}

bool WorkWithDatabase::createNewDatabase()
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

    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    if (!query.exec(str)){
        qDebug() << query.lastError().text();
        qDebug() << "Таблицу не удалось создать или она уже создана.";
        return false;
    }
    return true;
}

bool WorkWithDatabase::insertNewCard(CardInformation &ci)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);
    /*query->prepare("INSERT INTO FileLibrary (inventoryNumber, receiptDate, designation,"
                  "name, comment, format1, format2, format3, format4, applicability, changeAccounting,"
                  "copyAccounting, issuanceOfCopies) VALUES (:inventoryNumber, ':receiptDate', ':designation',"
                  "':name', ':comment', :format1, :format2, :format3, :format4, ':applicability', ':changeAccounting',"
                  "':copyAccounting', ':issuanceOfCopies');");

    query->bindValue(":inventoryNumber",ci.getInventoryNumber());
    query->bindValue(":receiptDate", ci.getReceiptDate().toString());
    query->bindValue(":designation", ci.getDesignation());
    query->bindValue(":name", ci.getName());
    query->bindValue(":comment", ci.getComment());
    query->bindValue(":format1", ci.getKitFormat("А1"));
    query->bindValue(":format2", ci.getKitFormat("А2"));
    query->bindValue(":format3", ci.getKitFormat("А3"));
    query->bindValue(":format4", ci.getKitFormat("А4"));
    query->bindValue(":applicability", "applicability" + QString::number(ci.getInventoryNumber()));
    query->bindValue(":changeAccounting", "changeAccounting" + QString::number(ci.getInventoryNumber()));
    query->bindValue(":copyAccounting", "copyAccounting" + QString::number(ci.getInventoryNumber()));
    query->bindValue(":issuanceOfCopies", "issuanceOfCopies" + QString::number(ci.getInventoryNumber()));*/

    QString strF = "INSERT INTO FileLibrary (inventoryNumber, receiptDate, designation, name, comment, format1, format2, format3, format4, applicability, changeAccounting, copyAccounting, issuanceOfCopies) VALUES ( %1, '%2', '%3', '%4', '%5', %6, %7, %8, %9, '%10', '%11', '%12', '%13');";

    QString str = strF.arg(ci.getInventoryNumber())
            .arg(ci.getReceiptDate().toString("dd.MM.yyyy"))
            .arg(ci.getDesignation())
            .arg(ci.getName())
            .arg(ci.getComment())
            .arg(ci.getKitFormat("А1"))
            .arg(ci.getKitFormat("А2"))
            .arg(ci.getKitFormat("А3"))
            .arg(ci.getKitFormat("А4"))
            .arg("applicability" + QString::number(ci.getInventoryNumber()))
            .arg("changeAccounting" + QString::number(ci.getInventoryNumber()))
            .arg("copyAccounting" + QString::number(ci.getInventoryNumber()))
            .arg("issuanceOfCopies" + QString::number(ci.getInventoryNumber()));

    if (!query.exec(str)){
        qDebug() << query.lastError().text();
        qDebug() << "Вставка в таблицу не удалась!";
        return false;
    }

    return true;
}

bool WorkWithDatabase::editCard(CardInformation &ci)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    query.prepare("UPDATE FileLibrary "
                  "SET inventoryNumber = :inventoryNumber, "
                  "receiptDate = :receiptDate, designation = :designation, "
                  "name = :name, comment = :comment, format1 = :format1, "
                  "format2 = :format2, format3 = :format3, format4 = :format4, "
                  "applicability = :applicability, changeAccounting = :changeAccounting, "
                  "copyAccounting = :copyAccounting, issuanceOfCopies = :issuanceOfCopies "
                  "WHERE inventoryNumber = '" + QString::number(ci.getInventoryNumber()) + "';");

    query.bindValue(":inventoryNumber",ci.getInventoryNumber());
    query.bindValue(":receiptDate", ci.getReceiptDate().toString("dd.MM.yyyy"));
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

bool WorkWithDatabase::deleteCard(CardInformation &ci)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    query.prepare("DELETE FROM FileLibrary WHERE inventoryNumber = :inventoryNumber;");

    query.bindValue(":inventoryNumber", ci.getInventoryNumber());

    if (!query.exec()){
        qDebug() << query.lastError().text();
        qDebug() << "Удаление строки в таблице не удалось!";
        return false;
    }

    return true;
}

QVector<CardInformation> WorkWithDatabase::searchCardAll()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    QString str = "SELECT * FROM FileLibrary;";
    if(!query.exec(str))
        qDebug() << "Не выполнен запрос SELECT * FROM FileLibrary";

    QSqlRecord record = query.record();
    QVector<CardInformation> *cci = new QVector<CardInformation>();

    while (query.next()){
        CardInformation nextci;
        nextci.setInventoryNumber(query.value(record.indexOf("inventoryNumber")).toInt());
        QString strDate = query.value(record.indexOf("receiptDate")).toString();
        nextci.setReceiptDate(QDate::fromString(strDate, "dd.MM.yyyy"));
        nextci.setDesignation(query.value(record.indexOf("designation")).toString());
        nextci.setName(query.value(record.indexOf("name")).toString());
        nextci.setComment(query.value(record.indexOf("comment")).toString());
        nextci.setKitFormat("А1", query.value(record.indexOf("format1")).toInt());
        nextci.setKitFormat("А2", query.value(record.indexOf("format2")).toInt());
        nextci.setKitFormat("А3", query.value(record.indexOf("format3")).toInt());
        nextci.setKitFormat("А4", query.value(record.indexOf("format4")).toInt());



        cci->append(nextci);
    }

    return *cci;
}
