#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H
#include <QCoreApplication>
#include <QString>
#include <QCoreApplication>
#include "QtSql/QSqlDatabase"
#include <QtSql>

class DataBaseWorker
{

public:
    DataBaseWorker(QString databaseFile);
    ~DataBaseWorker();
    unsigned short CheckFileAndHash(QString fileName, QByteArray hash);
    void AddToDataBase(QString fileName, QByteArray hash);
    QList<QString> GetAllData();
private:
    QSqlDatabase db;
};

#endif // DATABASEWORKER_H
