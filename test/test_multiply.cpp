//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <exception>
#include <cxxabi.h>

#include "../include/safe_integer.hpp"

#include "test.hpp"

template<class T1, class T2>
bool test_multiply(
    T1 v1,
    T2 v2,
    const char *av1,
    const char *av2,
    char expected_result
){
    using namespace boost::numeric;
    auto unsafe_result = v1 + v2;
    {
        std::cout << "testing  safe<" << av1 << "> * " << av2 << " -> ";
        static_assert(boost::numeric::is_safe<safe<T1> >::value, "safe not safe!");

        safe<T1> t1 = v1;

        using result_type = decltype(t1 * v2);
        result_type result;

        static_assert(
            boost::numeric::is_safe<result_type>::value,
            "Expression failed to return safe type"
        );

        try{
            result = t1 * v2;
            std::cout << std::hex << result << "(" << std::dec << result << ")"
                << std::endl;
            if(expected_result == 'x'){
                const std::type_info & ti = typeid(result);
                int status;
                std::cout
                    << "*** failed to detect error in multiplication "
                    << abi::__cxa_demangle(ti.name(),0,0,&status) << '\n'
                    << std::endl;
                try{
                    t1 * v2;
                }
                catch(std::exception){}
                assert(result != unsafe_result);
                return false;
            }
        }
        catch(std::exception){
            std::cout << std::hex << result << "(" << std::dec << result << ")"
                << std::endl;
            if(expected_result == '.'){
                const std::type_info & ti = typeid(result);
                int status;
                std::cout
                    << "*** erroneously detected error in multiplication "
                    << abi::__cxa_demangle(ti.name(),0,0,&status) << '\n'
                    << std::endl;
                try{
                    t1 * v2;
                }
                catch(std::exception){}
                assert(result == unsafe_result);
                return false;
            }
        }
    }
    {
        std::cout << "testing  " << av1 << " * " << "safe<"<< av2 << "> -> ";
        static_assert(boost::numeric::is_safe<safe<T2> >::value, "safe not safe!");

        safe<T2> t2 = v2;

        using result_type = decltype(v1 * t2);
        result_type result;

        static_assert(
            boost::numeric::is_safe<result_type>::value,
            "Expression failed to return safe type"
        );

        try{
            result = v1 * t2;
            std::cout << std::hex << result << "(" << std::dec << result << ")"
                << std::endl;
            if(expected_result == 'x'){
                const std::type_info & ti = typeid(result);
                int status;
                std::cout
                    << "*** failed to detect error in multiplication "
                    << abi::__cxa_demangle(ti.name(),0,0,&status) << '\n'
                    << std::endl;
                try{
                    v1 * t2;
                }
                catch(std::exception){}
                assert(result != unsafe_result);
                return false;
            }
        }
        catch(std::exception){
            std::cout << std::hex << result << "(" << std::dec << result << ")"
                << std::endl;
            if(expected_result == '.'){
                const std::type_info & ti = typeid(result);
                int status;
                std::cout
                    << "*** erroneously detected error in multiplication "
                    << abi::__cxa_demangle(ti.name(),0,0,&status) << '\n'
                    << std::endl;
                try{
                    v1 * t2;
                }
                catch(std::exception){}
                assert(result == unsafe_result);
                return false;
            }
        }
    }
    {
        std::cout << "testing  safe<" << av1 << "> * safe<" << av2 << "> -> ";
        safe<T1> t1 = v1;
        safe<T2> t2 = v2;

        using result_type = decltype(t1 * t2);
        result_type result;

        static_assert(
            boost::numeric::is_safe<result_type>::value,
            "Expression failed to return safe type"
        );

        try{
            result = t1 * t2;
            std::cout << std::hex << result << "(" << std::dec << result << ")"
                << std::endl;
            if(expected_result == 'x'){
                const std::type_info & ti = typeid(result);
                int status;
                std::cout
                    << "*** failed to detect error in multiplication "
                    << abi::__cxa_demangle(ti.name(),0,0,&status) << '\n'
                    << std::endl;
                try{
                    t1 * t2;
                }
                catch(std::exception){}
                assert(result != unsafe_result);
                return false;
            }
        }
        catch(std::exception){
            std::cout << std::hex << result << "(" << std::dec << result << ")"
                << std::endl;
            if(expected_result == '.'){
                const std::type_info & ti = typeid(result);
                int status;
                std::cout
                    << "*** erroneously detected error in multiplication "
                    << abi::__cxa_demangle(ti.name(),0,0,&status) << '\n'
                    << std::endl;
                try{
                    t1 * t2;
                }
                catch(std::exception){}
                assert(result == unsafe_result);
                return false;
            }
        }
    }
    return true;
}

