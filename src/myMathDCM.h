#ifndef MYMATH_DCM_H
#define MYMATH_DCM_H

#include "myMathBasicFunctions.h"
#include "myMathRotation.h"
#include "myMathMatrix.h"

#include <cmath>
#include <stdexcept>


namespace myMath
{
template< typename T >
class Angle;

template< typename T >
class Quaternion;

template< typename T >
class DCM : public Matrix< T, 3u, 3u >
{
public:
    DCM();
    DCM( const Matrix< T, 3u, 3u >& m );
    DCM( const DCM< T >& dcm ) = default;
    DCM( const std::initializer_list< T >& list );
    DCM( const T ( &m )[3][3] );
    DCM( const T ( &m )[9] );

    using Matrix< T, 3, 3 >::operator=;

    using Matrix< T, 3, 3 >::operator+;
    using Matrix< T, 3, 3 >::operator-;
    using Matrix< T, 3, 3 >::operator*;
    using Matrix< T, 3, 3 >::operator/;

    using Matrix< T, 3, 3 >::operator+=;
    using Matrix< T, 3, 3 >::operator-=;
    using Matrix< T, 3, 3 >::operator/=;

    using Matrix< T, 3, 3 >::operator==;
    using Matrix< T, 3, 3 >::operator!=;

    DCM< T > operator*( const DCM< T >& dcm ) const;
    DCM< T > operator*( const Matrix< T, 3, 3 >& m ) const;

    DCM< T > operator*( const T& x ) const = delete;
    DCM< T >& operator*=( const T& x ) const = delete;
    DCM< T > operator/( const T& x ) const = delete;
    DCM< T >& operator/=( const T& x ) const = delete;

    template< unsigned int C >
    Matrix< T, 3, C > operator*( const Matrix< T, 3, C >& m ) const;

    Vector< T, 3u > operator*( const Vector< T, 3u >& v ) const;

    DCM< T >& operator*=( const DCM< T >& dcm );
    DCM< T >& operator*=( const Matrix< T, 3u, 3u >& m );

    static DCM< T > Identity( void );

    DCM< T > Transpose() const;
    void Normalize();
    Quaternion< T > ToQuaternion() const;
    Angle< T > ToAngle( const TaitBryanOrder& rotOrder ) const;
    Angle< T > ToAngle( const EulerOrder& rotOrder ) const;
};
} // namespace myMath

#include "myMathAngle.h"
#include "myMathQuaternion.h"

namespace myMath
{

typedef DCM< float  > DCMf;
typedef DCM< double > DCMd;

template< typename T >
inline DCM< T >::DCM() : Matrix< T, 3u, 3u >( Matrix< T, 3u, 3u >::Identity() )
{
}


template< typename T >
inline DCM< T >::DCM( const Matrix< T, 3u, 3u >& m ) : Matrix< T, 3u, 3u >( m )
{
}


template< typename T >
inline DCM< T >::DCM( const std::initializer_list< T >& list ) : Matrix< T, 3u, 3u >( list )
{
}


template< typename T >
inline DCM< T >::DCM( const T ( &m )[3][3] ) : Matrix< T, 3u, 3u >( m )
{
}


template< typename T >
inline DCM< T >::DCM( const T ( &m )[9] ) : Matrix< T, 3u, 3u >()
{
    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < 3u; j++ )
        {
            this->mat[i][j] = m[i * 3u + j];
        }
    }
}


template< typename T >
DCM< T > DCM< T >::operator*( const DCM< T >& dcm ) const
{
    DCM< T > tmp;

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < 3u; j++ )
        {
            T tmp_sum = static_cast< T >( 0 );

            for ( unsigned int k{0u}; k < 3u; k++ )
            {
                tmp_sum += this->mat[i][k] * dcm[k][j];
            }

            tmp[i][j] = tmp_sum;
        }
    }

    return tmp;
}


