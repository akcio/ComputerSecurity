#include "graphicalsteganography.h"

GraphicalSteganography::GraphicalSteganography()
{

}

QList<bool> GraphicalSteganography::GetBitsFromBinary(QString fileName)
{
    QFile binaryFile(fileName);
    QDataStream inputStream(&binaryFile);
    if (!binaryFile.open(QIODevice::ReadOnly))
            return QList<bool>();
    QByteArray bytes;// = binaryFile.readAll();
    bytes.insert(4, binaryFile.readAll());
    qint32 length = bytes.count() - 4;
    QByteArray lengthByted = IntToQByteArray(length);
    for (int i=0; i<4; i++)
        bytes[i] = lengthByted[i];
    binaryFile.close();
    return QByteArrayToListBits(bytes);
}

QByteArray GraphicalSteganography::IntToQByteArray(qint32 myInt)
{
    qint8 first = (myInt  & 0x000000FF) >> 0;
    qint8 second = (myInt & 0x0000FF00) >> 8;
    qint8 third = (myInt  & 0x00FF0000) >> 16;
    qint8 fourth = (myInt & 0xFF000000) >> 24;
    QByteArray bytes;
    bytes.append(first);
    bytes.append(second);
    bytes.append(third);
    bytes.append(fourth);

    qint32 parsed = 0;

    parsed += first & 0xFF;
    parsed += (second << 8) & 0xFF00;
    parsed += (third << 16) & 0xFF0000;
    parsed += (fourth << 24) & 0xFF000000;

    bool super = parsed == myInt;
    return bytes;

}

qint32 GraphicalSteganography::QByteArrayToInt(QByteArray bytes)
{
    qint32 parsed = 0;
    parsed += bytes[0] & 0xFF;
    parsed += (bytes[1] << 8) & 0xFF00;
    parsed += (bytes[2] << 16) & 0xFF0000;
    parsed += (bytes[3] << 24) & 0xFF000000;
    return parsed;
}

QList<bool> GraphicalSteganography::QByteArrayToListBits(QByteArray bytes)
{
    QList<bool> bits;
    for (int i=0; i < bytes.count(); i++)
    {
        qint8 byte = bytes[i];
        bits.append(byte & 0x01);
        bits.append(byte & 0x02);
        bits.append(byte & 0x04);
        bits.append(byte & 0x08);
        bits.append(byte & 0x10);
        bits.append(byte & 0x20);
        bits.append(byte & 0x40);
        bits.append(byte & 0x80);
    }
    return bits;
}

int GraphicalSteganography::EncryptBit(int color, bool bit)
{
    int newColor = 0;
    QByteArray decodeMask;
    decodeMask.append(0x01*bit);
    decodeMask.append(0x02);
    decodeMask.append(0x04);
    decodeMask.append(0x08);
    decodeMask.append(0x10);
    decodeMask.append(0x20);
    decodeMask.append(0x40);
    decodeMask.append(0x80);
    for (int i=1; i<8; i++)
        newColor += color & decodeMask[i];
    return newColor + bit;
}

Problems GraphicalSteganography::Hide(QString imageName, QString binaryFileName)
{
    QImage Image;
    if (!Image.load(imageName, "BMP"))
        return Problems::CANNT_LOAD_IMAGE;
    QList<bool> binaryBits = GetBitsFromBinary(binaryFileName);
    if (binaryBits.count() == 0)
        return Problems::NO_BINARY;
    if (Image.byteCount() < binaryBits.count())
        return Problems::IMAGE_TO_SHORT;
    while (binaryBits.count() % 3 != 0)
        binaryBits.append(false);
    int bitIterator = 0;
    for (int height=0; height < Image.height(); height++)
        for (int width=0; width < Image.width(); width++)
            if (bitIterator < binaryBits.count())
            {
                int r, g, b, a;
                int rn, gn, bn, an;

                int rn1 = EncryptBit(r, binaryBits[bitIterator++]);
                int gn1 = EncryptBit(g, binaryBits[bitIterator++]);
                int bn1 = EncryptBit(b, binaryBits[bitIterator++]);


                Image.pixelColor(QPoint(width, height)).getRgb(&r, &g, &b, &a);
                QColor newColor(rn1, gn1, bn1, a);
                Image.setPixelColor(width, height, newColor);
                Image.pixelColor(QPoint(width, height)).getRgb(&rn, &gn, &bn, &an);
                int c = 10;
                int h = c + 10;


            }
            else
            {
                int r, g, b, a;
                Image.pixelColor(QPoint(width, height)).getRgb(&r, &g, &b, &a);
                QColor newColor(EncryptBit(r, false), EncryptBit(g, false), EncryptBit(b, false), a);
                Image.setPixelColor(width, height, newColor);

            }

    Image.save(imageName);
    //Image.save(imageName+"1", "BMP");
    return Problems::SUCCESS;
}

QByteArray GraphicalSteganography::ListBitsToQByteArray(QList<bool> listBits)
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
    while (listBits.count() % 8 == 0)
        listBits.append(false);
    qint8 byte = 0;
    if (listBits.count() > 0)
        byte = listBits[0] * decodeMask[0];
    for (int i=1; i<listBits.count(); i++)
    {
        if (i % 8 == 0)
        {
            converted.append(byte);
            byte = listBits[i] * decodeMask[0];
            continue;
        }
        byte += listBits[i] * decodeMask[i % 8];
    }
    return converted;
}

bool GraphicalSteganography::DecryptBit(int color)
{
    bool decryptedBit = color & 0x01;
    return decryptedBit;
}

std::string GraphicalSteganography::ParseError(Problems problem)
{
    if (problem == Problems::SUCCESS)
        return "Success\n";
    if (problem == Problems::NO_BINARY)
        return "Failed work with binary file\n";
    if (problem == Problems::CANNT_LOAD_IMAGE)
        return "Image can't load\n";
    if (problem == Problems::IMAGE_TO_SHORT)
        return "Image too short for this binary\n";
    return "Other error\n";
}

Problems GraphicalSteganography::Show(QString imageName, QString outputFileName)
{
    QImage Image;
    if (!Image.load(imageName, "BMP"))
        return Problems::CANNT_LOAD_IMAGE;
    QList<bool> binaryBits;
    for (int height = 0; height < Image.height(); height++)
        for (int width = 0; width < Image.width(); width++)
        {
            int r, g, b, a;
            Image.pixelColor(QPoint(width, height)).getRgb(&r, &g, &b, &a);
            binaryBits.append(DecryptBit(r));
            binaryBits.append(DecryptBit(g));
            binaryBits.append(DecryptBit(b));

        }
    QByteArray binaryFileData = ListBitsToQByteArray(binaryBits);
    QByteArray lengthByted;
    for (int i=0; i<4; i++)
        lengthByted.append(binaryFileData[i]);
    qint32 length = QByteArrayToInt(lengthByted);
    QByteArray dataToWrite = binaryFileData.mid(4, length);
    //binaryFileData.insert(0, );
    QFile outPutFile(outputFileName);
    if (!outPutFile.open(QIODevice::WriteOnly))
            return Problems::NO_BINARY;
    QDataStream outputStream(&outPutFile);

    outputStream.writeRawData(dataToWrite, length);
    outPutFile.close();

    return Problems::SUCCESS;

}
