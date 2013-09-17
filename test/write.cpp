
#include "rtest.h"

#include "rjson.h"
#include <iomanip>
#include <sstream>

SUITE(write)
{
    TEST(noindent_object)
    {
        rjson::Object object;
        object["a"] = "a";
        object["b"] = "b";
        object["c"] = "c";
        
        std::stringstream buff;
        buff << object;
        
        std::string ref = "{\"a\":\"a\",\"b\":\"b\",\"c\":\"c\"}";
        CHECK_EQUAL(ref, buff.str());
    }
    
    TEST(indent_object)
    {
        rjson::Object object;
        object["a"] = "a";
        object["b"] = "b";
        object["c"] = "c";
        
        std::stringstream buff;
        buff << std::setw(2) << object;
        
        std::string ref = "{\n" 
                          "  \"a\": \"a\",\n"
                          "  \"b\": \"b\",\n"
                          "  \"c\": \"c\"\n"
                          "}";
        CHECK_EQUAL(ref, buff.str());
    }
    
    TEST(noindent_array)
    {
        rjson::Array array;
        array.push_back("a");
        array.push_back("b");
        array.push_back("c");
        
        std::stringstream buff;
        buff << array;
        
        std::string ref = "[\"a\",\"b\",\"c\"]";
        CHECK_EQUAL(ref, buff.str());
    }
    
    TEST(indent_array)
    {
        rjson::Array array;
        array.push_back("a");
        array.push_back("b");
        array.push_back("c");
        
        std::stringstream buff;
        buff << std::setw(2) << array;
        
        std::string ref = "[\n"
                          "  \"a\",\n"
                          "  \"b\",\n"
                          "  \"c\"\n"
                          "]";
        CHECK_EQUAL(ref, buff.str());
    }
    
    TEST(indent_mixed)
    {
        rjson::Object object;
        object["a"] = "a";
        object["b"] = "b";
        object["c"] = "c";
        
        rjson::Array array;
        array.push_back("a");
        array.push_back("b");
        array.push_back("c");
        object["array"] = array;
        
        std::stringstream buff;
        buff << std::setw(2) << object;
        
        std::string ref = "{\n" 
                          "  \"a\": \"a\",\n"
                          "  \"array\": [\n"
                          "    \"a\",\n"
                          "    \"b\",\n"
                          "    \"c\"\n"
                          "  ],\n"
                          "  \"b\": \"b\",\n"
                          "  \"c\": \"c\"\n"
                          "}";
        CHECK_EQUAL(ref, buff.str());
    }
}    
