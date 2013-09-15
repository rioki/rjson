
#include "rtest.h"

#include "rjson.h"

SUITE(value)
{
    TEST(null)
    {
        rjson::Value value;
        CHECK_EQUAL(rjson::TYPE_NULL, value.get_type());
    }
    
    TEST(boolean1)
    {
        rjson::Value value(true);
        CHECK_EQUAL(rjson::TYPE_BOOLEAN, value.get_type());
        CHECK_EQUAL(true, (bool)value);
    }
    
    TEST(boolean2)
    {
        rjson::Value value(false);
        CHECK_EQUAL(rjson::TYPE_BOOLEAN, value.get_type());
        CHECK_EQUAL(false, (bool)value);
    }
    
    TEST(number1)
    {
        short ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (short)value);
    }
    
    TEST(number2)
    {
        unsigned short ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (unsigned short)value);
    }
    
    TEST(number3)
    {
        int ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (int)value);
    }
    
    TEST(number4)
    {
        unsigned int ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (unsigned int)value);
    }
    
    TEST(number5)
    {
        long ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (long)value);
    }
    
    TEST(number6)
    {
        unsigned long ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (unsigned long)value);
    }
    
    TEST(number7)
    {
        long long ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (long long)value);
    }
    
    TEST(number8)
    {
        unsigned long long ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (unsigned long long)value);
    }
    
    TEST(number9)
    {
        float ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (float)value);
    }
    
    TEST(number10)
    {
        double ref = 12;
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_NUMBER, value.get_type());
        CHECK_EQUAL(ref, (double)value);
    }
    
    TEST(string1)
    {
        rjson::Value value("Test");
        CHECK_EQUAL(rjson::TYPE_STRING, value.get_type());
        const char* v = value;
        CHECK_EQUAL("Test", v);
    }
    
    TEST(string2)
    {
        std::string ref = "Test";
        rjson::Value value(ref);
        CHECK_EQUAL(rjson::TYPE_STRING, value.get_type());
        std::string v = value;
        CHECK_EQUAL(ref, v);
    }
}
