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
    query.prepare("INSERT INTO FileLibrary (inventoryNumber, receiptDate, designation,"
                  "name, comment, format1, format2, format3, format4, applicability, changeAccounting,"
                  "copyAccounting, issuanceOfCopies) VALUES (:inventoryNumber, :receiptDate, :designation,"
                  ":name, :comment, :format1, :format2, :format3, :format4, :applicability, :changeAccounting,"
                  ":copyAccounting, :issuanceOfCopies);");

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
        qDebug() << "Вставка в таблицу не удалась!";
        return false;
    }

    //миниформы
    if (!insertNewCardTablesMiniForm(ci)){
        qDebug() << "Сбой в создании таблиц миниформ";
        return false;
    }

    return true;
}


bool WorkWithDatabase::insertNewCardTablesMiniForm(CardInformation &ci)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    //applicability
    QString strPrepare = "CREATE TABLE IF NOT EXISTS applicability" + QString::number(ci.getInventoryNumber()) + "("
                         "introductionDate TEXT,"
                         "designation TEXT);";
    if (!query.exec(strPrepare)){
        qDebug() << "Не удалось создать таблицу applicability";
        return false;
    }

    if (ci.getApplicability().length() != 0){
        for (int i = 0; i < ci.getApplicability().length(); ++i){
            query.prepare("INSERT INTO applicability" + QString::number(ci.getInventoryNumber()) + "("
                          "introductionDate, designation) VALUES ("
                          ":introductionDate, :designation);");
            query.bindValue(":introductionDate", ci.getApplicability().at(i).getIntroductionDate().toString("dd.MM.yyyy"));
            query.bindValue(":designation", ci.getApplicability().at(i).getDesignation());
            query.exec();
        }
    }

    //changeAccounting
    query.prepare("CREATE TABLE IF NOT EXISTS changeAccounting" + QString::number(ci.getInventoryNumber()) + "("
                         "change TEXT,"
                         "notificationNumber INTEGER,"
                         "dateOfEntry TEXT);");
    if (!query.exec()){
        qDebug() << "Не удалось создать таблицу changeAccounting";
        return false;
    }

    if (ci.getChangeAccounting().length() != 0){
        for (int i = 0; i < ci.getChangeAccounting().length(); ++i){
            query.prepare("INSERT INTO changeAccounting" + QString::number(ci.getInventoryNumber()) + "("
                          "change, notificationNumber, dateOfEntry) VALUES ("
                          ":change, :notificationNumber, :dateOfEntry);");
            query.bindValue(":change", ci.getChangeAccounting().at(i).getChange());
            query.bindValue(":notificationNumber", ci.getChangeAccounting().at(i).getNotificationNumber());
            query.bindValue(":dateOfEntry", ci.getChangeAccounting().at(i).getDateOfEntry().toString("dd.MM.yyyy"));
            query.exec();
        }
    }

    //copyAccounting
    query.prepare("CREATE TABLE IF NOT EXISTS copyAccounting" + QString::number(ci.getInventoryNumber()) + "("
                         "copyNumberOfCopy INTEGER,"
                         "receiptDate TEXT,"
                         "dateOfWriteOff TEXT,"
                         "replacementDate TEXT);");
    if (!query.exec()){
        qDebug() << "Не удалось создать таблицу copyAccounting";
        return false;
    }

    if (ci.getCopyAccounting().length() != 0){
        for (int i = 0; i < ci.getCopyAccounting().length(); ++i){
            query.prepare("INSERT INTO copyAccounting" + QString::number(ci.getInventoryNumber()) + "("
                          "copyNumberOfCopy, receiptDate, dateOfWriteOff, replacementDate) VALUES ("
                          ":copyNumberOfCopy, :receiptDate, :dateOfWriteOff, :replacementDate);");
            query.bindValue(":copyNumberOfCopy", ci.getCopyAccounting().at(i).getCopyNumberOfCopy());
            query.bindValue(":receiptDate", ci.getCopyAccounting().at(i).getReceiptDate().toString("dd.MM.yyyy"));
            query.bindValue(":dateOfWriteOff", ci.getCopyAccounting().at(i).getDateOfWriteOff().toString("dd.MM.yyyy"));
            query.bindValue(":replacementDate", ci.getCopyAccounting().at(i).getReplacementDate().toString("dd.MM.yyyy"));
            query.exec();
        }
    }

    //issuanceOfCopies
    query.prepare("CREATE TABLE IF NOT EXISTS issuanceOfCopies" + QString::number(ci.getInventoryNumber()) + "("
                         "subscriber TEXT,"
                         "dateOfIssue TEXT,"
                         "instanceNumber INTEGER,"
                         "writtenOff TEXT);");
    if (!query.exec()){
        qDebug() << "Не удалось создать таблицу issuanceOfCopies";
        return false;
    }

    if (ci.getIssuanceOfCopies().length() != 0){
        for (int i = 0; i < ci.getIssuanceOfCopies().length(); ++i){
            query.prepare("INSERT INTO issuanceOfCopies" + QString::number(ci.getInventoryNumber()) + "("
                          "subscriber, dateOfIssue, instanceNumber, writtenOff) VALUES ("
                          ":subscriber, :dateOfIssue, :instanceNumber, :writtenOff);");
            query.bindValue(":subscriber", ci.getIssuanceOfCopies().at(i).getSubscriber());
            query.bindValue(":dateOfIssue", ci.getIssuanceOfCopies().at(i).getDateOfIssue().toString("dd.MM.yyyy"));
            query.bindValue(":instanceNumber", ci.getIssuanceOfCopies().at(i).getInstanceNumber());
            query.bindValue(":writtenOff", ci.getIssuanceOfCopies().at(i).getWrittenOff());
            query.exec();
        }

    }

    return true;
}


