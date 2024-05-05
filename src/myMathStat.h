#ifndef MYMATH_STAT_H
#define MYMATH_STAT_H

#include <cmath>
#include <stdexcept>
#include <limits>


namespace myMath
{
    /////////////////////////////////
    //         DECLARATIONS        //
    /////////////////////////////////

    template< typename T > T Beta( const T x, const T y );
    template< typename T > T BetaIncomplete( const T x, const T a, const T b );
    template< typename T > T BetaInverse( const T p, const T a, const T b );
    template< typename T > T BetaLN( const T z, const T w );
    template< typename T > T BetaPDF( const T x, const T p, const T q );
    template< typename T > T ChiSquaredCDF( const T x, const T v );
    template< typename T > T ErrorFunction( const T x );
    template< typename T > T ErrorFunctionComplement( const T x );
    template< typename T > T F_CDF( const T x, const T d1, const T d2 );
    template< typename T > T F_NoncentralCDF( const T w, const T n1, const T n2, const T lambda );
    template< typename T > T F_Inverse( const T p, const T v1, const T v2 );
    template< typename T > T F_PDF( const T x, const T m, const T n );
    template< typename T > T GammaCDF( const T x, const T a, const T b );
    template< typename T > T GammaIncompleteP( const T x, const T a );
    template< typename T > T GammaIncompleteQ( const T x, const T a );
    template< typename T > T GammaLN( const T z );
    template< typename T > T GammaPDF( const T x, const T a, const T b );
    template< typename T > T GammaInverseCDF( const T x, const T a, const T b );
    template< typename T > T NormalCDF( const T x, const T mu, const T sigma );
    template< typename T > T NormalInverseCDF( const T p, const T mu, const T sigma );



    /////////////////////////////////
    //         DEFINITIONS         //
    /////////////////////////////////

    template< typename T >
    T Beta( const T x, const T y )
    {
        if ( x <= static_cast< T >( 0 ) || y <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "Beta: x and y must be greater than 0" );
        }

