#include <regex>
#include "scanner.h"

using namespace std;
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
#define LESSOREQUAL '<='

shared_ptr<Token> Scanner::nextToken()
{


    if (!nextChar())
    {
        return nullptr;
    }
    regex tab("[ \t\r\n]");
    if (regex_match(&ch, tab))
    {
        while (regex_match(&ch, tab))
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
        regex comment(".*|[\r]");
        if (regex_match(&ch, comment))
        {
            while (regex_match(&ch, comment))
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


    if (regex_match(&ch, tab))
    {
        while (regex_match(&ch, tab))
        {
            if (!nextChar())
            {
                break;
            }
        }
    }

    while (ch == SLASH && nextChar() && ch == ASTERISK)
    {
        regex comment(".*|[\r\n]");
        if (regex_match(&ch, comment))
        {
            while (regex_match(&ch, comment))
            {
                nextChar();
                if (ch == ASTERISK && nextChar() && ch == SLASH)
                {
                    nextChar();
                    break;
                }
            }
            if (regex_match(&ch, tab))
            {
                while (regex_match(&ch, tab))
                {
                    if (!nextChar())
                    {
                        break;
                    }
                }
            }
        }
    }


    if (regex_match(&ch, tab))
    {
        while (regex_match(&ch, tab))
        {
            if (!nextChar())
            {
                break;
            }
        }
    }
    regex digit("[\\d]");
    if (ch == '.' && nextChar() && !regex_match(&ch, digit))
    {
        inputFile.unget();
        inputFile.unget();
        nextChar();
        return shared_ptr<Token>
                (new Token(static_cast<tokenType>(ch), string(1, ch)));
    }
    else
        {
        if(charToScan == '.')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    if (ch == LESSTHEN && nextChar() && ch == EQUAL)
    {
        return shared_ptr<Token>(new Token(LE_OP, "LESSOREQUAL"));
    }else{
        if(charToScan == '<')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    if (ch == EQUAL && nextChar() && ch == EQUAL)
    {
        return shared_ptr<Token>(new Token(EQ_OP, "=="));
    }
    else
        {
        if(charToScan == '=')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    if (ch == PLUS && nextChar() && ch == PLUS)
    {
        return shared_ptr<Token>(new Token(INC_OP, "++"));
    }
    else
        {

        if(charToScan == PLUS)
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }


    switch (ch)
    {
        // לכל תו ייצוג משלו ע"פ הdefine בראש התוכנית
        case SEMICOLON : case AMPERSAND : case PLUS : case LEFTBRACKET : case RIGHTBRACKET : case COMMA : case COLON : case LEFTCIRCLEBRACKET : case RIGHTCIRCLEBRACKET : case LEFTSQUREBRACKET : case RIGHTSQUREBRACKET : case TILDE : case ASTERISK : case PERCENT : case CIRCUMFLEX :case QUESTION :case EQUAL: case SLASH:
            return shared_ptr<Token>
                    (new Token(static_cast<tokenType>(ch), string(1, ch)));


    }

    if (ch == '-' && nextChar() && ch == '>')
    {
        return shared_ptr<Token>(new Token(PTR_OP, "->"));
    }

    regex d("([0-9]*\.|[0-9]*\.[0-9]+e?[0-9]+|[0-9]|)");
    regex dig("[\\d.Ee]");
    regex dig0("[\\d.]");
    if (regex_match(&ch, dig0))
    {
        string str = "";
        while (regex_match(&ch, dig))
        {
            str += ch;
            nextChar();
        }
        if (&ch != string(" "))
        {
            inputFile.unget();
        }
        if (regex_match(str, d))
        {
            return shared_ptr<Token>(new Token(CONSTANT, str));
        } else
            {
            return shared_ptr<Token>(new Token(ERROR, str));
            }


    }

    if (ch == '\'')
    {
        nextChar();
        string c3 = &ch;
        nextChar();
        if (ch != '\'')
        {
            return nullptr;
        }
        shared_ptr<Token> t(new Token(CONSTANT, c3));
        return t;
    }

    if (ch == '"')
    {
        string str = "";
        nextChar();
        regex strin("[^\"]");
        while (regex_match(&ch, strin))
        {
            str += ch;
            nextChar();
        }
        shared_ptr<Token> t(new Token(STRING_LITERAL, str));
        return t;
    }

    regex var("[\\w]");
    if (regex_match(&ch, var))
    {
        string EmptyString = "";
        while (regex_match(&ch, var))
        {
            EmptyString += ch;
            nextChar();
        }
        if (&ch != string(" "))
        {
            inputFile.unget();
        }
        shared_ptr<Token> t = symTab.lookupToken(EmptyString);
        if (t->getType() == IDENTIFIER)
        {
            t->add_line(lineno);
        }
        return t;
    }


}
