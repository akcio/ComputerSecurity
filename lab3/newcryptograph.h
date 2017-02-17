#ifndef NEWCRYPTOGRAPH_H
#define NEWCRYPTOGRAPH_H
#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>

using namespace std;

class NewCryptograph
{
public:
    NewCryptograph();
    static QString EncodePermutation(QString toEncode, QList<int> key);
    static QString DecodePermutation(QString toDecode, QList<int> key);
    static bool CheckKey(QList<int> key);
    QString EncodeCardano(QString toEncode);
    void SetGridToDefault();
    QString DecodeCardano(QString toDecode);
    static void SaveToFile(QString fileName, QString text);
    static QString LoadFromFile(QString fileName);
private:
    bool openSpace[4][4] = {
        {0,0,1,0},
        {0,1,0,0},
        {0,0,0,0},
        {1,0,1,0},
    };
    void RotateGrid();
    void PrintGrid();
};

#endif // NEWCRYPTOGRAPH_H
