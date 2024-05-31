#ifndef MYMATH_MATRIX_FUNCTIONS_H
#define MYMATH_MATRIX_FUNCTIONS_H

#include "myMathBasicFunctions.h"
#include "myMathVector.h"
#include "myMathMatrix.h"
#include "myMathDCM.h"

namespace myMath
{
    /////////////////////////////////
    //         DECLARATIONS        //
    /////////////////////////////////
    template < class T, unsigned int R >
    T DotProduct( const Vector< T, R >& lhs, const Vector< T, R >& rhs );

    template < class T >
    Vector< T, 3u > CrossProduct( const Vector< T, 3u >& lhs, const Vector< T, 3u >& rhs );

    template < class T, unsigned int R >
    T Magnitude( const Vector< T, R >& obj );

    template < class T, unsigned int R, unsigned int C >
    Matrix< T, C, R > Transpose( const Matrix< T, R, C >& obj );

    template < class T >
    DCM< T > Transpose( const DCM< T >& obj );

    template < class T, unsigned int R, unsigned int C >
    Matrix< T, R, C > OuterProduct( const Vector< T, R >& lhs, const Vector< T, C >& rhs );

    template< class T, unsigned int R >
    Matrix< T, R, R > Identity( void );

    /////////////////////////////////
    //         DEFINITIONS         //
    /////////////////////////////////
    template < class T, unsigned int R >
    inline T Magnitude( const Vector< T, R >& obj )
    {
        T tmp = static_cast< T >( 0 );

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp += SQ( obj.vec[i]  );
        }

        return static_cast< T >( std::sqrt( tmp ) );
    }

    template < class T, unsigned int R >
    inline T DotProduct( const Vector< T, R >& lhs, const Vector< T, R >& rhs )
    {
        T prod{static_cast< T >( 0 )};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            prod += lhs.vec[i] * rhs.vec[i];
        }

        return prod;
    }

    template < class T >
    inline Vector< T, 3u > CrossProduct( const Vector< T, 3u >& lhs, const Vector< T, 3u >& rhs )
    {
            Vector< T, 3u > prod;

            prod[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
            prod[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
            prod[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

            return prod;
    }

    template < class T, unsigned int R, unsigned int C >
    inline Matrix<T, C, R> Transpose( const Matrix< T, R, C >& obj )
    {
        Matrix<T, C, R> tmp;

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp[j][i] = obj[i][j];
            }
        }

        return tmp;
    }

    template < class T >
    inline DCM< T > Transpose( const DCM< T >& obj )
    {
        DCM< T > tmp;

        for ( unsigned int i{0u}; i <3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                tmp[j][i] = obj[i][j];
            }
        }

        return tmp;
    }

    template < class T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C > OuterProduct( const Vector< T, R >& lhs, const Vector<T, C>& rhs )
    {
        Matrix< T, R, C > tmp{static_cast< T >( 0 )};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.mat[i][j] = lhs.vec[i] * rhs.vec[j];
            }
        }

        return tmp;
    }

    template< class T, unsigned int R >
    inline Matrix< T, R, R > Identity( void )
    {
        Matrix< T, R, R > tmp{static_cast< T >( 0 )};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp.mat[i][i] = static_cast< T >( 1 );
        }

        return tmp;
    }

} // namespace myMath

#endif // MYMATH_MATRIX_FUNCTIONS_H
