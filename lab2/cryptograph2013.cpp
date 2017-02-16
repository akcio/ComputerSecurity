#include "Cryptograph2013.h"
#include <QCoreApplication>


Cryptograph2013::Cryptograph2013()
{

}
static QString Cryptograph2013::Encode(QString toEncode, unsigned int key)
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

static QString Cryptograph2013::Decode(QString toDecode, unsigned int key)
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

static bool Cryptograph2013::CheckKey(QList<int> key)
{
    for (int i=1; i<=key.length(); i++)
        if (!key.contains(i))
            return false;
    return true;
}

static QString Cryptograph2013::EncodePermutation(QString toEncode, QList<int> key)
{
    QString encoded = "";//toEncode;
    int blockCount = toEncode.count() / key.count();
    for (int i=0; i<toEncode.count() - blockCount*key.count(); i++)
    {
        toEncode += " ";
    }
    if (!CheckKey(key))
        return "Key Error";
    for (int i=0; i<blockCount; i++)
    {
        for (int k=0; k < key.count(); k++)
        {
            encoded[i*blockCount+k]=toEncode.at(i*blockCount+key[k]+1);
        }
    }
    return encoded;
}

static QString Cryptograph2013::DecodePermutation(QString toDecode, QList<int> key)
{
    QString decoded = "";//toEncode;
    int blockCount = toDecode.count() / key.count();
    for (int i=0; i<toDecode.count() - blockCount*key.count(); i++)
    {
        toDecode += " ";
    }
    if (!CheckKey(key))
        return "Key Error";
    for (int i=0; i<blockCount; i++)
    {
        for (int k=0; k < key.count(); k++)
        {
            //decoded[]=toDecode.at();
            decoded[i*blockCount+key[k]-1]=toDecode.at(i*blockCount+k);
        }
    }
    return decoded;
}

