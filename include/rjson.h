
#ifndef _RJSON_H_
#define _RJSON_H_

#include <string>
#include <vector>
#include <map>
#include <iosfwd>
#include <stdexcept>

namespace rjson
{
    enum Type
    {
        TYPE_NULL,
        TYPE_BOOLEAN,
        TYPE_NUMBER,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_OBJECT
    };
    
    class Value;
    
    // MAYBE use clases instead of typedef so a new type is created for type resolution
    
    typedef std::vector<Value> Array;
    //class Array : public std::vector<Value> {}:
    
    typedef std::map<std::string, Value> Object;
    //class Object : public std::map<std::string, Value> {};

    struct InvalidType : public std::logic_error
    {
        InvalidType(const std::string& msg)
        : std::logic_error(msg) {}
    };
    
    struct ParseError : public std::runtime_error
    {
        ParseError(const std::string& msg)
        : std::runtime_error(msg) {}
    };
    
    class Value
    {
    public:
    
        Value();
        
        Value(bool value);
        
        Value(short value);
        
        Value(unsigned short value);
        
        Value(int value);
        
        Value(unsigned int value);
        
        Value(long value);
        
        Value(unsigned long value);
        
        Value(long long value);
        
        Value(unsigned long long value);
        
        Value(float value);
        
        Value(double value);
        
        Value(const char* value);
        
        Value(const std::string& value);
        
        Value(const Array& value);
        
        Value(const Object& value);
        
        Value(const Value& orig);
        
        ~Value();
        
        const Value& operator = (const Value& orig);
        
        bool operator == (const Value& other) const;
        
        bool operator != (const Value& other) const;
        
        Type get_type() const;
        
        operator bool () const;
        
        operator short () const;
        
        operator unsigned short () const;
        
        operator int () const;
        
        operator unsigned int () const;
        
        operator long () const;
        
        operator unsigned long () const;
        
        operator long long () const;
        
        operator unsigned long long () const;
        
        operator float () const;
        
        operator double () const;
        
        operator const char* () const;
        
        operator std::string () const;
        
        operator const Array& () const;
        
        operator const Object& () const;
        
    private:       
        Type type;
        
        union {
            bool    boolValue;
            double  doubleValue;
            char*   stringValue;
            Array*  arrayValue;
            Object* objectValue;
        };
    
        void clear();
        void copy(const Value& orig);
    };
    
    std::ostream& operator << (std::ostream& os, Type t);
    std::ostream& operator << (std::ostream& os, const Value& v);
    std::ostream& operator << (std::ostream& os, const Array& a);
    std::ostream& operator << (std::ostream& os, const Object& o);
    
    std::istream& operator >> (std::istream& is, Type& t);
    std::istream& operator >> (std::istream& is, Value& t);
    std::istream& operator >> (std::istream& is, Array& a);
    std::istream& operator >> (std::istream& is, Object& o);
}

#endif
