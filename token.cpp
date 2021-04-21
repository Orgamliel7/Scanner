#include <iostream>
#include <fstream>
#include <string>
#include "token.h"
#include  "tokenstrings.h"

using namespace std;


tokenType Token::getType() {
    return this->type;
}

string Token::getText() {
    return this->text;
}

void Token::printToken() {

    //cout << enumToString(getType()) << "\t" << getText() << endl;
    if(getType()>257) {
        cout << tokenStrings[getType()-258] << "\t" << getText() << endl;
    }else {
        cout << (char)getType()<< "\t" << getText() << endl;
    }
}


void varToken::add_line(int l) {
    lines->insert(l);
}


shared_ptr<set<int>> varToken::getLines() {
    return this->lines;
}



