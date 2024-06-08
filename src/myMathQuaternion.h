#ifndef MYMATH_QUATERNION_H
#define MYMATH_QUATERNION_H

#include "myMathBasicFunctions.h"
#include "myMathRotation.h"
#include "myMathVector.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    template < typename T >
    class DCM;

    template < typename T >
    class Angle;

    template < typename T >
    class Quaternion : public Vector< T, 4u >
    {
      public:
        Quaternion();
        Quaternion( const T& w, const T& x, const T& y, const T& z );
        Quaternion( const T ( &q )[4] );
        Quaternion( const Quaternion< T >& q );
        Quaternion( const Vector< T, 4u >& q );
        Quaternion( const T& w, const Vector< T, 3u >& v );
        Quaternion( const T ang, const Axis ax );

        ~Quaternion() = default;

        using Vector< T, 4u >::operator=;
        using Vector< T, 4u >::operator[];
        using Vector< T, 4u >::operator+;
        using Vector< T, 4u >::operator+=;
        using Vector< T, 4u >::operator-;
        using Vector< T, 4u >::operator-=;
        using Vector< T, 4u >::operator/;
        using Vector< T, 4u >::operator/=;

        using Vector< T, 4u >::operator==;
        using Vector< T, 4u >::operator!=;

        Quaternion< T > operator*( const Quaternion< T >& q ) const;
        Quaternion< T > operator*( const T scalar ) const;

        Quaternion< T >& operator*=( const Quaternion< T >& q );
        Quaternion< T >& operator*=( const T scalar );

        static Quaternion< T > Identity( void );

        T& w( void );
        T& x( void );
        T& y( void );
        T& z( void );

        const T& w( void ) const;
        const T& x( void ) const;
        const T& y( void ) const;
        const T& z( void ) const;

        Quaternion< T > Conjugate( void ) const;
        Quaternion< T > Inverse( void ) const;
        DCM< T > ToDCM( void ) const;
        Angle< T > ToAngle( const TaitBryanOrder& rotOrder ) const;
        Angle< T > ToAngle( const EulerOrder& rotOrder ) const;

        Vector< T, 3u > Rotate( const Vector< T, 3u >& vec, const RotType& rotType = RotType::PASSIVE ) const;

        Quaternion< T > Deriv( const Vector< T, 3u >& w ) const;
    };
} // namespace myMath

#include "myMathAngle.h"
#include "myMathDCM.h"
#include "myMathMatrix.h"

namespace myMath
{
    typedef Quaternion< double > QuaternionD;
    typedef Quaternion< float >  QuaternionF;

    template < typename T >
    inline Quaternion< T >::Quaternion() : Vector< T, 4u >()
    {
        this->vec[0] = static_cast< T >( 1 );
    }

    template < typename T >
    inline Quaternion< T >::Quaternion( const T& w, const T& x, const T& y, const T& z ) : Vector< T, 4u >( {w, x, y, z} )
    {
    }

    template < typename T >
    inline Quaternion< T >::Quaternion( const T ( &q )[4] ) : Vector< T, 4u >( q )
    {
    }

    template < typename T >
    inline Quaternion< T >::Quaternion( const Quaternion< T >& q ) : Vector< T, 4u >( static_cast < Vector< T, 4u >>( q ) )
    {
    }

    template < typename T >
    inline Quaternion< T >::Quaternion( const Vector< T, 4u >& q ) : Vector< T, 4u >( q )
    {
    }

    template < typename T >
    inline Quaternion< T >::Quaternion( const T& w, const Vector< T, 3u >& v ) : Vector< T, 4u >( {w, v[0], v[1], v[2]} )
    {
    }


