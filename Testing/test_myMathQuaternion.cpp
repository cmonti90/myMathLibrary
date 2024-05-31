#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathQuaternion.h"

BOOST_AUTO_TEST_SUITE( test_myMathQuaternion )


BOOST_AUTO_TEST_CASE( test_Quaternion_DefaultConstructor )
{
    myMath::Quaternion< double > q;

    BOOST_CHECK_SMALL( q[0] - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_SUITE_END()