#include "saver.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
Saver::Saver()
{

}

bool Saver::Save(QString fileName, QString password)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
    QTextStream out(&file);
    out << password;
    return true;
}

bool Saver::Save(QString fileName, QList<QString> passwords)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
    QTextStream out(&file);
    unsigned int key = GenerateKey();
    foreach (auto password, passwords)
    {
        out << Encode(password, key) << endl;
    }
    return true;
}

QList<QString> Saver::Load(QString fileName, unsigned int key)
{
    QFile file(fileName);
    QList<QString> decoded;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return decoded;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString toDecode = in.readLine();
        decoded.append(Decode(toDecode, key));
    }
    return decoded;
}

QString Saver::Encode(QString toEncode, unsigned int key)
{
    //ENCODING
    QString encoded = toEncode;
    return encoded;
}

QString Saver::Decode(QString toDecode, unsigned int key)
{
    //DECODING
    QString decoded = toDecode;
    return decoded;
}

unsigned int Saver::GenerateKey()
{
    //GENERATE KEY!
    return 1;
}
