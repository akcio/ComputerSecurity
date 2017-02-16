#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <string>
#include <cryptograph.h>

using namespace std;



int main(int argc, char *argv[])
{
    string test = "ebarz";
    QString key = Cryptograph::GenerateKey(test.length());
    QString tmp = Cryptograph::EncodeOneAlphabet(QString::fromStdString(test), 150);
    cout << tmp.toStdString() << endl;
    cout << Cryptograph::DecodeOneAlphabet(tmp, 150).toStdString() << endl;
    tmp = Cryptograph::EncodeMultiAlpabet(QString::fromStdString(test), key);
    cout << tmp.toStdString() << endl;
    cout << Cryptograph::DecodeMultiAlpabet(tmp, key).toStdString() << endl;
    cout << key.toStdString()  << endl;

    cout << "_________" << endl;

    Cryptograph cr;
    QString filename = "tmp";

    cr.SaveToFileUnicoded(filename, Cryptograph::EncodeMultiAlpabet(QString::fromStdString(test), key));
    cr.SaveToFile(QString::fromStdString("key"), key);

    tmp = cr.LoadFromFileUnicoded(QString::fromStdString("tmp"));
    key = cr.LoadFromFile(QString::fromStdString("key"));
    cout << tmp.toStdString() << endl;
    cout << Cryptograph::DecodeMultiAlpabet(tmp, key).toStdString() << endl;
    cout << key.toStdString()  << endl;
    return 0;
}
