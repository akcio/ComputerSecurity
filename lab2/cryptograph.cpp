#include "cryptograph.h"

Cryptograph::Cryptograph()
{
}

Cryptograph::Cryptograph(unsigned int randomSeed)
{
    srand(randomSeed);
}

QString Cryptograph::EncodeOneAlphabet(QString toEncode, int key)
{
    QString encoded = "";
    for (int i=0; i<toEncode.count(); i++)
    {
        int newChar = ((toEncode.at(i).unicode()) + key) % 256;
        if (newChar == 0)
            newChar = 256;
        encoded += (char)newChar;
    }
    return encoded;
}

QString Cryptograph::DecodeOneAlphabet(QString toDecode, int key)
{
    QString decoded = "";
    for (int i=0; i<toDecode.count(); i++)
    {
        int newChar = (toDecode.at(i).unicode() - key) % 256;
        if (newChar == 0)
            newChar = 256;
        decoded += (char)newChar;
    }
    return decoded;
}

QString Cryptograph::EncodeMultiAlpabet(QString toEncode, QString key)
{
    QString encoded = "";
    for (int i=0; i<toEncode.count(); i++)
    {
        ushort newChar = ((toEncode.at(i).unicode()) + key.at(i % key.count()).unicode());
        /*if (newChar == 0)
            newChar = 255;*/
        encoded += (QChar)newChar;
    }
    return encoded;
}

QString Cryptograph::DecodeMultiAlpabet(QString toDecode, QString key)
{
    QString decoded = "";
    for (int i=0; i<toDecode.count(); i++)
    {
        ushort newChar = ((toDecode.at(i).unicode()) - key.at(i % key.count()).unicode());
        /*if (newChar == 0)
            newChar = 255;
            */
        decoded += (QChar)newChar;
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
    QString fileText;
    while (!in.atEnd())
    {
        ushort fileChar;
        in >> fileChar;
        if (fileChar == 0)
            break;
        fileText += (QChar)fileChar;
        //fileText += in.readLine();
    }
    file.close();
    return fileText;
}

void Cryptograph::SaveToFile(QString fileName, QString text)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    out.setCodec("UTF-8");

    out << text << endl;

    file.close();
}

QString Cryptograph::LoadFromFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return QString::fromStdString("");
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString fileText = "";

    while (!in.atEnd())
    {
        QChar fileChar;
        in >> fileChar;
        if (fileChar.unicode() == 0)
            break;
        fileText += (QChar)fileChar;
        //fileText += in.readLine();
    }
    //fileText = in.readAll();

    file.close();
    return fileText;
}
