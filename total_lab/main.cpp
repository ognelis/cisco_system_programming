#include <iostream>

using namespace std;

bool isSeparator(char& symbol);

int main()
{
    cout << isSeparator(abc) << endl;
    return 0;
}

bool isSeparator(char& symbol)
{
    switch(symbol)
    {
        case ' ' :
        case '\n':
        case '\t':
            return (true);
        default:
            return (false);
            break;
    }
}
