
#ifndef _RTEST_H_
#define _RTEST_H_

#include <stdexcept>
#include <sstream>
#include <cmath>

namespace rtest
{
    int run();

    namespace impl
    {
        struct Failure
        {
            const char*  file;
            unsigned int line;
            std::string  msg;

            Failure(const char* file, unsigned int line, const std::string& msg);
        };

        struct Test 
        {
            const char*  name;
            const char*  file;
            unsigned int line;

            Test(const char* name, const char* file, unsigned int line);

            virtual void run() = 0;
        };
        
        void check(bool cond, const char* scond, const char* file, unsigned int line);
        
        template <typename T1, typename T2>
        void check_equal(T1 a, T2 b, const char* file, unsigned int line) 
        {
            if (a != b)
            {                                                                                      
                std::stringstream buff;                                                               
                buff << "Expected " << a << " but got " << b << ".";
                throw ::rtest::impl::Failure(file, line, buff.str());                         
            }
        }
        
        template <>
        void check_equal(const char* a, const char* b, const char* file, unsigned int line);
        
        template <>
        void check_equal(const std::string& a, const char* b, const char* file, unsigned int line);
        
        template <>
        void check_equal(const char* a, const std::string& b, const char* file, unsigned int line);
        
        template <typename T1, typename T2, typename T3>
        void check_close(T1 a, T2 b, T3 eps, const char* file, unsigned int line) 
        {
            if (std::abs(a - b) >= eps)
            {                                                                                      
                std::stringstream buff;                                                               
                buff << "Expected " << a << " +- " << eps << " but got " << b << ".";
                throw ::rtest::impl::Failure(file, line, buff.str());                         
            }
        }
    }
}

#define SUITE(NAME) namespace NAME ## _suite

#define TEST(NAME)                                                                                 \
    struct Test_ ## NAME : public ::rtest::impl::Test                                              \
    {                                                                                              \
        Test_ ## NAME()                                                                            \
        : Test(#NAME, __FILE__, __LINE__) {}                                                       \
                                                                                                   \
        void run();                                                                                \
                                                                                                   \
    } test_ ## NAME;                                                                               \
                                                                                                   \
    void Test_ ## NAME ::run()                                                                     
                                                                                                   
#define TEST_FIXTURE(FIXTURE, NAME)                                                                \
    struct Helper_ ## NAME : public FIXTURE                                                        \
    {                                                                                              \
        void run();                                                                                \
    };                                                                                             \
                                                                                                   \
    struct Test_ ## NAME : public ::rtest::impl::Test                                              \
    {                                                                                              \
        Test_ ## NAME()                                                                            \
        : Test(#NAME, __FILE__, __LINE__) {}                                                       \
                                                                                                   \
        void run()                                                                                 \
        {                                                                                          \
            Helper_ ## NAME fixture;                                                               \
            fixture.run();                                                                         \
        }                                                                                          \
    } test_ ## NAME;                                                                               \
                                                                                                   \
    void Helper_ ## NAME ::run()

#define CHECK(COND) ::rtest::impl::check(COND, #COND, __FILE__, __LINE__)

#define CHECK_EQUAL(A, B) ::rtest::impl::check_equal(A, B, __FILE__, __LINE__) 

#define CHECK_CLOSE(A, B, EPS) ::rtest::impl::check_close(A, B, EPS, __FILE__, __LINE__) 

#define CHECK_THROW(EXPR, OBJ)                                                                     \
    try                                                                                            \
    {                                                                                              \
        EXPR;                                                                                      \
        throw ::rtest::impl::Failure(__FILE__, __LINE__, "'" #EXPR "' did not throw '" #OBJ "'."); \
    }                                                                                              \
    catch (OBJ)                                                                                    \
    {                                                                                              \
                                                                                                   \
    }


#endif
