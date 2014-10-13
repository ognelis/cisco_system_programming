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

bool isSeparator(char& symbol);
bool isString(char& symbol);
void getCommandLineArguments(size_t num_args, char **arg_strings);
char* getFileName();
log& getFile(const char* name);
void readLog(log* text);


int main(int argc, char *argv[])
{
    getCommandLineArguments(argc,argv);
    //log out = getFile("/home/ognelis/cisco_system_programming/total_lab/god.txt");
    //readLog(&out);
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

bool isString(char& symbol)
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

void getCommandLineArguments(size_t num_args, char **arg_strings)
{
    if (num_args != 1)
    {
        for (size_t i = 0; i < num_args; i++)
        {
            log out = getFile(arg_strings[i]);
            readLog(&out);
        }
    }
    else
    {
        log out = getFile(getFileName());
        readLog(&out);
    }
}

char* getFileName()
{
    char* name = new char [256];
    char* buffer = name;
    int symbol;
    cout << "write file name with dir: ";
    while ((symbol = getchar()) != EOF  )
    {
        *buffer = symbol;
        buffer++;
    }
    *buffer = '\0';
    cout << endl;
    return (name);
}

// TODO: доделать
log& getFile(const char* name)
{
    log* out = new log;
    char symbol;
    FILE *fp;
    if ((fp=fopen(name,"r")) == NULL)
    {
        cout << "\nFile isn't opened: " << name <<endl;
    }
    bool separator;

    while ((symbol = fgetc(fp)) != EOF)
    {
        if (isSeparator(symbol) == true)
        {
           if (isString(symbol) == true)
               out->nLines++;

           separator = true;
        }
        else
        {
           if (separator == true)
               out->nWordsInLines++;

           separator=false;
        }
        out->nSymbols++;
    }
    fclose(fp);

    if (out->nSymbols > 0) out->nSymbols--;
    if (out->nLines == 0) out->nLines = 1;
    if (separator == true) out->nWordsInLines++;

    return(*out);
}

void readLog(log* text)
{
    cout <<"There is(are): " << text->nSymbols << " symbols." <<endl;
    cout <<"There is(are): " << text->nLines   << "  lines."   <<endl;
    cout <<"There is(are): " << text->nWordsInLines << "    words.\n" <<endl;
}
