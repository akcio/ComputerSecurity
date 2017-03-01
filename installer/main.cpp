#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QCryptographicHash>
#include <iostream>
#include <QDir>

using namespace std;

QByteArray programText;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file;
    if (QFile::exists("toInstall/lab5"))
        file.setFileName(QString::fromStdString("toInstall/lab5"));
    else
    if (QFile::exists("toInstall/lab5.exe"))
        file.setFileName(QString::fromStdString("toInstall/lab5.exe"));
    else
    {
        cout << "No file to copy" << endl;
        return 0;
    }
    file.open(QIODevice::ReadOnly);
    QByteArray fileText = file.readAll();
    QCryptographicHash* hash;
    QString resultHash = QString::fromStdString(hash->hash(fileText,QCryptographicHash::Md5).toHex().toStdString());
    file.close();

    string path;
    cout << "Input path to install folder: ";
    getline(cin, path);

    QString newPath = QString::fromStdString(path) + "/" + file.fileName();
    cout << newPath.toStdString() << endl;

    /*if(!file.copy(newPath))
        cout << "Error copy binary" << endl;
    */
    QDir dir("toInstall");
    QStringList fileList = dir.entryList();
    foreach(QString fileName, fileList)
    {
        if (!QFile::copy(dir.dirName()+"/"+fileName, QString::fromStdString(path) + "/" + fileName))
            cout << "Can't copy: " << fileName.toStdString() << " from toInstall" << endl;
    }

    /*QDataStream st(&newFile);
    st.writeRawData(fileText, file.size());
    newFile.close();
    */
    QFile fileHash(QString::fromStdString(path+"/.hash"));
    if (!fileHash.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout << "No path for hash" << endl;
        return 5;
    }
    QTextStream out(&fileHash);
    out.setCodec("UTF-8");
    out << resultHash;
    fileHash.close();
    cout << "Success";
    return 0;
}