template< typename T >
DCM< T > DCM< T >::operator*( const Matrix< T, 3u, 3u >& m ) const
{
    DCM< T > tmp;

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < 3u; j++ )
        {
            T tmp_sum = static_cast< T >( 0 );

            for ( unsigned int k{0u}; k < 3u; k++ )
            {
                tmp_sum += this->mat[i][k] * m[k][j];
            }

            tmp[i][j] = tmp_sum;
        }
    }

    return tmp;
}

template< typename T >
template<unsigned int C>
Matrix<T, 3, C> DCM< T >::operator*( const Matrix<T, 3, C>& m ) const
{
    Matrix<T, 3u, C> tmp;

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < C; j++ )
        {
            T tmp_sum = static_cast< T >( 0 );

            for ( unsigned int k{0u}; k < 3u; k++ )
            {
                tmp_sum += this->mat[i][k] * m[k][j];
            }

            tmp[i][j] = tmp_sum;
        }
    }

    return tmp;
}

template< typename T >
Vector<T, 3u> DCM< T >::operator*( const Vector<T, 3u>& v ) const
{
    Vector<T, 3u> tmp{0.0};

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < 3u; j++ )
        {
            tmp.vec[i] += this->mat[i][j] * v[j];
        }
    }

    return tmp;
}


template< typename T >
DCM< T >& DCM< T >::operator*=( const DCM< T >& dcm )
{
    Matrix< T, 3u, 3u >::operator*=( dcm );
    return *this;
}


template< typename T >
DCM< T >& DCM< T >::operator*=( const Matrix< T, 3u, 3u >& m )
{
    Matrix< T, 3u, 3u >::operator*=( m );
    return *this;
}


template< class T >
DCM< T > operator*( const T& x, const DCM< T >& obj )
{
    return obj * x;
}

template< class T, unsigned int C >
Matrix< T, 3u, C > operator*=( const DCM< T >& lhs, const Matrix< T, 3u, C >& rhs )
{
    Matrix< T, 3u, C > tmp;

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < C; j++ )
        {
            T tmp_sum = static_cast< T >( 0 );

            for ( unsigned int k{0u}; k < 3u; k++ )
            {
                tmp_sum += lhs[i][k] * rhs[k][j];
            }

            tmp[i][j] = tmp_sum;
        }
    }

    return tmp;
}


template< typename T >
DCM< T > DCM< T >::Transpose() const
{
    DCM< T > tmp;

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        for ( unsigned int j{0u}; j < 3u; j++ )
        {
            tmp[i][j] = this->mat[j][i];
        }
    }

    return tmp;
}


template< typename T >
void DCM< T >::Normalize()
{
    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        this->mat[i].Normalize();
    }
}


