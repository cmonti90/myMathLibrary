#ifndef MYMATH_ANGLE_H
#define MYMATH_ANGLE_H

#include "myMathBasicFunctions.h"
#include "myMathRotation.h"
#include "myMathVector.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    template <typename T>
    class DCM;

    template <typename T>
    class Quaternion;

    template <typename T>
    class Angle : public Vector<T, 3u>
    {
      public:
        Angle();
        Angle( const T x );
        Angle( const T ( &x )[3u] );
        Angle( const Vector<T, 3u>& obj );
        Angle( const Angle<T>& obj );

        ~Angle() = default;

        using Vector<T, 3u>::operator=;
        using Vector<T, 3u>::operator+;
        using Vector<T, 3u>::operator-;
        
        using Vector<T, 3u>::operator+=;
        using Vector<T, 3u>::operator-=;

        using Vector<T, 3u>::operator==;
        using Vector<T, 3u>::operator!=;

        void Normalize();

        DCM<T> ToDCM( const TaitBryanOrder& rotOrder ) const;
        DCM<T> ToDCM( const EulerOrder& rotOrder ) const;

        Quaternion<T> ToQuaternion( const TaitBryanOrder& rotOrder ) const;
        Quaternion<T> ToQuaternion( const EulerOrder& rotOrder ) const;

        void wrapAnglesZeroToTwoPi( const Axis ax = Axis::ALL );
        void wrapAnglesMinusPiToPi( const Axis ax = Axis::ALL );
    };
} // namespace myMath

#include "myMathDCM.h"
#include "myMathQuaternion.h"

namespace myMath
{
    typedef Angle< double > AngleD;
    typedef Angle< float >  AngleF;


    template <typename T>
    inline Angle<T>::Angle() : Vector<T, 3u>( static_cast<T>( 0 ) )
    {
    }


    template <typename T>
    inline Angle<T>::Angle( const T x ) : Vector<T, 3u>( x )
    {
    }


    template <typename T>
    inline Angle<T>::Angle( const T ( &x )[3u] ) : Vector<T, 3u>( x )
    {
    }


    template <typename T>
    inline Angle<T>::Angle( const Vector<T, 3u>& obj ) : Vector<T, 3u>( obj )
    {
    }


    template <typename T>
    inline Angle<T>::Angle( const Angle<T>& ang ) : Vector<T, 3u>( static_cast<Vector<T, 3u>>( ang ) )
    {
    }
    

