#include <QCoreApplication>
#include <QString>
#include <iostream>
#include <passwordgenerator.h>
#include <saver.h>
#include <time.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int passwordLen = 10;
    int passwordCnt = 0;
    string fileName = "";
    cout << "Длина пароля: ";
    cin >> passwordLen;
    cout << "Количество паролей: ";
    cin >> passwordCnt;
    cout << "Имя файла для сохранения: ";

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
    cout << endl <<"!!! Выполнено !!!" << endl;
    return 0;
}
