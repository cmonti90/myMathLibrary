#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathDCM.h"

BOOST_AUTO_TEST_SUITE( test_myMathDCM )

BOOST_AUTO_TEST_CASE( test_myMathDCM_DefaultConstructor )
{
    myMath::DCMd dcm;

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_ScalarConstructor )
{
    myMath::DCMd dcm( 1.0 );

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_AggregateConstructor )
{
    const double x[9] = { 1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0
                        };

    myMath::DCMd dcm( x );

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_DoubleAggregateConstructor )
{
    const double x[3][3] = { { 1.0, 2.0, 3.0 },
        { 4.0, 5.0, 6.0 },
        { 7.0, 8.0, 9.0 }
    };

    myMath::DCMd dcm( x );

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_InitializerListConstructor )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_CopyConstructor )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    myMath::DCMd dcm2( dcm );

    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_CopyMatrixConstructor )
{
    const myMath::Matrix3d mat = { 1.0, 2.0, 3.0,
                                   4.0, 5.0, 6.0,
                                   7.0, 8.0, 9.0
                                 };

    myMath::DCMd dcm2( mat );

    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_AssignmentDCMOperator )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    myMath::DCMd dcm2;
    dcm2 = dcm;


    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );
}




BOOST_AUTO_TEST_CASE( test_myMathDCM_AssignmentMatrixOperator )
{
    const myMath::Matrix3d mat = { 1.0, 2.0, 3.0,
                                   4.0, 5.0, 6.0,
                                   7.0, 8.0, 9.0
                                 };

    myMath::DCMd dcm2;
    dcm2 = mat;

    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );

}




BOOST_AUTO_TEST_CASE( test_myMathDCM_AssignmentDoubleAggregateOperator )
{
    const double mat[3][3] = { { 1.0, 2.0, 3.0 },
        { 4.0, 5.0, 6.0 },
        { 7.0, 8.0, 9.0 }
    };

    myMath::DCMd dcm2;
    dcm2 = mat;

    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );

}