bool WorkWithDatabase::editCard(CardInformation &ci)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    if (!deleteCard(ci)){
        qDebug() << "Ошибка при удалении карточки";
        return false;
    }

    if (!insertNewCard(ci)){
        qDebug() << "Ошибка при вставке карточки";
        return false;
    }

    /*deleteCardTablesMiniForm(ci);

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

    if(!insertNewCardTablesMiniForm(ci)){
        qDebug() << "Замена таблиц миниформ не удалась";
        return false;
    }*/

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

    deleteCardTablesMiniForm(ci);

    return true;
}


void WorkWithDatabase::deleteCardTablesMiniForm(CardInformation &ci)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    query.prepare("DROP TABLE IF EXISTS applicability" + QString::number(ci.getInventoryNumber()) + ";");
    query.exec();
    query.prepare("DROP TABLE IF EXISTS changeAccounting" + QString::number(ci.getInventoryNumber()) + ";");
    query.exec();
    query.prepare("DROP TABLE IF EXISTS copyAccounting" + QString::number(ci.getInventoryNumber()) + ";");
    query.exec();
    query.prepare("DROP TABLE IF EXISTS issuanceOfCopies" + QString::number(ci.getInventoryNumber()) + ";");
    query.exec();
}


bool WorkWithDatabase::deleteCard(int inventoryNumber){
    CardInformation ci;
    ci.setInventoryNumber(inventoryNumber);
    return deleteCard(ci);
}


