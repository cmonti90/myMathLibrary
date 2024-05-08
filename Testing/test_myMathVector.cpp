#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathVector.h"


BOOST_AUTO_TEST_SUITE( TestMyMathVectorSuite )

BOOST_AUTO_TEST_CASE( testIndexing )
{

    constexpr int size = 6;
    myMath::Vector< int, size > vec{0, 1, 2, 3, 4, 5};

    for ( int i = 0; i < size; ++i ) {
        BOOST_CHECK_EQUAL( vec[ i ], i );
    }
}

BOOST_AUTO_TEST_CASE( testConstructors )
{
    constexpr int size = 6;

    // Test default constructor
    myMath::Vector< int, size > vec1;

    for ( int i = 0; i < size; i++ )
    {
        BOOST_CHECK_EQUAL( vec1[i], 0 );
    }


    // Test constructor with a single value
    constexpr int numTest = 5;
    myMath::Vector< int, size > vec2( numTest );

    for ( int i = 0; i < size; i++ )
    {
        BOOST_CHECK_EQUAL( vec2[i], numTest );
    }


    // Test constructor with an aggregate
    const int arr[size] = {0, 1, 2, 3, 4, 5};
    myMath::Vector< int, size > vec3( arr );

    for ( int i = 0; i < size; i++ )
    {
        BOOST_CHECK_EQUAL( vec3[i], arr[i] );
    }


    // Test copy constructor
    myMath::Vector< int, size > vec4( vec3 );

    for ( int i = 0; i < size; i++ )
    {
        BOOST_CHECK_EQUAL( vec4[i], vec3[i] );
    }


    // Test initializer list constructor
    myMath::Vector< int, size > vec5{0, 1, 2, 3, 4, 5};

    for ( int i = 0; i < size; i++ )
    {
        BOOST_CHECK_EQUAL( vec5[i], i );
    }


}


BOOST_AUTO_TEST_CASE( testAssignments )
{
    constexpr int vecSize = 20;
    constexpr int numTest = 10;

    // Test assignment of a single value
    myMath::Vector< int, vecSize > vec = numTest;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec[i], numTest );
    }


    // Test assignment of an aggregate
    const int arr[vecSize] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                              10, 11, 12, 13, 14, 15, 16, 17, 18, 19
                             };

    vec = arr;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec[i], arr[i] );
    }


    // Test assignment of another vector
    myMath::Vector< int, vecSize > vec2 = 5;
    vec = vec2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec[i], vec2[i] );
    }


    // Test assignment of an initializer list
    vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
           10, 11, 12, 13, 14, 15, 16, 17, 18, 19
          };

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec[i], i );
    }

}


BOOST_AUTO_TEST_CASE( testBinaryOperators )
{
    constexpr int vecSize = 20;

    myMath::Vector< int, vecSize > vec1 = 5;
    myMath::Vector< int, vecSize > vec2 = 10;

    // Test addition
    myMath::Vector< int, vecSize > vec3 = vec1 + vec2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec3[i], vec1[i] + vec2[i] );
    }


    // Test subtraction
    vec3 = vec1 - vec2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec3[i], vec1[i] - vec2[i] );
    }


    // Test multiplication with a RHS scalar
    constexpr int scalar = 2;
    vec3 = vec1 * scalar;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec3[i], vec1[i] * scalar );
    }


    // Test multiplication with a LHS scalar
    vec3 = scalar * vec1;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec3[i], scalar * vec1[i] );
    }


    // Test division with a RHS scalar
    myMath::Vector< double, vecSize > vec4 = 2.0;
    myMath::Vector< double, vecSize > vec5 = vec4 / static_cast< double >( scalar );

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec5[i], static_cast< double >( vec4[i] ) / scalar );
    }

}


BOOST_AUTO_TEST_CASE( testAssignmentBinaryOperators )
{
    constexpr int vecSize = 20;

    constexpr int scalar1 = 5;
    constexpr int scalar2 = 10;

    myMath::Vector< int, vecSize > vec1;
    myMath::Vector< int, vecSize > vec2;

    // Test addition
    vec1 = scalar1;
    vec2 = scalar2;

    vec1 += vec2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec1[i], scalar1 + scalar2 );
    }


    // Test subtraction
    vec1 = scalar1;
    vec2 = scalar2;

    vec1 -= vec2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec1[i], scalar1 - scalar2 );
    }


    // Test multiplication
    vec1 = scalar1;

    vec1 *= scalar2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec1[i], scalar1 * scalar2 );
    }


    // Test division
    vec1 = scalar1;

    vec1 /= scalar2;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec1[i], scalar1 / scalar2 );
    }

}


BOOST_AUTO_TEST_CASE( testNegation )
{
    constexpr int vecSize = 20;

    myMath::Vector< int, vecSize > vec1 = 5;
    myMath::Vector< int, vecSize > vec2 = -vec1;

    for ( int i = 0; i < vecSize; i++ )
    {
        BOOST_CHECK_EQUAL( vec2[i], -vec1[i] );
    }
}


BOOST_AUTO_TEST_CASE( testEquivalence )
{
    constexpr int vecSize = 20;

    myMath::Vector< int, vecSize > vec1 = 5;
    myMath::Vector< int, vecSize > vec2 = vec1;

    BOOST_CHECK( vec1 == vec2 );
    BOOST_CHECK( !( vec1 != vec2 ) );

    vec2 = vec1 + 5;

    BOOST_CHECK( vec1 != vec2 );
    BOOST_CHECK( !( vec1 == vec2 ) );
}


BOOST_AUTO_TEST_CASE( testMagnitude )
{
    myMath::Vector< double, 3 > vec = {1.0, 2.0, 3.0};

    BOOST_CHECK_EQUAL( vec.Magnitude(), std::sqrt( vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] ) );
}


BOOST_AUTO_TEST_CASE( testNormalization )
{
    myMath::Vector< double, 3 > vec1 = {1.0, 2.0, 3.0};
    myMath::Vector< double, 3 > unitVec = vec1;
    unitVec.Normalize();

    BOOST_CHECK_EQUAL( unitVec.Magnitude(), 1.0 );
    BOOST_CHECK_EQUAL( unitVec[0], vec1[0] / vec1.Magnitude() );
    BOOST_CHECK_EQUAL( unitVec[1], vec1[1] / vec1.Magnitude() );
    BOOST_CHECK_EQUAL( unitVec[2], vec1[2] / vec1.Magnitude() );
}


BOOST_AUTO_TEST_CASE( testUnitVector )
{
    myMath::Vector< double, 3 > vec1 = {1.0, 2.0, 3.0};
    myMath::Vector< double, 3 > unitVec = vec1.Unit();

    BOOST_CHECK_EQUAL( unitVec.Magnitude(), 1.0 );
    BOOST_CHECK_EQUAL( unitVec[0], vec1[0] / vec1.Magnitude() );
    BOOST_CHECK_EQUAL( unitVec[1], vec1[1] / vec1.Magnitude() );
    BOOST_CHECK_EQUAL( unitVec[2], vec1[2] / vec1.Magnitude() );
}

BOOST_AUTO_TEST_SUITE_END()
