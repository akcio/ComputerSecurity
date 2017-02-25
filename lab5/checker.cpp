#include "checker.h"

Checker::Checker()
{
    Path = (QFileInfo(QCoreApplication::applicationFilePath() ).fileName());
    Hash = "";
}

bool Checker::HasHashFile()
{
    QFile file(".hash");
    bool a = file.exists();
    return file.exists();
}

QString Checker::GetHash()
{
    QString hashText;
    if (Hash != "")
        return Hash;
    QFile* file = new QFile(Path);
    if(file->open(QIODevice::ReadOnly))
    {
        QCryptographicHash* hash;
        QByteArray resultHash = hash->hash(file->readAll(),QCryptographicHash::Md5);
        file->close();
        hashText += QString::fromStdString(resultHash.toHex().toStdString());
    }
    Hash = hashText;
    return hashText;
}

void Checker::CreateHashFile()
{
    QFile file(".hash");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << GetHash();

    file.close();
}

QString Checker::LoadHash()
{
    QFile file(".hash");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return QString::fromStdString("");
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString fileText = "";

    while (!in.atEnd())
    {
        QChar fileChar;
        in >> fileChar;
        if (fileChar.unicode() == 0)
            break;
        fileText += (QChar)fileChar;
        //fileText += in.readLine();
    }
    //fileText = in.readAll();

    file.close();
    return fileText;
}

bool Checker::CheckBinary()
{
    if (HasHashFile())
    {
        QString loadedHash = LoadHash();
        QString realHash = GetHash();
        if (realHash == loadedHash)
            return true;
    }
    //else
    //    CreateHashFile();
    return false;
}
