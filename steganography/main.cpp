#include <QCoreApplication>
#include <textsteganoraphy.h>
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
    while (true)
        TextSteganoraphyHandler();
    return 0;
}
