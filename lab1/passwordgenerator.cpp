#include <QCoreApplication>
#include "passwordgenerator.h"
#include <stdlib.h>

PasswordGenerator::PasswordGenerator()
{
    srand(NULL);
}
PasswordGenerator::PasswordGenerator(unsigned int randomSeed)
{
    srand(randomSeed);
}

QString PasswordAlphabet = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGJKLZXCVBNM1234567890_-*+";

QChar GetRandSymbol()
{
    int charPosition = rand() % PasswordAlphabet.size();
    return PasswordAlphabet.at(charPosition);
}

QString PasswordGenerator::GeneratePassword(int length)
{
    QString password;
    for (int i=0; i<length; i++)
    {
        password += GetRandSymbol();
    }
    return password;
}
