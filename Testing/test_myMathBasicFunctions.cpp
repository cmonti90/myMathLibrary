#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathBasicFunctions.h"

BOOST_AUTO_TEST_SUITE( test_myMathBasicFunctions )

BOOST_AUTO_TEST_CASE( test_myMathBasicFunctions_factorial )
{
    BOOST_CHECK_EQUAL( myMath::factorial( -1 ), 0 );
    BOOST_CHECK_EQUAL( myMath::factorial( 0 ), 1 );
    BOOST_CHECK_EQUAL( myMath::factorial( 1 ), 1 );
    BOOST_CHECK_EQUAL( myMath::factorial( 2 ), 2 );
    BOOST_CHECK_EQUAL( myMath::factorial( 3 ), 6 );
    BOOST_CHECK_EQUAL( myMath::factorial( 4 ), 24 );
    BOOST_CHECK_EQUAL( myMath::factorial( 5 ), 120 );
    BOOST_CHECK_EQUAL( myMath::factorial( 6 ), 720 );
    BOOST_CHECK_EQUAL( myMath::factorial( 7 ), 5040 );
    BOOST_CHECK_EQUAL( myMath::factorial( 8 ), 40320 );
    BOOST_CHECK_EQUAL( myMath::factorial( 9 ), 362880 );
    BOOST_CHECK_EQUAL( myMath::factorial( 10 ), 3628800 );
}


BOOST_AUTO_TEST_CASE( test_myMathBasicFunctions_SQ )
{
    BOOST_CHECK_EQUAL( myMath::SQ( -1 ), 1 );
    BOOST_CHECK_EQUAL( myMath::SQ( 0 ), 0 );
    BOOST_CHECK_EQUAL( myMath::SQ( 1 ), 1 );
    BOOST_CHECK_EQUAL( myMath::SQ( -1.0 ), 1.0 );
    BOOST_CHECK_EQUAL( myMath::SQ( 0.0 ), 0.0 );
    BOOST_CHECK_EQUAL( myMath::SQ( 1.0 ), 1.0 );
    BOOST_CHECK_EQUAL( myMath::SQ( 2.0 ), 4.0 );
    BOOST_CHECK_EQUAL( myMath::SQ( 3.0 ), 9.0 );
    BOOST_CHECK_EQUAL( myMath::SQ( 4.0 ), 16.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathBasicFunctions_Sign )
{
    BOOST_CHECK_EQUAL( myMath::Sign( -1 ), -1 );
    BOOST_CHECK_EQUAL( myMath::Sign( 0 ), 0 );
    BOOST_CHECK_EQUAL( myMath::Sign( 1 ), 1 );
    BOOST_CHECK_EQUAL( myMath::Sign( -1.0 ), -1.0 );
    BOOST_CHECK_EQUAL( myMath::Sign( 0.0 ), 0.0 );
    BOOST_CHECK_EQUAL( myMath::Sign( 1.0 ), 1.0 );
    BOOST_CHECK_EQUAL( myMath::Sign( 10.0 ), 1.0 );
    BOOST_CHECK_EQUAL( myMath::Sign( -10.0 ), -1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathBasicFunctions_wrapZeroToTwoPi )
{
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -16.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -15.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) - ( 1.0 / 4.0 ) * myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -14.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) - ( 1.0 / 2.0 ) * myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -13.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) - ( 3.0 / 4.0 ) * myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -12.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) -                 myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -11.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) - ( 5.0 / 4.0 ) * myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -10.0 / 8.0 ) * 2.0 * myMath::Constants::PI ) - ( 3.0 / 2.0 ) * myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( myMath::wrapZeroToTwoPi( ( -9.0  / 8.0 ) * 2.0 * myMath::Constants::PI ) - ( 7.0 / 4.0 ) * myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );


}


BOOST_AUTO_TEST_CASE( test_myMathBasicFunctions_isZero )
{

    BOOST_CHECK( myMath::isZero( 0 ) );
    BOOST_CHECK( myMath::isZero( 0.0 ) );
    BOOST_CHECK( myMath::isZero( 0.0f ) );
    BOOST_CHECK( myMath::isZero( 0.0L ) );

    BOOST_CHECK( !myMath::isZero( 45 ) );
    BOOST_CHECK( !myMath::isZero( 45.0 ) );
    BOOST_CHECK( !myMath::isZero( 45.0f ) );
    BOOST_CHECK( !myMath::isZero( 45.0L ) );

    BOOST_CHECK( !myMath::isZero( -45 ) );
    BOOST_CHECK( !myMath::isZero( -45.0 ) );
    BOOST_CHECK( !myMath::isZero( -45.0f ) );
    BOOST_CHECK( !myMath::isZero( -45.0L ) );
}



BOOST_AUTO_TEST_SUITE_END()