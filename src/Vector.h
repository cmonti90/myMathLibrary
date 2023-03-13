#pragma once

#ifndef E19DE42F_624A_4EBF_8117_D3009272C05E
#define E19DE42F_624A_4EBF_8117_D3009272C05E

#include "BasicFunctions.h"

namespace myMath
{
    template <class T, unsigned int R>
    class Vector
    {
    public:
        T vec[R];

        Vector();
        Vector(const T &x);
        Vector(const T (&x)[R]);
        Vector(const Vector<T, R> &obj);
        ~Vector() = default;

        T &operator[](const unsigned int i);
        const T &operator[](const unsigned int i) const;

        Vector<T, R> &operator=(const T &x);
        Vector<T, R> &operator=(const T (&x)[R]);
        Vector<T, R> &operator=(const Vector<T, R> &obj);

        Vector<T, R> operator+(const Vector<T, R> &obj) const;
        Vector<T, R> operator-(const Vector<T, R> &obj) const;
        Vector<T, R> operator*(const double &x) const;
        Vector<T, R> operator/(const double &x) const;

        Vector<T, R> &operator+=(const Vector<T, R> &obj);
        Vector<T, R> &operator-=(const Vector<T, R> &obj);
        Vector<T, R> &operator*=(const double &x);
        Vector<T, R> &operator/=(const double &x);

        T Magnitude(void) const;
        // T dot(const Vector<T, R> &obj) const;
        // Vector<T, R> cross(const Vector<T, R> &obj) const;
    };

    typedef Vector<double, 2u> Vector2d;
    typedef Vector<double, 3u> Vector3d;
    typedef Vector<double, 4u> Vector4d;
    

    template <class T, unsigned int R>
    Vector<T, R>::Vector()
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = 0.0;
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const T &x)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x;
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const T (&x)[R])
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x[i];
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const Vector<T, R> &obj)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = obj.vec[i];
        }
    }

    template <class T, unsigned int R>
    T &Vector<T, R>::operator[](const unsigned int i)
    {
        return this->vec[i];
    }
    
    template <class T, unsigned int R>
    const T &Vector<T, R>::operator[](const unsigned int i) const
    {
        return this->vec[i];
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const T &x)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const T (&x)[R])
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const Vector<T, R> &obj)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator+(const Vector<T, R> &obj) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] += obj.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator-(const Vector<T, R> &obj) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] -= obj.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator*(const double &x) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator/(const double &x) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] /= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator+=(const Vector<T, R> &obj)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] += obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator-=(const Vector<T, R> &obj)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] -= obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator*=(const double &x)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] *= x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator/=(const double &x)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] /= x;
        }

        return *this;
    }

    template <class T, unsigned int C>
    Vector<T, C> operator*(const double &x, const Vector<T, C> &obj)
    {
        Vector<T, C> tmp{obj};

        for (unsigned int i{0}; i < C; i++)
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    T Vector<T, R>::Magnitude(void) const
    {
        T tmp = static_cast<T>(0.0);

        for (unsigned int i{0}; i < R; i++)
        {
            tmp += SQ(this->vec[i], 2);
        }
    }

    // template <class T, unsigned int R>
    // T Vector<T, R>::dot(const Vector<T, R> &obj) const
    // {
    //     T prod{static_cast<T>(0.0)};

    //     for (unsigned int i{0}; i < R; i++)
    //     {
    //         prod += this->vec[i] * obj.vec[i];
    //     }

    //     return prod;
    // }

    // template <class T, unsigned int R>
    // Vector<T, R> Vector<T, R>::cross(const Vector<T, R> &obj) const
    // {
    //     if (R == 3u)
    //     {
    //         Vector<double, 3u> prod{0.0};
    //         Matrix3d concat{0.0};

    //         for (unsigned int i{0}; i < 3u; i++)
    //         {
    //             concat.mat[0][i] = (2 * ((i + 2) % 2 == 0) - 1);
    //             concat.mat[1][i] = this->vec[i];
    //             concat.mat[2][i] = obj.vec[i];
    //         }

    //         for (unsigned int i{0}; i < 3u; i++)
    //         {
    //             prod.vec[i] = concat.Minor(0, i);
    //         }

    //         return prod;
    //     }
    //     else
    //     {
    //         Vector<T, R> tmp{0.0};

    //         return tmp;
    //     }
    // }
}

#endif /* E19DE42F_624A_4EBF_8117_D3009272C05E */
