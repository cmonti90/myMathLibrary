#ifndef MYMATH_BASIC_FUNCTIONS_H
#define MYMATH_BASIC_FUNCTIONS_H


#include "myMathConstants.h"

#include <cmath>


namespace myMath
{

/////////////////////////////////
//         DECLARATIONS        //
/////////////////////////////////
unsigned int factorial( const unsigned int x );

int factorial( const int x );

template< typename T >
T SQ( const T x );

template< typename T >
T Sign( const T x );

template< typename T >
T wrapZeroToTwoPi( const T ang );

template< typename T >
T wrapMinusPiToPi( const T ang );

template< typename T >
bool isZero( const T x );


/////////////////////////////////
//         DEFINITIONS         //
/////////////////////////////////
inline unsigned int factorial( const unsigned int x )
{
    if ( x < 2u ) { return 1u; }
    
    unsigned int tmp{1u};

    for ( unsigned int i{2u}; i <= x; i++ )
    {
        tmp *= i;
    }

    return tmp;
}


inline int factorial( const int x )
{
    if( x < 0 ) { return 0; }

    return static_cast< int >( factorial( static_cast< unsigned int >( x ) ) );
}


template< typename T >
inline T SQ( const T x )
{
    return ( x * x );
}


template< typename T >
inline T Sign( const T x )
{
    if ( x == static_cast< T >( 0.0 ) )
    {
        return static_cast< T >( 0.0 );
    }

    return ( x < static_cast< T >( 0.0 ) ? ( static_cast< T >( -1.0 ) ) : ( static_cast< T >( 1.0 ) ) );
}


template< typename T >
inline T wrapZeroToTwoPi( const T ang )
{
    T result = fmod( ang, static_cast< T >( 2.0 * Constants::PI ) );

    if ( result < static_cast< T >( 0.0 ) )
    {
        result += static_cast< T >( 2.0 * Constants::PI );
    }

    return result;
}


template< typename T >
inline T wrapMinusPiToPi( const T ang )
{
    T result = fmod( ang, static_cast< T >( 2.0 * Constants::PI ) );

    // Wrap to [-pi, pi)
    if ( result < static_cast< T >( -1.0 * Constants::PI ) )
    {
        result += static_cast< T >( 2.0 * Constants::PI );
    }
    else if ( result >= static_cast< T >( Constants::PI ) )
    {
        result -= static_cast< T >( 2.0 * Constants::PI );
    }

    return result;
}


template< typename T >
inline bool isZero( const T x )
{
    return ( x == static_cast< T >( 0 ) );
}


} // namespace myMath


#endif // MYMATH_BASIC_FUNCTIONS_H
