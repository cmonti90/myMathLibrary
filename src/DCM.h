#ifndef BA9453AD_D478_47EC_9001_44325F419B41
#define BA9453AD_D478_47EC_9001_44325F419B41

#include "BasicFunctions.h"
#include "Rotation.h"
#include "Matrix.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    template <typename T>
    class Angle;

    template <typename T>
    class Quaternion;

    template <typename T>
    class DCM : public Matrix<T, 3, 3>
    {
      public:
        DCM();
        DCM( const Matrix<T, 3, 3>& m );
        DCM( const T ( &m )[3][3] );
        DCM( const T ( &m )[9] );

        DCM<T>& operator=( const DCM<T>& dcm );
        DCM<T>& operator=( const Matrix<T, 3, 3>& m );
        DCM<T>& operator=( const T ( &m )[3][3] );
        DCM<T>& operator=( const T ( &m )[9] );

        DCM<T> operator*( const DCM<T>& dcm ) const;
        DCM<T> operator*( const Matrix<T, 3, 3>& m ) const;

        template <unsigned int C>
        Matrix<T, 3, C> operator*( const Matrix<T, 3, C>& m ) const;

        template <unsigned int C>
        DCM<T> operator*( const T ( &m )[3][C] ) const;
        Vector<T, 3u> operator*( const Vector<T, 3u>& v ) const;

        DCM<T>& operator*=( const DCM<T>& dcm );

        DCM<T>& operator*=( const Matrix<T, 3, 3>& m );
        DCM<T>& operator*=( const T ( &m )[3][3] );
        DCM<T>& operator*=( const T ( &m )[9] );

        DCM<T> operator-( void ) const;

        bool operator==( const DCM<T>& dcm ) const;
        bool operator!=( const DCM<T>& dcm ) const;

        static DCM<T> Identity( void )
        {
            DCM<T> identityMat( static_cast<T>( 0 ) );

            for ( unsigned int i{0u}; i < 3u; i++ )
            {
                identityMat[i][i] = static_cast<T>( 1 );
            }

            return identityMat;
        }

        DCM<T> Transpose() const;
        void Normalize();
        Quaternion<T> ToQuaternion() const;
        Angle<T> ToEuler( const TaitBryanOrder& rotOrder ) const;
        Angle<T> ToEuler( const EulerOrder& rotOrder ) const;

        Angle<T> Rotate( const Angle<T>& angle, const TaitBryanOrder& rotOrder, const TaitBryanOrder rotOrderOut ) const;
        Angle<T> Rotate( const Angle<T>& angle, const EulerOrder& rotOrder, const TaitBryanOrder rotOrderOut ) const;
        Angle<T> Rotate( const Angle<T>& angle, const EulerOrder& rotOrder, const EulerOrder rotOrderOut ) const;
        DCM<T> Rotate( const DCM<T>& dcm ) const;
        Quaternion<T> Rotate( const Quaternion<T>& q ) const;
        Vector<T, 3u> Rotate( const Vector<T, 3u>& v ) const;
    };
} // namespace myMath

#include "Angle.h"
#include "Quaternion.h"

namespace myMath
{

    typedef DCM<double> DCMd;
    typedef DCM<float> DCMf;

    template <typename T>
    DCM<T>::DCM() : Matrix<T, 3, 3>()
    {
    }

    template <typename T>
    DCM<T>::DCM( const Matrix<T, 3, 3>& m ) : Matrix<T, 3, 3>( m )
    {
    }

    template <typename T>
    DCM<T>::DCM( const T ( &m )[3][3] ) : Matrix<T, 3, 3>( m )
    {
    }

