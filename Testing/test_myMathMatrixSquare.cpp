#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathMatrix.h"

BOOST_AUTO_TEST_SUITE( myMathMatrixSquare )


BOOST_AUTO_TEST_CASE( myMathMatrixSquareBrackeIndexing )
{
    myMath::Matrix< double, 3, 3 > A;
    A[ 0 ][ 0 ] = 1.0;
    A[ 0 ][ 1 ] = 2.0;
    A[ 0 ][ 2 ] = 3.0;
    A[ 1 ][ 0 ] = 4.0;
    A[ 1 ][ 1 ] = 5.0;
    A[ 1 ][ 2 ] = 6.0;
    A[ 2 ][ 0 ] = 7.0;
    A[ 2 ][ 1 ] = 8.0;
    A[ 2 ][ 2 ] = 9.0;

    BOOST_CHECK_EQUAL( A[ 0 ][ 0 ], 1.0 );
    BOOST_CHECK_EQUAL( A[ 0 ][ 1 ], 2.0 );
    BOOST_CHECK_EQUAL( A[ 0 ][ 2 ], 3.0 );
    BOOST_CHECK_EQUAL( A[ 1 ][ 0 ], 4.0 );
    BOOST_CHECK_EQUAL( A[ 1 ][ 1 ], 5.0 );
    BOOST_CHECK_EQUAL( A[ 1 ][ 2 ], 6.0 );
    BOOST_CHECK_EQUAL( A[ 2 ][ 0 ], 7.0 );
    BOOST_CHECK_EQUAL( A[ 2 ][ 1 ], 8.0 );
    BOOST_CHECK_EQUAL( A[ 2 ][ 2 ], 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareParenthesesIndexing )
{
    myMath::Matrix< double, 3, 3 > A;
    A( 0, 0 ) = 1.0;
    A( 0, 1 ) = 2.0;
    A( 0, 2 ) = 3.0;
    A( 1, 0 ) = 4.0;
    A( 1, 1 ) = 5.0;
    A( 1, 2 ) = 6.0;
    A( 2, 0 ) = 7.0;
    A( 2, 1 ) = 8.0;
    A( 2, 2 ) = 9.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 9.0 );

}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareDefaultContructor )
{
    myMath::Matrix< double, 3, 3 > A;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareScalarConstructor )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0 };

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 1.0 );
}



