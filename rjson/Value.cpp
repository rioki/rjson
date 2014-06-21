
#include "rjson.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>

namespace rjson
{
    char* strdup(const char* value)
    {
        size_t l = std::strlen(value);
        char* buff = (char*)std::malloc(l + 1);
        std::strcpy(buff, value);
        return buff;
    }

    Value::Value() 
    : type(TYPE_NULL) {}
    
    Value::Value(bool value)
    : type(TYPE_BOOLEAN), boolValue(value) {}
   
    Value::Value(short value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(unsigned short value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(int value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(unsigned int value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(long value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(unsigned long value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(long long value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(unsigned long long value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(float value)
    : type(TYPE_NUMBER), doubleValue(static_cast<double>(value)) {}
    
    Value::Value(double value)
    : type(TYPE_NUMBER), doubleValue(value) {}
    
    Value::Value(const char* value)
    : type(TYPE_STRING), stringValue(strdup(value)) {}
    
    Value::Value(const std::string& value)
    : type(TYPE_STRING), stringValue(strdup(value.c_str())) {}
    
    Value::Value(const Array& value)
    : type(TYPE_ARRAY), arrayValue(new Array(value)) {}
    
    Value::Value(const Object& value)
    : type(TYPE_OBJECT), objectValue(new Object(value)) {}
    
    Value::Value(const Value& orig)
    {
        copy(orig);
    }
    
    Value::~Value()
    {
        clear();        
    }
    
    const Value& Value::operator = (const Value& orig)
    {
        if (this != & orig)
        {
            clear();
            copy(orig);            
        }
        
        return *this;
    }
    
    bool Value::operator == (const Value& other) const
    {
        if (type != other.type)
        {
            return false;
        }
        
        switch (type)
        {
            case TYPE_NULL:
                return true;
            case TYPE_BOOLEAN:
                return boolValue == other.boolValue;
            case TYPE_NUMBER:
                // this is problematic, since floats don't compare well
                return doubleValue == other.doubleValue;
            case TYPE_STRING:
                return std::strcmp(stringValue, other.stringValue) == 0;                
            case TYPE_ARRAY:
                return *arrayValue == *other.arrayValue;
            case TYPE_OBJECT:
                return *objectValue == *other.objectValue;
            default:
                assert(false && "this never happens!");
                throw std::logic_error("equal operator: invalid type");     
        }
    }
        
    bool Value::operator != (const Value& other) const
    {
        return ! (*this == other);
    }
    
    Type Value::get_type() const
    {
        return type;
    }
    
    Value::operator bool () const
    {
        if (type == TYPE_BOOLEAN)
        {
            return boolValue;
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting BOOLEAN, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator short () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<short>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator unsigned short () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<unsigned short>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator int () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<int>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator unsigned int () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<unsigned int>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator long () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<long>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator unsigned long () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<unsigned long>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator long long () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<long long>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator unsigned long long () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<unsigned long long>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator float () const
    {
        if (type == TYPE_NUMBER)
        {
            return static_cast<float>(doubleValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator double () const
    {
        if (type == TYPE_NUMBER)
        {
            return doubleValue;
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting NUMBER, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator std::string () const
    {
        if (type == TYPE_STRING)
        {
            return std::string(stringValue);
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting STRING, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator const Array& () const
    {
        if (type == TYPE_ARRAY)
        {
            return *arrayValue;
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting ARRAY, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    Value::operator const Object& () const
    {
        if (type == TYPE_OBJECT)
        {
            return *objectValue;
        }
        else
        {
            std::stringstream buff;
            buff << "Invalid type: requesting OBJECT, but type is " << type << "!";
            throw InvalidType(buff.str());
        }
    }
    
    void Value::clear()
    {
        switch (type)
        {
            case TYPE_NULL:
            case TYPE_BOOLEAN:
            case TYPE_NUMBER:
                // nothing to do
                break;
            case TYPE_STRING:
                std::free(stringValue);
                break;
            case TYPE_ARRAY:
                delete arrayValue;
                break;
            case TYPE_OBJECT:
                delete objectValue;
                break;
            default:
                assert(false && "this never happens!");
        }
    }
    
    void Value::copy(const Value& orig)
    {
        type = orig.type;
        switch (type)
        {
            case TYPE_NULL:
                // nothing to do
                break;
            case TYPE_BOOLEAN:
                boolValue = orig.boolValue;
                break;
            case TYPE_NUMBER:
                doubleValue = orig.doubleValue;
                break;
            case TYPE_STRING:
                stringValue = strdup(orig.stringValue);
                break;
            case TYPE_ARRAY:
                arrayValue = new Array(*orig.arrayValue);
                break;
            case TYPE_OBJECT:
                objectValue = new Object(*orig.objectValue);
                break;
            default:
                assert(false && "this never happens!");
                throw std::logic_error("Copy constructor of Value: invalid type");     
        }
    }
}
