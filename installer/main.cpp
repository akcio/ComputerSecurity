#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QCryptographicHash>
#include <iostream>

using namespace std;;

QByteArray programText;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("lab5");
    file.open(QIODevice::ReadOnly);
    QByteArray fileText = file.readAll();
    QCryptographicHash* hash;
    QString resultHash = QString::fromStdString(hash->hash(fileText,QCryptographicHash::Md5).toHex().toStdString());
    file.close();

    string path;
    cout << "Input path to install folder: ";
    getline(cin, path);

    QFile newFile(QString::fromStdString(path) + "/" + file.fileName());
    if (!newFile.open(QIODevice::WriteOnly | QIODevice::Text))
            return 1;
    QDataStream st(&newFile);
    st.writeRawData(fileText, fileText.length());
    newFile.close();
    QFile fileHash(QString::fromStdString(path+"/.hash"));
    if (!fileHash.open(QIODevice::WriteOnly | QIODevice::Text))
            return 5;
    QTextStream out(&fileHash);
    out.setCodec("UTF-8");
    out << resultHash;
    fileHash.close();

    return 0;
}
