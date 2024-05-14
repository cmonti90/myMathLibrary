#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathMatrix.h"


BOOST_AUTO_TEST_SUITE( TestMyMathMatrixNonSquareSuite )


BOOST_AUTO_TEST_CASE( testNonSquareMatrixParenthesesIndexing )
{
    // non const
    myMath::Matrix< int, 2, 4 > matrix1;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 8 );


    // const
    const myMath::Matrix< int, 2, 4 > matrix2 = matrix1;

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix2( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix2( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix2( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix2( 1, 3 ), 8 );

}


BOOST_AUTO_TEST_CASE( testNonSquareMatrixSquareBracketIndexing )
{
    myMath::Matrix< int, 2, 4 > matrix1;

    matrix1[0][0] = 1;
    matrix1[0][1] = 2;
    matrix1[0][2] = 3;
    matrix1[0][3] = 4;
    matrix1[1][0] = 5;
    matrix1[1][1] = 6;
    matrix1[1][2] = 7;
    matrix1[1][3] = 8;


    BOOST_CHECK_EQUAL( matrix1[0][0], 1 );
    BOOST_CHECK_EQUAL( matrix1[0][1], 2 );
    BOOST_CHECK_EQUAL( matrix1[0][2], 3 );
    BOOST_CHECK_EQUAL( matrix1[0][3], 4 );
    BOOST_CHECK_EQUAL( matrix1[1][0], 5 );
    BOOST_CHECK_EQUAL( matrix1[1][1], 6 );
    BOOST_CHECK_EQUAL( matrix1[1][2], 7 );
    BOOST_CHECK_EQUAL( matrix1[1][3], 8 );


    const myMath::Matrix< int, 2, 4 > matrix2 = matrix1;


    BOOST_CHECK_EQUAL( matrix2[0][0], 1 );
    BOOST_CHECK_EQUAL( matrix2[0][1], 2 );
    BOOST_CHECK_EQUAL( matrix2[0][2], 3 );
    BOOST_CHECK_EQUAL( matrix2[0][3], 4 );
    BOOST_CHECK_EQUAL( matrix2[1][0], 5 );
    BOOST_CHECK_EQUAL( matrix2[1][1], 6 );
    BOOST_CHECK_EQUAL( matrix2[1][2], 7 );
    BOOST_CHECK_EQUAL( matrix2[1][3], 8 );

}

BOOST_AUTO_TEST_CASE( testNonSquareMatrixDefaultConstructor )
{
    // Default constructor
    myMath::Matrix< int, 2, 4 > matrix1;

    for ( int i = 0; i < 2; i++ )
    {
        for ( int j = 0; j < 4; j++ )
        {
            BOOST_CHECK_EQUAL( matrix1( i, j ), 0 );
        }
    }
}


BOOST_AUTO_TEST_CASE( testNonSquareMatrixSingleValueConstructor )
{
    // Single value constructor
    myMath::Matrix< int, 2, 4 > matrix1( 5 );

    for ( int i = 0; i < 2; i++ )
    {
        for ( int j = 0; j < 4; j++ )
        {
            BOOST_CHECK_EQUAL( matrix1( i, j ), 5 );
        }
    }

}


BOOST_AUTO_TEST_CASE( testNonSquareMatrixAggregateConstructor )
{
    // Aggregate reference constructor
    int x[2][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } };
    myMath::Matrix< int, 2, 4 > matrix1( x );

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 8 );

}


BOOST_AUTO_TEST_CASE( testNonSquareMatrixMatrixConstructor )
{
    // Matrix constructor
    myMath::Matrix< int, 2, 4 > matrix1( 5 );
    myMath::Matrix< int, 2, 4 > matrix2( matrix1 );

    for ( int i = 0; i < 2; i++ )
    {
        for ( int j = 0; j < 4; j++ )
        {
            BOOST_CHECK_EQUAL( matrix2( i, j ), 5 );
        }
    }


}

