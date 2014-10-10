#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

struct log
{
    size_t nLines = 0;
    size_t nSymbols = 0;
    size_t nWordsInLines = 0;
};

bool isSeparator(char symbol);
bool isString(char symbol);
char* getFileName();
log getFile(const char* name);
void readLog(log text);


int main()
{
    log  out = getFile("/home/ognelis/cisco_system_programming/total_lab/god.txt");
    readLog(&out);
    return 0;
}

bool isSeparator(char symbol)
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

bool isString(char symbol)
{
    if (symbol == '\n')
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

char* getFileName()
{
    char* name = new char [256];
    char* buffer = name;
    int symbol;
    while ((symbol = getchar()) != EOF  )
    {
        *buffer = symbol;
        buffer++;
    }
    *buffer = '\0';
    return (name);
}

// TODO: доделать
log getFile(const char* name)
{
    log out;
    char symbol;
    FILE *fp;
    fp=fopen(name,"r");
    bool separator;

    while ((symbol = fgetc(fp)) != EOF)
    {
        if (isSeparator(symbol) == true)
        {
           if (isString(symbol) == true)
               out.nLines++;

           separator = true;
        }
        else
        {
           if (separator == true)
               out.nWordsInLines++;

           separator=false;
        }
        out.nSymbols++;
    }
    fclose(fp);

    if (out.nSymbols > 0) out.nSymbols--;
    if (out.nLines == 0) out.nLines = 1;
    if (separator == true) out.nWordsInLines++;

    return(out);
}

void readLog(log text)
{
    cout <<"There is(are): " << text.nSymbols << " symbols." <<endl;
    cout <<"There is(are): " << text.nLines   << "  lines."   <<endl;
    cout <<"There is(are): " << text.nWordsInLines << " words." <<endl;
}
