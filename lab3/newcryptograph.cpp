#include "newcryptograph.h"
NewCryptograph::NewCryptograph()
{

}


QString NewCryptograph::EncodePermutation(QString toEncode, QList<int> key)
{
    QString encoded = "";//toEncode;
    int blockCount = (toEncode.count() + key.count() - 1) / (key.count());
    int neededSpaces = blockCount*(key.count()) - toEncode.count();
    for (int i=0; i<neededSpaces; i++)
        toEncode += QString::fromStdString("#");
    if (!CheckKey(key))
        return "Key Error";
    for (int i=0; i < blockCount; i++)
    {
        for (int k=0; k < (key.count()); k++)
        {
            //cout << i*key.count() + key.at(k) << " ";
            encoded += toEncode.at(i*key.count()+key.at(k) - 1);
        }
    }
    return encoded;
}

QString NewCryptograph::DecodePermutation(QString toDecode, QList<int> key)
{
    QString decoded = toDecode;//toEncode;
    int blockCount = (toDecode.count() + key.count() - 1) / (key.count());
    int neededSpaces = blockCount*(key.count()) - toDecode.count();
    for (int i=0; i<neededSpaces; i++)
        toDecode += QString::fromStdString("#");
    if (!CheckKey(key))
        return "Key Error";
    for (int i=0; i < blockCount; i++)
    {
        for (int k=0; k < (key.count()); k++)
        {
            decoded[i*key.count()+key.at(k) - 1] = toDecode[i*key.count() + k];
            //cout << i*key.count() + k;// i*key.count()+key.at(k) - 1;
            //decoded += toDecode.at(i*key.count()+key.at(k) - 1);
        }
    }
    return decoded;
}

bool NewCryptograph::CheckKey(QList<int> key)
{
    for (int i=1; i <= key.count(); i++)
    {
        //cout << key.at(i-1) << " contains" << key.contains(i) << endl;
        if (!key.contains(i))
            return false;
    }
    return true;
}

void NewCryptograph::RotateGrid()
{
    bool tmpSpace[4][4];
    for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
            tmpSpace[j][3-i] = openSpace[i][j];
    for (int i=0; i<4; i++)
        for (int j=0; j < 4; j++)
            openSpace[i][j] = tmpSpace[i][j];
}

void NewCryptograph::PrintGrid()
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
            cout << openSpace[i][j];
        cout << endl;
    }
}

void NewCryptograph::SetGridToDefault()
{
    bool defaultSpace[4][4] = {
        {0,0,1,0},
        {0,1,0,0},
        {0,0,0,0},
        {1,0,1,0},
    };
   for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
           openSpace[i][j] = defaultSpace[i][j];
}

QString NewCryptograph::EncodeCardano(QString toEncode)
{
    while (toEncode.length() < 16)
        toEncode += "#";
    int stringIterator = 0;
    SetGridToDefault();
    char matrix[4][4];
    for (short step =0; step < 4; step++)
    {
        for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                if (openSpace[i][j])
                    matrix[i][j] = toEncode[stringIterator++].toLatin1();
        RotateGrid();
    }
    QString output;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
            output += matrix[i][j];
        output += "\n";
    }
    return output;
}

QString NewCryptograph::DecodeCardano(QString toDecode)
{
    char cryptChar[4][4];
    int stringIterator = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cryptChar[i][j] = toDecode[stringIterator++].toLatin1();
        stringIterator++;
    }
    SetGridToDefault();
    QString output;
    for (short step=0; step < 4; step++)
    {
        for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                if (openSpace[i][j])
                    output += cryptChar[i][j];
        RotateGrid();
    }
    return output;
}

void NewCryptograph::SaveToFile(QString fileName, QString text)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    out.setCodec("UTF-8");

    out << text;

    file.close();
}

QString NewCryptograph::LoadFromFile(QString fileName)
{
    QFile file(fileName);
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