BOOST_AUTO_TEST_CASE( testNonSquareMatrixInitializerListConstructor )
{
    // Initializer list constructor
    myMath::Matrix< int, 2, 4 > matrix1{ 1, 2, 3, 4, 5, 6, 7, 8 };

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 8 );

}



BOOST_AUTO_TEST_CASE( testNonSquareMatrixAssignment )
{

    // Assignment of a single value
    myMath::Matrix< int, 2, 4 > matrix1 = 5;

    for ( int i = 0; i < 2; i++ )
    {
        for ( int j = 0; j < 4; j++ )
        {
            BOOST_CHECK_EQUAL( matrix1( i, j ), 5 );
        }
    }


    // Assignment of an aggregate
    myMath::Matrix< int, 2, 4 > matrix2;
    int x[2][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } };

    matrix2 = x;

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix2( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix2( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix2( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix2( 1, 3 ), 8 );


    // Assignment of a matrix
    myMath::Matrix< int, 2, 4 > matrix3 = 5;

    matrix3 = matrix2;

    BOOST_CHECK_EQUAL( matrix3( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix3( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix3( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix3( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix3( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix3( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix3( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix3( 1, 3 ), 8 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareAddition )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;
    myMath::Matrix< int, 2, 4 > matrix3;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 1;
    matrix2( 0, 1 ) = 2;
    matrix2( 0, 2 ) = 3;
    matrix2( 0, 3 ) = 4;
    matrix2( 1, 0 ) = 5;
    matrix2( 1, 1 ) = 6;
    matrix2( 1, 2 ) = 7;
    matrix2( 1, 3 ) = 8;

    matrix3 = matrix1 + matrix2;

    BOOST_CHECK_EQUAL( matrix3( 0, 0 ), 2 );
    BOOST_CHECK_EQUAL( matrix3( 0, 1 ), 4 );
    BOOST_CHECK_EQUAL( matrix3( 0, 2 ), 6 );
    BOOST_CHECK_EQUAL( matrix3( 0, 3 ), 8 );
    BOOST_CHECK_EQUAL( matrix3( 1, 0 ), 10 );
    BOOST_CHECK_EQUAL( matrix3( 1, 1 ), 12 );
    BOOST_CHECK_EQUAL( matrix3( 1, 2 ), 14 );
    BOOST_CHECK_EQUAL( matrix3( 1, 3 ), 16 );
}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareSubtraction )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;
    myMath::Matrix< int, 2, 4 > matrix3;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 8;
    matrix2( 0, 1 ) = 7;
    matrix2( 0, 2 ) = 6;
    matrix2( 0, 3 ) = 5;
    matrix2( 1, 0 ) = 4;
    matrix2( 1, 1 ) = 3;
    matrix2( 1, 2 ) = 2;
    matrix2( 1, 3 ) = 1;

    matrix3 = matrix1 - matrix2;

    BOOST_CHECK_EQUAL( matrix3( 0, 0 ), -7 );
    BOOST_CHECK_EQUAL( matrix3( 0, 1 ), -5 );
    BOOST_CHECK_EQUAL( matrix3( 0, 2 ), -3 );
    BOOST_CHECK_EQUAL( matrix3( 0, 3 ), -1 );
    BOOST_CHECK_EQUAL( matrix3( 1, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix3( 1, 1 ), 3 );
    BOOST_CHECK_EQUAL( matrix3( 1, 2 ), 5 );
    BOOST_CHECK_EQUAL( matrix3( 1, 3 ), 7 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareMatrixMultiplication )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 4, 3 > matrix2;
    myMath::Matrix< int, 2, 3 > matrix3;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 1;
    matrix2( 0, 1 ) = 2;
    matrix2( 0, 2 ) = 3;
    matrix2( 1, 0 ) = 4;
    matrix2( 1, 1 ) = 5;
    matrix2( 1, 2 ) = 6;
    matrix2( 2, 0 ) = 7;
    matrix2( 2, 1 ) = 8;
    matrix2( 2, 2 ) = 9;
    matrix2( 3, 0 ) = 10;
    matrix2( 3, 1 ) = 11;
    matrix2( 3, 2 ) = 12;

    matrix3 = matrix1 * matrix2;

    BOOST_CHECK_EQUAL( matrix3( 0, 0 ), 70 );
    BOOST_CHECK_EQUAL( matrix3( 0, 1 ), 80 );
    BOOST_CHECK_EQUAL( matrix3( 0, 2 ), 90 );
    BOOST_CHECK_EQUAL( matrix3( 1, 0 ), 158 );
    BOOST_CHECK_EQUAL( matrix3( 1, 1 ), 184 );
    BOOST_CHECK_EQUAL( matrix3( 1, 2 ), 210 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareVectorMultiplication )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Vector< int, 4 > vector1;
    myMath::Vector< int, 2 > vector2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    vector1[0] = 1;
    vector1[1] = 2;
    vector1[2] = 3;
    vector1[3] = 4;

    vector2 = matrix1 * vector1;

    BOOST_CHECK_EQUAL( vector2[0], 30 );
    BOOST_CHECK_EQUAL( vector2[1], 70 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareRhsScalarMultiplication )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2 = matrix1 * 2;

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), 2 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), 4 );
    BOOST_CHECK_EQUAL( matrix2( 0, 2 ), 6 );
    BOOST_CHECK_EQUAL( matrix2( 0, 3 ), 8 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), 10 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), 12 );
    BOOST_CHECK_EQUAL( matrix2( 1, 2 ), 14 );
    BOOST_CHECK_EQUAL( matrix2( 1, 3 ), 16 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareLhsScalarMultiplication )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2 = 2 * matrix1;

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), 2 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), 4 );
    BOOST_CHECK_EQUAL( matrix2( 0, 2 ), 6 );
    BOOST_CHECK_EQUAL( matrix2( 0, 3 ), 8 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), 10 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), 12 );
    BOOST_CHECK_EQUAL( matrix2( 1, 2 ), 14 );
    BOOST_CHECK_EQUAL( matrix2( 1, 3 ), 16 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareScalarDivision )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 2;
    matrix1( 0, 1 ) = 4;
    matrix1( 0, 2 ) = 6;
    matrix1( 0, 3 ) = 8;
    matrix1( 1, 0 ) = 10;
    matrix1( 1, 1 ) = 12;
    matrix1( 1, 2 ) = 14;
    matrix1( 1, 3 ) = 16;

    matrix2 = matrix1 / 2;

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix2( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix2( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix2( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix2( 1, 3 ), 8 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareMatrixAdditionAssignment )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 1;
    matrix2( 0, 1 ) = 2;
    matrix2( 0, 2 ) = 3;
    matrix2( 0, 3 ) = 4;
    matrix2( 1, 0 ) = 5;
    matrix2( 1, 1 ) = 6;
    matrix2( 1, 2 ) = 7;
    matrix2( 1, 3 ) = 8;

    matrix1 += matrix2;

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 2 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 4 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 6 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), 8 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 10 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 12 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 14 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 16 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareMatrixSubtractionAssignment )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 8;
    matrix2( 0, 1 ) = 7;
    matrix2( 0, 2 ) = 6;
    matrix2( 0, 3 ) = 5;
    matrix2( 1, 0 ) = 4;
    matrix2( 1, 1 ) = 3;
    matrix2( 1, 2 ) = 2;
    matrix2( 1, 3 ) = 1;

    matrix1 -= matrix2;

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), -7 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), -5 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), -3 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), -1 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 3 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 5 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 7 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareMatrixMultiplicationAssignment )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 4, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 1;
    matrix2( 0, 1 ) = 2;
    matrix2( 0, 2 ) = 3;
    matrix2( 1, 0 ) = 4;
    matrix2( 1, 1 ) = 5;
    matrix2( 1, 2 ) = 6;
    matrix2( 2, 0 ) = 7;
    matrix2( 2, 1 ) = 8;
    matrix2( 2, 2 ) = 9;
    matrix2( 3, 0 ) = 10;
    matrix2( 3, 1 ) = 11;
    matrix2( 3, 2 ) = 12;

    matrix1 *= matrix2;

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 70 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 80 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 90 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 158 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 184 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 210 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareScalarMultiplicationAssignment )
{
    myMath::Matrix< int, 2, 4 > matrix1;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix1 *= 2;

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 2 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 4 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 6 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), 8 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 10 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 12 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 14 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 16 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareScalarDivisionAssignment )
{
    myMath::Matrix< int, 2, 4 > matrix1;

    matrix1( 0, 0 ) = 2;
    matrix1( 0, 1 ) = 4;
    matrix1( 0, 2 ) = 6;
    matrix1( 0, 3 ) = 8;
    matrix1( 1, 0 ) = 10;
    matrix1( 1, 1 ) = 12;
    matrix1( 1, 2 ) = 14;
    matrix1( 1, 3 ) = 16;

    matrix1 /= 2;

    BOOST_CHECK_EQUAL( matrix1( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix1( 0, 1 ), 2 );
    BOOST_CHECK_EQUAL( matrix1( 0, 2 ), 3 );
    BOOST_CHECK_EQUAL( matrix1( 0, 3 ), 4 );
    BOOST_CHECK_EQUAL( matrix1( 1, 0 ), 5 );
    BOOST_CHECK_EQUAL( matrix1( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix1( 1, 2 ), 7 );
    BOOST_CHECK_EQUAL( matrix1( 1, 3 ), 8 );

}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareNegation )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2 = -matrix1;

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), -1 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), -2 );
    BOOST_CHECK_EQUAL( matrix2( 0, 2 ), -3 );
    BOOST_CHECK_EQUAL( matrix2( 0, 3 ), -4 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), -5 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), -6 );
    BOOST_CHECK_EQUAL( matrix2( 1, 2 ), -7 );
    BOOST_CHECK_EQUAL( matrix2( 1, 3 ), -8 );
}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareEquivalence )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 2, 4 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2( 0, 0 ) = 1;
    matrix2( 0, 1 ) = 2;
    matrix2( 0, 2 ) = 3;
    matrix2( 0, 3 ) = 4;
    matrix2( 1, 0 ) = 5;
    matrix2( 1, 1 ) = 6;
    matrix2( 1, 2 ) = 7;
    matrix2( 1, 3 ) = 8;

    BOOST_CHECK( matrix1 == matrix2 );
    BOOST_CHECK( !( matrix1 != matrix2 ) );

    matrix2( 1, 3 ) = 9;

    BOOST_CHECK( !( matrix1 == matrix2 ) );
    BOOST_CHECK( matrix1 != matrix2 );
}


