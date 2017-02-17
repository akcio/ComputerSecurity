#ifndef NEWCRYPTOGRAPH_H
#define NEWCRYPTOGRAPH_H
#include <QCoreApplication>
#include <iostream>

using namespace std;

class NewCryptograph
{
public:
    NewCryptograph();
    static QString EncodePermutation(QString toEncode, QList<int> key);
    static QString DecodePermutation(QString toDecode, QList<int> key);
    static bool CheckKey(QList<int> key);
};

#endif // NEWCRYPTOGRAPH_H
