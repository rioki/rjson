
#include "rtest.h"

#include "rjson.h"
#include <fstream>

#include <iostream>

SUITE(parse)
{
    TEST(initial)
    {
        std::ifstream input("test/package.json");
        CHECK(input.good());
        
        rjson::Value value;
        input >> value;
        
        // NOTE: this is dependent on the JSON, 
        CHECK_EQUAL(rjson::TYPE_OBJECT, value.get_type());
        
        rjson::Object object = value;
        
        std::cout << value << std::endl;
        
        CHECK_EQUAL("http-server", (const char*)object["name"]);
    }
}    
