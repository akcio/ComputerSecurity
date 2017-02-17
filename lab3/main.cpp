#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <string>
#include <newcryptograph.h>

using namespace std;


void Permutation()
{
    char c;
    cout << "e to encode. d to decode: ";
    cin >> c;
    cout << "Input string: ";
    string text;
    cin >> text;
    //cout << text;
    cout << "Input code: ";
    string code;
    cin >> code;
    QString Qcode = QString::fromStdString(code);
    QList<int> key;
    for (int i=0; i < code.length(); i++)
    {
        key.append((int)((int)code[i]-'0'));
    }
    if (c == 'e')
    {
        QString qsw  = QString::fromStdString(text);
        QString answer = NewCryptograph::EncodePermutation(qsw, key);//EncodePermutation(qsw, key);
        cout << answer.toStdString() << endl;

    }
    if (c == 'd')
    {
        QString qsw  = QString::fromStdString(text);
        QString answer = NewCryptograph::DecodePermutation(qsw, key);//DecodePermutation(qsw, key);
        cout << answer.toStdString() << endl;
    }
    cout << "Ok" << endl;
}

void Cardano()
{
    char c;
    cout << "e to encode. d to decode: ";
    cin >> c;
    string fileName;
    QString encoded;
    NewCryptograph NC;
    if (c == 'e')
    {
        cout << "String: ";
        string text;
        cin >> text;
        encoded = NC.EncodeCardano(QString::fromStdString(text));
        cout << encoded.toStdString() << endl;
        cout << "Input filename: ";
        cin >> fileName;
        NC.SaveToFile(QString::fromStdString(fileName), encoded);
        cout << "Success!" << endl;
    }
    if (c == 'd')
    {
        cout << "Input filename: ";
        cin >> fileName;
        encoded = NC.LoadFromFile(QString::fromStdString(fileName));
        QString decode = NC.DecodeCardano(encoded);
        cout << decode.toStdString() << endl;
        cout << "Input filename: ";
        cin >> fileName;
        NC.SaveToFile(QString::fromStdString(fileName), encoded);
        cout << "Success!" << endl;
    }
}

void MineMethod()
{
    char c;
    cout << "e to encode. d to decode: ";
    cin >> c;
    NewCryptograph NC;
    QList<int> key;
    key.append(4);
    key.append(2);
    key.append(1);
    key.append(3);
    string text;
    if (c == 'e')
    {
        cout << "Input string: ";
        cin >> text;
        QString encoded = NC.EncodePermutation(NC.EncodeCardano(QString::fromStdString(text)), key);
        cout << encoded.toStdString() << endl;
        cout << "Filename to save: ";
        cin >> text;
        NC.SaveToFile(QString::fromStdString(text), encoded);
    }
    if (c == 'd')
    {
        cout << "FileName: ";
        cin >> text;
        QString encoded = NC.LoadFromFile(QString::fromStdString(text));
        QString decoded = NC.DecodeCardano(NC.DecodePermutation(encoded, key));
        cout << decoded.toStdString() << endl;
    }
}

int main(int argc, char *argv[])
{
    char c;
    while (true)
    {
        cout << "Permutation - p, Cardano - c, other - o: ";
        cin >> c;
        if (c == 'p')
            Permutation();
        if (c == 'c')
            Cardano();
        if (c == 'o')
            MineMethod();
        if (c == 'q')
            break;
    }
    return 0;
}