        return std::exp( GammaLN( x ) + GammaLN( y ) - GammaLN( x + y ) );
    }


    template< typename T >
    T BetaIncomplete( const T x, const T a, const T b )
    {
        const unsigned int maxIters = 100u;
        const T small = std::numeric_limits< T >::epsilon();
        const T stop = static_cast< T >( 3e-7 );
        unsigned int m;
        int inverter = 0;
        T finalA = a;
        T finalB = b;

        if ( x >= ( a + static_cast< T >( 1 ) ) / ( a + b + static_cast< T >( 2 ) ) )
        {
            finalA = b;
            finalB = a;
            x = static_cast< T >( 1 ) - x;
            inverter = 1;
        }

        T stepD   = static_cast< T >( -( finalA + finalB ) * x / ( finalA + static_cast< T >( 1 ) ) );
        T totalC  = static_cast< T >( 1 );
        T totalD  = static_cast< T >( static_cast< T >( 1 ) / ( static_cast< T >( 1 ) + stepD ) );
        T ans     = static_cast< T >( 1 );
        T prevAns = static_cast< T >( 0 );


        // Beta incomlpete is not defined for x values outside of [0, 1]
        if ( x < static_cast< T >( 0 ) || x > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "BetaIncomplete: x must be in the range [0, 1]" );
        }

        if ( a <= static_cast< T >( 0 ) || b <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "BetaIncomplete: a and b must be greater than 0" );
        }

        if ( x == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 0 );
        }
        else if ( x == static_cast< T >( 1 ) )
        {
            return static_cast< T >( 1 );
        }

        for ( unsigned int i = 2u; i <= maxIters; i++ )
        {
            ans *= totalC * totalD;

            if ( std::abs( ans - prevAns ) < stop )
            {
                return ( static_cast< T >( inverter ) + ( static_cast< T >( 1 - 2 * inverter ) ) *
                         std::exp( finalA * std::log( x ) + finalB * std::log( static_cast< T >( 1 ) - x ) -
                                   std::log( finalA ) - BetaLN( finalA, finalB ) + std::log( ans ) ) );
            }
            else
            {
                if ( i % 2 == 0 )
                {
                    m = static_cast< int >( i / 2 );
                    stepD = ( ( static_cast< T >( m ) * ( finalB - static_cast< T >( m ) ) * x ) /
                              ( ( finalA + static_cast< T >( 2 ) * static_cast< T >( m ) - static_cast< T >( 1 ) ) *
                                ( finalA + static_cast< T >( 2 ) * static_cast< T >( m ) ) ) );
                }
                else
                {
                    m = static_cast< int >( ( i - 1 ) / 2 );
                    stepD = - ( ( finalA + static_cast< T >( m ) ) * ( finalA + finalB + static_cast< T >( m ) ) * x ) /
                            ( ( finalA + static_cast< T >( 2 ) * static_cast< T >( m ) )
                              * ( finalA + static_cast< T >( 2 ) * static_cast< T >( m ) + static_cast< T >( 1 ) ) );
                }

                totalC = static_cast< T >( 1 ) + stepD / totalC;
                totalD = static_cast< T >( 1 ) / ( static_cast< T >( 1 ) + stepD * totalD );

                if ( isZero( totalC ) )
                {
                    totalC = small;
                }

                if ( isZero( totalD ) )
                {
                    totalD = small;
                }

                prevAns = ans;
            }
        }

        throw std::runtime_error( "BetaIncomplete: failed to converge" );

        return static_cast< T >( 0 );
    }


    template< typename T >
    T BetaInverse( const T p, const T a, const T b )
    {
        const T min = static_cast< T >( std::numeric_limits< T >::min() );
        const T small = static_cast< T >( 1e-8 );
        const unsigned int maxIter = 100u;

        if ( p < static_cast< T >( 0 ) || p > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "BetaInverse: p must be in the range [0, 1]" );
        }

        if ( a <= static_cast< T >( 0 ) || b <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "BetaInverse: a and b must be greater than 0" );
        }

        if ( p == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 0 );
        }
        else if ( p == static_cast< T >( 1 ) )
        {
            return static_cast< T >( 1 );
        }

        T x_cur = a / ( a + b );
        T x_next;
        T f  = static_cast< T >( 1 );
        T df = static_cast< T >( 1 );

        for ( unsigned int i = 0; i < maxIter; i++ )
        {
            f  = BetaIncomplete( x_cur, a, b ) - p;
            df = std::max( BetaPDF( x_cur, a, b ), min );
            x_next = std::max( x_cur / static_cast< T >( 10 ), std::min( x_cur + ( p - f ) / df, x_cur * static_cast< T >( 10 ) ) );

            if ( x_next >= static_cast< T >( 1 ) )
            {
                x_next = static_cast< T >( 1 ) - ( static_cast< T >( 1 ) - x_cur ) / static_cast< T >( 10 );
            }

            if ( std::fabs( f - p ) < small )
            {
                return x_next;
            }
            else
            {
                x_cur = x_next;
            }

        }

        throw std::runtime_error( "BetaInverse: failed to converge" );

        return static_cast< T >( 0 );
    }


    template< typename T >
    T BetaLN( const T z, const T w )
    {
        if ( z <= static_cast< T >( 0 ) || w <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "BetaLN: z and w must be greater than 0" );
        }

        return ( GammaLN( z ) + GammaLN( w ) - GammaLN( z + w ) );
    }


    template< typename T >
    T BetaPDF( const T x, const T p, const T q )
    {
        T log_1mx, log_x;

        if ( x < static_cast< T >( 0 ) || x > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "BetaPDF: x must be in the range [0, 1]" );
        }

        if ( p <= static_cast< T >( 0 ) || q <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "BetaPDF: p and q must be greater than 0" );
        }

        if ( q == static_cast< T >( 1 ) )
        {
            log_1mx = static_cast< T >( 0 );
        }
        else
        {
            log_1mx = ( q - static_cast< T >( 1 ) ) * std::log( static_cast< T >( 1 ) - x );
        }

        if ( p == static_cast< T >( 1 ) )
        {
            log_x = static_cast< T >( 0 );
        }
        else
        {
            log_x = ( p - static_cast< T >( 1 ) ) * std::log( x );
        }

        return std::exp( log_x + log_1mx - BetaLN( p, q ) );
    }


    template< typename T >
    T ChiSquaredCDF( const T x, const T v )
    {
        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "ChiSquaredCDF: x must be greater than or equal to 0" );
        }

        if ( v <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "ChiSquaredCDF: v must be greater than 0" );
        }

        return GammaIncompleteP( x / static_cast< T >( 2 ), v / static_cast< T >( 2 ) );
    }


    template< typename T >
    T ErrorFunction( const T x )
    {
        const T ans = std::exp( -std::log( static_cast< T >( Constants::PI ) ) / static_cast< T >( 2 ) + GammaLN( static_cast< T >( 0.5 ) ) )
                      * GammaIncompleteP( std::pow( x, static_cast< T >( 2 ) ), static_cast< T >( 0.5 ) );

        return ( x >= static_cast< T >( 0 ) ? ans : -ans );
    }


    template< typename T >
    T ErrorFunctionComplement( const T x )
    {
        return static_cast< T >( 1 ) - ErrorFunction( x );
    }


    template< typename T >
    T F_CDF( const T x, const T d1, const T d2 )
    {
        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_CDF: x must be greater than or equal to 0" );
        }

        if ( d1 <= static_cast< T >( 0 ) || d2 <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_CDF: d1 and d2 must be greater than 0" );
        }

        return BetaIncomplete( d1 * x / ( d1 * x + d2 ),
                               d1 / static_cast< T >( 2 ),
                               d2 / static_cast< T >( 2 ) );
    }


    template< typename T >
    T F_NoncentralCDF( const T w, const T n1, const T n2, const T lambda )
    {
        const int maxIter{5000};
        const T small = static_cast< T >( 1e-10 );

        T cur_p, cur_s, next_r, check;
        const T x = n1 * w / ( n1 * w + n2 );
        T a = n1 / static_cast< T >( 2 );
        T b = n2 / static_cast< T >( 2 );
        T prev_s = BetaIncomplete( x, a, b );
        T cur_r = lambda / static_cast< T >( 2 );

        if ( x < static_cast< T >( 0 ) || x > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "F_NoncentralCDF: x must be in the range [0, 1]" );
        }

        if ( w <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_NoncentralCDF: w must be greater than 0" );
        }

        if ( n1 <= static_cast< T >( 0 ) || n2 <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_NoncentralCDF: n1 and n2 must be greater than 0" );
        }

        if ( lambda == static_cast< T >( 0 ) )
        {
            return F_CDF( w, n1, n2 );
        }

        for ( int n = 1; n <= maxIter; n++ )
        {
            cur_p = BetaIncomplete( x, a + static_cast< T >( n ), b );
            cur_s = prev_s + cur_r * cur_p;

            next_r = lambda * cur_r / static_cast< T >( 2 * ( n + 1 ) );

            check = next_r * cur_p * std::min( static_cast< T >( 1 ),
                                               std::exp( -lambda / static_cast< T >( 2 ) ) + ( lambda / static_cast< T >( 2 * ( n + 2 ) ) ) );

            if ( check <= small )
            {
                return std::exp( -lambda / static_cast< T >( 2 ) ) * cur_s;
            }
            else
            {
                prev_s = cur_s;
                cur_r = next_r;
            }
        }

        throw std::runtime_error( "F_NoncentralCDF: failed to converge" );

        return static_cast< T >( 0 );
    }


    template< typename T >
    T F_Inverse( const T p, const T v1, const T v2 )
    {
        const T min = static_cast< T >( 1e-8 );
        const T minDf = static_cast< T >( 1e-32 );
        const T inf = static_cast< T >( 1e30 );
        const unsigned int maxIter = 1000u;

        T x_cur  = v1;
        T x_next = static_cast< T >( 0 );
        T f      = static_cast< T >( 1 );
        T df     = static_cast< T >( 1 );

        if ( p < static_cast< T >( 0 ) || p > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "F_Inverse: p must be in the range [0, 1]" );
        }

        if ( v1 <= static_cast< T >( 0 ) || v2 <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_Inverse: v1 and v2 must be greater than 0" );
        }

        if ( p == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 0 );
        }
        else if ( p == static_cast< T >( 1 ) )
        {
            return inf;
        }

        for ( unsigned int i = 1; i < maxIter; i++ )
        {
            f  = F_CDF( x_cur, v1, v2 );
            df = std::max( F_PDF( x_cur, v1, v2 ), minDf );
            x_next = std::max( x_cur / static_cast< T >( 1.5 ), std::min( x_cur + ( p - f ) / df, x_cur * static_cast< T >( 1.5 ) ) );

            if ( std::fabs( f - p ) < min )
            {
                return x_next;
            }
            else
            {
                x_cur = x_next;
            }

        }

        throw std::runtime_error( "F_Inverse: failed to converge" );

        return static_cast< T >( 0 );
    }


    template< typename T >
    T F_PDF( const T x, const T n, const T m )
    {
        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_PDF: x must be greater than or equal to 0" );
        }

        if ( m <= static_cast< T >( 0 ) || n <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "F_PDF: m and n must be greater than 0" );
        }

        return std::pow( m, m / static_cast< T >( 2 ) ) * std::pow( n, n / static_cast< T >( 2 ) ) * std::pow( x, n / static_cast< T >( 2 ) - static_cast< T >( 1 ) )  /
               ( std::pow( m + n * x, ( m + n ) / static_cast< T >( 2 ) ) * Beta( n / static_cast< T >( 2 ), m / static_cast< T >( 2 ) ) );
    }


    template< typename T >
    T GammaCDF( const T x, const T a, const T b )
    {
        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaCDF: x must be greater than or equal to 0" );
        }

        if ( a <= static_cast< T >( 0 ) || b <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaCDF: a and b must be greater than 0" );
        }

        return GammaIncompleteP( x / b, a );
    }


    template< typename T >
    T GammaIncompleteP( const T x, const T a )
    {
        const T stop = static_cast< T >( 3e-7 );
        const T small = std::numeric_limits< T >::epsilon();
        const int maxIters = 5000;

        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaIncompleteP: x must be greater than or equal to 0" );
        }

        if ( a <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaIncompleteP: a must be greater than 0" );
        }

        if ( x == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 0 );
        }

        T ans     = static_cast< T >( 0 );
        T prevAns = static_cast< T >( 0 );

        if ( x < ( a + static_cast< T >( 1 ) ) )
        {
            T prevTerm = static_cast< T >( 1 ) / a;

            for ( int n = 0; n < maxIters + 1; n++ )
            {
                ans += prevTerm;
                prevTerm *= x / ( a + static_cast< T >( n + 1 ) );

                if ( std::abs( ans - prevAns ) <= stop )
                {
                    return std::exp( -x + a * std::log( x ) + std::log( ans ) - GammaLN( a ) );
                }
                else
                {
                    prevAns = ans;
                }
            }
        }
        else
        {
            T totalC  = static_cast< T >( 1 );
            T totalD  = x / ( x - a + static_cast< T >( 1 ) );
            T ans     = static_cast< T >( 1 ) / x;
            T prevAns = static_cast< T >( 0 );
            T d, g;

            for ( int i = 3; i <= maxIters; i++ )
            {
                ans *= totalC * totalD;

                if ( std::abs( ans - prevAns ) <= stop )
                {
                    return static_cast< T >( 1 ) - std::exp( -x + a * std::log( x ) - GammaLN( a ) + std::log( ans ) );
                }
                else
                {
                    if ( i % 2 == 0 )
                    {
                        d = static_cast< T >( i / 2.0 ) - a;
                        g = static_cast< T >( 1 );
                    }
                    else
                    {
                        d = static_cast< T >( i - 1 ) / static_cast< T >( 2.0 );
                        g = x;
                    }

                    totalC = g + d / totalC;
                    totalD = static_cast< T >( 1 ) / ( g + d * totalD );

                    if ( totalC <= static_cast< T >( 0 ) )
                    {
                        totalC = small;
                    }

                    if ( totalD <= static_cast< T >( 0 ) )
                    {
                        totalD = small;
                    }

                    prevAns = ans;
                }
            }
        }

        throw std::runtime_error( "GammaIncompleteP: failed to converge" );

        return static_cast< T >( 0 );
    }


    template< typename T >
    T GammaIncompleteQ( const T x, const T a )
    {
        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaIncompleteQ: x must be greater than or equal to 0" );
        }

        if ( a <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaIncompleteQ: a must be greater than 0" );
        }

        return static_cast< T >( 1 ) - GammaIncompleteP( x, a );
    }


    template< typename T >
    T GammaLN( const T z )
    {
        if ( z <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaLN: z must be greater than 0" );
        }

        const T gammaLnConstants[7] = { static_cast< T >( 1.000000000190015 ),
                                        static_cast< T >( 76.18009172947146 ),
                                        static_cast< T >( -86.50532032941677 ),
                                        static_cast< T >( 24.01409824083091 ),
                                        static_cast< T >( -1.231739572450155 ),
                                        static_cast< T >( 0.1208650973866179E-2 ),
                                        static_cast< T >( -0.5395239384953e-5 )
                                      };

        const T sqrtTwoPi = static_cast< T >( 2.506628274631000502415765284811 );
        const T inf = static_cast< T >( 1e30 );

        if ( z < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaLN: z must be greater than or equal to 0" );
        }

        if ( isZero( z ) )
        {
            return inf;
        }

        T sum = gammaLnConstants[0];

        for ( unsigned int i = 1; i < 7; i++ )
        {
            sum += gammaLnConstants[i] / ( z + static_cast< T >( i ) );
        }

        return static_cast< T >( ( z + 0.5 ) * std::log( z + 5.5 ) - ( z + 5.5 ) + std::log( sqrtTwoPi * sum / z ) );
    }


    template< typename T >
    T GammaPDF( const T x, const T a, const T b )
    {
        if ( x < static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaPDF: x must be greater than or equal to 0" );
        }

        if ( a <= static_cast< T >( 0 ) || b <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaPDF: a and b must be greater than 0" );
        }

        if ( a == static_cast< T >( 1 ) && x == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 1.0 / b );
        }

        return std::exp( ( a - static_cast< T >( 1 ) ) * std::log( x ) - x / b - GammaLN( a ) - a * std::log( b ) );
    }


    template< typename T >
    T GammaInverseCDF( const T p, const T a, const T b )
    {
        const T inf = static_cast< T >( 1e30 );
        const int maxIters = 5000;
        const T small = static_cast< T >( 1e-10 );
        const T min   = static_cast< T >( 1e-32 );
        const T newtonStepLimit = static_cast< T >( 10 );

        T x_cur = a;
        T x_next = static_cast< T >( 0 );
        T f = static_cast< T >( 1 );
        T df = static_cast< T >( 1 );

        if ( p < static_cast< T >( 0 ) || p > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "GammaInverseCDF: p must be in the range [0, 1]" );
        }

        if ( a <= static_cast< T >( 0 ) || b <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "GammaInverseCDF: a and b must be greater than 0" );
        }

        if ( p == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 0 );
        }
        else if ( p == static_cast< T >( 1 ) )
        {
            return inf;
        }

        for ( unsigned int i = 1; i < maxIters; i++ )
        {
            f  = GammaCDF( x_cur, a, static_cast< T >( 1 ) );
            df = std::max( GammaPDF( x_cur, a, static_cast< T >( 1 ) ), min );
            x_next = std::max( x_cur / newtonStepLimit, std::min( x_cur + ( p - f ) / df, x_cur * newtonStepLimit ) );

            if ( std::fabs( f - p ) < small )
            {
                return b * x_next;
            }
            else
            {
                x_cur = x_next;
            }
        }

        throw std::runtime_error( "GammaInverseCDF: failed to converge" );

        return static_cast< T >( 0 );
    }


    template< typename T >
    T NormalInverseCDF( const T p, const T mu, const T sigma )
    {
        if ( p < static_cast< T >( 0 ) || p > static_cast< T >( 1 ) )
        {
            throw std::invalid_argument( "NormalInverseCDF: p must be in the range [0, 1]" );
        }

        if ( sigma <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "NormalInverseCDF: sigma must be greater than 0" );
        }

        constexpr T a1 = static_cast< T >( -3.969683028665376e+01 );
        constexpr T a2 = static_cast< T >( 2.209460984245205e+02 );
        constexpr T a3 = static_cast< T >( -2.759285104469687e+02 );
        constexpr T a4 = static_cast< T >( 1.383577518672690e+02 );
        constexpr T a5 = static_cast< T >( -3.066479806614716e+01 );
        constexpr T a6 = static_cast< T >( 2.506628277459239e+00 );

        constexpr T b1 = static_cast< T >( -5.447609879822406e+01 );
        constexpr T b2 = static_cast< T >( 1.615858368580409e+02 );
        constexpr T b3 = static_cast< T >( -1.556989798598866e+02 );
        constexpr T b4 = static_cast< T >( 6.680131188771972e+01 );
        constexpr T b5 = static_cast< T >( -1.328068155288572e+01 );

        constexpr T c1 = static_cast< T >( -7.784894002430293e-03 );
        constexpr T c2 = static_cast< T >( -3.223964580411365e-01 );
        constexpr T c3 = static_cast< T >( -2.400758277161838e+00 );
        constexpr T c4 = static_cast< T >( -2.549732539343734e+00 );
        constexpr T c5 = static_cast< T >( 4.374664141464968e+00 );
        constexpr T c6 = static_cast< T >( 2.938163982698783e+00 );

        constexpr T d1 = static_cast< T >( 7.784695709041462e-03 );
        constexpr T d2 = static_cast< T >( 3.224671290700398e-01 );
        constexpr T d3 = static_cast< T >( 2.445134137142996e+00 );
        constexpr T d4 = static_cast< T >( 3.754408661907416e+00 );

        constexpr T p_low = static_cast< T >( 0.02425 );

        constexpr T p_high = static_cast< T >( 1 ) - p_low;

        T x, q, r, u, e;

        if ( p < p_low )
        {
            q = std::sqrt( -static_cast< T >( 2 ) * std::log( p ) );
            x = ( ( ( ( ( c1 * q + c2 ) * q + c3 ) * q + c4 ) * q + c5 ) * q + c6 ) /
                ( ( ( ( d1 * q + d2 ) * q + d3 ) * q + d4 ) * q + static_cast< T >( 1 ) );
        }
        else if ( p <= p_high )
        {
            q = p - static_cast< T >( 0.5 );
            r = q * q;
            x = ( ( ( ( ( a1 * r + a2 ) * r + a3 ) * r + a4 ) * r + a5 ) * r + a6 ) * q /
                ( ( ( ( ( b1 * r + b2 ) * r + b3 ) * r + b4 ) * r + b5 ) * r + static_cast< T >( 1 ) );
        }
        else
        {
            q = std::sqrt( -static_cast< T >( 2 ) * std::log( static_cast< T >( 1 ) - p ) );
            x = - ( ( ( ( ( c1 * q + c2 ) * q + c3 ) * q + c4 ) * q + c5 ) * q + c6 ) /
                ( ( ( ( d1 * q + d2 ) * q + d3 ) * q + d4 ) * q + static_cast< T >( 1 ) );
        }

        if ( p > static_cast< T >( 0 ) && p < static_cast< T >( 1 ) )
        {
            e = static_cast< T >( 0.5 ) * ErrorFunctionComplement( -x / std::sqrt( static_cast< T >( 2 ) ) - p );
            u = e * std::sqrt( static_cast< T >( 2.0 * Constants::PI ) * std::exp( x * x / static_cast< T >( 2 ) ) );
            x -= u / ( static_cast< T >( 1 ) + x * u / static_cast< T >( 2 ) );
        }

        return mu + sigma * x;
    }


    template< typename T >
    T NormalCDF( const T x, const T mu, const T sigma )
    {
        if ( sigma <= static_cast< T >( 0 ) )
        {
            throw std::invalid_argument( "NormalCDF: sigma must be greater than 0" );
        }

        return static_cast< T >( 0.5 ) * ( static_cast< T >( 1 ) + ErrorFunction( ( x - mu ) / ( sigma * std::sqrt( static_cast< T >( 2 ) ) ) ) );
    }


} // namespace myMath


#endif // MYMATH_STAT_H