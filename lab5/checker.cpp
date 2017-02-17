#include "checker.h"

Checker::Checker(std::string path)
{
    Path = path;
}

bool Checker::HasHashFile()
{
    QFile file(".hash");
    return file.exists();
}

QString Checker::GetHash()
{
    QString hashText = "cdba";
    //QCoreApplication qCore(0, []);
    QFile* file = new QFile(QString::fromStdString(Path));
    if(file->open(QIODevice::ReadOnly))
    {
        QCryptographicHash* hash;
        QByteArray resultHash = hash->hash(file->readAll(),QCryptographicHash::Sha512);
        file->close();
        hashText += QString::fromStdString(resultHash.toHex().toStdString());
    }
    return hashText;
}

void Checker::CreateHashFile()
{
    QFile file(".hash");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << GetHash() << endl;

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
        if (LoadHash() == GetHash())
            return true;
    }
    else
        CreateHashFile();
    return false;
}
