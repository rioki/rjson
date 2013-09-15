
#include "rtest.h"

#include "rjson.h"

SUITE(array)
{
    TEST(initial)
    {
        rjson::Array array;
    }
    
    TEST(with_value)
    {
        rjson::Array array;
        array.push_back(rjson::Value("Test"));
        array.push_back(rjson::Value(12.5));
        array.push_back(rjson::Value(false));
        
        rjson::Value value(array);
        CHECK_EQUAL(rjson::TYPE_ARRAY, value.get_type());
        
        rjson::Array a2 = value;
        CHECK_EQUAL(array, a2);
    }
    
    TEST(print)
    {
        rjson::Array array;
        array.push_back(rjson::Value("Test\n\a"));
        array.push_back(rjson::Value(12.5));
        array.push_back(rjson::Value(false));
        
        std::stringstream buff;
        buff << array;        
        
        std::string ref = "[\"Test\\n\\u0007\",12.5,false]";
        
        CHECK_EQUAL(ref, buff.str());
    }
}    
