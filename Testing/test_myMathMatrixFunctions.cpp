#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathMatrixFunctions.h"


BOOST_AUTO_TEST_SUITE( test_myMathAngle )


BOOST_AUTO_TEST_CASE( test_DotProduct )
{
    myMath::Vector3d a{ 1.0, 2.0, 3.0 };
    myMath::Vector3d b{ 4.0, 5.0, 6.0 };

    BOOST_CHECK_SMALL( myMath::DotProduct( a, b ) - ( a[0]*b[0] + a[1] * b[1] + a[2] *b[2] ), 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_CrossProduct )
{
    myMath::Vector3d a{ 1.0, 2.0, 3.0 };
    myMath::Vector3d b{ 4.0, 5.0, 6.0 };

    myMath::Vector3d c = myMath::CrossProduct( a, b );

    BOOST_CHECK_SMALL( c[0] - ( a[1] * b[2] - a[2] * b[1] ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c[1] - ( a[2] * b[0] - a[0] * b[2] ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c[2] - ( a[0] * b[1] - a[1] * b[0] ), 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Magnitude )
{
    myMath::Vector3d a{ 1.0, 2.0, 3.0 };

    BOOST_CHECK_SMALL( myMath::Magnitude( a ) - std::sqrt( a[0] * a[0] + a[1] * a[1] + a[2] * a[2] ), 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Transpose_Matrix )
{
    myMath::Matrix< double, 5, 7 > a{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                                        8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0,
                                        15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0,
                                        22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0,
                                        29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0};

    myMath::Matrix< double, 7, 5 > b = myMath::Transpose( a );

    BOOST_CHECK_SMALL( b( 0, 0 ) - a( 0, 0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 0, 1 ) - a( 1, 0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 0, 2 ) - a( 2, 0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 0 ) - a( 0, 1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 1 ) - a( 1, 1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 2 ) - a( 2, 1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 0 ) - a( 0, 2 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 1 ) - a( 1, 2 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 2 ) - a( 2, 2 ), 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Transpose_DCM )
{
    myMath::DCM< double > a{ 1.0, 2.0, 3.0,
                             4.0, 5.0, 6.0,
                             7.0, 8.0, 9.0 };

    myMath::DCM< double > b = myMath::Transpose( a );

    BOOST_CHECK_SMALL( b( 0, 0 ) - a( 0, 0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 0, 1 ) - a( 1, 0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 0, 2 ) - a( 2, 0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 0 ) - a( 0, 1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 1 ) - a( 1, 1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 2 ) - a( 2, 1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 0 ) - a( 0, 2 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 1 ) - a( 1, 2 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 2 ) - a( 2, 2 ), 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_OuterProduct )
{
    myMath::Vector3d a{ 1.0, 2.0, 3.0 };
    myMath::Vector3d b{ 4.0, 5.0, 6.0 };

    myMath::Matrix3d c = myMath::OuterProduct( a, b );

    BOOST_CHECK_SMALL( c( 0, 0 ) - a[0] * b[0], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 0, 1 ) - a[0] * b[1], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 0, 2 ) - a[0] * b[2], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 1, 0 ) - a[1] * b[0], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 1, 1 ) - a[1] * b[1], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 1, 2 ) - a[1] * b[2], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 2, 0 ) - a[2] * b[0], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 2, 1 ) - a[2] * b[1], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( c( 2, 2 ) - a[2] * b[2], 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Identity )
{
    myMath::Matrix3d a = myMath::Identity< double, 3 >();

    BOOST_CHECK_SMALL( a( 0, 0 ) - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 0, 1 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 0, 2 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 1, 0 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 1, 1 ) - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 1, 2 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 2, 0 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 2, 1 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( a( 2, 2 ) - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );


    myMath::DCMd b = myMath::Identity< double, 3 >();

    BOOST_CHECK_SMALL( b( 0, 0 ) - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 0, 1 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 0, 2 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 0 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 1 ) - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 1, 2 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 0 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 1 ) - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( b( 2, 2 ) - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
}



BOOST_AUTO_TEST_SUITE_END()