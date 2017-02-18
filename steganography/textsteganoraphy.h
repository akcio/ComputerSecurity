#ifndef TEXTSTEGANORAPHY_H
#define TEXTSTEGANORAPHY_H
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

class TextSteganoraphy
{
public:
    TextSteganoraphy(QString fileName);
    void PrepareFile();
    void HideText(QString text);
    QString GetHiddenText();
    int GetAvailableSymbolsCount();
    static QByteArray BitsToBytes(QList<bool> bitList);
    static QList<bool> StringToBits(QString text);
private:
    QString FileName;
    QList<bool> GetHiddenBits();

};

#endif // TEXTSTEGANORAPHY_H
