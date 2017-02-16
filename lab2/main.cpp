#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <string>
#include <ctime>
#include <cryptograph.h>

using namespace std;

Cryptograph cryptograph;

void MultiAlphabet()
{
    string text, key;
    QString output="";
    char doings;
    cout << "Key: ";
    cin >> key;
    cout << "decode - d, encode - e: ";
    cin >> doings;
    if (doings == 'e')
    {
        cout << "String: ";
        cin >> text;
        output = cryptograph.EncodeMultiAlpabet(QString::fromStdString(text), QString::fromStdString(key));
        cout << "Input fileName to save: ";
        cin >> text;
        cryptograph.SaveToFileUnicoded(QString::fromStdString(text), output);
    }
    if (doings == 'd')
    {
        cout << "Input fileName to load: ";
        cin >> text;
        QString input = cryptograph.LoadFromFileUnicoded(QString::fromStdString(text));
        output = cryptograph.DecodeMultiAlpabet(input, QString::fromStdString(key));
    }
    cout << "Success: " << output.toStdString() << endl;

}

void SaveToFileIfNeed(QString text)
{
    char doings;
    cout << endl << "Need save to file(y/n): ";
    cin >> doings;
    if (doings == 'y')
    {
        cout << "FileName: " << endl;
        string fileName;
        cin >> fileName;
        cryptograph.SaveToFile(QString::fromStdString(fileName), text);
        cout << "Saved!" << endl;
    }
}

void OneAlphabet()
{
    char doings;
    string text;
    int key;
    QString output = "";
    cout << "load from file?(y/n): ";
    cin >> doings;
    if (doings == 'y')
    {
        cout << "FileName: ";
        cin >> text;
        QString loadedText = cryptograph.LoadFromFile(QString::fromStdString(text));
        cout << "Key: ";
        cin >> key;
        cout << "d for decode, e for encode: ";
        cin >> doings;
        if (doings == 'd')
            output = cryptograph.DecodeOneAlphabet(loadedText, key);
        if (doings == 'e')
            output = cryptograph.EncodeOneAlphabet(loadedText, key);
    }
    else
    {
        cout << "String: ";
        cin >> text;
        cout << "Key: ";
        cin >> key;
        cout << "d for decode, e for encode: ";
        cin >> doings;
        if (doings == 'd')
            output = cryptograph.DecodeOneAlphabet(QString::fromStdString(text), key);
        if (doings == 'e')
            output = cryptograph.EncodeOneAlphabet(QString::fromStdString(text), key);
    }
    cout << "Success: " << output.toStdString();
    SaveToFileIfNeed(output);

}

void OneNotePad()
{
    string text;
    QString output="";
    char doings;
    cout << "decode - d, encode - e: ";
    cin >> doings;
    if (doings == 'e')
    {
        QString key;
        cout << "String: ";
        cin >> text;
        key = cryptograph.GenerateKey(text.length());
        output = cryptograph.EncodeMultiAlpabet(QString::fromStdString(text), key);
        cout << "Input fileName to save: ";
        cin >> text;
        cryptograph.SaveToFileUnicoded(QString::fromStdString(text), output);
        cryptograph.SaveToFile(QString::fromStdString("key"), key);
        cout << "Key saved to key" << endl;
    }
    if (doings == 'd')
    {
        string key;
        cout << "Input fileName to load: ";
        cin >> text;
        cout << "Input key file to load: ";
        cin >> key;
        QString input = cryptograph.LoadFromFileUnicoded(QString::fromStdString(text));
        output = cryptograph.DecodeMultiAlpabet(input, QString::fromStdString(key));
    }
    cout << "Success: " << output.toStdString() << endl;

}

int main(int argc, char *argv[])
{
    cryptograph = Cryptograph(time(NULL));
    while (true)
    {
        cout << "OneAlphabet - a, Multi - m, OneNotepad - n";
        char c;
        cin >> c;
        if (c == 'a')
            OneAlphabet();
        if (c == 'm')
            MultiAlphabet();
        if (c == 'n')
            OneNotePad();
        if (c == 'q')
            break;
    }

    return 0;
}

void OldTest()
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
}
