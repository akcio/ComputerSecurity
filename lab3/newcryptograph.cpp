#include "newcryptograph.h"
NewCryptograph::NewCryptograph()
{

}


QString NewCryptograph::EncodePermutation(QString toEncode, QList<int> key)
{
    QString encoded = "";//toEncode;
    int blockCount = (toEncode.count() + key.count() - 1) / (key.count());
    int neededSpaces = blockCount*(key.count()) - toEncode.count();
    for (int i=0; i<neededSpaces; i++)
        toEncode += QString::fromStdString("#");
    if (!CheckKey(key))
        return "Key Error";
    for (int i=0; i < blockCount; i++)
    {
        for (int k=0; k < (key.count()); k++)
        {
            //cout << i*key.count() + key.at(k) << " ";
            encoded += toEncode.at(i*key.count()+key.at(k) - 1);
        }
    }
    return encoded;
}

QString NewCryptograph::DecodePermutation(QString toDecode, QList<int> key)
{
    QString decoded = toDecode;//toEncode;
    int blockCount = (toDecode.count() + key.count() - 1) / (key.count());
    int neededSpaces = blockCount*(key.count()) - toDecode.count();
    for (int i=0; i<neededSpaces; i++)
        toDecode += QString::fromStdString("#");
    if (!CheckKey(key))
        return "Key Error";
    for (int i=0; i < blockCount; i++)
    {
        for (int k=0; k < (key.count()); k++)
        {
            decoded[i*key.count()+key.at(k) - 1] = toDecode[i*key.count() + k];
            //cout << i*key.count() + k;// i*key.count()+key.at(k) - 1;
            //decoded += toDecode.at(i*key.count()+key.at(k) - 1);
        }
    }
    return decoded;
}

bool NewCryptograph::CheckKey(QList<int> key)
{
    for (int i=1; i <= key.count(); i++)
    {
        //cout << key.at(i-1) << " contains" << key.contains(i) << endl;
        if (!key.contains(i))
            return false;
    }
    return true;
}
