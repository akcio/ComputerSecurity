#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <string>

using namespace std;


QString Encode(QString toEncode, unsigned int key)
{
    QString encoded = "";
    for (int i=0; i<toEncode.count(); i++)
    {
        int newChar = ((toEncode.at(i).toLatin1())+key) % 255;
        if (newChar == 0)
            newChar = 255;
        encoded += (char)newChar;
    }
    return encoded;
}

QString Decode(QString toDecode, unsigned int key)
{
    QString decoded = "";
    for (int i=0; i<toDecode.count(); i++)
    {
        int newChar = (toDecode.at(i).toLatin1()-key) % 255;
        if (newChar == 0)
            newChar = 255;
        decoded += (char)newChar;
    }
    return decoded;
}

static bool CheckKey(QList<int> key)
{
    for (int i=1; i<key.length(); i++)
    {
        if (!key.contains(i))
            return false;
    }
    return true;
}

QString EncodePermutation(QString toEncode, QList<int> key)
{
    QString encoded = "";//toEncode;
    int blockCount = (toEncode.count() + key.count() - 2) / (key.count() - 1);
    int neededSpaces = blockCount*(key.count() - 1) - toEncode.count();
    for (int i=0; i<neededSpaces; i++)
        toEncode += QString::fromStdString("#");

    if (!CheckKey(key))
        return "Key Error";
    cout << endl;
    for (int i=0; i < blockCount; i++)
    {
        for (int k=0; k < (key.count()-1); k++)
        {
            encoded += toEncode.at(i*blockCount+key.at(k)-i - 1);
        }
    }
    return encoded;
}

QString DecodePermutation(QString toDecode, QList<int> key)
{
    QString decoded = "";//toEncode;
    int blockCount = (toDecode.count() + key.count() - 2) / (key.count() - 1);
    int neededSpaces = blockCount*(key.count() - 1) - toDecode.count();
    for (int i=0; i<neededSpaces; i++)
        toDecode += QString::fromStdString("#");

    if (!CheckKey(key))
        return "Key Error";
    cout << endl;
    for (int i=0; i < blockCount; i++)
    {
        for (int k=0; k < (key.count()-1); k++)
        {
            decoded += toDecode.at(i*blockCount+key.at(k)-i - 1);
        }
    }
    return decoded;


    for (int i=0; i<blockCount; i++)
    {
        for (int k=0; k < key.count(); k++)
        {
            //decoded[]=toDecode.at();
            decoded[i*blockCount+key[k]-1]=toDecode.at(i*blockCount+k);
        }
    }
    return decoded;
}


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
    for (int i=0; i <= code.length(); i++)
        key.append((int)((int)code[i]-'0'));
    cout << code;

    if (c == 'e')
    {
        QString qsw  = QString::fromStdString(text);
        QString answer = EncodePermutation(qsw, key);
        cout << answer.toStdString() << endl;

    }
    if (c == 'd')
    {
        QString qsw  = QString::fromStdString(text);
        QString answer = DecodePermutation(qsw, key);
        cout << answer.toStdString() << endl;
    }
    cout << "Ok" << endl;
}

void Subsitution()
{
    char c;
    cout << "e to encode. d to decode: ";
    cin >> c;
    string text;
    cin >> text;
    if (c == 'e')
    {
        QString qsw  = QString::fromStdString(text);
        QString answer = Encode(qsw, 5);
        cout << answer.toStdString() << endl;
    }
    if (c == 'd')
    {
        QString qsw  = QString::fromStdString(text);
        QString answer = Decode(qsw, 5);
        cout << answer.toStdString() << endl;
    }
    cout << "Ok" << endl;
}

int main(int argc, char *argv[])
{
    char c;
    while (true)
    {
        cout << "For permutations input f. For Substitution s: ";
        cin >> c;
        if (c =='f')
            Permutation();
        if (c == 's')
            Subsitution();
        if (c == 'q')
            break;
    }
    return 0;
}
