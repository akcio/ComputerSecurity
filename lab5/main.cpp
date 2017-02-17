#include <QCoreApplication>
#include "QtSql/QSqlDatabase"
#include <QtSql>
#include <databaseworker.h>
#include <iostream>
#include <string>
#include <checker.h>

using namespace std;

void PrintAllDataBase(DataBaseWorker db)
{
    QList<QString> allStrings = db.GetAllData();
    foreach (auto row, allStrings)
    {
        cout << row.toStdString() << endl;
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Checker checker;
    if (!checker.CheckBinary())
    {
        cout << "Хэшсумма не совпала" << endl;
        return 0;
    }
    string fileName;
    cout << "Input database filename: ";
    cin >> fileName;
    QString QfileName = QString::fromStdString(fileName);
    DataBaseWorker db(QfileName);
    //PrintAllDataBase(db);
    while (true)
    {
        cout << "Input filename to check: ";
        cin >> fileName;
        QfileName = QString::fromStdString(fileName);
        QFile* file = new QFile(QfileName);
        if(file->open(QIODevice::ReadOnly))
        {
            QCryptographicHash* hash;
            QByteArray resultHash = hash->hash(file->readAll(),QCryptographicHash::Sha512);
            file->close();
            unsigned short result = db.CheckFileAndHash(QfileName, resultHash);
            if (result == 0)
            {
                db.AddToDataBase(QfileName, resultHash);
                cout << "File not found. Added to database" << endl;
            }
            if (result == 2)
                cout << "Hash doesn't match" << endl;
            if (result == 1)
                cout << "File ok!" << endl;
        }
        else
        {
            cout << "Not found | or open eroor with file" << endl;
        }
    }

   return 0;
}
