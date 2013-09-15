
#include "rtest.h"

#include "rjson.h"

SUITE(object)
{
    TEST(initial)
    {
        rjson::Object object;
    }
    
    TEST(with_value)
    {
        rjson::Object object;
        object["a"] = rjson::Value("Test");
        object["b"] = rjson::Value(12.5);
        object["c"] = rjson::Value(false);
        
        rjson::Value value(object);
        CHECK_EQUAL(rjson::TYPE_OBJECT, value.get_type());
        
        rjson::Object o2 = value;
        CHECK_EQUAL(object, o2);
    }
    
    TEST(print)
    {
        rjson::Object object;
        object["a"] = rjson::Value("Test");
        object["b"] = rjson::Value(12.5);
        object["c"] = rjson::Value(false);
        
        std::stringstream buff;
        buff << object;        
        
        std::string ref = "{\"a\":\"Test\",\"b\":12.5,\"c\":false}";
        
        CHECK_EQUAL(ref, buff.str());
    }
    
    TEST(print_array_and_object)
    {
        rjson::Object package;
        package["name"] = "rjson";
        package["version"] = "0.0.0";
        
        rjson::Array tags;
        tags.push_back("json");
        tags.push_back("c++");
        
        package["tags"] = tags;
        
        std::stringstream buff;
        buff << package;        
        
        std::string ref = "{\"name\":\"rjson\",\"tags\":[\"json\",\"c++\"],\"version\":\"0.0.0\"}";
        
        CHECK_EQUAL(ref, buff.str());
    }
}    

