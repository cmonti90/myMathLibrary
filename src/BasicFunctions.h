#ifndef D01103EE_17E6_4BA7_9F31_064A6885444F
#define D01103EE_17E6_4BA7_9F31_064A6885444F

namespace myMath
{
    /////////////////////////////////
    //         DECLARATIONS        //
    /////////////////////////////////
    unsigned int factorial(const unsigned int x);
    int factorial(const int x);

    template <typename T>
    T ABS(const T x);

    template <typename T>
    T SQ(const T x);

    template <typename T>
    T SIGN(const T x);

    template <typename T>
    T MAX(const T x, const T y);

    template <typename T>
    T MIN(const T x, const T y);


    /////////////////////////////////
    //         DEFINITIONS         //
    /////////////////////////////////
    inline unsigned int factorial(const unsigned int x)
    {
        unsigned int tmp{1u};

        if (x == 0u || x == 1u)
        {
            return 1u;
        }

        for (unsigned int i{2u}; i <= x; i++)
        {
            tmp *= i;
        }

        return tmp;
    }

    inline int factorial(const int x)
    {
        int x_new = x < 0 ? (-1 * static_cast<int>(factorial(static_cast<unsigned int>(x)))) : (static_cast<int>(factorial(static_cast<unsigned int>(x))));

        return x_new;
    }

    template <typename T>
    inline T ABS(const T x)
    {
        return (x < static_cast<T>(0.0) ? (static_cast<T>(-1.0) * x) : (x));
    }

    template <typename T>
    inline T SQ(const T x)
    {
        return (x * x);
    }

    template <typename T>
    inline T SIGN(const T x)
    {
        if (x == static_cast<T>(0.0))
        {
            return static_cast<T>(0.0);
        }
        
        return (x < static_cast<T>(0.0) ? (static_cast<T>(-1.0)) : (static_cast<T>(1.0)));
    }

    template <typename T>
    inline T MAX(const T x, const T y)
    {
        return (x > y ? x : y);
    }

    template <typename T>
    inline T MIN(const T x, const T y)
    {
        return (x < y ? x : y);
    }
}

#endif /* D01103EE_17E6_4BA7_9F31_064A6885444F */
