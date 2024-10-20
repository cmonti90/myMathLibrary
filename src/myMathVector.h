#ifndef MYMATH_VECTOR_H
#define MYMATH_VECTOR_H

#include "myMathConstants.h"
#include "myMathBasicFunctions.h"
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <cstring>

namespace myMath
{
    template< typename T, unsigned int R >
    class Vector
    {
      public:
        T vec[R];

        Vector();
        Vector( const T& x );
        Vector( const T ( &x )[R] );
        Vector( const Vector< T, R >& obj );
        Vector( const std::initializer_list< T >& x );

        virtual ~Vector() = default;

        T& operator[]( const unsigned int i );
        const T& operator[]( const unsigned int i ) const;

        Vector< T, R >& operator=( const T& x );
        Vector< T, R >& operator=( const T ( &x )[R] );
        Vector< T, R >& operator=( const Vector< T, R >& obj );
        Vector< T, R >& operator=( const std::initializer_list< T >& x );

        Vector< T, R > operator+( const Vector< T, R >& obj ) const;
        Vector< T, R > operator-( const Vector< T, R >& obj ) const;
        Vector< T, R > operator*( const T& x ) const;
        Vector< T, R > operator/( const T& x ) const;

        Vector< T, R >& operator+=( const Vector< T, R >& obj );
        Vector< T, R >& operator-=( const Vector< T, R >& obj );
        Vector< T, R >& operator*=( const T& x );
        Vector< T, R >& operator/=( const T& x );

        Vector< T, R > operator-( void ) const;

        bool operator==( const Vector< T, R >& obj ) const;
        bool operator!=( const Vector< T, R >& obj ) const;

        T Magnitude( void ) const;
        void Normalize( void );
        Vector< T, R > Unit() const;
    };

    typedef Vector< float, 2u > Vector2f;
    typedef Vector< float, 3u > Vector3f;
    typedef Vector< float, 4u > Vector4f;

    typedef Vector< double, 2u > Vector2d;
    typedef Vector< double, 3u > Vector3d;
    typedef Vector< double, 4u > Vector4d;

    template< typename T, unsigned int R >
    Vector< T, R >::Vector()
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = static_cast< T >( 0.0 );
        }
    }

    template< typename T, unsigned int R >
    Vector< T, R >::Vector( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = x;
        }
    }

    template< typename T, unsigned int R >
    Vector< T, R >::Vector( const T ( &x )[R] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = x[i];
        }
    }

    template< typename T, unsigned int R >
    Vector< T, R >::Vector( const Vector< T, R >& obj )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = obj.vec[i];
        }
    }

    template< typename T, unsigned int R >
    Vector< T, R >::Vector( const std::initializer_list< T >& x )
    {
        if ( static_cast<unsigned int>( x.size() ) == 1u )
        {
            std::memset( this->vec, *( x.begin() ), sizeof( this->vec ) );
        }
        else if ( static_cast<unsigned int>( x.size() ) != R )
        {
            throw std::invalid_argument( "Initializer list has incorrect size of " + std::to_string( x.size() ) + " instead of " + std::to_string( R ) + "" );
        }
        else if ( x.size() == 0 )
        {
            throw std::invalid_argument( "Initializer list is empty" );
        }

        std::copy( x.begin(), x.end(), this->vec );
    }

    template< typename T, unsigned int R >
    T& Vector< T, R >::operator[]( const unsigned int i )
    {
        return this->vec[i];
    }

    template< typename T, unsigned int R >
    const T& Vector< T, R >::operator[]( const unsigned int i ) const
    {
        return this->vec[i];
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator=( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = x;
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator=( const T ( &x )[R] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = x[i];
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator=( const Vector< T, R >& obj )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] = obj.vec[i];
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator=( const std::initializer_list< T >& x )
    {
        if ( static_cast<unsigned int>( x.size() ) == 1u )
        {
            std::memset( this->vec, *( x.begin() ), sizeof( this->vec ) );
        }
        else if ( static_cast<unsigned int>( x.size() ) != R )
        {
            throw std::invalid_argument( "Initializer list has incorrect size of " + std::to_string( x.size() ) + " instead of " + std::to_string( R ) + "" );
        }

        std::copy( x.begin(), x.end(), this->vec );

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R > Vector< T, R >::operator+( const Vector< T, R >& obj ) const
    {
        Vector< T, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp.vec[i] += obj.vec[i];
        }

        return tmp;
    }

    template< typename T, unsigned int R >
    Vector< T, R > Vector< T, R >::operator-( const Vector< T, R >& obj ) const
    {
        Vector< T, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp.vec[i] -= obj.vec[i];
        }

        return tmp;
    }

    template< typename T, unsigned int R >
    Vector< T, R > Vector< T, R >::operator*( const T& x ) const
    {
        Vector< T, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template< typename T, unsigned int R >
    Vector< T, R > Vector< T, R >::operator/( const T& x ) const
    {
        Vector< T, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp.vec[i] /= x;
        }

        return tmp;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator+=( const Vector< T, R >& obj )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] += obj.vec[i];
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator-=( const Vector< T, R >& obj )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] -= obj.vec[i];
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator*=( const T& x )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] *= x;
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R >& Vector< T, R >::operator/=( const T& x )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            this->vec[i] /= x;
        }

        return *this;
    }

    template< typename T, unsigned int R >
    Vector< T, R > Vector< T, R >::operator-( void ) const
    {
        Vector< T, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp.vec[i] = -tmp.vec[i];
        }

        return tmp;
    }

    template< typename T, unsigned int R >
    bool Vector< T, R >::operator==( const Vector< T, R >& obj ) const
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            if ( ABS( this->vec[i] - obj.vec[i] ) > Constants::ZERO_THRESHOLD )
            {
                return false;
            }
        }

        return true;
    }

    template< typename T, unsigned int R >
    bool Vector< T, R >::operator!=( const Vector< T, R >& obj ) const
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            if ( ABS( this->vec[i] - obj.vec[i] ) > Constants::ZERO_THRESHOLD )
            {
                return true;
            }
        }

        return false;
    }

    template<class T, unsigned int C>
    Vector<T, C> operator*( const T& x, const Vector<T, C>& obj )
    {
        Vector<T, C> tmp{obj};

        for ( unsigned int i{0u}; i < C; i++ )
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template< typename T, unsigned int R >
    T Vector< T, R >::Magnitude( void ) const
    {
        T tmp = static_cast< T >( 0.0 );

        for ( unsigned int i{0u}; i < R; i++ )
        {
            tmp += SQ( this->vec[i] );
        }

        return static_cast< T >( std::sqrt( tmp ) );
    }

    template< typename T, unsigned int R >
    void Vector< T, R >::Normalize()
    {
        T mag{this->Magnitude()};

        if ( isZero( mag ) )
        {
            return;
        }

        *this /= mag;
    }

    template< typename T, unsigned int R >
    Vector< T, R > Vector< T, R >::Unit() const
    {
        Vector< T, R > tmp{*this};
        T mag{this->Magnitude()};

        if ( isZero( mag ) )
        {
            return tmp;
        }

        tmp /= mag;

        return tmp;
    }
}

#endif // MYMATH_VECTOR_H
