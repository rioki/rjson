
%option c++
%option 8bit
%option warn
%option yyclass="JsonLexer" 

%{
#define _SKIP_YYFLEXLEXER_
#include "JsonLexer.h"

#define YY_NO_UNISTD_H
#include "JsonParser.hpp"

#define yyterminate() return token::END
#define YY_USER_ACTION  yylloc->columns(yyleng);

#include <cassert>

std::string unescape(const char* str);

%}

string          \"([^\"\n\r]+|\\\")*\"
number          ("+"|"-")?[1-9][0-9]*(\.[0-9]*)?(("e"|"E"("+"|"-")?[0-9]*))?

%%

%{
yylloc->step();
%}



[ \t]+              /* skip whitespaces */

(\n)|(\r\n)|(\r)    yylloc->lines(1); yylloc->step();

"null"              {
                        yylval->value = new rjson::Value;
                        return token::_NULL;
                    }
                   
"true"              {
                        yylval->value = new rjson::Value(true);
                        return token::TRUE;
                    }
                    
"false"             {
                        yylval->value = new rjson::Value(false);
                        return token::FALSE;
                    }

{string}            {
                        try
                        {
                            yylval->value = new rjson::Value(unescape(YYText()));
                        }
                        catch (rjson::ParseError& ex)
                        {
                            error << *yylloc->begin.filename << "(" << yylloc->begin.line << "): " << ex.what() << std::endl;
                            return token::ERROR;
                        }
                        return token::STRING;
                    }
                    
{number}            {                        
                        // NOTE: we can use atof, because we know it is well formed
                        // not perfect, but I can live with that...
                        yylval->value = new rjson::Value(atof(YYText()));
                        return token::NUMBER;
                    }

"{"                 return token::LCURL;
"}"                 return token::RCURL;
"["                 return token::LBRAK;
"]"                 return token::RBRAK;
","                 return token::COMMA;
":"                 return token::COLON;

                    
.                   {
                        error << *yylloc->begin.filename << "(" << yylloc->begin.line << "): Unexpected " << YYText() << std::endl;
                        return token::ERROR;
                    }


%%

std::string unescape(const char* str)
{
    size_t l = strlen(str);
    assert(l > 2); // we should always have at least ""

    std::string r;
    
    for (size_t i = 1; i < (l - 1); i++)
    {
        if (str[i] == '\\')
        {
            switch (str[i])
            {
                case 'b':
                    r += "\b";
                    break;
                case 'f':
                    r += "\f";
                    break;
                case 'n':
                    r += "\n";
                    break;
                case 'r':
                    r += "\r";
                    break;
                case 't':
                    r += "\t";
                    break;
                case '\\':
                    r += "\\";
                    break;
                case '/':
                    r += "/";
                    break;
                case '"':
                    r += "\"";
                    break;
                case 'u':
                    // TODO unicode sequences
                    break;
                default:
                    throw rjson::ParseError("unknown escape sequence");                    
            }
        }
        else
        {
            r += str[i];
        }
    }
    
    return r;
}

JsonLexer::JsonLexer(std::istream& input, std::ostream& e)
: yylval(NULL), yylloc(NULL), error(e)
{
    switch_streams(&input, NULL);
}
        
int JsonLexer::yylex(semantic_type* _yylval, location_type* _yylloc)
{
    this->yylval = _yylval;
    this->yylloc = _yylloc;
    return yylex();
}

int yyFlexLexer::yywrap()
{
    return 1;
}
