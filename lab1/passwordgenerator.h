#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QCoreApplication>

class PasswordGenerator
{
public:
    PasswordGenerator();
    PasswordGenerator(unsigned int randomSeed);
    QString GeneratePassword(int length);
private:
    QString PasswordAlphabet;
};

#endif // PASSWORDGENERATOR_H
