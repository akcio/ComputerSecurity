#include <QCoreApplication>
#include <textsteganoraphy.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TextSteganoraphy TS(QString("test"));
    cout << "Available symbols: " << (TS.PrepareFile() - 1) / 8 << endl;
    TS.HideText("qwe");
    cout << TS.GetHiddenText().toStdString() << endl;
    return 0;
}