#include "test.hpp"
#include "test_values.hpp"

// note: These tables presume that the the size of an int is 32 bits.
// This should be changed for a different architecture or better yet
// be dynamically adjusted depending on the indicated architecture

const char *test_multiplication_result[VALUE_ARRAY_SIZE] = {
//      0       0       0       0
//      01234567012345670123456701234567
//      01234567890123456789012345678901
/* 0*/ "................................",
/* 1*/ ".........xx..xx..........xxx.xxx",
/* 2*/ ".........xx..xx.........xxxxxxxx",
/* 3*/ "..........x...x.........xxxxxxxx",
/* 4*/ "................................",
/* 5*/ ".........xx..xx..........xxx.xxx",
/* 6*/ ".........xx..xx.........xxxxxxxx",
/* 7*/ "..........x...x.........xxxxxxxx",

/* 8*/ "................................",
/* 9*/ ".xx..xx..xx..xx..xxx.xxx.xxx.xxx",
/*10*/ ".xxx.xxx.xxx.xx..xxx.xxxxxxxxxxx",
/*11*/ "..........x...x.........xxxxxxxx",
/*12*/ "................................",
/*13*/ ".xx..xx..xx..xx..xxx.xxx.xxx.xxx",
/*14*/ ".xxx.xxx.xxx.xxx.xxx.xxx.xxxxxxx",
/*15*/ "..............x.............xxxx",

//      0       0       0       0
//      01234567012345670123456701234567
//      01234567890123456789012345678901
/*16*/ "................................",
/*17*/ ".........xx..xx..........xxx.xxx",
/*18*/ ".........xx..xx..........xxx.xxx",
/*19*/ ".........xx..xx..........xxx.xxx",
/*20*/ "................................",
/*21*/ ".........xx..xx..........xxx.xxx",
/*22*/ ".........xx..xx..........xxx.xxx",
/*23*/ ".........xx..xx..........xxx.xxx",

/*24*/ "..xx..xx..xx....................",
/*25*/ ".xxx.xxx.xxx.xx..xxx.xxx.xxx.xxx",
/*26*/ ".xxx.xxx.xxx.xx..xxx.xxx.xxx.xxx",
/*27*/ ".xxx.xxx.xxx.xx..xxx.xxx.xxx.xxx",
/*28*/ "..xx..xx..xx..xx................",
/*29*/ ".xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx",
/*30*/ ".xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx",
/*31*/ ".xxx.xxx.xxx.xxx.xxx.xxx.xxx.xxx"
};

#define TEST_IMPL(v1, v2, result) \
    rval &= test_multiply(        \
        v1,                       \
        v2,                       \
        BOOST_PP_STRINGIZE(v1),   \
        BOOST_PP_STRINGIZE(v2),   \
        result                    \
    );
/**/

#define TESTX(value_index1, value_index2)          \
    (std::cout << value_index1 << ',' << value_index2 << ','); \
    TEST_IMPL(                                     \
        BOOST_PP_ARRAY_ELEM(value_index1, VALUES), \
        BOOST_PP_ARRAY_ELEM(value_index2, VALUES), \
        test_multiplication_result[value_index1][value_index2] \
    )
/**/

int main(int argc, char * argv[]){
    // sanity check on test matrix - should be symetrical
    for(int i = 0; i < VALUE_ARRAY_SIZE; ++i)
        for(int j = i + 1; j < VALUE_ARRAY_SIZE; ++j)
            if(!(test_multiplication_result[i][j]
            == test_multiplication_result[j][i]))
                std::cerr << "asymmetry in operations "
                    << "i == " << i
                    << " j == " << j
                    << std::endl;
    bool rval = true;
    TEST_EACH_VALUE_PAIR
    return ! rval ;
}