    template <typename T>
    DCM<T>::DCM( const T ( &m )[9] ) : Matrix<T, 3, 3>()
    {
        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                this->mat[i][j] = m[i * 3u + j];
            }
        }
    }

    template <typename T>
    DCM<T>& DCM<T>::operator=( const DCM<T>& dcm )
    {
        Matrix<T, 3, 3>::operator=( dcm );
        return *this;
    }

    template <typename T>
    DCM<T>& DCM<T>::operator=( const Matrix<T, 3, 3>& m )
    {
        Matrix<T, 3, 3>::operator=( m );
        return *this;
    }

    template <typename T>
    DCM<T>& DCM<T>::operator=( const T ( &m )[3][3] )
    {
        Matrix<T, 3, 3>::operator=( m );
        return *this;
    }

    template <typename T>
    DCM<T>& DCM<T>::operator=( const T ( &m )[9] )
    {
        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                this->mat[i][j] = m[i * 3u + j];
            }
        }

        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator*( const DCM<T>& dcm ) const
    {
        DCM<T> tmp;

        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                T tmp_sum = static_cast<T>( 0.0 );

                for ( unsigned int k{0u}; k < 3u; k++ )
                {
                    tmp_sum += this->mat[i][k] * dcm[k][j];
                }

                tmp[i][j] = tmp_sum;
            }
        }

        return tmp;
    }

    template <typename T>
    DCM<T> DCM<T>::operator*( const Matrix<T, 3, 3>& m ) const
    {
        DCM<T> tmp;

        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                T tmp_sum = static_cast<T>( 0.0 );

                for ( unsigned int k{0u}; k < 3u; k++ )
                {
                    tmp_sum += this->mat[i][k] * m[k][j];
                }

                tmp[i][j] = tmp_sum;
            }
        }

        return tmp;
    }

    template <typename T>
    template <unsigned int C>
    Matrix<T, 3, C> DCM<T>::operator*( const Matrix<T, 3, C>& m ) const
    {
        Matrix<T, 3u, C> tmp;

        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                T tmp_sum = static_cast<T>( 0.0 );

                for ( unsigned int k{0u}; k < 3u; k++ )
                {
                    tmp_sum += this->mat[i][k] * m[k][j];
                }

                tmp[i][j] = tmp_sum;
            }
        }

        return tmp;
    }

    template <typename T>
    Vector<T, 3u> DCM<T>::operator*( const Vector<T, 3u>& v ) const
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

    template <typename T>
    DCM<T>& DCM<T>::operator*=( const DCM<T>& dcm )
    {
        Matrix<T, 3, 3>::operator*=( dcm );
        return *this;
    }

    template <typename T>
    DCM<T>& DCM<T>::operator*=( const Matrix<T, 3, 3>& m )
    {
        Matrix<T, 3, 3>::operator*=( m );
        return *this;
    }

    template <typename T>
    DCM<T>& DCM<T>::operator*=( const T ( &m )[3][3] )
    {
        Matrix<T, 3, 3>::operator*=( m );
        return *this;
    }

    template <typename T>
    DCM<T>& DCM<T>::operator*=( const T ( &m )[9] )
    {
        Matrix<T, 3, 3>::operator*=( m );
        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator-( void ) const
    {
        return static_cast<T>( -1 ) * *this;
    }

    template <typename T>
    bool DCM<T>::operator==( const DCM<T>& dcm ) const
    {
        return Matrix<T, 3, 3>::operator==( dcm );
    }

    template <typename T>
    bool DCM<T>::operator!=( const DCM<T>& dcm ) const
    {
        return Matrix<T, 3, 3>::operator!=( dcm );
    }

    template <typename T>
    DCM<T> DCM<T>::Transpose() const
    {
        DCM<T> tmp;

        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            for ( unsigned int j{0u}; j < 3u; j++ )
            {
                tmp[i][j] = this->mat[j][i];
            }
        }

        return tmp;
    }

    template <typename T>
    void DCM<T>::Normalize()
    {
        for ( unsigned int i{0u}; i < 3u; i++ )
        {
            this->mat[i].Normalize();
        }
    }

    template <typename T>
    Quaternion<T> DCM<T>::ToQuaternion() const
    {
        Quaternion<T> q;

        T q0_mag = std::sqrt( ( static_cast<T>( 1 ) + this->mat[0][0] + this->mat[1][1] + this->mat[2][2] ) ) / static_cast<T>( 2 );
        T q1_mag = std::sqrt( ( static_cast<T>( 1 ) + this->mat[0][0] - this->mat[1][1] - this->mat[2][2] ) ) / static_cast<T>( 2 );
        T q2_mag = std::sqrt( ( static_cast<T>( 1 ) - this->mat[0][0] + this->mat[1][1] - this->mat[2][2] ) ) / static_cast<T>( 2 );
        T q3_mag = std::sqrt( ( static_cast<T>( 1 ) - this->mat[0][0] - this->mat[1][1] + this->mat[2][2] ) ) / static_cast<T>( 2 );

        T q_max = MAX( q0_mag, MAX( q1_mag, MAX( q2_mag, q3_mag ) ) );

        if ( q_max == q0_mag )
        {
            q[0] = q0_mag;
            q[1] = ( this->mat[1][2] - this->mat[2][1] ) / ( static_cast<T>( 4 ) * q0_mag );
            q[2] = ( this->mat[2][0] - this->mat[0][2] ) / ( static_cast<T>( 4 ) * q0_mag );
            q[3] = ( this->mat[0][1] - this->mat[1][0] ) / ( static_cast<T>( 4 ) * q0_mag );
        }
        else if ( q_max == q1_mag )
        {
            q[0] = ( this->mat[1][2] - this->mat[2][1] ) / ( static_cast<T>( 4 ) * q1_mag );
            q[1] = q1_mag;
            q[2] = ( this->mat[0][1] + this->mat[1][0] ) / ( static_cast<T>( 4 ) * q1_mag );
            q[3] = ( this->mat[2][0] + this->mat[0][2] ) / ( static_cast<T>( 4 ) * q1_mag );
        }
        else if ( q_max == q2_mag )
        {
            q[0] = ( this->mat[2][0] - this->mat[0][2] ) / ( static_cast<T>( 4 ) * q2_mag );
            q[1] = ( this->mat[0][1] + this->mat[1][0] ) / ( static_cast<T>( 4 ) * q2_mag );
            q[2] = q2_mag;
            q[3] = ( this->mat[1][2] + this->mat[2][1] ) / ( static_cast<T>( 4 ) * q2_mag );
        }
        else
        {
            q[0] = ( this->mat[0][1] - this->mat[1][0] ) / ( static_cast<T>( 4 ) * q3_mag );
            q[1] = ( this->mat[2][0] + this->mat[0][2] ) / ( static_cast<T>( 4 ) * q3_mag );
            q[2] = ( this->mat[1][2] + this->mat[2][1] ) / ( static_cast<T>( 4 ) * q3_mag );
            q[3] = q3_mag;
        }

        q.Normalize();

        return q;
    }

    template <typename T>
    Angle<T> DCM<T>::ToEuler( const TaitBryanOrder& rotOrder ) const
    {
        Angle<T> euler1;
        Angle<T> euler2;
        Angle<T> euler;

        switch ( rotOrder )
        {
            case TaitBryanOrder::XYZ:
                {
                    euler1[1] = std::asin( this->mat[2][0] );

                    if ( isZero( ABS( euler1[1] ) - Constants::PI / 2.0 ) )
                    {
                        euler1[0] = std::atan2( this->mat[0][1], this->mat[1][1] );
                        euler1[2] = static_cast<T>( 0 );

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

                    if ( isZero( ABS( euler1[1] ) - Constants::PI / 2.0 ) )
                    {
                        euler1[0] = std::atan2( this->mat[0][2], this->mat[2][2] );
                        euler1[2] = static_cast<T>( 0 );

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

                    if ( isZero( ABS( euler1[1] ) - Constants::PI / 2.0 ) )
                    {
                        euler1[0] = std::atan2( this->mat[1][0], this->mat[0][0] );
                        euler1[2] = static_cast<T>( 0 );

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

                    if ( isZero( ABS( euler1[1] ) - Constants::PI / 2.0 ) )
                    {
                        euler1[0] = std::atan2( this->mat[1][2], this->mat[2][2] );
                        euler1[2] = static_cast<T>( 0 );

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

                    if ( isZero( ABS( euler1[1] ) - Constants::PI / 2.0 ) )
                    {
                        euler1[0] = std::atan2( this->mat[0][1], this->mat[0][0] );
                        euler1[2] = static_cast<T>( 0 );

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

                    if ( isZero( ABS( euler1[1] ) - Constants::PI / 2.0 ) )
                    {
                        euler1[0] = std::atan2( this->mat[2][1], this->mat[1][1] );
                        euler1[2] = static_cast<T>( 0 );

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


        euler1.wrapAnglesMinusPiToPi();
        euler2.wrapAnglesMinusPiToPi();

        euler = euler1.Magnitude() < euler2.Magnitude() ? euler1 : euler2;

        #ifdef DEBUG
        DCM<T> check = euler.ToDCM( rotOrder );

        if ( *this != check )
        {
            std::cout << "WARNING! Conversion to Tait-Bryan sequence: " << static_cast<unsigned int>( rotOrder ) << " is not possible!" << std::endl;
        }
        #endif

        return euler;
    }

    template <typename T>
    Angle<T> DCM<T>::ToEuler( const EulerOrder& rotOrder ) const
    {
        Angle<T> euler1;
        Angle<T> euler2;
        Angle<T> euler;

        switch ( rotOrder )
        {
            case EulerOrder::XYX:
                {
                    euler1[1] = std::acos( this->mat[0][0] );

                    if ( isZero( euler1[1] ) )
                    {
                        euler1[0] = std::atan2( this->mat[1][2], this->mat[1][1] );
                        euler1[2] = static_cast<T>( 0 );

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
                        euler1[2] = static_cast<T>( 0 );

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
                        euler1[2] = static_cast<T>( 0 );

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
                        euler1[2] = static_cast<T>( 0 );

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
                        euler1[2] = static_cast<T>( 0 );

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
                        euler1[2] = static_cast<T>( 0 );

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

        euler1.wrapAnglesMinusPiToPi();
        euler2.wrapAnglesMinusPiToPi();

        euler = euler1.Magnitude() < euler2.Magnitude() ? euler1 : euler2;

        DCM<T> check = euler.ToDCM( rotOrder );

        if ( *this != check )
        {
            std::cout << "WARNING! Conversion to Euler sequence: " << static_cast<unsigned int>( rotOrder ) << " is not possible!" << std::endl;
        }

        return euler;
    }

    template <typename T>
    Angle<T> DCM<T>::Rotate( const Angle<T>& angle, const TaitBryanOrder& rotOrder, const TaitBryanOrder rotOrderOut ) const
    {
        return ( ( *this ) * angle.ToDCM( rotOrder ) ).ToEuler( rotOrderOut );
    }

    template <typename T>
    Angle<T> DCM<T>::Rotate( const Angle<T>& angle, const EulerOrder& rotOrder, const TaitBryanOrder rotOrderOut ) const
    {
        return ( ( *this ) * angle.ToDCM( rotOrder ) ).ToEuler( rotOrderOut );
    }

    template <typename T>
    Angle<T> DCM<T>::Rotate( const Angle<T>& angle, const EulerOrder& rotOrder, const EulerOrder rotOrderOut ) const
    {
        return ( ( *this ) * angle.ToDCM( rotOrder ) ).ToEuler( rotOrderOut );
    }

    template <typename T>
    DCM<T> DCM<T>::Rotate( const DCM<T>& dcm ) const
    {
        return ( *this ) * dcm;
    }

    template <typename T>
    Quaternion<T> DCM<T>::Rotate( const Quaternion<T>& q ) const
    {
        return q * ToQuaternion();
    }

    template <typename T>
    Vector<T, 3u> DCM<T>::Rotate( const Vector<T, 3u>& v ) const
    {
        return ( *this ) * v;
    }

} // namespace myMath

#endif /* BA9453AD_D478_47EC_9001_44325F419B41 */