    template <typename T>
    void Angle<T>::Normalize()
    {
        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            this->vec[i] = fmod( this->vec[i], static_cast<T>( 2.0 * Constants::PI ) );
        }
    }


    template <typename T>
    DCM<T> Angle<T>::ToDCM( const TaitBryanOrder& rotOrder ) const
    {
        DCM<T> tmp;

        T c0 = std::cos( this->vec[0] );
        T c1 = std::cos( this->vec[1] );
        T c2 = std::cos( this->vec[2] );

        T s0 = std::sin( this->vec[0] );
        T s1 = std::sin( this->vec[1] );
        T s2 = std::sin( this->vec[2] );

        switch ( rotOrder )
        {
            case TaitBryanOrder::XYZ:
                {
                    tmp[0][0] = c1 * c2;
                    tmp[0][1] = c0 * s2 + c2 * s0 * s1;
                    tmp[0][2] = s0 * s2 - c0 * c2 * s1;

                    tmp[1][0] = -c1 * s2;
                    tmp[1][1] = c0 * c2 - s0 * s1 * s2;
                    tmp[1][2] = c2 * s0 + c0 * s1 * s2;

                    tmp[2][0] = s1;
                    tmp[2][1] = -c1 * s0;
                    tmp[2][2] = c0 * c1;

                    break;
                }
            case TaitBryanOrder::XZY:
                {
                    tmp[0][0] = c1 * c2;
                    tmp[0][1] = s0 * s2 + c0 * c2 * s1;
                    tmp[0][2] = c2 * s0 * s1 - c0 * s2;

                    tmp[1][0] = -s1;
                    tmp[1][1] = c0 * c1;
                    tmp[1][2] = s0 * c1;

                    tmp[2][0] = c1 * s2;
                    tmp[2][1] = c0 * s1 * s2 - s0 * c2;
                    tmp[2][2] = c0 * c2 + s0 * s1 * s2;

                    break;
                }
            case TaitBryanOrder::YXZ:
                {
                    tmp[0][0] = c0 * c2 + s0 * s1 * s2;
                    tmp[0][1] = c1 * s2;
                    tmp[0][2] = c0 * s1 * s2 - s0 * c2;

                    tmp[1][0] = c2 * s0 * s1 - c0 * s2;
                    tmp[1][1] = c1 * c2;
                    tmp[1][2] = s0 * s2 + c0 * c2 * s1;

                    tmp[2][0] = c1 * s0;
                    tmp[2][1] = -s1;
                    tmp[2][2] = c0 * c1;

                    break;
                }
            case TaitBryanOrder::YZX:
                {
                    tmp[0][0] = c0 * c1;
                    tmp[0][1] = s1;
                    tmp[0][2] = -s0 * c1;

                    tmp[1][0] = s0 * s2 - c0 * c2 * s1;
                    tmp[1][1] = c1 * c2;
                    tmp[1][2] = c0 * s2 + s0 * c2 * s1;

                    tmp[2][0] = s0 * c2 + c0 * s2 * s1;
                    tmp[2][1] = -c1 * s2;
                    tmp[2][2] = c0 * c2 - s0 * s2 * s1;

                    break;
                }
            case TaitBryanOrder::ZXY:
                {
                    tmp[0][0] = c0 * c2 - s0 * s1 * s2;
                    tmp[0][1] = c2 * s0 + c0 * s1 * s2;
                    tmp[0][2] = -c1 * s2;

                    tmp[1][0] = -c1 * s0;
                    tmp[1][1] = c0 * c1;
                    tmp[1][2] = s1;

                    tmp[2][0] = c0 * s2 + c2 * s0 * s1;
                    tmp[2][1] = s0 * s2 - c0 * c2 * s1;
                    tmp[2][2] = c1 * c2;

                    break;
                }
            case TaitBryanOrder::ZYX:
                {
                    tmp[0][0] = c0 * c1;
                    tmp[0][1] = c1 * s0;
                    tmp[0][2] = -s1;

                    tmp[1][0] = c0 * s1 * s2 - s0 * c2;
                    tmp[1][1] = c0 * c2 + s0 * s1 * s2;
                    tmp[1][2] = c1 * s2;

                    tmp[2][0] = s0 * s2 + c0 * s1 * c2;
                    tmp[2][1] = s0 * s1 * c2 - c0 * s2;
                    tmp[2][2] = c1 * c2;

                    break;
                }
            default:
                {
                    throw std::invalid_argument( "Invalid Tait-Bryan Order" );
                }
        }

        return tmp;
    }


    template <typename T>
    DCM<T> Angle<T>::ToDCM( const EulerOrder& rotOrder ) const
    {
        DCM<T> tmp;

        T c0 = std::cos( this->vec[0] );
        T c1 = std::cos( this->vec[1] );
        T c2 = std::cos( this->vec[2] );

        T s0 = std::sin( this->vec[0] );
        T s1 = std::sin( this->vec[1] );
        T s2 = std::sin( this->vec[2] );

        switch ( rotOrder )
        {
            case EulerOrder::XYX:
                {
                    tmp[0][0] = c1;
                    tmp[0][1] = s0 * s1;
                    tmp[0][2] = -c0 * s1;

                    tmp[1][0] = s1 * s2;
                    tmp[1][1] = c0 * c2 - s0 * c1 * s2;
                    tmp[1][2] = c2 * s0 + c0 * c1 * s2;

                    tmp[2][0] = s1 * c2;
                    tmp[2][1] = -c0 * s2 - s0 * c1 * c2;
                    tmp[2][2] = c0 * c1 * c2 - s0 * s2;

                    break;
                }
            case EulerOrder::XZX:
                {
                    tmp[0][0] = c1;
                    tmp[0][1] = c0 * s1;
                    tmp[0][2] = s0 * s1;

                    tmp[1][0] = -s1 * c2;
                    tmp[1][1] = c0 * c1 * c2 - s0 * s2;
                    tmp[1][2] = c0 * s2 + s0 * c1 * c2;

                    tmp[2][0] = s1 * s2;
                    tmp[2][1] = -s0 * c2 - c0 * c1 * s2;
                    tmp[2][2] = c0 * c2 - s0 * c1 * s2;

                    break;
                }
            case EulerOrder::YXY:
                {
                    tmp[0][0] = c0 * c2 - s0 * c1 * s2;
                    tmp[0][1] = s1 * s2;
                    tmp[0][2] = -s0 * c2 - c0 * c1 * s2;

                    tmp[1][0] = s0 * s1;
                    tmp[1][1] = c1;
                    tmp[1][2] = c0 * s1;

                    tmp[2][0] = c0 * s2 + s0 * c1 * c2;
                    tmp[2][1] = -s1 * c2;
                    tmp[2][2] = c0 * c1 * c2 - s0 * s2;

                    break;
                }
            case EulerOrder::YZY:
                {
                    tmp[0][0] = c0 * c1 * c2 - s0 * s2;
                    tmp[0][1] = c2 * s1;
                    tmp[0][2] = -c0 * s2 - c1 * c2 * s0;

                    tmp[1][0] = -c0 * s1;
                    tmp[1][1] = c1;
                    tmp[1][2] = s0 * s1;

                    tmp[2][0] = c2 * s0 + c0 * c1 * s2;
                    tmp[2][1] = s1 * s2;
                    tmp[2][2] = c0 * c2 - c1 * s0 * s2;

                    break;
                }
            case EulerOrder::ZXZ:
                {
                    tmp[0][0] = c0 * c2 - c1 * s0 * s2;
                    tmp[0][1] = c2 * s0 + c0 * c1 * s2;
                    tmp[0][2] = s1 * s2;

                    tmp[1][0] = -c0 * s2 - c1 * c2 * s0;
                    tmp[1][1] = c0 * c1 * c2 - s0 * s2;
                    tmp[1][2] = c2 * s1;

                    tmp[2][0] = s0 * s1;
                    tmp[2][1] = -c0 * s1;
                    tmp[2][2] = c1;

                    break;
                }
            case EulerOrder::ZYZ:
                {
                    tmp[0][0] = c0 * c1 * c2 - s0 * s2;
                    tmp[0][1] = c0 * s2 + c1 * c2 * s0;
                    tmp[0][2] = -c2 * s1;

                    tmp[1][0] = -c2 * s0 - c0 * c1 * s2;
                    tmp[1][1] = c0 * c2 - c1 * s0 * s2;
                    tmp[1][2] = s1 * s2;

                    tmp[2][0] = c0 * s1;
                    tmp[2][1] = s0 * s1;
                    tmp[2][2] = c1;

                    break;
                }
            default:
                {
                    throw std::invalid_argument( "Invalid Euler Order" );
                }
        }

        return tmp;
    }


    template <typename T>
    Quaternion<T> Angle<T>::ToQuaternion( const TaitBryanOrder& rotOrder ) const
    {
        Quaternion<T> qat;

        Quaternion<T> qx;
        Quaternion<T> qy;
        Quaternion<T> qz;

        switch ( rotOrder )
        {
            case TaitBryanOrder::XYZ:
                {
                    qx = Quaternion<T>( this->vec[0], Axis::X );
                    qy = Quaternion<T>( this->vec[1], Axis::Y );
                    qz = Quaternion<T>( this->vec[2], Axis::Z );

                    qat = qx * qy * qz;

                    break;
                }
            case TaitBryanOrder::XZY:
                {
                    qx = Quaternion<T>( this->vec[0], Axis::X );
                    qz = Quaternion<T>( this->vec[1], Axis::Z );
                    qy = Quaternion<T>( this->vec[2], Axis::Y );

                    qat = qx * qz * qy;

                    break;
                }
            case TaitBryanOrder::YXZ:
                {
                    qy = Quaternion<T>( this->vec[0], Axis::Y );
                    qx = Quaternion<T>( this->vec[1], Axis::X );
                    qz = Quaternion<T>( this->vec[2], Axis::Z );

                    qat = qy * qx * qz;

                    break;
                }
            case TaitBryanOrder::YZX:
                {
                    qy = Quaternion<T>( this->vec[0], Axis::Y );
                    qz = Quaternion<T>( this->vec[1], Axis::Z );
                    qx = Quaternion<T>( this->vec[2], Axis::X );

                    qat = qy * qz * qx;

                    break;
                }
            case TaitBryanOrder::ZXY:
                {
                    qz = Quaternion<T>( this->vec[0], Axis::Z );
                    qx = Quaternion<T>( this->vec[1], Axis::X );
                    qy = Quaternion<T>( this->vec[2], Axis::Y );

                    qat = qz * qx * qy;

                    break;
                }
            case TaitBryanOrder::ZYX:
                {
                    qz = Quaternion<T>( this->vec[0], Axis::Z );
                    qy = Quaternion<T>( this->vec[1], Axis::Y );
                    qx = Quaternion<T>( this->vec[2], Axis::X );

                    qat = qz * qy * qx;

                    break;
                }
            default:
                {
                    throw std::invalid_argument( "Invalid Tait-Bryan Order" );
                }
        }

        qat.Normalize();

        return qat;
    }


    template <typename T>
    Quaternion<T> Angle<T>::ToQuaternion( const EulerOrder& rotOrder ) const
    {
        Quaternion<T> q1;
        Quaternion<T> q2;
        Quaternion<T> q3;

        switch ( rotOrder )
        {
            case EulerOrder::XYX:
                {
                    q1 = Quaternion<T>( this->vec[0], Axis::X );
                    q2 = Quaternion<T>( this->vec[1], Axis::Y );
                    q3 = Quaternion<T>( this->vec[2], Axis::X );

                    break;
                }
            case EulerOrder::XZX:
                {
                    q1 = Quaternion<T>( this->vec[0], Axis::X );
                    q2 = Quaternion<T>( this->vec[1], Axis::Z );
                    q3 = Quaternion<T>( this->vec[2], Axis::X );

                    break;
                }
            case EulerOrder::YXY:
                {
                    q1 = Quaternion<T>( this->vec[0], Axis::Y );
                    q2 = Quaternion<T>( this->vec[1], Axis::X );
                    q3 = Quaternion<T>( this->vec[2], Axis::Y );

                    break;
                }
            case EulerOrder::YZY:
                {
                    q1 = Quaternion<T>( this->vec[0], Axis::Y );
                    q2 = Quaternion<T>( this->vec[1], Axis::Z );
                    q3 = Quaternion<T>( this->vec[2], Axis::Y );

                    break;
                }
            case EulerOrder::ZXZ:
                {
                    q1 = Quaternion<T>( this->vec[0], Axis::Z );
                    q2 = Quaternion<T>( this->vec[1], Axis::X );
                    q3 = Quaternion<T>( this->vec[2], Axis::Z );

                    break;
                }
            case EulerOrder::ZYZ:
                {
                    q1 = Quaternion<T>( this->vec[0], Axis::Z );
                    q2 = Quaternion<T>( this->vec[1], Axis::Y );
                    q3 = Quaternion<T>( this->vec[2], Axis::Z );

                    break;
                }
            default:
                {
                    throw std::invalid_argument( "Invalid Euler Order" );
                }
        }

        return ( q1 * q2 * q3 );
    }


    template <typename T>
    void Angle<T>::wrapAnglesZeroToTwoPi( const Axis ax )
    {
        if ( ax == Axis::ALL )
        {
            wrapAnglesZeroToTwoPi( Axis::X );
            wrapAnglesZeroToTwoPi( Axis::Y );
            wrapAnglesZeroToTwoPi( Axis::Z );
        }
        else
        {
            if ( ax > Axis::Z )
            {
                throw std::invalid_argument( "Invalid Axis" );
            }

            this->vec[ax] = wrapZeroToTwoPi( this->vec[ax] );
        }
    }

    template <typename T>
    void Angle<T>::wrapAnglesMinusPiToPi( const Axis ax )
    {
        if ( ax == Axis::ALL )
        {
            wrapAnglesMinusPiToPi( Axis::X );
            wrapAnglesMinusPiToPi( Axis::Y );
            wrapAnglesMinusPiToPi( Axis::Z );
        }
        else
        {
            if ( ax > Axis::Z )
            {
                throw std::invalid_argument( "Invalid Axis" );
            }

            this->vec[ax] = wrapMinusPiToPi( this->vec[ax] );
        }
    }

} // namespace myMath

#endif // MYMATH_ANGLE_H
