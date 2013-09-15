
#include "rjson.h"

#include <cassert>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "JsonLexer.h"
#include "JsonParser.hpp"

namespace rjson
{
    std::ostream& operator << (std::ostream& os, Type t) 
    {
        switch (t)
        {
            case TYPE_NULL:
                os << "NULL";
                break;
            case TYPE_BOOLEAN:
                os << "BOOLEAN";
                break;
            case TYPE_NUMBER:
                os << "NUMBER";
                break;
            case TYPE_STRING:
                os << "STRING";
                break;
            case TYPE_ARRAY:
                os << "ARRAY";
                break;
            case TYPE_OBJECT:
                os << "OBJECT";
                break;
            default:               
                assert(false && "this never happens!");
                throw std::logic_error("stream op for Type: invalid type");     
        }
        return os;
    }
    
    void print_escaped(std::ostream& os, const char* str)
    {
        size_t s = std::strlen(str);
        
        os << "\"";
        
        for (size_t i = 0; i < s; i++)
        {
            // non printables
            if (str[i] < 32)
            {
                switch (str[i])
                {
                    case '\b':
                        os << "\\b";
                        break;
                    case '\f':
                        os << "\\f";                        
                        break;
                    case '\n':
                        os << "\\n";
                        break;
                    case '\r':
                        os << "\\r";
                        break;
                    case '\t':
                        os << "\\t";
                        break;
                    default:
                        os << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (unsigned int)str[i];
                        break;
                }
            }
            else if (str[i] == '"')
            {
                os << "\\\"";
            }
            else if (str[i] == '\\')
            {
                os << "\\\\";
            }
            else
            {
                os << str[i];
            }
        }
        
        os << "\"";
    }

    std::ostream& operator << (std::ostream& os, const Value& v)
    {
        switch (v.get_type())
        {
            case TYPE_NULL:
                os << "null";
                break;
            case TYPE_BOOLEAN:
                if ((bool)v)
                {
                    os << "true";
                }
                else
                {
                    os << "false";
                }
                break;
            case TYPE_NUMBER:
                os << (double)v;
                break;
            case TYPE_STRING:
                print_escaped(os, (const char*)v);
                break;
            case TYPE_ARRAY:
                os << (const Array&)v;
                break;
            case TYPE_OBJECT:
                os << (const Object&)v;
                break;
            default:               
                assert(false && "this never happens!");
                throw std::logic_error("stream op for Value: invalid type"); 
        }
        return os;
    }

    std::ostream& operator << (std::ostream& os, const Array& a)
    {
        os << "[";
        for (unsigned int i = 0; i < a.size(); i++)
        {
            os << a[i];
            if (i != a.size() - 1)
            {
                os << ",";
            }
        }
        os << "]";
    
        return os;
    }

    std::ostream& operator << (std::ostream& os, const Object& o)
    {        
        os << "{";

        Object::const_iterator i = o.begin();
        while (i != o.end())
        {
            print_escaped(os, i->first.c_str());
            
            os << ":" << i->second;
            
            i++;
            
            if (i != o.end())
            {
                os << ",";
            }
        }        
        
        os << "}";
    
        return os;
    }

    std::istream& operator >> (std::istream& is, Type& t)
    {
        std::string word;
        is >> word;
    
        if (word == "NULL")
        {
            t = TYPE_NULL;
        }
        else if (word == "BOOLEAN")
        {
            t = TYPE_BOOLEAN;
        }
        else if (word == "NUMBER")
        {
            t = TYPE_NUMBER;
        }
        else if (word == "STRING")
        {
            t = TYPE_STRING;
        }
        else if (word == "ARRAY")
        {
            t = TYPE_ARRAY;
        }
        else if (word == "OBJECT")
        {
            t = TYPE_OBJECT;
        }
        else
        {
            std::stringstream buff;
            buff << word << " is not a valid type!";
            throw ParseError(buff.str());
        }        
            
        return is;        
    }
    
    std::istream& operator >> (std::istream& is, Value& value)
    {
        std::stringstream error;
        std::string filename;
        
        JsonLexer lexer(is, error);
        yy::JsonParser parser(lexer, value, error, filename);
        int r = parser.parse();
        
        if (r != 0)
        {
            throw std::runtime_error(error.str());
        }
        
        return is;
    }
    
    std::istream& operator >> (std::istream& is, Array& a)
    {
        Value value;
        is >> value;
        a = value; // may throw if not correct type
        return is;
    }
    
    std::istream& operator >> (std::istream& is, Object& o)
    {
        Value value;
        is >> value;
        o = value; // may throw if not correct type
        return is;
    }
}
