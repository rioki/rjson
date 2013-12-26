
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
    typedef rjson::parser::token token;
    typedef rjson::parser::token_type token_type;
    typedef rjson::parser::semantic_type semantic_type;
    typedef rjson::parser::location_type location_type;

    JsonLexer(std::istream& input, std::ostream& error);    
        
    int lex(semantic_type* yylval, location_type* yylloc);
    
    virtual int yylex();
            
private:
    semantic_type* yylval;
    location_type* yylloc;                
    
    std::ostream& error;
    
    JsonLexer(const JsonLexer&);
    const JsonLexer& operator = (const JsonLexer&);
};

#endif