template< typename T >
Quaternion< T > DCM< T >::ToQuaternion() const
{
    Quaternion< T > q;

    T q0_mag = std::sqrt( ( static_cast< T >( 1 ) + this->mat[0][0] + this->mat[1][1] + this->mat[2][2] ) ) / static_cast< T >( 2 );
    T q1_mag = std::sqrt( ( static_cast< T >( 1 ) + this->mat[0][0] - this->mat[1][1] - this->mat[2][2] ) ) / static_cast< T >( 2 );
    T q2_mag = std::sqrt( ( static_cast< T >( 1 ) - this->mat[0][0] + this->mat[1][1] - this->mat[2][2] ) ) / static_cast< T >( 2 );
    T q3_mag = std::sqrt( ( static_cast< T >( 1 ) - this->mat[0][0] - this->mat[1][1] + this->mat[2][2] ) ) / static_cast< T >( 2 );

    T q_max = std::max( q0_mag, std::max( q1_mag, std::max( q2_mag, q3_mag ) ) );

    if ( q_max == q0_mag )
    {
        q[0] = q0_mag;
        q[1] = ( this->mat[1][2] - this->mat[2][1] ) / ( static_cast< T >( 4 ) * q0_mag );
        q[2] = ( this->mat[2][0] - this->mat[0][2] ) / ( static_cast< T >( 4 ) * q0_mag );
        q[3] = ( this->mat[0][1] - this->mat[1][0] ) / ( static_cast< T >( 4 ) * q0_mag );
    }
    else if ( q_max == q1_mag )
    {
        q[0] = ( this->mat[1][2] - this->mat[2][1] ) / ( static_cast< T >( 4 ) * q1_mag );
        q[1] = q1_mag;
        q[2] = ( this->mat[0][1] + this->mat[1][0] ) / ( static_cast< T >( 4 ) * q1_mag );
        q[3] = ( this->mat[2][0] + this->mat[0][2] ) / ( static_cast< T >( 4 ) * q1_mag );
    }
    else if ( q_max == q2_mag )
    {
        q[0] = ( this->mat[2][0] - this->mat[0][2] ) / ( static_cast< T >( 4 ) * q2_mag );
        q[1] = ( this->mat[0][1] + this->mat[1][0] ) / ( static_cast< T >( 4 ) * q2_mag );
        q[2] = q2_mag;
        q[3] = ( this->mat[1][2] + this->mat[2][1] ) / ( static_cast< T >( 4 ) * q2_mag );
    }
    else
    {
        q[0] = ( this->mat[0][1] - this->mat[1][0] ) / ( static_cast< T >( 4 ) * q3_mag );
        q[1] = ( this->mat[2][0] + this->mat[0][2] ) / ( static_cast< T >( 4 ) * q3_mag );
        q[2] = ( this->mat[1][2] + this->mat[2][1] ) / ( static_cast< T >( 4 ) * q3_mag );
        q[3] = q3_mag;
    }

    return q;
}


