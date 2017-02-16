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
    cout << "FileName: ";
    cin >> fileName;
    QString QfileName = QString::fromStdString(fileName);
    sfr.RemoveFile(QfileName);
    cout << "Delete" << endl;
    return 0;
}
