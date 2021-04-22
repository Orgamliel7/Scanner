#include <iostream>
#include <fstream>
#include <string>
#include "token.h"
#include  "tokenstrings.h"

using namespace std;
//  אם ערך סוג המילה קטן מ- 258 הוא מודפס כתוו, אם אינו קטן מ- 258 מודפס שם הערך ב- enum
tokenType Token::getType()
{
    return this->type;
}

string Token::getText()
{
    return this->text;
}

void Token::printToken()
{
    int decideIfChar = 257;
    int enum_ = decideIfChar+1;
    if(getType()>decideIfChar)
    {
        cout << tokenStrings[getType()-enum_] << "\t" << getText() << endl;
    }
    else
        {
        cout << (char)getType()<< "\t" << getText() << endl;
        }
}


void varToken::add_line(int line)
{
    lines->insert(line);
}


shared_ptr<set<int>> varToken::getLines()
{
    return this->lines;
}



