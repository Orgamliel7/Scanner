#include "symtab.h"

void SymbolTable::initReserved() {
    string text;
    string value;
    ifstream file;
    file.open("reserved.txt");
    if (file.is_open()) {
        while (file.good()) {
            file >> text;
            file >> value;
            tokenType value2 = static_cast<tokenType>(stoi(value));
            shared_ptr<Token> t(new Token(value2, text));
            symMap.insert({text, t});
        }
    }
    file.close();
}

shared_ptr<Token> SymbolTable::lookupToken(string text) {
    auto it = symMap.find(text);
    if (it == symMap.end()) {
        shared_ptr<Token> t(new varToken( text));
        insertToken(text, t);
        return t;
    } else {
        return it->second;
    }

}

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp) {
    symMap.insert({text, tokenp});
}

void SymbolTable::xref() {

    for (auto itr = symMap.begin(); itr != symMap.end(); ++itr) {
        if(itr->second->getLines()){
            cout << '\t' << itr->first<<"\t";
            for (auto it = itr->second->getLines()->begin(); it != itr->second->getLines()->end(); ++it) {
                cout << " " << *it;
            }
            cout<<endl;
            //  cout<<*itr->second->getLines()->begin()<<endl;
        }




    }
}