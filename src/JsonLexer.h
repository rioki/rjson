
#ifndef _JSON_LEXER_H_
#define _JSON_LEXER_H_

#if ! defined(_SKIP_YYFLEXLEXER_)
#include "FlexLexer.h"
#endif

#include <iosfwd>
#include "JsonParser.hpp"

class JsonLexer : public yyFlexLexer
{
public:
    typedef yy::JsonParser::token token;
    typedef yy::JsonParser::token_type token_type;
    typedef yy::JsonParser::semantic_type semantic_type;
    typedef yy::JsonParser::location_type location_type;

    JsonLexer(std::istream& input, std::ostream& error);    
        
    int yylex(semantic_type* yylval, location_type* yylloc);
    
    virtual int yylex();
            
private:
    semantic_type* yylval;
    location_type* yylloc;                
    
    std::ostream& error;
    
    JsonLexer(const JsonLexer&);
    const JsonLexer& operator = (const JsonLexer&);
};

#endif