    template < typename T >
    Quaternion< T >::Quaternion( const T ang, const Axis ax ) : Vector< T, 4u >()
    {
        switch ( ax )
        {
            case Axis::X:
                {
                    this->vec[0] = std::cos( ang / static_cast< T >( 2 ) );
                    this->vec[1] = std::sin( ang / static_cast< T >( 2 ) );
                    this->vec[2] = static_cast< T >( 0 );
                    this->vec[3] = static_cast< T >( 0 );

                    break;
                }
            case Axis::Y:
                {
                    this->vec[0] = std::cos( ang / static_cast< T >( 2 ) );
                    this->vec[1] = static_cast< T >( 0 );
                    this->vec[2] = std::sin( ang / static_cast< T >( 2 ) );
                    this->vec[3] = static_cast< T >( 0 );

                    break;
                }
            case Axis::Z:
                {
                    this->vec[0] = std::cos( ang / static_cast< T >( 2 ) );
                    this->vec[1] = static_cast< T >( 0 );
                    this->vec[2] = static_cast< T >( 0 );
                    this->vec[3] = std::sin( ang / static_cast< T >( 2 ) );

                    break;
                }
            default:
                {
                    throw std::invalid_argument( "Invalid Axis" );

                    break;
                }
        }
    }


    template < typename T >
    Quaternion< T > Quaternion< T >::operator*( const Quaternion< T >& q ) const
    {
        Quaternion< T > qat;

        qat[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        qat[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        qat[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        qat[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        return qat;
    }


    template < typename T >
    Quaternion< T > Quaternion< T >::operator*( const T scalar ) const
    {
        Quaternion< T > qat;

        qat[0] = this->vec[0] * scalar;
        qat[1] = this->vec[1] * scalar;
        qat[2] = this->vec[2] * scalar;
        qat[3] = this->vec[3] * scalar;

        return qat;
    }


    template < typename T >
    Quaternion< T >& Quaternion< T >::operator*=( const Quaternion< T >& q )
    {
        Quaternion< T > qat{*this};

        this->vec[0] = qat[0] * q[0] - qat[1] * q[1] - qat[2] * q[2] - qat[3] * q[3];
        this->vec[1] = qat[0] * q[1] + qat[1] * q[0] + qat[2] * q[3] - qat[3] * q[2];
        this->vec[2] = qat[0] * q[2] - qat[1] * q[3] + qat[2] * q[0] + qat[3] * q[1];
        this->vec[3] = qat[0] * q[3] + qat[1] * q[2] - qat[2] * q[1] + qat[3] * q[0];

        return *this;
    }


    template < typename T >
    Quaternion< T >& Quaternion< T >::operator*=( const T scalar )
    {
        this->vec[0] *= scalar;
        this->vec[1] *= scalar;
        this->vec[2] *= scalar;
        this->vec[3] *= scalar;

        return *this;
    }

    template < typename T >
    Quaternion< T > Quaternion< T >::Identity( void )
    {
        return Quaternion< T >( static_cast< T >( 1 ), static_cast< T >( 0 ), static_cast< T >( 0 ), static_cast< T >( 0 ) );
    }


    template < typename T >
    T& Quaternion< T >::w( void )
    {
        return this->vec[0];
    }


    template < typename T >
    T& Quaternion< T >::x( void )
    {
        return this->vec[1];
    }


    template < typename T >
    T& Quaternion< T >::y( void )
    {
        return this->vec[2];
    }


    template < typename T >
    T& Quaternion< T >::z( void )
    {
        return this->vec[3];
    }


    template < typename T >
    const T& Quaternion< T >::w( void ) const
    {
        return this->vec[0];
    }


    template < typename T >
    const T& Quaternion< T >::x( void ) const
    {
        return this->vec[1];
    }


    template < typename T >
    const T& Quaternion< T >::y( void ) const
    {
        return this->vec[2];
    }


    template < typename T >
    const T& Quaternion< T >::z( void ) const
    {
        return this->vec[3];
    }


    template < typename T >
    Quaternion< T > Quaternion< T >::Conjugate( void ) const
    {
        Quaternion< T > tmp;

        tmp[0] =  this->vec[0];
        tmp[1] = -this->vec[1];
        tmp[2] = -this->vec[2];
        tmp[3] = -this->vec[3];

        return tmp;
    }


    template < typename T >
    Quaternion< T > Quaternion< T >::Inverse( void ) const
    {
        Quaternion< T > tmp = this->Conjugate();

        const T mag = this->Magnitude();

        if ( !isZero( mag ) )
        {
            tmp /= SQ( mag );
        }

        return tmp;
    }


    template < typename T >
    DCM< T > Quaternion< T >::ToDCM( void ) const
    {

        DCM< T > dcm;

        Quaternion< T > quatNormalize( this->vec );
        
        if ( !isZero( quatNormalize.Magnitude() - static_cast< T >( 1 ) ) )
        {
            quatNormalize.Normalize();
        }

        const T q0_sq = SQ( quatNormalize[0] );
        const T q1_sq = SQ( quatNormalize[1] );
        const T q2_sq = SQ( quatNormalize[2] );
        const T q3_sq = SQ( quatNormalize[3] );

        dcm[0][0] = q0_sq + q1_sq - q2_sq - q3_sq;
        dcm[0][1] = static_cast< T >( 2 ) * ( quatNormalize[1] * quatNormalize[2] + quatNormalize[0] * quatNormalize[3] );
        dcm[0][2] = static_cast< T >( 2 ) * ( quatNormalize[1] * quatNormalize[3] - quatNormalize[0] * quatNormalize[2] );

        dcm[1][0] = static_cast< T >( 2 ) * ( quatNormalize[1] * quatNormalize[2] - quatNormalize[0] * quatNormalize[3] );
        dcm[1][1] = q0_sq - q1_sq + q2_sq - q3_sq;
        dcm[1][2] = static_cast< T >( 2 ) * ( quatNormalize[2] * quatNormalize[3] + quatNormalize[0] * quatNormalize[1] );

        dcm[2][0] = static_cast< T >( 2 ) * ( quatNormalize[1] * quatNormalize[3] + quatNormalize[0] * quatNormalize[2] );
        dcm[2][1] = static_cast< T >( 2 ) * ( quatNormalize[2] * quatNormalize[3] - quatNormalize[0] * quatNormalize[1] );
        dcm[2][2] = q0_sq - q1_sq - q2_sq + q3_sq;

        return dcm;
    }


    template < typename T >
    Angle< T > Quaternion< T >::ToAngle( const TaitBryanOrder& rotOrder ) const
    {
        return ToDCM().ToAngle( rotOrder );
    }


    template < typename T >
    Angle< T > Quaternion< T >::ToAngle( const EulerOrder& rotOrder ) const
    {
        return ToDCM().ToAngle( rotOrder );
    }


    template < typename T >
    Vector< T, 3u > Quaternion< T >::Rotate( const Vector< T, 3u >& vec, const RotType& rotType ) const
    {
        Vector< T, 3u > vec_rot;

        Quaternion< T > q_vec{static_cast< T >( 0.0 ), vec};

        Quaternion< T > q_rot;

        switch ( rotType )
        {
            case RotType::ACTIVE:
                {
                    q_rot = this->Inverse() * q_vec * ( *this );

                    break;
                }
            case RotType::PASSIVE:
                {
                    q_rot = ( *this ) * q_vec * this->Inverse();

                    break;
                }
            default:
                {
                    throw std::invalid_argument( "Invalid Rotation Type" );

                    break;
                }
        }

        vec_rot[0] = q_rot[1];
        vec_rot[1] = q_rot[2];
        vec_rot[2] = q_rot[3];

        return vec_rot;
    }


    template < typename T >
    Quaternion< T > Quaternion< T >::Deriv( const Vector< T, 3u >& w ) const
    {
        Quaternion< T > q_dot;

        q_dot[0] = static_cast< T >( 0.5 ) * ( -this->vec[1] * w[0] - this->vec[2] * w[1] - this->vec[3] * w[2] );
        q_dot[1] = static_cast< T >( 0.5 ) * (  this->vec[0] * w[0] - this->vec[3] * w[1] + this->vec[2] * w[2] );
        q_dot[2] = static_cast< T >( 0.5 ) * (  this->vec[3] * w[0] + this->vec[0] * w[1] - this->vec[1] * w[2] );
        q_dot[3] = static_cast< T >( 0.5 ) * ( -this->vec[2] * w[0] + this->vec[1] * w[1] + this->vec[0] * w[2] );

        return q_dot;
    }

} // namespace myMath

#endif // MYMATH_QUATERNION_H