BOOST_AUTO_TEST_CASE( myMathMatrixSquareDoubleAggregateContructor )
{
    constexpr double x[3][3] = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
    myMath::Matrix< double, 3, 3 > A{ x };

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareCopyContructor )
{
    myMath::Matrix< double, 3, 3 > A;
    A( 0, 0 ) = 1.0;
    A( 0, 1 ) = 2.0;
    A( 0, 2 ) = 3.0;
    A( 1, 0 ) = 4.0;
    A( 1, 1 ) = 5.0;
    A( 1, 2 ) = 6.0;
    A( 2, 0 ) = 7.0;
    A( 2, 1 ) = 8.0;
    A( 2, 2 ) = 9.0;

    myMath::Matrix< double, 3, 3 > B{ A };

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareInitializerListContructor )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareAssignmentOperatorScalar )
{
    myMath::Matrix< double, 3, 3 > A;
    A = 1.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareAssignmentOperatorDoubleAggregate )
{
    constexpr double x[3][3] = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
    myMath::Matrix< double, 3, 3 > A;
    A = x;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareAssignmentOperatorSquareMatrix )
{
    myMath::Matrix< double, 3, 3 > A;
    A( 0, 0 ) = 1.0;
    A( 0, 1 ) = 2.0;
    A( 0, 2 ) = 3.0;
    A( 1, 0 ) = 4.0;
    A( 1, 1 ) = 5.0;
    A( 1, 2 ) = 6.0;
    A( 2, 0 ) = 7.0;
    A( 2, 1 ) = 8.0;
    A( 2, 2 ) = 9.0;

    myMath::Matrix< double, 3, 3 > B;
    B = A;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareAssignmentOperatorInitializerList )
{
    myMath::Matrix< double, 3, 3 > A;
    A = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareAdditionOperator )
{
    const myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    const myMath::Matrix< double, 3, 3 > B{ 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    const myMath::Matrix< double, 3, 3 > C = A + B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 0, 1 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 0, 2 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 1, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 1, 1 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 1, 2 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 2, 0 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 2, 1 ), 10.0 );
    BOOST_CHECK_EQUAL( C( 2, 2 ), 10.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareSubtractionOperator )
{
    const myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    const myMath::Matrix< double, 3, 3 > B{ 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    const myMath::Matrix< double, 3, 3 > C = A - B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), -8.0 );
    BOOST_CHECK_EQUAL( C( 0, 1 ), -6.0 );
    BOOST_CHECK_EQUAL( C( 0, 2 ), -4.0 );
    BOOST_CHECK_EQUAL( C( 1, 0 ), -2.0 );
    BOOST_CHECK_EQUAL( C( 1, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( C( 1, 2 ), 2.0 );
    BOOST_CHECK_EQUAL( C( 2, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( C( 2, 1 ), 6.0 );
    BOOST_CHECK_EQUAL( C( 2, 2 ), 8.0 );
}



BOOST_AUTO_TEST_CASE( myMathMatrixSquareMultiplicationOperatorScalar )
{
    const myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    myMath::Matrix< double, 3, 3 > B = A * 2.0;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 4.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 8.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 10.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 12.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 14.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 16.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 18.0 );

    B = 2.0 * A;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 4.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 8.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 10.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 12.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 14.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 16.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 18.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareMultiplicationOperatorVector )
{
    const myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    const myMath::Vector< double, 3 > B{ 9.0, 8.0, 7.0 };
    const myMath::Vector< double, 3 > C = A * B;

    BOOST_CHECK_EQUAL( C[ 0 ], 46.0 );
    BOOST_CHECK_EQUAL( C[ 1 ], 118.0 );
    BOOST_CHECK_EQUAL( C[ 2 ], 190.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareMultiplicationOperatorSquareMatrix )
{
    const myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    const myMath::Matrix< double, 3, 3 > B{ 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    const myMath::Matrix< double, 3, 3 > C = A * B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), 30.0 );
    BOOST_CHECK_EQUAL( C( 0, 1 ), 24.0 );
    BOOST_CHECK_EQUAL( C( 0, 2 ), 18.0 );
    BOOST_CHECK_EQUAL( C( 1, 0 ), 84.0 );
    BOOST_CHECK_EQUAL( C( 1, 1 ), 69.0 );
    BOOST_CHECK_EQUAL( C( 1, 2 ), 54.0 );
    BOOST_CHECK_EQUAL( C( 2, 0 ), 138.0 );
    BOOST_CHECK_EQUAL( C( 2, 1 ), 114.0 );
    BOOST_CHECK_EQUAL( C( 2, 2 ), 90.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareMultiplicationOperatorNonSquareMatrix )
{
    const myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    const myMath::Matrix< double, 3, 2 > B{ 9.0, 8.0, 7.0, 6.0, 5.0, 4.0 };
    const myMath::Matrix< double, 3, 2 > C = A * B;

    BOOST_CHECK_EQUAL( C( 0, 0 ), 38.0 );
    BOOST_CHECK_EQUAL( C( 0, 1 ), 32.0 );
    BOOST_CHECK_EQUAL( C( 1, 0 ), 101.0 );
    BOOST_CHECK_EQUAL( C( 1, 1 ), 86.0 );
    BOOST_CHECK_EQUAL( C( 2, 0 ), 164.0 );
    BOOST_CHECK_EQUAL( C( 2, 1 ), 140.0 );
}


BOOST_AUTO_TEST_CASE( myMathMatrixSquareDivisionOperatorScalar )
{
    const myMath::Matrix< double, 3, 3 > A{ 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0 };
    const myMath::Matrix< double, 3, 3 > B = A / 2.0;

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 3.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 4.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 6.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 8.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareAdditionAssignmentOperator )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0 };
    A += 1.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 2.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareSubtractionAssignmentOperator )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0 };
    A -= 1.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 0.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareMultiplicationAssignmentOperatorScalar )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0 };
    A *= 2.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 2.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareMutliplcationSquareMatrixAssignment )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    myMath::Matrix< double, 3, 3 > B{ 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    A *= B;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 30.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 24.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 18.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 84.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 69.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 54.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 138.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 114.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 90.0 );

}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareDivisionAssignmentOperatorScalar )
{
    myMath::Matrix< double, 3, 3 > A{ 2.0 };
    A /= 2.0;

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 1.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareNegation )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0 };
    A = -A;

    BOOST_CHECK_EQUAL( A( 0, 0 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), -1.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), -1.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareEquivalence )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0 };
    myMath::Matrix< double, 3, 3 > B{ 1.0 };

    BOOST_CHECK( A == B );

    B( 0, 0 ) = 2.0;
    BOOST_CHECK( A != B );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareMinor )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    myMath::Matrix< double, 2, 2 > B = A.Minor( 1, 1 );

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 3.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 7.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareDeterminant )
{
    // Check 0.0 determinant
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double det = A.Determinant();

    BOOST_CHECK_SMALL( det, 10.0 * std::numeric_limits< double >::epsilon() );

    // Check non-zero determinant
    myMath::Matrix< double, 3, 3 > B{ 1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0 };
    det = B.Determinant();

    BOOST_CHECK_CLOSE( det, 1.0, 1.0e-10 );

}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareTranspose )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    myMath::Matrix< double, 3, 3 > B = A.Transpose();

    BOOST_CHECK_EQUAL( B( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 4.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 7.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 8.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 3.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 6.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareTransposeInPlace )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    A.TransposeInPlace();

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 4.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 7.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 2.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 5.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 8.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 3.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 6.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 9.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareInverse )
{
    // Check 0.0 determinant
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    myMath::Matrix< double, 3, 3 > B = A.Inverse();

    BOOST_CHECK_EQUAL( B( 0, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 1, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( B( 2, 2 ), 0.0 );

    // Check non-zero determinant
    myMath::Matrix< double, 3, 3 > C{ 1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0 };
    myMath::Matrix< double, 3, 3 > D = C.Inverse();

    BOOST_CHECK_CLOSE( D( 0, 0 ), -24.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 0, 1 ), 18.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 0, 2 ), 5.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 1, 0 ), 20.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 1, 1 ), -15.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 1, 2 ), -4.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 2, 0 ), -5.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 2, 1 ), 4.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( D( 2, 2 ), 1.0, 1.0e-10 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareInverseInPlace )
{
    // Check 0.0 determinant
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    A.Invert();

    BOOST_CHECK_EQUAL( A( 0, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 0.0 );

    // Check non-zero determinant
    myMath::Matrix< double, 3, 3 > B{ 1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0 };
    B.Invert();

    BOOST_CHECK_CLOSE( B( 0, 0 ), -24.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 0, 1 ), 18.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 0, 2 ), 5.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 1, 0 ), 20.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 1, 1 ), -15.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 1, 2 ), -4.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 2, 0 ), -5.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 2, 1 ), 4.0, 1.0e-10 );
    BOOST_CHECK_CLOSE( B( 2, 2 ), 1.0, 1.0e-10 );

}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareTrace )
{
    myMath::Matrix< double, 3, 3 > A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double trace = A.Trace();

    BOOST_CHECK_EQUAL( trace, 15.0 );
}


BOOST_AUTO_TEST_CASE( testMyMathMatrixSquareIdentity )
{
    myMath::Matrix< double, 3, 3 > A = myMath::Matrix< double, 3, 3 >::Identity();

    BOOST_CHECK_EQUAL( A( 0, 0 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 0, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 0, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 1, 1 ), 1.0 );
    BOOST_CHECK_EQUAL( A( 1, 2 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 0 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 1 ), 0.0 );
    BOOST_CHECK_EQUAL( A( 2, 2 ), 1.0 );
}


BOOST_AUTO_TEST_SUITE_END()