template< typename T >
Angle< T > DCM< T >::ToAngle( const TaitBryanOrder& rotOrder ) const
{
    Angle< T > euler1;
    Angle< T > euler2;
    Angle< T > euler;

    switch ( rotOrder )
    {
        case TaitBryanOrder::XYZ:
        {
            euler1[1] = std::asin( this->mat[2][0] );

            if ( isZero( std::abs( euler1[1] ) - Constants::PI / 2.0 ) )
            {
                euler1[0] = std::atan2( this->mat[0][1], this->mat[1][1] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = Constants::PI - euler1[1];

                T cos_euler1_1 = std::cos( euler1[1] );
                T cos_euler2_1 = std::cos( euler2[1] );

                euler1[0] = std::atan2( -this->mat[2][1] / cos_euler1_1, this->mat[2][2] / cos_euler1_1 );
                euler1[2] = std::atan2( -this->mat[1][0] / cos_euler1_1, this->mat[0][0] / cos_euler1_1 );

                euler2[0] = std::atan2( -this->mat[2][1] / cos_euler2_1, this->mat[2][2] / cos_euler2_1 );
                euler2[2] = std::atan2( -this->mat[1][0] / cos_euler2_1, this->mat[0][0] / cos_euler2_1 );
            }

            break;
        }
        case TaitBryanOrder::XZY:
        {
            euler1[1] = std::asin( -this->mat[1][0] );

            if ( isZero( std::abs( euler1[1] ) - Constants::PI / 2.0 ) )
            {
                euler1[0] = std::atan2( this->mat[0][2], this->mat[2][2] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = Constants::PI - euler1[1];

                T cos_euler1_1 = std::cos( euler1[1] );
                T cos_euler2_1 = std::cos( euler2[1] );

                euler1[0] = std::atan2( this->mat[1][2] / cos_euler1_1, this->mat[1][1] / cos_euler1_1 );
                euler1[2] = std::atan2( this->mat[2][0] / cos_euler1_1, this->mat[0][0] / cos_euler1_1 );

                euler2[0] = std::atan2( this->mat[1][2] / cos_euler2_1, this->mat[1][1] / cos_euler2_1 );
                euler2[2] = std::atan2( this->mat[2][0] / cos_euler2_1, this->mat[0][0] / cos_euler2_1 );
            }

            break;
        }
        case TaitBryanOrder::YXZ:
        {
            euler1[1] = std::asin( -this->mat[2][1] );

            if ( isZero( std::abs( euler1[1] ) - Constants::PI / 2.0 ) )
            {
                euler1[0] = std::atan2( this->mat[1][0], this->mat[0][0] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = Constants::PI - euler1[1];

                T cos_euler1_1 = std::cos( euler1[1] );
                T cos_euler2_1 = std::cos( euler2[1] );

                euler1[0] = std::atan2( this->mat[2][0] / cos_euler1_1, this->mat[2][2] / cos_euler1_1 );
                euler1[2] = std::atan2( this->mat[0][1] / cos_euler1_1, this->mat[1][1] / cos_euler1_1 );

                euler2[0] = std::atan2( this->mat[2][0] / cos_euler2_1, this->mat[2][2] / cos_euler2_1 );
                euler2[2] = std::atan2( this->mat[0][1] / cos_euler2_1, this->mat[1][1] / cos_euler2_1 );
            }

            break;
        }
        case TaitBryanOrder::YZX:
        {
            euler1[1] = std::asin( this->mat[0][1] );

            if ( isZero( std::abs( euler1[1] ) - Constants::PI / 2.0 ) )
            {
                euler1[0] = std::atan2( this->mat[1][2], this->mat[2][2] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = Constants::PI - euler1[1];

                T cos_euler1_1 = std::cos( euler1[1] );
                T cos_euler2_1 = std::cos( euler2[1] );

                euler1[0] = std::atan2( -this->mat[0][2] / cos_euler1_1, this->mat[0][0] / cos_euler1_1 );
                euler1[2] = std::atan2( -this->mat[2][1] / cos_euler1_1, this->mat[1][1] / cos_euler1_1 );

                euler2[0] = std::atan2( -this->mat[0][2] / cos_euler2_1, this->mat[0][0] / cos_euler2_1 );
                euler2[2] = std::atan2( -this->mat[2][1] / cos_euler2_1, this->mat[1][1] / cos_euler2_1 );
            }

            break;
        }
        case TaitBryanOrder::ZXY:
        {
            euler1[1] = std::asin( this->mat[1][2] );

            if ( isZero( std::abs( euler1[1] ) - Constants::PI / 2.0 ) )
            {
                euler1[0] = std::atan2( this->mat[0][1], this->mat[0][0] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = Constants::PI - euler1[1];

                T cos_euler1_1 = std::cos( euler1[1] );
                T cos_euler2_1 = std::cos( euler2[1] );

                euler1[0] = std::atan2( -this->mat[1][0] / cos_euler1_1, this->mat[1][1] / cos_euler1_1 );
                euler1[2] = std::atan2( -this->mat[0][2] / cos_euler1_1, this->mat[2][2] / cos_euler1_1 );

                euler2[0] = std::atan2( -this->mat[1][0] / cos_euler2_1, this->mat[1][1] / cos_euler2_1 );
                euler2[2] = std::atan2( -this->mat[0][2] / cos_euler2_1, this->mat[2][2] / cos_euler2_1 );
            }

            break;
        }
        case TaitBryanOrder::ZYX:
        {
            euler1[1] = std::asin( -this->mat[0][2] );

            if ( isZero( std::abs( euler1[1] ) - Constants::PI / 2.0 ) )
            {
                euler1[0] = std::atan2( this->mat[2][1], this->mat[1][1] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = Constants::PI - euler1[1];

                T cos_euler1_1 = std::cos( euler1[1] );
                T cos_euler2_1 = std::cos( euler2[1] );

                euler1[0] = std::atan2( this->mat[0][1] / cos_euler1_1, this->mat[0][0] / cos_euler1_1 );
                euler1[2] = std::atan2( this->mat[1][2] / cos_euler1_1, this->mat[2][2] / cos_euler1_1 );

                euler2[0] = std::atan2( this->mat[0][1] / cos_euler2_1, this->mat[0][0] / cos_euler2_1 );
                euler2[2] = std::atan2( this->mat[1][2] / cos_euler2_1, this->mat[2][2] / cos_euler2_1 );
            }

            break;
        }
        default:
        {
            throw std::invalid_argument( "Invalid Tait-Bryan Order" );
            break;
        }
    }

    return euler1;

    euler = euler1.Magnitude() < euler2.Magnitude() ? euler1 : euler2;

    #ifdef DEBUG
    DCM< T > check = euler.ToDCM( rotOrder );

    if ( *this != check )
    {
        std::cout << "WARNING! Conversion to Tait-Bryan sequence: " << static_cast<unsigned int>( rotOrder ) << " is not possible!" << std::endl;
    }
    #endif

    return euler;
}


template< typename T >
Angle< T > DCM< T >::ToAngle( const EulerOrder& rotOrder ) const
{
    Angle< T > euler1;
    Angle< T > euler2;
    Angle< T > euler;

    switch ( rotOrder )
    {
        case EulerOrder::XYX:
        {
            euler1[1] = std::acos( this->mat[0][0] );

            if ( isZero( euler1[1] ) )
            {
                euler1[0] = std::atan2( this->mat[1][2], this->mat[1][1] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = -euler1[1];

                T sin_euler1_1 = std::sin( euler1[1] );
                T sin_euler2_1 = std::sin( euler2[1] );

                euler1[0] = std::atan2( this->mat[0][1] / sin_euler1_1, -this->mat[0][2] / sin_euler1_1 );
                euler1[2] = std::atan2( this->mat[1][0] / sin_euler1_1, this->mat[2][0] / sin_euler1_1 );

                euler2[0] = std::atan2( this->mat[0][1] / sin_euler2_1, -this->mat[0][2] / sin_euler2_1 );
                euler2[2] = std::atan2( this->mat[1][0] / sin_euler2_1, this->mat[2][0] / sin_euler2_1 );
            }

            break;
        }
        case EulerOrder::XZX:
        {
            euler1[1] = std::acos( this->mat[0][0] );

            if ( isZero( euler1[1] ) )
            {
                euler1[0] = std::atan2( this->mat[1][2], this->mat[1][1] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = -euler1[1];

                T sin_euler1_1 = std::sin( euler1[1] );
                T sin_euler2_1 = std::sin( euler2[1] );

                euler1[0] = std::atan2( this->mat[0][2] / sin_euler1_1, this->mat[0][1] / sin_euler1_1 );
                euler1[2] = std::atan2( this->mat[2][0] / sin_euler1_1, -this->mat[1][0]  / sin_euler1_1 );

                euler2[0] = std::atan2( this->mat[0][2] / sin_euler2_1, this->mat[0][1] / sin_euler2_1 );
                euler2[2] = std::atan2( this->mat[2][0] / sin_euler2_1, -this->mat[1][0]  / sin_euler2_1 );
            }

            break;
        }
        case EulerOrder::YXY:
        {
            euler1[1] = std::acos( this->mat[1][1] );

            if ( isZero( euler1[1] ) )
            {
                euler1[0] = std::atan2( this->mat[2][0], this->mat[2][2] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = -euler1[1];

                T sin_euler1_1 = std::sin( euler1[1] );
                T sin_euler2_1 = std::sin( euler2[1] );

                euler1[0] = std::atan2( this->mat[1][0] / sin_euler1_1, this->mat[1][2] / sin_euler1_1 );
                euler1[2] = std::atan2( this->mat[0][1] / sin_euler1_1, -this->mat[2][1] / sin_euler1_1 );

                euler2[0] = std::atan2( this->mat[1][0] / sin_euler2_1, this->mat[1][2] / sin_euler2_1 );
                euler2[2] = std::atan2( this->mat[0][1] / sin_euler2_1, -this->mat[2][1] / sin_euler2_1 );
            }

            break;
        }
        case EulerOrder::YZY:
        {
            euler1[1] = std::acos( this->mat[1][1] );

            if ( isZero( euler1[1] ) )
            {
                euler1[0] = std::atan2( -this->mat[0][2], this->mat[0][0] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = -euler1[1];

                T sin_euler1_1 = std::sin( euler1[1] );
                T sin_euler2_1 = std::sin( euler2[1] );

                euler1[0] = std::atan2( this->mat[1][2] / sin_euler1_1, -this->mat[1][0] / sin_euler1_1 );
                euler1[2] = std::atan2( this->mat[2][1] / sin_euler1_1, this->mat[0][1] / sin_euler1_1 );

                euler2[0] = std::atan2( this->mat[1][2] / sin_euler2_1, -this->mat[1][0] / sin_euler2_1 );
                euler2[2] = std::atan2( this->mat[2][1] / sin_euler2_1, this->mat[0][1] / sin_euler2_1 );
            }

            break;
        }
        case EulerOrder::ZXZ:
        {
            euler1[1] = std::acos( this->mat[2][2] );

            if ( isZero( euler1[1] ) )
            {
                euler1[0] = std::atan2( this->mat[0][1], this->mat[0][0] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = -euler1[1];

                T sin_euler1_1 = std::sin( euler1[1] );
                T sin_euler2_1 = std::sin( euler2[1] );

                euler1[0] = std::atan2( this->mat[2][0] / sin_euler1_1, -this->mat[2][1] / sin_euler1_1 );
                euler1[2] = std::atan2( this->mat[0][2] / sin_euler1_1, this->mat[1][2] / sin_euler1_1 );

                euler2[0] = std::atan2( this->mat[2][0] / sin_euler2_1, -this->mat[2][1] / sin_euler2_1 );
                euler2[2] = std::atan2( this->mat[0][2] / sin_euler2_1, this->mat[1][2] / sin_euler2_1 );
            }

            break;
        }
        case EulerOrder::ZYZ:
        {
            euler1[1] = std::acos( this->mat[2][2] );

            if ( isZero( euler1[1] ) )
            {
                euler1[0] = std::atan2( this->mat[0][1], this->mat[0][0] );
                euler1[2] = static_cast< T >( 0 );

                euler2 = euler1;
            }
            else
            {
                euler2[1] = -euler1[1];

                T sin_euler1_1 = std::sin( euler1[1] );
                T sin_euler2_1 = std::sin( euler2[1] );

                euler1[0] = std::atan2( this->mat[2][1] / sin_euler1_1, this->mat[2][0] / sin_euler1_1 );
                euler1[2] = std::atan2( this->mat[1][2] / sin_euler1_1, -this->mat[0][2] / sin_euler1_1 );

                euler2[0] = std::atan2( this->mat[2][1] / sin_euler2_1, this->mat[2][0] / sin_euler2_1 );
                euler2[2] = std::atan2( this->mat[1][2] / sin_euler2_1, -this->mat[0][2] / sin_euler2_1 );
            }

            break;
        }
        default:
        {
            throw std::invalid_argument( "Invalid Euler Order" );
        }
    }

    return euler1;

    euler = euler1.Magnitude() < euler2.Magnitude() ? euler1 : euler2;

    #ifdef DEBUG

    DCM< T > check = euler.ToDCM( rotOrder );

    if ( *this != check )
    {
        std::cout << "WARNING! Conversion to Euler sequence: " << static_cast<unsigned int>( rotOrder ) << " is not possible!" << std::endl;
    }

    #endif

    return euler;
}


template< typename T >
DCM< T > DCM< T >::Identity( void )
{
    DCM< T > identityMat( static_cast< T >( 0 ) );

    for ( unsigned int i{0u}; i < 3u; i++ )
    {
        identityMat[i][i] = static_cast< T >( 1 );
    }

    return identityMat;
}

} // namespace myMath

#endif // MYMATH_DCM_H
