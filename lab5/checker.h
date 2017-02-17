#ifndef CHEKER_H
#define CHEKER_H
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <string>
#include <QFileInfo>

class Checker
{
public:
    Checker();
    bool HasHashFile();
    void CreateHashFile();
    QString GetHash();
    QString LoadHash();
    bool CheckBinary();
private:
    QString Path;
    QString Hash;
};

#endif // CHEKER_H
