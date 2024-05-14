#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathMatrix.h"

BOOST_AUTO_TEST_SUITE( test_myMathMatrix1x1 )


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_ParenthesesIndexing )
{
    myMath::Matrix< double, 1, 1 > A;

    A( 0, 0 ) = 1;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_BracketsIndexing )
{
    myMath::Matrix< double, 1, 1 > A;

    A[ 0 ][ 0 ] = 1;

    BOOST_CHECK_EQUAL( A[ 0 ][ 0 ], 1 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_DefaultConstructor )
{
    myMath::Matrix< double, 1, 1 > A;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_ScalarConstructor )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1 );
}

BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_DoubleAggregateConstructor )
{
    const double x[1][1] = { { 1.0 } };

    myMath::Matrix< double, 1, 1 > A( x );

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
}



BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_CopyConstructor )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B( A );

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_InitializerListConstructor )
{
    myMath::Matrix< double, 1, 1 > A{ 1.0 };

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_AssignmentOperatorScalar )
{
    myMath::Matrix< double, 1, 1 > A;

    A = 1.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_AssignmentOperatorDoubleAggregate )
{
    const double x[1][1] = { { 1.0 } };
    myMath::Matrix< double, 1, 1 > A;

    A = x;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_AssignmentOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B;

    B = A;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_AdditionOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B( 1.0 );
    myMath::Matrix< double, 1, 1 > C;

    C = A + B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), 2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_SubtractionOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B( 1.0 );
    myMath::Matrix< double, 1, 1 > C;

    C = A - B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_MultiplicationOperatorScalar )
{
    myMath::Matrix< double, 1, 1 > A( 2.0 );
    myMath::Matrix< double, 1, 1 > B;

    B = A * 3.0;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 6.0 );

    B = 4.0 * A;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 8.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_MultiplicationOperatorVector )
{
    myMath::Matrix< double, 1, 1 > A( 2.0 );
    myMath::Vector< double, 1 > B( 3.0 );
    myMath::Vector< double, 1 > C;

    C = A * B;

    BOOST_CHECK_EQUAL( C[ 0 ], 6.0 );

}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_MultiplicationOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 2.0 );
    myMath::Matrix< double, 1, 3 > B = { 1.0, 2.0, 3.0 };
    myMath::Matrix< double, 1, 3 > C;

    C = A * B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( C( 0, 1 ), 4.0 );
    BOOST_CHECK_EQUAL( C( 0, 2 ), 6.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_DivisionOperatorScalar )
{
    myMath::Matrix< double, 1, 1 > A( 6.0 );
    myMath::Matrix< double, 1, 1 > B;

    B = A / 3.0;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_AdditionAssignmentOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B( 1.0 );

    A += B;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_SubtractionAssignmentOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B( 1.0 );

    A -= B;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_MultiplicationAssignmentOperatorScalar )
{
    myMath::Matrix< double, 1, 1 > A( 2.0 );

    A *= 3.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 6.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_MultiplicationAssignmentOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 2.0 );
    myMath::Matrix< double, 1, 1 > B = { 3.0 };

    A *= B;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 6.0 );
}



BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_DivisionAssignmentOperatorScalar )
{
    myMath::Matrix< double, 1, 1 > A( 6.0 );

    A /= 3.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 2.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_NegationOperator )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B;

    B = -A;

    BOOST_CHECK_EQUAL( B( 0, 0 ), -1.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_EqualityOperatorMatrix )
{
    myMath::Matrix< double, 1, 1 > A( 1.0 );
    myMath::Matrix< double, 1, 1 > B( 1.0 );

    BOOST_CHECK( A == B );

    B( 0, 0 ) = 2.0;

    BOOST_CHECK( A != B );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_Determinant )
{
    myMath::Matrix< double, 1, 1 > A( 5.0 );

    BOOST_CHECK_EQUAL( A.Determinant(), 5.0 );

    A = 0.0;

    BOOST_CHECK_EQUAL( A.Determinant(), 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_Transpose )
{
    myMath::Matrix< double, 1, 1 > A( 7.0 );
    myMath::Matrix< double, 1, 1 > B;

    B = A.Transpose();

    BOOST_CHECK_EQUAL( B( 0, 0 ), 7.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_TransposeInPlace )
{
    myMath::Matrix< double, 1, 1 > A( 3.0 );

    A.TransposeInPlace();

    BOOST_CHECK_EQUAL( A( 0, 0 ), 3.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_Invert )
{
    myMath::Matrix< double, 1, 1 > A( 4.0 );

    A.Invert();

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.25 );

    A = 0.0;
    A.Invert();

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_Inverse )
{
    myMath::Matrix< double, 1, 1 > A( 4.0 );
    myMath::Matrix< double, 1, 1 > B;

    B = A.Inverse();

    BOOST_CHECK_EQUAL( B( 0, 0 ), 0.25 );

    A = 0.0;

    BOOST_CHECK_EQUAL( A.Inverse()( 0, 0 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( test_myMathMatrix1x1_Trace )
{
    myMath::Matrix< double, 1, 1 > A( 6.0 );

    BOOST_CHECK_EQUAL( A.Trace(), 6.0 );
}

BOOST_AUTO_TEST_SUITE_END()