BOOST_AUTO_TEST_CASE( testMatrixNonSquareTranspose )
{
    myMath::Matrix< int, 2, 4 > matrix1;
    myMath::Matrix< int, 4, 2 > matrix2;

    matrix1( 0, 0 ) = 1;
    matrix1( 0, 1 ) = 2;
    matrix1( 0, 2 ) = 3;
    matrix1( 0, 3 ) = 4;
    matrix1( 1, 0 ) = 5;
    matrix1( 1, 1 ) = 6;
    matrix1( 1, 2 ) = 7;
    matrix1( 1, 3 ) = 8;

    matrix2 = matrix1.Transpose();

    BOOST_CHECK_EQUAL( matrix2( 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( matrix2( 0, 1 ), 5 );
    BOOST_CHECK_EQUAL( matrix2( 1, 0 ), 2 );
    BOOST_CHECK_EQUAL( matrix2( 1, 1 ), 6 );
    BOOST_CHECK_EQUAL( matrix2( 2, 0 ), 3 );
    BOOST_CHECK_EQUAL( matrix2( 2, 1 ), 7 );
    BOOST_CHECK_EQUAL( matrix2( 3, 0 ), 4 );
    BOOST_CHECK_EQUAL( matrix2( 3, 1 ), 8 );

}

BOOST_AUTO_TEST_SUITE_END()