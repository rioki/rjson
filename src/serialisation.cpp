
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
    
    struct indent
    {
        unsigned int spaces;
        unsigned int level;
    
        indent(unsigned int s, unsigned int l)
        : spaces(s), level(l) {}
    };
    
    std::ostream& operator << (std::ostream& os, indent in)
    {
        unsigned int cnt = in.spaces * in.level;
    
        for (unsigned int i = 0; i < cnt; i++)
        {            
            os << " ";
        }
        return os;
    }
    
    void write(std::ostream& os, unsigned int spaces, unsigned int level, const Array& array);
    void write(std::ostream& os, unsigned int spaces, unsigned int level, const Object& object);
    
    void write(std::ostream& os, unsigned int spaces, unsigned int level, const Value& value)
    {
        switch (value.get_type())
        {
            case TYPE_NULL:
                os << "null";
                break;
            case TYPE_BOOLEAN:
                if ((bool)value)
                {
                    os << "true";
                }
                else
                {
                    os << "false";
                }
                break;
            case TYPE_NUMBER:
                os << (double)value;
                break;
            case TYPE_STRING:
                print_escaped(os, (const char*)value);
                break;
            case TYPE_ARRAY:
                write(os, spaces, level, (const Array&)value);                
                break;
            case TYPE_OBJECT:
                write(os, spaces, level, (const Object&)value);
                break;
            default:               
                assert(false && "this never happens!");
                throw std::logic_error("stream op for Value: invalid type"); 
        }
    }
    
    void write(std::ostream& os, unsigned int spaces, unsigned int level, const Array& array)
    {
        level++;
        
        if (spaces == 0)
        {
            os << "[";
        }
        else
        {
            os << "[\n" << indent(spaces, level);
        }
        
        for (unsigned int i = 0; i < array.size(); i++)
        {
            write(os, spaces, level, array[i]);
            if (i != array.size() - 1)
            {
                if (spaces == 0)
                {
                    os << ",";
                }
                else
                {
                    os << ",\n" << indent(spaces, level);
                }                
            }
        }
        
        level--;
        
        if (spaces == 0)
        {
            os << "]";
        }
        else
        {
            os << "\n" << indent(spaces, level) << "]";
        }
    }
    
    void write(std::ostream& os, unsigned int spaces, unsigned int level, const Object& object)
    {
        level++;
        if (spaces == 0)
        {
            os << "{";
        }
        else
        {
            os << "{\n" << indent(spaces, level);
        }

        Object::const_iterator i = object.begin();
        while (i != object.end())
        {
            print_escaped(os, i->first.c_str());
            
            if (spaces == 0)
            {
                os << ":";
            }
            else
            {
                os << ": ";
            }
            
            write(os, spaces, level, i->second);            
            i++;
            
            if (i != object.end())
            {
                if (spaces == 0)
                {
                    os << ",";
                }
                else
                {
                    os << ",\n" << indent(spaces, level);
                } 
            }
        }
        
        level--;
        
        if (spaces == 0)
        {
            os << "}";
        }
        else
        {
            os << "\n" << indent(spaces, level) << "}";
        }
    }
    
    std::ostream& operator << (std::ostream& os, const Value& v)
    {
        unsigned int spaces = os.width();
        os.width(0);
        
        write(os, spaces, 0, v);
        return os;
    }
    
    std::ostream& operator << (std::ostream& os, const Array& a)
    {
        unsigned int spaces = os.width();
        os.width(0);
        
        write(os, spaces, 0, a);    
        return os;
    }

    std::ostream& operator << (std::ostream& os, const Object& o)
    {        
        unsigned int spaces = os.width();
        os.width(0);
        
        write(os, spaces, 0, o);    
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
        parser prs(lexer, value, error, filename);
        int r = prs.parse();
        
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
