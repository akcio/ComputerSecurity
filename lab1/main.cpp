#include <QCoreApplication>
#include <QString>
#include <iostream>
#include <passwordgenerator.h>
#include <saver.h>
#include <time.h>
#include <string>

using namespace std;

void GeneratePassWord()
{
    int passwordLen = 10;
    int passwordCnt = 0;
    string fileName = "";
    cout << "Password length: ";
    cin >> passwordLen;
    cout << "Passwprd counts: ";
    cin >> passwordCnt;
    cout << "SaveFile name: ";

    cin >> fileName;
    QString QfileName = QString::fromStdString(fileName);

    PasswordGenerator pg(time(NULL));
    QList<QString> passwords;
    for (int i=0; i<passwordCnt; i++)
    {
        passwords.append(pg.GeneratePassword(passwordLen));
    }
    Saver sv;
    sv.Save(QfileName, passwords);
    cout << endl <<"!!! Success !!!" << endl;

}

void LoadPasswords(QString QfileName)
{
    Saver sv;
    QList<QString> deshifr = sv.Load(QfileName);
    foreach (auto pass, deshifr)
    {
        cout << pass.toStdString() << endl;
    }

}

int main(int argc, char *argv[])
{
    char c;
    string filename;
    cout << "For generate input g. For load l filename: ";
    cin >> c;
    if (c == 'g')
        GeneratePassWord();
    if (c == 'l')
    {
        cin >> filename;
        LoadPasswords(QString::fromStdString(filename));
    }

    return 0;
}
