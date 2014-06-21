
#include "rtest.h"

#include "rjson.h"
#include <fstream>
#include <sstream>

SUITE(parse)
{
    TEST(initial)
    {
        std::ifstream input("package.json");
        CHECK(input.good());
        
        rjson::Value value;
        input >> value;
        
        // NOTE: this is dependent on the JSON, 
        CHECK_EQUAL(rjson::TYPE_OBJECT, value.get_type());
        
        rjson::Object object = value;
                
        CHECK_EQUAL("http-server", (std::string)object["name"]);
    }
    
    TEST(numbers) 
    {
        std::stringstream buff;
        buff << "[123,\n +2,\n -3,\n 0.4,\n +0.5,\n -0.5,\n 0.678910,\n"
                " 2e-2,\n 3E+4,\n 5e9,\n 9E3,\n 1.2e3,\n 1.2E+6]";
        
        rjson::Array value;
        buff >> value;
        
        
    }
}    
