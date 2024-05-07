#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathVector.h"


BOOST_AUTO_TEST_SUITE( TestMyMathVectorSuite )


BOOST_AUTO_TEST_CASE( testIndexing )
{

    constexpr int size = 6;
    myMath::Vector< int, size > vec{0,1,2,3,4,5};

    for ( int i = 0; i < size; ++i ) {
        BOOST_CHECK_EQUAL( vec[ i ], i );
    }
}


BOOST_AUTO_TEST_SUITE_END()
