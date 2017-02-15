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
    enum DatabaseAnswer { HAS_ROW, ROW_BROKEN, NO_ROW };
    unsigned short CheckFileAndHash(QString fileName, QByteArray hash);
    void AddToDataBase(QString fileName, QByteArray hash);
private:
    QSqlDatabase db;
};

#endif // DATABASEWORKER_H
