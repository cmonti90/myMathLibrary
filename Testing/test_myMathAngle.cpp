#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathAngle.h"

BOOST_AUTO_TEST_SUITE( test_myMathAngle )

BOOST_AUTO_TEST_CASE( test_myMathAngle_BracketIndexing )
{
    myMath::Angle< double > A;

    A[0] = 1;

    BOOST_CHECK_EQUAL( A[0], 1 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_DefaultConstructor )
{
    myMath::Angle< double > A;

    BOOST_CHECK_EQUAL( A[0], 0.0 );
    BOOST_CHECK_EQUAL( A[1], 0.0 );
    BOOST_CHECK_EQUAL( A[2], 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_ScalarConstructor )
{
    myMath::Angle< double > A( 1.0 );

    BOOST_CHECK_EQUAL( A[0], 1.0 );
    BOOST_CHECK_EQUAL( A[1], 1.0 );
    BOOST_CHECK_EQUAL( A[2], 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_AggregateConstructor )
{
    const double x[3] = { 1.0, 2.0, 3.0 };

    myMath::Angle< double > A( x );

    BOOST_CHECK_EQUAL( A[0], 1.0 );
    BOOST_CHECK_EQUAL( A[1], 2.0 );
    BOOST_CHECK_EQUAL( A[2], 3.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_VectorConstructor )
{
    myMath::Vector< double, 3 > x( {1.0, 2.0, 3.0} );

    myMath::Angle< double > A( x );

    BOOST_CHECK_EQUAL( A[0], 1.0 );
    BOOST_CHECK_EQUAL( A[1], 2.0 );
    BOOST_CHECK_EQUAL( A[2], 3.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_CopyConstructor )
{
    myMath::Angle< double > A( 1.0 );
    myMath::Angle< double > B( A );

    BOOST_CHECK_EQUAL( B[0], 1.0 );
    BOOST_CHECK_EQUAL( B[1], 1.0 );
    BOOST_CHECK_EQUAL( B[2], 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_AssignmentOperator )
{
    myMath::Angle< double > A( 1.0 );
    myMath::Angle< double > B;

    B = A;

    BOOST_CHECK_EQUAL( B[0], 1.0 );
    BOOST_CHECK_EQUAL( B[1], 1.0 );
    BOOST_CHECK_EQUAL( B[2], 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_AdditionOperator )
{
    myMath::Angle< double > A( 1.0 );
    myMath::Angle< double > B( 1.0 );

    myMath::Angle< double > C = A + B;

    BOOST_CHECK_EQUAL( C[0], 2.0 );
    BOOST_CHECK_EQUAL( C[1], 2.0 );
    BOOST_CHECK_EQUAL( C[2], 2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_SubtractionOperator )
{
    myMath::Angle< double > A( 1.0 );
    myMath::Angle< double > B( 1.0 );

    myMath::Angle< double > C = A - B;

    BOOST_CHECK_EQUAL( C[0], 0.0 );
    BOOST_CHECK_EQUAL( C[1], 0.0 );
    BOOST_CHECK_EQUAL( C[2], 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_AdditionAssignmentOperator )
{
    myMath::Angle< double > A( 1.0 );
    myMath::Angle< double > B( 1.0 );

    A += B;

    BOOST_CHECK_EQUAL( A[0], 2.0 );
    BOOST_CHECK_EQUAL( A[1], 2.0 );
    BOOST_CHECK_EQUAL( A[2], 2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_SubtractionAssignmentOperator )
{
    myMath::Angle< double > A( 4.0 );
    myMath::Angle< double > B( 6.0 );

    A -= B;

    BOOST_CHECK_EQUAL( A[0], -2.0 );
    BOOST_CHECK_EQUAL( A[1], -2.0 );
    BOOST_CHECK_EQUAL( A[2], -2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_wrapAnglesZeroToTwoPi )
{
    myMath::Angle< double > A( 3.0 * myMath::Constants::PI, -5.0 * myMath::Constants::PI, -0.25 );

    A.wrapAnglesZeroToTwoPi();

    BOOST_CHECK_CLOSE( A[0], myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[1], myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[2], 2.0 * myMath::Constants::PI - 0.25, 10.0 * std::numeric_limits< double >::epsilon() );



    A[0] = 2.0 * myMath::Constants::PI;
    A[1] = -2.0 * myMath::Constants::PI;
    A[2] = myMath::Constants::PI;

    A.wrapAnglesZeroToTwoPi();

    BOOST_CHECK_CLOSE( A[0], 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[1], 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[2], myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_wrapAnglesMinusPiToPi )
{
    myMath::Angle< double > A( 3.0 * myMath::Constants::PI, -5.0 * myMath::Constants::PI, -0.25 );

    A.wrapAnglesMinusPiToPi();

    BOOST_CHECK_CLOSE( A[0], -myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[1], -myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_EQUAL( A[2], -0.25 );


    A[0] = 2.0 * myMath::Constants::PI;
    A[1] = -2.0 * myMath::Constants::PI;
    A[2] = myMath::Constants::PI;

    A.wrapAnglesMinusPiToPi();

    BOOST_CHECK_CLOSE( A[0], 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[1], 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_CLOSE( A[2], -myMath::Constants::PI, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_myMathAngle_ToDCM_TaitBryanOrder )
{
    myMath::Angle< double > A( 0.0, 0.0, 0.0 );

    myMath::Matrix< double, 3, 3 > DCM = A.ToDCM( myMath::TaitBryanOrder::ZYX );

    BOOST_CHECK_EQUAL( DCM( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( DCM( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( DCM( 0, 2 ), 0.0 );

    BOOST_CHECK_EQUAL( DCM( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( DCM( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( DCM( 1, 2 ), 0.0 );

    BOOST_CHECK_EQUAL( DCM( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( DCM( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( DCM( 2, 2 ), 1.0 );

    // ZYX
    A = myMath::Angle< double >( myMath::Constants::PI / 2.0, - 3.0 * myMath::Constants::PI / 8.0, 11.0 * myMath::Constants::PI / 16.0 );

    DCM = A.ToDCM( myMath::TaitBryanOrder::ZYX );

    BOOST_CHECK_SMALL( DCM( 0, 0 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 1 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 2 ) - (  0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 1, 0 ) - (  0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 1 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 2 ) - (  0.318189645143208 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 2, 0 ) - (  0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 1 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 2 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZY
    DCM = A.ToDCM( myMath::TaitBryanOrder::XZY );

    BOOST_CHECK_SMALL( DCM( 0, 0 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 1 ) - (  0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 2 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 1, 0 ) - (  0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 1 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 2 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 2, 0 ) - (  0.318189645143208 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 1 ) - (  0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 2 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXZ
    DCM = A.ToDCM( myMath::TaitBryanOrder::YXZ );

    BOOST_CHECK_SMALL( DCM( 0, 0 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 1 ) - (  0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 2 ) - (  0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 1, 0 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 1 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 2 ) - (  0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 2, 0 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 1 ) - (  0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 2 ) - ( 0.0 )               , 10.0 * std::numeric_limits< double >::epsilon() );


    // YZX
    DCM = A.ToDCM( myMath::TaitBryanOrder::YZX );

    BOOST_CHECK_SMALL( DCM( 0, 0 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 1 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 2 ) - ( -0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 1, 0 ) - (  0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 1 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 2 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 2, 0 ) - ( -0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 1 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 2 ) - (  0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXY
    DCM = A.ToDCM( myMath::TaitBryanOrder::ZXY );

    BOOST_CHECK_SMALL( DCM( 0, 0 ) - (  0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 1 ) - ( -0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 2 ) - ( -0.318189645143208 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 1, 0 ) - ( -0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 1 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 2 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 2, 0 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 1 ) - (  0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 2 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XYZ
    DCM = A.ToDCM( myMath::TaitBryanOrder::XYZ );

    BOOST_CHECK_SMALL( DCM( 0, 0 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 1 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 0, 2 ) - (  0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 1, 0 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 1 ) - (  0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 1, 2 ) - ( -0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( DCM( 2, 0 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 1 ) - ( -0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( DCM( 2, 2 ) - ( 0.0 )               , 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_CASE( test_myMathAngle_ToDCM_EulerOrder )
{
    myMath::Angle< double > A( 0.0, 0.0, 0.0 );

    myMath::DCMd dcm = A.ToDCM( myMath::EulerOrder::XYX );

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 0.0 );

    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 0.0 );

    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 1.0 );


    // XYX
    A = myMath::Angle< double >( myMath::Constants::PI / 2.0, - 3.0 * myMath::Constants::PI / 8.0, 11.0 * myMath::Constants::PI / 16.0 );

    dcm = A.ToDCM( myMath::EulerOrder::XYX );

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) - ( -0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) - (  0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) - ( -0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZX
    dcm = A.ToDCM( myMath::EulerOrder::XZX );

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) - ( -0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - ( -0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) - (  0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXY
    dcm = A.ToDCM( myMath::EulerOrder::YXY );

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) - (  0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) - ( -0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) - ( -0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YZY
    dcm = A.ToDCM( myMath::EulerOrder::YZY );

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - ( -0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) - (  0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) - ( -0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXZ
    dcm = A.ToDCM( myMath::EulerOrder::ZXZ );

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) - ( -0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) - (  0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - ( -0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) - (  0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZYZ
    dcm = A.ToDCM( myMath::EulerOrder::ZYZ );

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - ( -0.831469612302545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) - ( -0.212607523691814 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) - ( -0.513279967159337 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) - (  0.555570233019602 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - ( -0.318189645143209 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) - ( -0.768177756711416 ), 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) - (  0.0 )              , 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) - ( -0.923879532511287 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) - (  0.382683432365090 ), 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_CASE( test_myMathAngle_ToQuaternion_TaitBryanOrder )
{
    myMath::Angle< double > A( 0.0, 0.0, 0.0 );

    myMath::Quaternion< double > q = A.ToQuaternion( myMath::TaitBryanOrder::ZYX );

    BOOST_CHECK_EQUAL( q[0], 1.0 );
    BOOST_CHECK_EQUAL( q[1], 0.0 );
    BOOST_CHECK_EQUAL( q[2], 0.0 );
    BOOST_CHECK_EQUAL( q[3], 0.0 );


    A = myMath::Angle< double >( myMath::Constants::PI / 2.0, - 3.0 * myMath::Constants::PI / 8.0, 11.0 * myMath::Constants::PI / 16.0 );
    
    // XYZ
    q = A.ToQuaternion( myMath::TaitBryanOrder::XYZ );

    BOOST_CHECK_SMALL( q[0] - (  0.623612506493336 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - ( -0.069308584599546 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - ( -0.703701868763191 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - (  0.333327829238873 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZY
    q = A.ToQuaternion( myMath::TaitBryanOrder::XZY );

    BOOST_CHECK_SMALL( q[0] - ( -0.069308584599545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - (  0.623612506493336 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - (  0.703701868763191 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - (  0.333327829238873 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXZ
    q = A.ToQuaternion( myMath::TaitBryanOrder::YXZ );

    BOOST_CHECK_SMALL( q[0] - ( -0.069308584599545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - (  0.333327829238873 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - (  0.623612506493336 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - (  0.703701868763191 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YZX
    q = A.ToQuaternion( myMath::TaitBryanOrder::YZX );

    BOOST_CHECK_SMALL( q[0] - (  0.623612506493336 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - (  0.333327829238873 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - ( -0.069308584599546 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - ( -0.703701868763191 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXY
    q = A.ToQuaternion( myMath::TaitBryanOrder::ZXY );

    BOOST_CHECK_SMALL( q[0] - (  0.623612506493336 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - ( -0.703701868763191 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - (  0.333327829238873 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - ( -0.069308584599546 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZYX
    q = A.ToQuaternion( myMath::TaitBryanOrder::ZYX );

    BOOST_CHECK_SMALL( q[0] - ( -0.069308584599545 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[1] - (  0.703701868763191 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[2] - (  0.333327829238873 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q[3] - (  0.623612506493336 ), 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_SUITE_END()