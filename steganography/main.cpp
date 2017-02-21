#include <QCoreApplication>
#include <textsteganoraphy.h>
#include <graphicalsteganography.h>
#include <iostream>

using namespace std;

void TextSteganoraphyHandler()
{
    string fileName;
    char doings;
    cout << "Input filename: ";
    cin >> fileName;
    cout << "decode - d, encode - e: ";
    cin >> doings;
    TextSteganoraphy TS(QString::fromStdString(fileName));
    if (doings == 'e')
    {
        TS.PrepareFile();
        cout << "Available symbols: " << TS.GetAvailableSymbolsCount() << endl
             << "Input hiding text: ";
        string textToHide;
        cin >> textToHide;
        TS.HideText(QString::fromStdString(textToHide));
        cout << "Hidden" << endl;
    }
    if (doings == 'd')
        cout << TS.GetHiddenText().toStdString() << endl;

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*while (true)
        TextSteganoraphyHandler();
    */
    GraphicalSteganography gp;
    gp.Hide(QString::fromStdString("ntmp.bmp"), QString::fromStdString("lab3"));
//    gp.Show(QString::fromStdString("tmp.bmp1"), QString::fromStdString("test2"));
    gp.Show(QString::fromStdString("ntmp.bmp1"), QString::fromStdString("test2"));

    return 0;
}
