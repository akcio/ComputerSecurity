#include <QCoreApplication>
#include "QtSql/QSqlDatabase"
#include <QtSql>
#include <databaseworker.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string fileName;
    cout << "Введи имя файла базы данных: ";
    cin >> fileName;
    QString QfileName = QString::fromStdString(fileName);
    DataBaseWorker db(QfileName);
    while (true)
    {
        cout << "Введи имя файла для проверки: ";
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
                cout << "Файл не найден. Добавлен в базу" << endl;
            }
            if (result == 2)
                cout << "Хэш не совпал" << endl;
            if (result == 1)
                cout << "Файл ок" << endl;
        }
        else
        {
            cout << "Не удалось открыть файл" << endl;
        }
    }

   return 0;
}
