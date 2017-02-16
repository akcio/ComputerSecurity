#ifndef CRYPTOGRAPH_H
#define CRYPTOGRAPH_H
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

class Cryptograph
{
public:
    Cryptograph();
    Cryptograph(unsigned int randomSeed);
    static QString EncodeOneAlphabet(QString toEncode, int key);
    static QString DecodeOneAlphabet(QString toDecode, int key);
    static QString EncodeMultiAlpabet(QString toEncode, QString key);
    static QString DecodeMultiAlpabet(QString toDecode, QString key);
    static QString GenerateKey(int length);
    static QString GenerateKey(int length, unsigned int randomSeed);
    static void SaveToFileUnicoded(QString fileName, QString text);
    static QString LoadFromFileUnicoded(QString fileName);
    void SaveToFile(QString fileName, QString text);
    QString LoadFromFile(QString fileName);
};

#endif // CRYPTOGRAPH_H
