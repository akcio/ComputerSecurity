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

void GraphicalSteganographyHandle()
{
    string imageFileName, binaryFileName;
    char doings;
    cout << "Hide - h, Show - s: ";
    cin >> doings;
    cout << "Image filename: ";
    cin >> imageFileName;
    GraphicalSteganography gp;
    Problems problem;
    if (doings == 'h')
    {
        cout << "Input binary fileName: ";
        cin >> binaryFileName;
        problem = gp.Hide(QString::fromStdString(imageFileName), QString::fromStdString(binaryFileName));
        cout << GraphicalSteganography::ParseError(problem);
    }
    if (doings == 's')
    {
        cout << "Input name for binary unpacked: ";
        cin >> binaryFileName;
        problem = gp.Show(QString::fromStdString(imageFileName), QString::fromStdString(binaryFileName));
        cout << GraphicalSteganography::ParseError(problem);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    while (true)
    {
        char doings;
        cout << "Text mode - t, graphical - g: ";
        cin >> doings;
        if (doings == 't')
            TextSteganoraphyHandler();
        if (doings == 'g')
            GraphicalSteganographyHandle();
        if (doings == 'q')
            break;
    }
    return 0;
}
