#pragma once

#ifndef MYMATH_MATRIX_H
#define MYMATH_MATRIX_H

#include "myMathConstants.h"
#include "myMathBasicFunctions.h"
#include "myMathVector.h"

#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace myMath
{
    template < typename T, unsigned int R, unsigned int C >
    class Matrix
    {
      public:
        Vector< T, C > mat[R];

        Matrix();
        Matrix( const T& x );
        Matrix( const T ( &x )[R][C] );
        Matrix( const T ( &&x )[R][C] );
        Matrix( const Matrix< T, R, C >& obj );
        Matrix( const std::initializer_list< T >& x );
        ~Matrix() = default;

        Vector< T, C >& operator[]( const unsigned int i );
        const Vector< T, C >& operator[]( const unsigned int i ) const;

        Matrix< T, R, C >& operator=( const T& x );
        Matrix< T, R, C >& operator=( const T ( &x )[R][C] );
        Matrix< T, R, C >& operator=( const T ( &&x )[R][C] );
        Matrix< T, R, C >& operator=( const Matrix< T, R, C >& obj );

        Matrix< T, R, C > operator+( const Matrix< T, R, C >& obj ) const;
        Matrix< T, R, C > operator-( const Matrix< T, R, C >& obj ) const;

        template < unsigned int C2 >
        Matrix< T, R, C2 > operator*( const Matrix< T, C, C2 >& rhs ) const;
        Vector<T, R> operator*( const Vector< T, C >& obj ) const;
        Matrix< T, R, C > operator*( const T& x ) const;
        Matrix< T, R, C > operator/( const T& x ) const;

        Matrix< T, R, C >& operator+=( const Matrix< T, R, C >& obj );
        Matrix< T, R, C >& operator-=( const Matrix< T, R, C >& obj );
        Matrix< T, R, C >& operator*=( const Matrix< T, R, C >& rhs );
        Matrix< T, R, C >& operator*=( const T& x );
        Matrix< T, R, C >& operator/=( const T& x );

        Matrix< T, R, C > operator-() const;

        bool operator==( const Matrix< T, R, C >& obj ) const;
        bool operator!=( const Matrix< T, R, C >& obj ) const;

        Matrix< T, C, R > Transpose( void ) const;
        void TransposeInPlace( void );
    };


    template < typename T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C >::Matrix()
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = static_cast< T >( 0 );
            }
        }
    }


    template < typename T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C >::Matrix( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = x;
            }
        }
    }


    template < typename T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C >::Matrix( const T ( &x )[R][C] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }
    }


    template < typename T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C >::Matrix( const T ( &&x )[R][C] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }
    }


    template < typename T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C >::Matrix( const Matrix< T, R, C >& obj )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = obj.mat[i][j];
            }
        }
    }


    template < typename T, unsigned int R, unsigned int C >
    inline Matrix< T, R, C >::Matrix( const std::initializer_list< T >& x )
    {
        if ( static_cast<unsigned int>( x.size() ) == 1u )
        {
            for ( unsigned int i{0u}; i < R; i++ )
            {
                for ( unsigned int j{0u}; j < C; j++ )
                {
                    this->mat[i][j] = *( x.begin() );
                }
            }
        }
        else if ( static_cast<unsigned int>( x.size() ) != ( R * C ) )
        {
            std::cout << "Initializer list has incorrect size of " << x.size() << " instead of " << ( R * C ) << std::endl;
            throw std::invalid_argument( "Initializer list has incorrect size of " + std::to_string( x.size() ) + " instead of " + std::to_string( ( R * C ) ) + "" );
        }
        else if ( x.size() == 0 )
        {
            throw std::invalid_argument( "Initializer list is empty" );
        }
        else
        {
            for ( unsigned int i{0u}; i < R; i++ )
            {
                for ( unsigned int j{0u}; j < C; j++ )
                {
                    this->mat[i][j] = *( x.begin() + ( i * C + j ) );
                }
            }
        }
    }


    template < typename T, unsigned int R, unsigned int C >
    Vector< T, C >& Matrix< T, R, C >::operator[]( const unsigned int i )
    {
        return this->mat[i];
    }


    template < typename T, unsigned int R, unsigned int C >
    const Vector< T, C >& Matrix< T, R, C >::operator[]( const unsigned int i ) const
    {
        return this->mat[i];
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator=( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = x;
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator=( const T ( &x )[R][C] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator=( const T ( &&x )[R][C] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator=( const Matrix< T, R, C >& obj )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] = obj.mat[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C > Matrix< T, R, C >::operator+( const Matrix< T, R, C >& obj ) const
    {
        Matrix< T, R, C > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.mat[i][j] += obj.mat[i][j];
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C > Matrix< T, R, C >::operator-( const Matrix< T, R, C >& obj ) const
    {
        Matrix< T, R, C > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.mat[i][j] -= obj.mat[i][j];
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    bool Matrix< T, R, C >::operator==( const Matrix< T, R, C >& obj ) const
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            if ( this->mat[i] != obj.mat[i] )
            {
                return false;
            }
        }

        return true;
    }


    template < typename T, unsigned int R, unsigned int C >
    bool Matrix< T, R, C >::operator!=( const Matrix< T, R, C >& obj ) const
    {
        return !( *this == obj );
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C > Matrix< T, R, C >::operator*( const T& x ) const
    {
        Matrix< T, R, C > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.mat[i][j] *= x;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    Vector<T, R> Matrix< T, R, C >::operator*( const Vector< T, C >& obj ) const
    {
        Vector<T, R> tmp{0.0};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.vec[i] += this->mat[i][j] * obj[j];
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C > Matrix< T, R, C >::operator/( const T& x ) const
    {
        Matrix< T, R, C > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.mat[i][j] /= x;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator+=( const Matrix< T, R, C >& obj )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] += obj.mat[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator-=( const Matrix< T, R, C >& obj )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] -= obj.mat[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator*=( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                this->mat[i][j] *= x;
            }
        }

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator*=( const Matrix< T, R, C >& rhs )
    {
        *this = *this * rhs;

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C >& Matrix< T, R, C >::operator/=( const T& x )
    {
        *this = *this / x;

        return *this;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C > Matrix< T, R, C >::operator-() const
    {
        return static_cast< T >( -1 ) * ( *this );
    }


    template < typename T, unsigned int R, unsigned int C >
    template < unsigned int C2 >
    Matrix< T, R, C2 > Matrix< T, R, C >::operator*( const Matrix< T, C, C2 >& rhs ) const
    {
        Matrix< T, R, C2 > tmp;

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C2; j++ )
            {
                T tmp_sum = static_cast< T >( 0 );

                for ( unsigned int k{0u}; k < C; k++ )
                {
                    tmp_sum += this->mat[i][k] * rhs.mat[k][j];
                }

                tmp.mat[i][j] = tmp_sum;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix< T, R, C > operator*( const T& x, const Matrix< T, R, C >& obj )
    {
        Matrix< T, R, C > tmp{obj};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmp.mat[i][j] *= x;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R, unsigned int C >
    Matrix<T, C, R> Matrix< T, R, C >::Transpose( void ) const
    {
        Matrix<T, C, R> tmpMat{*this};

        for ( unsigned int i{0u}; i < C; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmpMat.mat[i][j] = this->mat[j].vec[i];
            }
        }

        return tmpMat;
    }
    

    template < typename T, unsigned int R, unsigned int C >
    void Matrix< T, R, C >::TransposeInPlace( void )
    {
        Matrix< T, R, C > tmpMat{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                tmpMat.mat[i][j] = this->mat[j].vec[i];
            }
        }

        this = tmpMat;
    }


    // Square Matrices
    template < typename T, unsigned int R >
    class Matrix< T, R, R >
    {
      public:
        Vector< T, R > mat[R];

        Matrix();
        Matrix( const T& x );
        Matrix( const T ( &x )[R][R] );
        Matrix( const T ( &&x )[R][R] );
        Matrix( const Matrix< T, R, R >& obj );
        Matrix( const std::initializer_list< T >& x );
        ~Matrix() = default;

        Vector< T, R >& operator[]( const unsigned int i );
        const Vector< T, R >& operator[]( const unsigned int i ) const;

        Matrix< T, R, R >& operator=( const T& x );
        Matrix< T, R, R >& operator=( const T ( &x )[R][R] );
        Matrix< T, R, R >& operator=( const T ( &&x )[R][R] );
        Matrix< T, R, R >& operator=( const Matrix< T, R, R >& obj );

        Matrix< T, R, R > operator+( const Matrix< T, R, R >& obj ) const;
        Matrix< T, R, R > operator-( const Matrix< T, R, R >& obj ) const;

        Matrix< T, R, R > operator*( const T& x ) const;
        Matrix< T, R, R > operator*( const Matrix< T, R, R >& rhs ) const;

        template< unsigned int C >
        Matrix< T, R, C > operator*( const Matrix< T, R, C >& rhs ) const;

        Matrix< T, R, R > operator/( const T& x ) const;

        Matrix< T, R, R >& operator+=( const Matrix< T, R, R >& obj );
        Matrix< T, R, R >& operator-=( const Matrix< T, R, R >& obj );

        Matrix< T, R, R >& operator*=( const T& x );
        Matrix< T, R, R >& operator*=( const Matrix< T, R, R >& rhs );

        Matrix< T, R, R >& operator/=( const T& x );

        Matrix< T, R, R > operator-() const;

        bool operator==( const Matrix< T, R, R >& obj ) const;
        bool operator!=( const Matrix< T, R, R >& obj ) const;

        T Minor( unsigned int i, unsigned int j ) const;
        T Determinant( void ) const;
        Matrix< T, R, R > Transpose( void ) const;
        void TransposeInPlace( void );
        void Invert( void );
        Matrix< T, R, R > Inverse( void ) const;

        static Matrix< T, R, R > Identity();
    };



    typedef Matrix< float, 2u, 2u > Matrix2f;
    typedef Matrix< float, 3u, 3u > Matrix3f;
    typedef Matrix< float, 4u, 4u > Matrix4f;

    typedef Matrix< double, 2u, 2u > Matrix2d;
    typedef Matrix< double, 3u, 3u > Matrix3d;
    typedef Matrix< double, 4u, 4u > Matrix4d;


    template < typename T, unsigned int R >
    inline Matrix< T, R, R >::Matrix()
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = static_cast< T >( 0 );
            }
        }
    }


    template < typename T, unsigned int R >
    inline Matrix< T, R, R >::Matrix( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = x;
            }
        }
    }


    template < typename T, unsigned int R >
    inline Matrix< T, R, R >::Matrix( const T ( &x )[R][R] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }
    }


    template < typename T, unsigned int R >
    inline Matrix< T, R, R >::Matrix( const T ( &&x )[R][R] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }
    }


    template < typename T, unsigned int R >
    inline Matrix< T, R, R >::Matrix( const Matrix< T, R, R >& obj )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = obj.mat[i][j];
            }
        }
    }


    template < typename T, unsigned int R >
    inline Matrix< T, R, R >::Matrix( const std::initializer_list< T >& x )
    {
        if ( static_cast<unsigned int>( x.size() ) == 1u )
        {
            for ( unsigned int i{0u}; i < R; i++ )
            {
                for ( unsigned int j{0u}; j < R; j++ )
                {
                    this->mat[i][j] = *( x.begin() );
                }
            }
        }
        else if ( static_cast<unsigned int>( x.size() ) != ( R * R ) )
        {
            std::cout << "Initializer list has incorrect size of " << x.size() << " instead of " << ( R * R ) << std::endl;
            throw std::invalid_argument( "Initializer list has incorrect size of " + std::to_string( x.size() ) + " instead of " + std::to_string( ( R * R ) ) + "" );
        }
        else if ( x.size() == 0 )
        {
            throw std::invalid_argument( "Initializer list is empty" );
        }
        else
        {
            for ( unsigned int i{0u}; i < R; i++ )
            {
                for ( unsigned int j{0u}; j < R; j++ )
                {
                    this->mat[i][j] = *( x.begin() + ( i * R + j ) );
                }
            }
        }
    }


    template < typename T, unsigned int R >
    Vector< T, R >& Matrix< T, R, R >::operator[]( const unsigned int i )
    {
        return this->mat[i];
    }


    template < typename T, unsigned int R >
    const Vector< T, R >& Matrix< T, R, R >::operator[]( const unsigned int i ) const
    {
        return this->mat[i];
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator=( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = x;
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator=( const T ( &x )[R][R] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator=( const T ( &&x )[R][R] )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = x[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator=( const Matrix< T, R, R >& obj )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] = obj.mat[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::operator+( const Matrix< T, R, R >& obj ) const
    {
        Matrix< T, R, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmp.mat[i][j] += obj.mat[i][j];
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::operator-( const Matrix< T, R, R >& obj ) const
    {
        Matrix< T, R, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmp.mat[i][j] -= obj.mat[i][j];
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R >
    bool Matrix< T, R, R >::operator==( const Matrix< T, R, R >& obj ) const
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            if ( this->mat[i] != obj.mat[i] )
            {
                return false;
            }
        }

        return true;
    }


    template < typename T, unsigned int R >
    bool Matrix< T, R, R >::operator!=( const Matrix< T, R, R >& obj ) const
    {
        return !( *this == obj );
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::operator*( const T& x ) const
    {
        Matrix< T, R, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmp.mat[i][j] *= x;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::operator*( const Matrix< T, R, R >& rhs ) const
    {
        Matrix< T, R, R > tmp;

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                T tmp_sum = static_cast< T >( 0 );

                for ( unsigned int k{0u}; k < R; k++ )
                {
                    tmp_sum += this->mat[i][k] * rhs.mat[k][j];
                }

                tmp.mat[i][j] = tmp_sum;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R >
    template < unsigned int C >
    Matrix< T, R, C > Matrix< T, R, R >::operator*( const Matrix< T, R, C >& rhs ) const
    {
        Matrix< T, R, C > tmp;

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < C; j++ )
            {
                T tmp_sum = static_cast< T >( 0 );

                for ( unsigned int k{0u}; k < R; k++ )
                {
                    tmp_sum += this->mat[i][k] * rhs.mat[k][j];
                }

                tmp.mat[i][j] = tmp_sum;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::operator/( const T& x ) const
    {
        Matrix< T, R, R > tmp{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmp.mat[i][j] /= x;
            }
        }

        return tmp;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator+=( const Matrix< T, R, R >& obj )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] += obj.mat[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator-=( const Matrix< T, R, R >& obj )
    {

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] -= obj.mat[i][j];
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator*=( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] *= x;
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator*=( const Matrix< T, R, R >& rhs )
    {
        *this = *this * rhs;

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R >& Matrix< T, R, R >::operator/=( const T& x )
    {
        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                this->mat[i][j] /= x;
            }
        }

        return *this;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::operator-() const
    {
        return static_cast< T >( -1 ) * ( *this );
    }


    template < typename T, unsigned int R >
    T Matrix< T, R, R >::Minor( unsigned int i, unsigned int j ) const
    {
        Matrix< T, R, R > minor;

        for ( unsigned int m{0u}; m < R; m++ )
        {
            for ( unsigned int n{0u}; n < R; n++ )
            {
                if ( m != i && n != j )
                {
                    minor.mat[m < i ? m : ( m - 1u )].vec[n < j ? n : ( n - 1u )] = this->mat[m].vec[n];
                }
            }
        }

        return ( minor.Determinant() );
    }

    template < typename T, unsigned int R >
    T Matrix< T, R, R >::Determinant( void ) const
    {
        Matrix< T, R, R > tmpMat{*this};
        T det{static_cast< T >( 1 )};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            unsigned int maxrow = i;

            for ( unsigned int j{i + 1u}; j < R; j++ )
            {
                if ( ABS( tmpMat[j][i] ) > ABS( tmpMat[maxrow][i] ) )
                {
                    maxrow = j;
                }
            }

            if ( maxrow != i )
            {
                Vector< T, R > tmpRow{tmpMat[i]};

                tmpMat[i] = tmpMat[maxrow];
                tmpMat[maxrow] = tmpRow;

                det *= static_cast< T >( -1 );
            }

            for ( unsigned int j{i + 1u}; j < R; j++ )
            {
                T factor = tmpMat[j][i] / tmpMat[i][i];

                for ( unsigned int k{i + 1u}; k < R; k++ )
                {
                    tmpMat[j][k] -= factor * tmpMat[i][k];
                }

                tmpMat[j][i] = static_cast< T >( 0 );
            }

            det *= tmpMat[i][i];
        }

        return det;
    }

    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::Inverse( void ) const
    {
        if ( ABS( this->Determinant() ) > static_cast< T >( Constants::ZERO_THRESHOLD ) )
        {

            Matrix< T, R, R > tmpMat{*this};
            Matrix< T, R, R > invMat{Matrix< T, R, R >::Identity()};

            for ( unsigned int i{0u}; i < R; i++ )
            {
                invMat[i][i] = static_cast< T >( 1 );
            }

            for ( unsigned int i{0u}; i < R; i++ )
            {
                unsigned int maxrow = i;

                for ( unsigned int j{i + 1u}; j < R; j++ )
                {
                    if ( ABS( tmpMat[j][i] ) > ABS( tmpMat[maxrow][i] ) )
                    {
                        maxrow = j;
                    }
                }

                if ( maxrow != i )
                {
                    Vector< T, R > tmpRow{tmpMat[i]};

                    tmpMat[i] = tmpMat[maxrow];
                    tmpMat[maxrow] = tmpRow;

                    tmpRow = invMat[i];

                    invMat[i] = invMat[maxrow];
                    invMat[maxrow] = tmpRow;
                }

                for ( unsigned int j{i + 1u}; j < R; j++ )
                {
                    T factor = tmpMat[j][i] / tmpMat[i][i];

                    for ( unsigned int k{i + 1u}; k < R; k++ )
                    {
                        tmpMat[j][k] -= factor * tmpMat[i][k];
                    }

                    for ( unsigned int k{0u}; k < R; k++ )
                    {
                        invMat[j][k] -= factor * invMat[i][k];
                    }

                    tmpMat[j][i] = static_cast< T >( 0 );
                }
            }

            for ( int i{static_cast<int>( R ) - 1}; i >= 0; i-- )
            {
                for ( unsigned int j{0u}; j < R; j++ )
                {
                    for ( unsigned int k{static_cast<unsigned int>( i ) + 1u}; k < R; k++ )
                    {
                        invMat[i][j] -= tmpMat[i][k] * invMat[k][j];
                    }

                    invMat[i][j] /= tmpMat[i][i];
                }
            }

            return invMat;
        }
        else
        {
            return Matrix< T, R, R >::Identity();
        }
    }

    template < typename T, unsigned int R >
    Matrix<T, R, R> Matrix< T, R, R >::Transpose( void ) const
    {
        Matrix<T, R, R> tmpMat{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmpMat.mat[i][j] = this->mat[j].vec[i];
            }
        }

        return tmpMat;
    }

    template < typename T, unsigned int R >
    void Matrix< T, R, R >::TransposeInPlace( void )
    {
        Matrix< T, R, R > tmpMat{*this};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmpMat.mat[i][j] = this->mat[j].vec[i];
            }
        }

        this = tmpMat;
    }

    template < typename T, unsigned int R >
    void Matrix< T, R, R >::Invert( void )
    {
        if ( ABS( this->Determinant() ) > static_cast< T >( Constants::ZERO_THRESHOLD ) )
        {
            Matrix< T, R, R > tmpMat{*this};
            Matrix< T, R, R > invMat{Matrix< T, R, R >::Identity()};

            for ( unsigned int i{0u}; i < R; i++ )
            {
                invMat[i][i] = static_cast< T >( 1 );
            }

            for ( unsigned int i{0u}; i < R; i++ )
            {
                unsigned int maxrow = i;

                for ( unsigned int j{i + 1u}; j < R; j++ )
                {
                    if ( ABS( tmpMat[j][i] ) > ABS( tmpMat[maxrow][i] ) )
                    {
                        maxrow = j;
                    }
                }

                if ( maxrow != i )
                {
                    Vector< T, R > tmpRow{tmpMat[i]};

                    tmpMat[i] = tmpMat[maxrow];
                    tmpMat[maxrow] = tmpRow;

                    tmpRow = invMat[i];

                    invMat[i] = invMat[maxrow];
                    invMat[maxrow] = tmpRow;
                }

                for ( unsigned int j{i + 1u}; j < R; j++ )
                {
                    T factor = tmpMat[j][i] / tmpMat[i][i];

                    for ( unsigned int k{i + 1u}; k < R; k++ )
                    {
                        tmpMat[j][k] -= factor * tmpMat[i][k];
                    }

                    for ( unsigned int k{0u}; k < R; k++ )
                    {
                        invMat[j][k] -= factor * invMat[i][k];
                    }

                    tmpMat[j][i] = static_cast< T >( 0 );
                }
            }

            for ( int i{static_cast<int>( R ) - 1}; i >= 0; i-- )
            {
                for ( unsigned int j{0u}; j < R; j++ )
                {
                    for ( unsigned int k{static_cast<unsigned int>( i ) + 1u}; k < R; k++ )
                    {
                        invMat[i][j] -= tmpMat[i][k] * invMat[k][j];
                    }

                    invMat[i][j] /= tmpMat[i][i];
                }
            }

            this = invMat;
        }
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > Matrix< T, R, R >::Identity()
    {
        Matrix< T, R, R > tmpMat;

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmpMat[i][j] = ( i == j ) ? static_cast< T >( 1 ) : static_cast< T >( 0 );
            }
        }

        return tmpMat;
    }


    template < typename T, unsigned int R >
    Matrix< T, R, R > operator*( const T& x, const Matrix< T, R, R >& obj )
    {
        Matrix< T, R, R > tmp{obj};

        for ( unsigned int i{0u}; i < R; i++ )
        {
            for ( unsigned int j{0u}; j < R; j++ )
            {
                tmp.mat[i][j] *= x;
            }
        }

        return tmp;
    }

} // namespace myMath

#endif // MYMATH_MATRIX_H
