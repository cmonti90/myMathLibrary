#ifndef MYMATH_DISTRIBUTION_H
#define MYMATH_DISTRIBUTION_H

#include <list>

namespace myMath
{
    template < class T, class T2 = double >
    class NormalDistribution
    {
      public:
        NormalDistribution();
        NormalDistribution( const std::list< T >& data );
        NormalDistribution( const NormalDistribution< T, T2 >& obj );

        ~NormalDistribution() = default;

        NormalDistribution< T, T2 >& operator=( const std::list< T >& data );
        NormalDistribution< T, T2 >& operator=( const NormalDistribution< T, T2 >& obj );

        T getMean( void ) const;
        T getVariance( void ) const;
        T getStandardDeviation( void ) const;

        void AddData( const T& data );
        void AddData( const std::list< T >& data );

        template < class T3 >
        void AddData( const NormalDistribution< T, T3 >& obj );

        void ClearData( void );

      private:
        std::list< T > data_;

        T2 mean_;
        T2 variance_;

    }; // class NormalDistribution

    template< class T, class T2 >
    NormalDistribution< T, T2 >::NormalDistribution()
    : data_()
    , mean_( static_cast< T2 >( 0 ) )
    , variance_( static_cast< T2 >( 0 ) )
    {
    }


    template< class T, class T2 >
    NormalDistribution< T, T2 >::NormalDistribution( const std::list< T >& data )
    : data_( data )
    {
    }


    template< class T, class T2 >
    NormalDistribution< T, T2 >::NormalDistribution( const NormalDistribution< T, T2 >& obj )
    : data_( obj.data )
    {
    }


    template< class T, class T2 >
    NormalDistribution< T, T2 >& NormalDistribution< T, T2 >::operator=( const std::list< T >& data )
    {
        this->data_ = data;
        return *this;
    }


    template< class T, class T2 >
    NormalDistribution< T, T2 >& NormalDistribution< T, T2 >::operator=( const NormalDistribution< T, T2 >& obj )
    {
        this->data_ = obj.data_;
        return *this;
    }


    template< class T, class T2 >
    T NormalDistribution< T, T2 >::getMean( void ) const
    {
        return mean_;
    }


    template< class T, class T2 >
    T NormalDistribution< T, T2 >::getVariance( void ) const
    {
        return variance_;
    }


    template< class T, class T2 >
    T NormalDistribution< T, T2 >::getStandardDeviation( void ) const
    {
        return std::sqrt( variance_ );
    }


    template< class T, class T2 >
    void NormalDistribution< T, T2 >::AddData( const T& data )
    {
        data_.push_back( data );

        // Update mean and variance fast method
        const T2 oldMean = mean_;
        mean_     = ( ( data_.size() - 1 ) * oldMean + data ) / data_.size();
        variance_ = ( ( data_.size() - 1 ) * variance_ + ( data - oldMean ) * ( data - oldMean ) ) / data_.size();
    }


    template< class T, class T2 >
    void NormalDistribution< T, T2 >::AddData( const std::list< T >& data )
    {
        for ( const T& d : data )
        {
            AddData( d );
        }
    }


    template< class T, class T2 >
    template< class T3 >
    void NormalDistribution< T, T2 >::AddData( const NormalDistribution< T, T3 >& obj )
    {
        for ( const T& d : obj.data_ )
        {
            AddData( d );
        }
    }


    template< class T, class T2 >
    void NormalDistribution< T, T2 >::ClearData( void )
    {
        data_.clear();
        mean_     = static_cast< T2 >( 0 );
        variance_ = static_cast< T2 >( 0 );
    }

} // namespace myMath


#endif // MYMATH_DISTRIBUTION_H