#include "cryptograph.h"

Cryptograph::Cryptograph()
{
}

Cryptograph::Cryptograph(unsigned int randomSeed)
{
    srand(randomSeed);
}

QString Cryptograph::EncodeOneAlphabet(QString toEncode, unsigned int key)
{
    QString encoded = "";
    for (int i=0; i<toEncode.count(); i++)
    {
        int newChar = ((toEncode.at(i).toLatin1()) + key) % 256;
        /*if (newChar == 0)
            newChar = 255;*/
        encoded += (char)newChar;
    }
    return encoded;
}

QString Cryptograph::DecodeOneAlphabet(QString toDecode, unsigned int key)
{
    QString decoded = "";
    for (int i=0; i<toDecode.count(); i++)
    {
        int newChar = (toDecode.at(i).toLatin1() - key) % 256;
        /*if (newChar == 0)
            newChar = 255;*/
        decoded += (char)newChar;
    }
    return decoded;
}

QString Cryptograph::EncodeMultiAlpabet(QString toEncode, QString key)
{
    QString encoded = "";
    for (int i=0; i<toEncode.count(); i++)
    {
        int newChar = ((toEncode.at(i).toLatin1()) + key.at(i % key.count()).toLatin1()) % 256;
        /*if (newChar == 0)
            newChar = 255;*/
        encoded += (char)newChar;
    }
    return encoded;
}

QString Cryptograph::DecodeMultiAlpabet(QString toDecode, QString key)
{
    QString decoded = "";
    for (int i=0; i<toDecode.count(); i++)
    {
        int newChar = ((toDecode.at(i).toLatin1()) - key.at(i % key.count()).toLatin1()) % 256;
        /*if (newChar == 0)
            newChar = 255;
            */
        decoded += (char)newChar;
    }
    return decoded;
}

QString Cryptograph::GenerateKey(int length)
{
    srand(NULL);
    QString key = "";
    for (int i=0; i<length; i++)
    {
        key += (char)(rand() % ('z'-'a') + 'a');
    }

    return key;
}

QString Cryptograph::GenerateKey(int length, unsigned int randomSeed)
{
    srand(randomSeed);
    QString key = "";
    for (int i=0; i<length; i++)
    {
        key += (char)(rand() % ('z'-'a') + 'a');
    }
    return key;
}

void Cryptograph::SaveToFileUnicoded(QString fileName, QString text)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    for (int i=0; i<text.length(); i++)
    {
        out << text.at(i).unicode() << " ";//.toLatin1();
    }
    //out << text << endl;
    file.close();
}

QString Cryptograph::LoadFromFileUnicoded(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return QString::fromStdString("");
    QTextStream in(&file);
    QString fileText = "";
    while (!in.atEnd())
    {
        ushort fileChar;
        in >> fileChar;
        fileText += (QChar)fileChar;
        //fileText += in.readLine();
    }
    file.close();
    return fileText;
}

void SaveToFile(QString fileName, QString text)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    out << text << endl;
    file.close();
}

QString LoadFromFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return QString::fromStdString("");
    QTextStream in(&file);
    QString fileText = "";
    while (!in.atEnd())
    {
        fileText += in.readLine();
    }
    file.close();
    return fileText;
}
