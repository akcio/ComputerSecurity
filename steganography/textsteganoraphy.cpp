#include "textsteganoraphy.h"

TextSteganoraphy::TextSteganoraphy(QString fileName)
{
    FileName = fileName;
}

qint32 TextSteganoraphy::PrepareFile()
{
    QFile inFile(FileName);
    QFile outFile("tmp.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return 0;
    QTextStream inStream(&inFile);
    QTextStream outStream(&outFile);
    QChar lastSymbol, currentSymbol;
    qint32 freePosCount = 1;
    inStream >> lastSymbol;
    outStream << lastSymbol;
    while(!inStream.atEnd())
    {
        inStream >> currentSymbol;
        if (currentSymbol.unicode() == 0)
            continue;
        if (lastSymbol == ' ' && currentSymbol == ' ')
            continue;
        lastSymbol = currentSymbol;
        freePosCount++;
        outStream << lastSymbol;
    }
    inFile.close();
    outFile.close();
    inFile.remove();
    outFile.rename(FileName);
    return freePosCount;
}

QList<bool> TextSteganoraphy::StringToBits(QString text)
{
    QByteArray textBytes;
    QList<bool> bitList;
    textBytes.insert(0, text);
    for (int i=0; i < textBytes.count(); i++)
    {
        qint8 byte = textBytes[i];
        bitList.append(byte & 0x01);
        bitList.append(byte & 0x02);
        bitList.append(byte & 0x04);
        bitList.append(byte & 0x08);
        bitList.append(byte & 0x10);
        bitList.append(byte & 0x20);
        bitList.append(byte & 0x40);
        bitList.append(byte & 0x80);
        /*
        bool testBit1 = byte & 0x01;
        bool testBit2 = byte & 0x02;
        bool testBit3 = byte & 0x04;
        bool testBit4 = byte & 0x08;
        bool testBit5 = byte & 0x10;
        bool testBit6 = byte & 0x20;
        bool testBit7 = byte & 0x40;
        bool testBit8 = byte & 0x80;
        */

    }
    return bitList;
}

void TextSteganoraphy::HideText(QString text)
{
    QList<bool> bitList = StringToBits(text);
    QFile inFile(FileName);
    QFile outFile(QString("tmp"));
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream inStream(&inFile);
    QTextStream outStream(&outFile);
    QChar currentSymbol;
    int bitListIterator = 0;
    while (!inStream.atEnd())
    {
        inStream >> currentSymbol;
        if (currentSymbol.unicode() == 0)
            continue;
        outStream << currentSymbol;
        if (currentSymbol == ' ' && bitListIterator < bitList.count())
            if (bitList[bitListIterator++])
                outStream << ' ';
    }
    inFile.close();
    outFile.close();
    inFile.remove();
    outFile.rename(FileName);
    return;
}

QList<bool> TextSteganoraphy::GetHiddenBits()
{
    QList<bool> bitList;
    QFile inFile(FileName);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return bitList;
    QTextStream inStream(&inFile);
    QChar lastSymbol='\0', currentSymbol;
    while(!inStream.atEnd())
    {
        inStream >> currentSymbol;
        if (currentSymbol.unicode() == 0)
            continue;
        if (currentSymbol == ' ' && lastSymbol == ' ')
        {
            inStream >> currentSymbol;
            lastSymbol = currentSymbol;
            bitList.append(true);
            continue;
        }
        if (currentSymbol != ' ' && lastSymbol == ' ')
            bitList.append(false);
        lastSymbol = currentSymbol;
    }
    inFile.close();
    return bitList;
}

QByteArray TextSteganoraphy::ConvertFromBitsToBytes(QList<bool> bitList)
{
    QByteArray decodeMask;
    decodeMask.append(0x01);
    decodeMask.append(0x02);
    decodeMask.append(0x04);
    decodeMask.append(0x08);
    decodeMask.append(0x10);
    decodeMask.append(0x20);
    decodeMask.append(0x40);
    decodeMask.append(0x80);
    QByteArray converted;
    qint8 byte = 0;
    if (bitList.count() > 0)
        byte = bitList[0] * decodeMask[0];
    for (int i=1; i<bitList.count(); i++)
    {
        if (i % 8 == 0)
        {
            converted.append(byte);
            byte = bitList[i] * decodeMask[0];
            continue;
        }
        byte += bitList[i] * decodeMask[i % 8];
    }
    return converted;
}

QString TextSteganoraphy::GetHiddenText()
{
    QByteArray stringByted = ConvertFromBitsToBytes(GetHiddenBits());
    return stringByted;
}