CardInformation WorkWithDatabase::searchCard(int inventoryNumber)
{
    CardInformation ci;

    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    query.prepare("SELECT * FROM FileLibrary WHERE inventoryNumber = :inventoryNumber;");
    query.bindValue(":inventoryNumber", inventoryNumber);
    query.exec();

    QSqlRecord record = query.record();
    if (record.isEmpty()){
        qDebug() << "Карточка под запрашиваемым номером отсутствует";
        return ci;
    }

    while (query.next()){
        ci.setInventoryNumber(query.value(record.indexOf("inventoryNumber")).toInt());
        ci.setReceiptDate(QDate::fromString(query.value(record.indexOf("receiptDate")).toString(), "dd.MM.yyyy"));
        ci.setDesignation(query.value(record.indexOf("designation")).toString());
        ci.setName(query.value(record.indexOf("name")).toString());
        ci.setComment(query.value(record.indexOf("comment")).toString());
        ci.setKitFormat("А1", query.value(record.indexOf("format1")).toInt());
        ci.setKitFormat("А2", query.value(record.indexOf("format2")).toInt());
        ci.setKitFormat("А3", query.value(record.indexOf("format3")).toInt());
        ci.setKitFormat("А4", query.value(record.indexOf("format4")).toInt());

        //-----------------------------------------------------------
        QVector<ApplicabilityCard> applicability;
        query.clear();
        record.clear();

        query.prepare("SELECT * FROM applicability" + QString::number(inventoryNumber) + ";");
        query.exec();
        record = query.record();

        while (query.next()){
            ApplicabilityCard appci;
            appci.setIntroductionDate(QDate::fromString(query.value(record.indexOf("introductionDate")).toString(), "dd.MM.yyyy"));
            appci.setDesignation(query.value(record.indexOf("designation")).toString());
            applicability.push_back(appci);
        }

        ci.setApplicability(applicability);

        //-------------------------------------------------------------
        QVector<ChangeAccountingCard> changeAccounting;
        query.clear();
        record.clear();

        query.prepare("SELECT * FROM changeAccounting" + QString::number(inventoryNumber) + ";");
        query.exec();
        record = query.record();

        while (query.next()){
            ChangeAccountingCard changeci;
            changeci.setChange(query.value(record.indexOf("change")).toString());
            changeci.setNotificationNumber(query.value(record.indexOf("notificationNumber")).toInt());
            changeci.setDateOfEntry(QDate::fromString(query.value(record.indexOf("dateOfEntry")).toString(), "dd.MM.yyyy"));
            changeAccounting.push_back(changeci);
        }

        ci.setChangeAccounting(changeAccounting);

        //----------------------------------------------------
        QVector<CopyAccounting> copyAccounting;
        query.clear();
        record.clear();

        query.prepare("SELECT * FROM copyAccounting" + QString::number(inventoryNumber) + ";");
        query.exec();
        record = query.record();

        while (query.next()){
            CopyAccounting copyci;
            copyci.setCopyNumberOfCopy(query.value(record.indexOf("copyNumberOfCopy")).toInt());
            copyci.setReceiptDate(QDate::fromString(query.value(record.indexOf("receiptDate")).toString(), "dd.MM.yyyy"));
            copyci.setDateOfWriteOff(QDate::fromString(query.value(record.indexOf("dateOfWriteOff")).toString(), "dd.MM.yyyy"));
            copyci.setReplacementDate(QDate::fromString(query.value(record.indexOf("replacementDate")).toString(), "dd.MM.yyyy"));
            copyAccounting.push_back(copyci);
        }

        ci.setCopyAccounting(copyAccounting);

        //------------------------------------------------
        QVector<IssuanceOfCopies> issuanceOfCopies;
        query.clear();
        record.clear();

        query.prepare("SELECT * FROM issuanceOfCopies" + QString::number(inventoryNumber) + ";");
        query.exec();
        record = query.record();

        while (query.next()){
            IssuanceOfCopies issuanceci;
            issuanceci.setSubscriber(query.value(record.indexOf("subscriber")).toString());
            issuanceci.setDateOfIssue(QDate::fromString(query.value(record.indexOf("dateOfIssue")).toString(), "dd.MM.yyyy"));
            issuanceci.setInstanceNumber(query.value(record.indexOf("instanceNumber")).toInt());
            issuanceci.setWrittenOff(query.value(record.indexOf("writtenOff")).toString());
            issuanceOfCopies.push_back(issuanceci);
        }

        ci.setIssuanceOfCopies(issuanceOfCopies);
    }

    return ci;
}


QVector<CardInformation> WorkWithDatabase::searchCardAll()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    QString str = "SELECT * FROM FileLibrary;";
    if(!query.exec(str))
        qDebug() << "Не выполнен запрос SELECT * FROM FileLibrary";

    QSqlRecord record = query.record();
    QVector<CardInformation> cci;

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



        cci.append(nextci);
    }

    return cci;
}


bool WorkWithDatabase::searchForInventoryNumber(int inventoryNumber)
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    query.prepare("SELECT * FROM FileLibrary WHERE inventoryNumber = :inventoryNumber;");
    query.bindValue(":inventoryNumber", inventoryNumber);
    query.exec();

    if (query.first())
        return true;
    return false;
}


bool WorkWithDatabase::searchForInventoryNumber(CardInformation &ci)
{
    return searchForInventoryNumber(ci.getInventoryNumber());
}


CardInformation WorkWithDatabase::searchNextCardFromInventoryNumber(int inventoryNumber)
{
    if (inventoryNumber >= searchMaxInventoryNumber()){
        return searchCard(searchMinInventoryNumber());
    }

    int i = inventoryNumber;
    while (!searchForInventoryNumber(++i )){

    }
    return searchCard(i);
}


CardInformation WorkWithDatabase::searchPreviousCardFromInventoryNumber(int inventoryNumber)
{
    if (inventoryNumber <= searchMinInventoryNumber()){
        return searchCard(searchMaxInventoryNumber());
    }

    int i = inventoryNumber;
    while (!searchForInventoryNumber(--i )){

    }
    return searchCard(i);
}


int WorkWithDatabase::searchMaxInventoryNumber()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    int maxInventoryNumber = (-1);

    query.prepare("SELECT MAX(inventoryNumber) AS maxInventoryNumber FROM FileLibrary;");
    query.exec();

    QSqlRecord record = query.record();
    while (query.next()){
        maxInventoryNumber = query.value(record.indexOf("maxInventoryNumber")).toInt();
    }
    return maxInventoryNumber;
}


int WorkWithDatabase::searchMinInventoryNumber()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    QSqlQuery query(db);

    int minInventoryNumber = (-1);

    query.prepare("SELECT MIN(inventoryNumber) AS minInventoryNumber FROM FileLibrary;");
    query.exec();

    QSqlRecord record = query.record();
    while (query.next()){
        minInventoryNumber = query.value(record.indexOf("minInventoryNumber")).toInt();
    }
    return minInventoryNumber;
}
