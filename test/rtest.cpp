
#include "rtest.h"

#include <vector>
#include <iostream>
#include <cstring>

namespace rtest
{
    std::vector<impl::Test*>& get_tests()
    {
        static std::vector<impl::Test*> tests;
        return tests;
    }
    
    int run()
    {
        std::vector<impl::Test*>& tests = get_tests();

        unsigned int failed = 0;
        for (unsigned int i = 0; i < tests.size(); i++)
        {
            try
            {
                tests[i]->run();
            }
            catch (impl::Failure& failure)
            {
                std::cerr << failure.file << "(" << failure.line << "): error: " << failure.msg << std::endl;
                failed++;
            }
            catch (std::exception& ex)
            {
                std::cerr << tests[i]->file << "(" << tests[i]->line << "): error: " << ex.what() << std::endl;
                failed++;
            }
            catch (...)
            {
                std::cerr << tests[i]->file << "(" << tests[i]->line << "): error: Test " << tests[i]->name << " crashed." << std::endl;
                failed++;
            }
        }
        
        unsigned int succeded = tests.size() - failed;
        std::cerr << succeded << " of " << tests.size() << " tests succeded." << std::endl;
                
        return failed == 0 ? 0 : -1;
    }

    namespace impl
    {
        Failure::Failure(const char* f, unsigned int l, const std::string& m)
        {
            file = f;
            line = l;
            msg  = m;
        }

        Test::Test(const char* n, const char* f, unsigned int l)
        {
            name = n;
            file = f;
            line = l;
            get_tests().push_back(this);
        }
        
        void check(bool cond, const char* scond, const char* file, unsigned int line)
        {
            if (!(cond))   
            {                                                         
                std::stringstream buff;                                                               
                buff << scond << " failed.";  
                throw ::rtest::impl::Failure(__FILE__, __LINE__, buff.str()); 
            }
        }
        
        template <>
        void check_equal(const char* a, const char* b, const char* file, unsigned int line)
        {
            if (std::strcmp(a, b) != 0)
            {                                                                                      
                std::stringstream buff;                                                               
                buff << "Expected " << a << " but got " << b << ".";
                throw ::rtest::impl::Failure(file, line, buff.str());                         
            }
        }
        
        template <>
        void check_equal(const std::string& a, const char* b, const char* file, unsigned int line)
        {
            check_equal(a.c_str(), b, file, line);
        }
        
        template <>
        void check_equal(const char* a, const std::string& b, const char* file, unsigned int line)
        {
            check_equal(a, b.c_str(), file, line);
        }
    }
}
