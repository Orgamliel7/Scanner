#include <regex>
#include "scanner.h"
#include <iostream>
#include <vector>
#include <string>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;
#define ZITUT '"'
#define DOT '.'
#define SLASH '/'
#define ASTERISK     '*'
#define SEMICOLON    ';'
#define AMPERSAND    '&'
#define PLUS         '+'
#define LEFTBRACKET    '{'
#define RIGHTBRACKET    '}'
#define COMMA    ','
#define COLON    ':'
#define LEFTCIRCLEBRACKET     '('
#define RIGHTCIRCLEBRACKET     ')'
#define LEFTSQUREBRACKET     '['
#define RIGHTSQUREBRACKET    ']'
#define TILDE    '~'
#define PERCENT    '%'
#define CIRCUMFLEX    '^'
#define QUESTION    '?'
#define EQUAL    '='
#define LESSTHEN '<'
#define BIGGERTHEN '>'
#define MINUS '-'
#define LESSOREQUAL "<="
#define EQUALITYCHECK "=="
#define PROMOTION "++"
#define RIGHTARROW "->"
#define ONE 1
#define EMPTYSTRING ""
#define SPACESTRING " "
#define BACKSLASHCHAR '\''



string GetToken()
{
    string tryToScan = "_";
    string token;
    char ch;
    cin.get(ch);
    if (ch == ' ')
    {
        cin.get(ch);
    }
    if (ch == 'i' || ch == 'f')
    {
        string buffer;
        while (!isspace(ch))
        {
            buffer += ch;
            cin.get(ch);
        }
        token += buffer;
    }
    if (isdigit(ch))
    {
        string buffer;
        while (ch != ';')
        {
            buffer += ch;
            cin.get(ch);
        }
        token += buffer;
        token += "\n;";
    }
    if (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E' || ch == '=')
    {
        token += ch;
    }
    return token;
}



shared_ptr<Token> Scanner::nextToken()
{

    string t = "string";
    // GetToken()
    //ניסיון ראשון לסריקה
    static char choo = '\0';
    // Checks whether c is an alphabetic letter
    if (isalpha(choo))
    {
        string text = EMPTYSTRING;
        text += ONE;
        regex word_pattern(R"(\w(\w|\d)*)");
        //בדיקת תקינות לטוקן
        if (regex_match(text, word_pattern))
        {
            shared_ptr <Token> token = symTab.lookupToken(text);
            // נבדוק אם בטבלת הסימבולים
        }
    }


    if (!nextChar())    // אם אין תו קדימה נחזיר פוינטר ריק
    {
        return nullptr;
    }
    regex badge("[ \t\r\n]"); // regex - ביטוי רגולרי
    if (regex_match(&ch, badge))
    {
        while (regex_match(&ch, badge))
        {
            if (!nextChar())
            {
                break;
            }
        }
    }
    char charToScan = ch;
    if (ch == SLASH && nextChar() && ch == SLASH)
    {
        nextChar();
        regex note(".*|[\r]");
        string refToC =  &ch;
        if (regex_match(refToC, note))
        {
            string refToC1 =  &ch;
            while (regex_match(&ch, note))
            {
                nextChar();
            }
        }
    }
    else
        {
        if (charToScan == SLASH)
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    STRING_LITERAL;
    int term;
    if (term== 0)
    {
        long long tempToken = 987654321;
        tempToken = tempToken;
    }
    else
    {
        term =1;
    }

    SymbolTable relation = SymbolTable();
    string Scanner = "";

    if (regex_match(&ch, badge))
    {
        while (regex_match(&ch, badge))
        {
            if (!nextChar())
            {
                break;
            }
        }
    }

    while (ch == SLASH && nextChar() && ch == ASTERISK)
    {
        regex note(".*|[\r\n]");
        if (regex_match(&ch, note))
        {
            while (regex_match(&ch, note))
            {
                nextChar();
                if (ch == ASTERISK && nextChar() && ch == SLASH)
                {
                    nextChar();
                    break;
                }
            }
            if (regex_match(&ch, badge))
            {
                while (regex_match(&ch, badge))
                {
                    if (!nextChar())
                    {

                        break;
                    }
                }
            }
        }
    }


    if (regex_match(&ch, badge))
    {
        while (regex_match(&ch, badge))
        {
            if (!nextChar())
            {
                break;
            }
        }
    }
    regex digit("[\\d]");
    if (ch == DOT && nextChar() && !regex_match(&ch, digit))
    {
        inputFile.unget();
        inputFile.unget();
        nextChar();
        return shared_ptr<Token>
                (new Token(static_cast<tokenType>(ch), string(ONE, ch)));
    }
    else
        {
        if (charToScan == DOT)
        {
            for (int i = 0; i < 2; ++i)
            {
                inputFile.unget();

            }
            nextChar();
        }
    }

    if (ch == LESSTHEN && nextChar() && ch == EQUAL)
    {
        return shared_ptr<Token>(new Token(LE_OP, LESSOREQUAL));
    }
    else
        {
        if (charToScan == LESSTHEN)
        {
            for (int i = 0; i < 2; ++i)
            {
                inputFile.unget();

            }
            nextChar();
        }
    }

    if (ch == EQUAL && nextChar() && ch == EQUAL)
    {
        return shared_ptr<Token>(new Token(EQ_OP, EQUALITYCHECK));
    }
    else
        {
        if (charToScan == EQUAL)
        {
            for (int i = 0; i < 2; ++i)
            {
                inputFile.unget();

            }
            nextChar();
        }
    }
    char chCheck = '"';
    if (chCheck == '"')
    {
        string st = string(1, chCheck);
        regex reg5("\"[^\"]*\"");
        for (int i = 0; i <chCheck ; ++i)
        {
            st += chCheck;
            if (chCheck == '"') break;
        }

    }
    int check = 0;
    if (ch == PLUS && nextChar() && ch == PLUS)
    {
         check++;
        return shared_ptr<Token>(new Token(INC_OP, PROMOTION));
    }
    else
        {

        if (charToScan == PLUS)
        {
            check++;
            for (int i = 0; i < 2; ++i)
            {
                inputFile.unget();

            }
            nextChar();
        }
    }


    switch (ch)
    {
        // לכל תו ייצוג משלו ע"פ הdefine בראש התוכנית
        case SEMICOLON :
        case AMPERSAND :
        case PLUS :
        case LEFTBRACKET :
        case RIGHTBRACKET :
        case COMMA :
        case COLON :
        case LEFTCIRCLEBRACKET :
        case RIGHTCIRCLEBRACKET :
        case LEFTSQUREBRACKET :
        case RIGHTSQUREBRACKET :
        case TILDE :
        case ASTERISK :
        case PERCENT :
        case CIRCUMFLEX :
        case QUESTION :
        case EQUAL:
        case SLASH:
            return shared_ptr<Token>
                    (new Token(static_cast<tokenType>(ch), string(ONE, ch)));


    }

    if (ch == MINUS && nextChar() && ch == BIGGERTHEN)
    {
        return shared_ptr<Token>(new Token(PTR_OP, RIGHTARROW));
    }
    regex reg0("([0-9]*\.|[0-9]*\.[0-9]+e?[0-9]+|[0-9]|)");
    regex reg1("([0-9]*\.|[0-9]*\.[0-9]+e?[0-9]+|[0-9]|)");
    regex reg2("[\\d.Ee]");
    regex reg3("[\\d.]");
    if (regex_match(&ch, reg3))
    {
        string text = EMPTYSTRING;
        while (regex_match(&ch, reg2))
        {
            text = text + ch;
            nextChar();
        }
        if (&ch != string(SPACESTRING))
        {
            for (int i = 0; i < 1; ++i)
            {
                inputFile.unget();

            }
        }
        if (regex_match(text, reg1))
        {
            return shared_ptr<Token>(new Token(CONSTANT, text));
        }
        else
            {
            return shared_ptr<Token>(new Token(ERROR, text));
        }


    }

    if (ch == BACKSLASHCHAR)
    {
        nextChar();
        string tokenc = &ch;
        nextChar();
        if (ch != BACKSLASHCHAR)
        {
            return nullptr;
        }
        shared_ptr <Token> OurToken(new Token(CONSTANT, tokenc));
        return OurToken;
    }

    if (ch == ZITUT)
    {
        string str = EMPTYSTRING;
        nextChar();
        regex strin("[^\"]");
        while (regex_match(&ch, strin))
        {
            str += ch;
            nextChar();
        }
        shared_ptr <Token> OurToken(new Token(STRING_LITERAL, str));
        return OurToken;
    }

    regex var("[\\w]");
    if (regex_match(&ch, var))
    {
        string EmptyString = EMPTYSTRING;

        while (regex_match(&ch, var))
        {
            EmptyString += ch;
            nextChar();
        }
        if (&ch != string(SPACESTRING))
        {
            int checkCh = 0;
            for (int i = 0; i < ch; ++i)
            {
               checkCh++;

            }
            for (int i = 0; i < 1; ++i)
            {
                inputFile.unget();

            }
        }
        shared_ptr <Token> OurToken = symTab.lookupToken(EmptyString);
        if (OurToken->getType() == IDENTIFIER) // אם הטוקן שלנו זה המזהה מקובץ ההדר
        {
            OurToken->add_line(lineno);  // נוסיף שורה
        }
        return OurToken; // ונחזיר את הטוקן
    }


}