BOOST_AUTO_TEST_CASE( test_myMathDCM_AdditionOperator )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    const myMath::DCMd dcm2 = { -14.3, 4.0, 0.0,
                                6.0, 280.1, -1.0,
                                -3.0, 2.1, 88.0
                              };

    myMath::DCMd dcm3 = dcm + dcm2;

    BOOST_CHECK_EQUAL( dcm3( 0, 0 ), -13.3 );
    BOOST_CHECK_EQUAL( dcm3( 0, 1 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm3( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 1 ), 285.1 );
    BOOST_CHECK_EQUAL( dcm3( 1, 2 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 1 ), 10.1 );
    BOOST_CHECK_EQUAL( dcm3( 2, 2 ), 97.0 );

    const myMath::Matrix3d mat = { 1.0, 2.0, 3.0,
                                   4.0, 5.0, 6.0,
                                   7.0, 8.0, 9.0
                                 };

    dcm3 = mat + dcm2;

    BOOST_CHECK_EQUAL( dcm3( 0, 0 ), -13.3 );
    BOOST_CHECK_EQUAL( dcm3( 0, 1 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm3( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 1 ), 285.1 );
    BOOST_CHECK_EQUAL( dcm3( 1, 2 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 1 ), 10.1 );
    BOOST_CHECK_EQUAL( dcm3( 2, 2 ), 97.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_SubtractionOperator )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    const myMath::DCMd dcm2 = { -14.3, 4.0, 0.0,
                                6.0, 280.1, -1.0,
                                -3.0, 2.1, 88.0
                              };

    myMath::DCMd dcm3 = dcm - dcm2;

    BOOST_CHECK_EQUAL( dcm3( 0, 0 ), 15.3 );
    BOOST_CHECK_EQUAL( dcm3( 0, 1 ), -2.0 );
    BOOST_CHECK_EQUAL( dcm3( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 0 ), -2.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 1 ), -275.1 );
    BOOST_CHECK_EQUAL( dcm3( 1, 2 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 1 ), 5.9 );
    BOOST_CHECK_EQUAL( dcm3( 2, 2 ), -79.0 );

    const myMath::Matrix3d mat = { 1.0, 2.0, 3.0,
                                   4.0, 5.0, 6.0,
                                   7.0, 8.0, 9.0
                                 };

    dcm3 = mat - dcm2;

    BOOST_CHECK_EQUAL( dcm3( 0, 0 ), 15.3 );
    BOOST_CHECK_EQUAL( dcm3( 0, 1 ), -2.0 );
    BOOST_CHECK_EQUAL( dcm3( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 0 ), -2.0 );
    BOOST_CHECK_EQUAL( dcm3( 1, 1 ), -275.1 );
    BOOST_CHECK_EQUAL( dcm3( 1, 2 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( dcm3( 2, 1 ), 5.9 );
    BOOST_CHECK_EQUAL( dcm3( 2, 2 ), -79.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_MultiplicationOperator )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    const myMath::DCMd dcm2 = { -14.3, 4.0, 0.0,
                                6.0, 280.1, -1.0,
                                -3.0, 2.1, 88.0
                              };

    myMath::DCMd dcm3 = dcm * dcm2;

    BOOST_CHECK_SMALL( dcm3( 0, 0 ) - ( -11.3 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 0, 1 ) - ( 570.5 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 0, 2 ) - ( 262.0 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 1, 0 ) - ( -45.2 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 1, 1 ) - ( 1429.1 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 1, 2 ) - ( 523.0 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 2, 0 ) - ( -79.1 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 2, 1 ) - ( 2287.7 ), 2500.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 2, 2 ) - ( 784.0 ), 100.0 * std::numeric_limits< double >::epsilon() );

    const myMath::Matrix3d mat = { 1.0, 2.0, 3.0,
                                   4.0, 5.0, 6.0,
                                   7.0, 8.0, 9.0
                                 };

    dcm3 = mat * dcm2;

    BOOST_CHECK_SMALL( dcm3( 0, 0 ) - ( -11.3 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 0, 1 ) - ( 570.5 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 0, 2 ) - ( 262.0 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 1, 0 ) - ( -45.2 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 1, 1 ) - ( 1429.1 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 1, 2 ) - ( 523.0 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 2, 0 ) - ( -79.1 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 2, 1 ) - ( 2287.7 ), 2500.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm3( 2, 2 ) - ( 784.0 ), 100.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_CASE( test_myMathDCM_MultiplicationNonSquareMatrixOperator )
{
    myMath::Matrix< double, 3, 4 > mat = { 1.0, 2.0, 3.0, 4.0,
                                           5.0, 6.0, 7.0, 8.0,
                                           9.0, 10.0, 11.0, 12.0
                                         };

    myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                         4.0, 5.0, 6.0,
                         7.0, 8.0, 9.0
                       };

    myMath::Matrix< double, 3, 4 > mat2 = dcm * mat;

    BOOST_CHECK_EQUAL( mat2( 0, 0 ), 38.0 );
    BOOST_CHECK_EQUAL( mat2( 0, 1 ), 44.0 );
    BOOST_CHECK_EQUAL( mat2( 0, 2 ), 50.0 );
    BOOST_CHECK_EQUAL( mat2( 0, 3 ), 56.0 );
    BOOST_CHECK_EQUAL( mat2( 1, 0 ), 83.0 );
    BOOST_CHECK_EQUAL( mat2( 1, 1 ), 98.0 );
    BOOST_CHECK_EQUAL( mat2( 1, 2 ), 113.0 );
    BOOST_CHECK_EQUAL( mat2( 1, 3 ), 128.0 );
    BOOST_CHECK_EQUAL( mat2( 2, 0 ), 128.0 );
    BOOST_CHECK_EQUAL( mat2( 2, 1 ), 152.0 );
    BOOST_CHECK_EQUAL( mat2( 2, 2 ), 176.0 );
    BOOST_CHECK_EQUAL( mat2( 2, 3 ), 200.0 );

}


BOOST_AUTO_TEST_CASE( test_myMathDCM_Identity )
{
    myMath::DCMd dcm = myMath::DCMd::Identity();

    BOOST_CHECK_EQUAL( dcm( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( dcm( 2, 2 ), 1.0 );
}



BOOST_AUTO_TEST_CASE( test_myMathDCM_TransposeOperator )
{
    const myMath::DCMd dcm = { 1.0, 2.0, 3.0,
                               4.0, 5.0, 6.0,
                               7.0, 8.0, 9.0
                             };

    myMath::DCMd dcm2 = dcm.Transpose();

    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );

    dcm2.TransposeInPlace();

    BOOST_CHECK_EQUAL( dcm2( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( dcm2( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( dcm2( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( dcm2( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathDCM_ToQuaternion )
{
    myMath::DCMd dcm = myMath::DCMd::Identity();

    myMath::QuaternionD q = dcm.ToQuaternion();

    BOOST_CHECK_SMALL( q.w() - ( 1.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.x() - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.y() - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.z() - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );


    dcm = myMath::AngleD ( 3.0 * myMath::Constants::PI / 4.0, 7.0 * myMath::Constants::PI / 8.0, 2.0 * myMath::Constants::PI / 3.0 ).ToDCM( myMath::TaitBryanOrder::ZYX );

    q = dcm.ToQuaternion();

    BOOST_CHECK_SMALL( q.w() - (  0.822058304633093 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.x() - ( -0.388408142297324 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.y() - (  0.343757519000414 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.z() - ( -0.234925577389066 ), 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_CASE( test_myMathDCM_ToAngle_TaitBryanOrder )
{
    myMath::DCMd dcm = myMath::DCMd::Identity();

    myMath::Angle< double > ang = dcm.ToAngle( myMath::TaitBryanOrder::XYZ );

    BOOST_CHECK_SMALL( ang[0] - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );


    dcm = myMath::AngleD ( 3.0 * myMath::Constants::PI / 4.0, 7.0 * myMath::Constants::PI / 8.0, 2.0 * myMath::Constants::PI / 3.0 ).ToDCM( myMath::TaitBryanOrder::ZYX );

    // XYZ
    ang = dcm.ToAngle( myMath::TaitBryanOrder::XYZ );

    BOOST_CHECK_SMALL( ang[0] - ( -0.801513309269998 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  0.844548649772118 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -0.180490806148252 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZY
    ang = dcm.ToAngle( myMath::TaitBryanOrder::XZY );

    BOOST_CHECK_SMALL( ang[0] - ( -0.937108698236525 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - ( -0.119492765396374 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - (  0.852672042824705 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXZ
    ang = dcm.ToAngle( myMath::TaitBryanOrder::YXZ );

    BOOST_CHECK_SMALL( ang[0] - (  1.017363870460633 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - ( -0.497321720650419 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -0.838027874616926 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YZX
    ang = dcm.ToAngle( myMath::TaitBryanOrder::YZX );

    BOOST_CHECK_SMALL( ang[0] - (  0.529902789748927 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - ( -0.711910568065696 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -0.681707795228405 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXY
    ang = dcm.ToAngle( myMath::TaitBryanOrder::ZXY );

    BOOST_CHECK_SMALL( ang[0] - ( -0.200058400607117 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - ( -0.927467146360809 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - (  0.691835813643225 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZYX
    ang = dcm.ToAngle( myMath::TaitBryanOrder::ZYX );

    BOOST_CHECK_SMALL( ang[0] - ( -0.785398163397448 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  0.392699081698724 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -1.047197551196598 ), 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_CASE( test_myMathDCM_ToAngle_EulerOrder )
{
    myMath::DCMd dcm = myMath::DCMd::Identity();

    myMath::Angle< double > ang = dcm.ToAngle( myMath::EulerOrder::XYX );

    BOOST_CHECK_SMALL( ang[0] - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( 0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );


    dcm = myMath::AngleD ( 3.0 * myMath::Constants::PI / 4.0, 7.0 * myMath::Constants::PI / 8.0, 2.0 * myMath::Constants::PI / 3.0 ).ToDCM( myMath::TaitBryanOrder::ZYX );

    // XYX
    ang = dcm.ToAngle( myMath::EulerOrder::XYX );

    BOOST_CHECK_SMALL( ang[0] - ( -1.040893537045970 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  0.858885758729201 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - (  0.158109019630106 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZX
    ang = dcm.ToAngle( myMath::EulerOrder::XZX );

    BOOST_CHECK_SMALL( ang[0] - ( -2.611689863840867 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  0.858885758729201 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - (  1.728905346425002 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXY
    ang = dcm.ToAngle( myMath::EulerOrder::YXY );

    BOOST_CHECK_SMALL( ang[0] - (  2.993689114114857 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  0.942338207407867 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -2.201551737999084 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YZY
    ang = dcm.ToAngle( myMath::EulerOrder::YZY );

    BOOST_CHECK_SMALL( ang[0] - ( -1.718699866269833 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  0.942338207407867 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - (  2.510837242385606 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXZ
    ang = dcm.ToAngle( myMath::EulerOrder::ZXZ );

    BOOST_CHECK_SMALL( ang[0] - (  2.138745486137063 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  1.090615267940999 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -2.695461262167475 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZYZ
    ang = dcm.ToAngle( myMath::EulerOrder::ZYZ );

    BOOST_CHECK_SMALL( ang[0] - (  0.567949159342166 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[1] - (  1.090615267940999 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( ang[2] - ( -1.124664935372578 ), 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_SUITE_END()