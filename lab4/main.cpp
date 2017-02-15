#include <QCoreApplication>
#include <time.h>
#include <superfileremover.h>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    SuperFileRemover sfr(time(NULL));
    string fileName;
    cout << "Введи имя файла: ";
    cin >> fileName;
    QString QfileName = QString::fromStdString(fileName);
    sfr.RemoveFile(QfileName);
    cout << "Удалено" << endl;
    return 0;
}
