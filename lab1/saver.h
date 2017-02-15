#ifndef SAVER_H
#define SAVER_H
#include <QCoreApplication>
#include <QFile>
class Saver
{
public:
    Saver();
    bool Save(QString fileName, QString password);
    bool Save(QString fileName, QList<QString> passwords);
    QList<QString> Load(QString filename, unsigned int key);
private:
    QString Encode(QString toEncode, unsigned int key);
    QString Decode(QString toDecode, unsigned int key);
    unsigned int GenerateKey();
};

#endif // SAVER_H
