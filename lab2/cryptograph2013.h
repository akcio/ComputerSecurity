#ifndef Cryptograph2013_H
#define Cryptograph2013_H
#include <QCoreApplication>

class Cryptograph2013
{
public:
    Cryptograph2013();
    static QString Encode(QString toEncode, unsigned int key);
    static QString Decode(QString toDecode, unsigned int key);
    static QString EncodePermutation(QString toEncode, QList<int> key);
    static QString DecodePermutation(QString toDecode, QList<int> key);
    static bool CheckKey(QList<int> key);
};

#endif // Cryptograph2013_H
