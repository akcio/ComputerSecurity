#include "databaseworker.h"
#include <QCoreApplication>
#include "QtSql/QSqlDatabase"
#include <QtSql>

QSqlDatabase db;


DataBaseWorker::DataBaseWorker(QString databaseFile)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("123.db");
    db.setDatabaseName(databaseFile);
    db.open();
    QSqlQuery query;
    query.exec("Create TABLE FileData (fileName varchar(255) NOT NULL, hash varchar(512),PRIMARY KEY (fileName))");
}

unsigned short DataBaseWorker::CheckFileAndHash(QString fileName, QByteArray hash)
{
    QSqlQuery query;
    QString qu = "SELECT * FROM FileData WHERE fileName='" + fileName + "'";
    query.exec(qu);
    bool brokenRow = false;
    while (query.next())
    {
        QString hashFromDataBase = query.value(1).toString();
        if (hash.toHex().toStdString() == hashFromDataBase.toStdString())
            return 1;
        else
            brokenRow = true;

    }
    if (brokenRow)
        return 2;
    return 0;
}

void DataBaseWorker::AddToDataBase(QString fileName, QByteArray hash)
{
    QSqlQuery query;
    query.exec("INSERT INTO FileData (fileName, hash) VALUES('" + fileName + "', '" + hash.toHex() + "')");
}

QList<QString> DataBaseWorker::GetAllData()
{
    QList<QString> result;
    QSqlQuery query;
    QString qu = "SELECT * FROM FileData";
    query.exec(qu);
    while (query.next())
    {
        QString fileName = query.value(0).toString();
        QString hash = query.value(1).toString();
        result.append(fileName + " | " + hash);

    }
    return result;
}

DataBaseWorker::~DataBaseWorker()
{
    db.close();
}
