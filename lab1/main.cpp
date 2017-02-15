#include <iostream>
#include <passwordgenerator.h>

using namespace std;

int main(int argc, char *argv[])
{
    PasswordGenerator pg;
    int a;
    cin >> a;
    cout << pg.GeneratePassword(a).toStdString() << endl;
    return 0;
}
