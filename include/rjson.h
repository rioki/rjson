//
// Copyright (c) 2013-2014 Sean Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


#ifndef _RJSON_H_
#define _RJSON_H_

#include <string>
#include <deque>
#include <map>
#include <iosfwd>
#include <stdexcept>

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT 
#endif

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
    
    typedef std::deque<Value> Array;
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
    
	class EXPORT Value
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
    
	EXPORT std::ostream& operator << (std::ostream& os, Type t);
	EXPORT std::ostream& operator << (std::ostream& os, const Value& v);
	EXPORT std::ostream& operator << (std::ostream& os, const Array& a);
	EXPORT std::ostream& operator << (std::ostream& os, const Object& o);
    
	EXPORT std::istream& operator >> (std::istream& is, Type& t);
	EXPORT std::istream& operator >> (std::istream& is, Value& t);
	EXPORT std::istream& operator >> (std::istream& is, Array& a);
	EXPORT std::istream& operator >> (std::istream& is, Object& o);
}

#endif
