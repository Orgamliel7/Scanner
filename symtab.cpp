#include "symtab.h"





void SymbolTable::initReserved()
{
    string text;
    string value;
    ifstream file;
    file.open("reserved.txt");
    if (file.is_open())
    {
        while (file.good())
        {
            file >> text;
            file >> value;
            tokenType value2 = static_cast<tokenType>(stoi(value));
            shared_ptr<Token> t(new Token(value2, text));
            symMap.insert({text, t});
        }
    }
    file.close();
}

shared_ptr<Token> SymbolTable::lookupToken(string parsing)
{
    auto iterator = symMap.find(parsing);
    if (iterator == symMap.end())
    {
        shared_ptr<Token> t(new varToken( parsing));
        insertToken(parsing, t);
        return t;
    }
    else
        {
        return iterator->second;
        }

}

void SymbolTable::insertToken(string parsing, shared_ptr<Token> tokenp)
{
    symMap.insert({parsing, tokenp});
}

void SymbolTable::xref()
{

    for (auto itrator = symMap.begin(); itrator != symMap.end(); ++itrator)
    {
        if(itrator->second->getLines())
        {
            cout << '\t' << itrator->first<<"\t";
            for (auto iterator2 = itrator->second->getLines()->begin(); iterator2 != itrator->second->getLines()->end(); ++iterator2)
            {
                string emp = " ";
                cout << emp << *iterator2;
            }
            cout<<endl;

        }




    }
}