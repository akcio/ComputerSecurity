#ifndef GRAPHICALSTEGANOGRAPHY_H
#define GRAPHICALSTEGANOGRAPHY_H
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QtGui/QBitmap>
#include <string>

enum Problems
{
    CANNT_LOAD_IMAGE,
    NO_BINARY,
    IMAGE_TO_SHORT,
    SUCCESS
};

class GraphicalSteganography
{
public:
    GraphicalSteganography();
    QList<bool> GetBitsFromBinary(QString fileName);
    Problems Hide(QString imageName, QString binaryFileName);
    Problems Show(QString imageName, QString outputFileName);
    QByteArray ListBitsToQByteArray(QList<bool> listBits);
    QList<bool> QByteArrayToListBits(QByteArray bytes);
    int EncryptBit(int color, bool bit);
    bool DecryptBit(int color);
    static std::string ParseError(Problems problem);


    QByteArray IntToQByteArray(qint32 myInt);
    qint32 QByteArrayToInt(QByteArray bytes);
};

#endif // GRAPHICALSTEGANOGRAPHY_H
