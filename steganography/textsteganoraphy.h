#ifndef TEXTSTEGANORAPHY_H
#define TEXTSTEGANORAPHY_H
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

class TextSteganoraphy
{
public:
    TextSteganoraphy(QString fileName);
    qint32 PrepareFile();
    void HideText(QString text);
    static QList<bool> StringToBits(QString text);
    QString GetHiddenText();
    QList<bool> GetHiddenBits();
    QByteArray ConvertFromBitsToBytes(QList<bool> bitList);
private:
    QString FileName;
};

#endif // TEXTSTEGANORAPHY_H
