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

QList<QString> Saver::Load(QString fileName)
{
    QFile file(fileName);
    QList<QString> decoded;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return decoded;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString toDecode = in.readLine();
        decoded.append(Decode(toDecode, GenerateKey()));
    }
    return decoded;
}

QString Saver::Encode(QString toEncode, unsigned int key)
{
    QString encoded = "";
    for (int i=0; i<toEncode.count(); i++)
    {
        int newChar = ((toEncode.at(i).toLatin1())+key) % 255;
        if (newChar == 0)
            newChar = 255;
        encoded += (char)newChar;
    }
    return encoded;
}

QString Saver::Decode(QString toDecode, unsigned int key)
{
    QString decoded = "";
    for (int i=0; i<toDecode.count(); i++)
    {
        int newChar = (toDecode.at(i).toLatin1()-key) % 255;
        if (newChar == 0)
            newChar = 255;
        decoded += (char)newChar;
    }
    return decoded;
}

unsigned int Saver::GenerateKey()
{
    //GENERATE KEY!
    return 3;
}
