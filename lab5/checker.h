#ifndef CHEKER_H
#define CHEKER_H
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <string>

class Checker
{
public:
    Checker(std::string path);
    bool HasHashFile();
    void CreateHashFile();
    QString GetHash();
    QString LoadHash();
    bool CheckBinary();
private:
    std::string Path;
};

#endif // CHEKER_H
