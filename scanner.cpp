#include "scanner.h"
#include <regex>

using namespace std;

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
    char c2 = ch;
    if (ch == '/' && nextChar() && ch == '/')
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
        if (c2 == '/')
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

    while (ch == '/' && nextChar() && ch == '*')
    {
        regex comment(".*|[\r\n]");
        if (regex_match(&ch, comment))
        {
            while (regex_match(&ch, comment))
            {
                nextChar();
                if (ch == '*' && nextChar() && ch == '/')
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
        if(c2 == '.')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    if (ch == '<' && nextChar() && ch == '=')
    {
        return shared_ptr<Token>(new Token(LE_OP, "<="));
    }else{
        if(c2 == '<')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    if (ch == '=' && nextChar() && ch == '=')
    {
        return shared_ptr<Token>(new Token(EQ_OP, "=="));
    }
    else
        {
        if(c2 == '=')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }

    if (ch == '+' && nextChar() && ch == '+')
    {
        return shared_ptr<Token>(new Token(INC_OP, "++"));
    }
    else
        {

        if(c2 == '+')
        {
            inputFile.unget();
            inputFile.unget();
            nextChar();
        }
    }



    switch (ch) { // each character represents itself
        case ';' :
        case '&' :
        case '+' :
        case '{' :
        case '}' :
        case ',' :
        case ':' :
        case '(' :
        case ')' :
        case '[' :
        case ']' :
        case '~' :
        case '*' :
        case '%' :
        case '^' :
        case '?' :
        case '=':
        case '/':
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
        string str = "";
        while (regex_match(&ch, var))
        {
            str += ch;
            nextChar();
        }
        if (&ch != string(" "))
        {
            inputFile.unget();
        }
        shared_ptr<Token> t = symTab.lookupToken(str);
        if (t->getType() == IDENTIFIER)
        {
            t->add_line(lineno);
        }
        return t;
    }


}
