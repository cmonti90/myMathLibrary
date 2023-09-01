#pragma once

#ifndef E19DE42F_624A_4EBF_8117_D3009272C05E
#define E19DE42F_624A_4EBF_8117_D3009272C05E

#include "BasicFunctions.h"
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <cstring>

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
        Vector(const std::initializer_list<T> &x);
        ~Vector() = default;

        T &operator[](const unsigned int i);
        const T &operator[](const unsigned int i) const;

        Vector<T, R> &operator=(const T &x);
        Vector<T, R> &operator=(const T (&x)[R]);
        Vector<T, R> &operator=(const Vector<T, R> &obj);
        Vector<T, R> &operator=(const std::initializer_list<T> &x);

        Vector<T, R> operator+(const Vector<T, R> &obj) const;
        Vector<T, R> operator-(const Vector<T, R> &obj) const;
        Vector<T, R> operator*(const double &x) const;
        Vector<T, R> operator/(const double &x) const;

        Vector<T, R> &operator+=(const Vector<T, R> &obj);
        Vector<T, R> &operator-=(const Vector<T, R> &obj);
        Vector<T, R> &operator*=(const double &x);
        Vector<T, R> &operator/=(const double &x);

        Vector<T, R> operator-(void) const;

        bool operator==(const Vector<T, R> &obj) const;
        bool operator!=(const Vector<T, R> &obj) const;

        T Magnitude(void) const;
        void Normalize(void);
    };

    typedef Vector<double, 2u> Vector2d;
    typedef Vector<double, 3u> Vector3d;
    typedef Vector<double, 4u> Vector4d;

    template <class T, unsigned int R>
    Vector<T, R>::Vector()
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = static_cast<T>(0.0);
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const T &x)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = x;
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const T (&x)[R])
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = x[i];
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const Vector<T, R> &obj)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = obj.vec[i];
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const std::initializer_list<T> &x)
    {
        if (static_cast<unsigned int>(x.size()) == 1u)
        {
            std::memset(this->vec, *(x.begin()), sizeof(this->vec));
        }
        else if (static_cast<unsigned int>(x.size()) != R)
        {
            throw std::invalid_argument("Initializer list has incorrect size of " + std::to_string(x.size()) + " instead of " + std::to_string(R) + "");
        }
        else if (x.size() == 0)
        {
            throw std::invalid_argument("Initializer list is empty");
        }

        std::copy(x.begin(), x.end(), this->vec);
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
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const T (&x)[R])
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = x[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const Vector<T, R> &obj)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] = obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const std::initializer_list<T> &x)
    {
        if (static_cast<unsigned int>(x.size()) == 1u)
        {
            std::memset(this->vec, *(x.begin()), sizeof(this->vec));
        }
        else if (static_cast<unsigned int>(x.size()) != R)
        {
            throw std::invalid_argument("Initializer list has incorrect size of " + std::to_string(x.size()) + " instead of " + std::to_string(R) + "");
        }

        std::copy(x.begin(), x.end(), this->vec);

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator+(const Vector<T, R> &obj) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp.vec[i] += obj.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator-(const Vector<T, R> &obj) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp.vec[i] -= obj.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator*(const double &x) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator/(const double &x) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp.vec[i] /= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator+=(const Vector<T, R> &obj)
    {

        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] += obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator-=(const Vector<T, R> &obj)
    {

        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] -= obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator*=(const double &x)
    {

        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] *= x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator/=(const double &x)
    {

        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] /= x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator-(void) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp.vec[i] = -tmp.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    bool Vector<T, R>::operator==(const Vector<T, R> &obj) const
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            if (this->vec[i] != obj.vec[i])
            {
                return false;
            }
        }

        return true;
    }

    template <class T, unsigned int R>
    bool Vector<T, R>::operator!=(const Vector<T, R> &obj) const
    {
        bool tmp{false};

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp = tmp || (this->vec[i] != obj.vec[i]);
        }

        return tmp;
    }

    template <class T, unsigned int C>
    Vector<T, C> operator*(const double &x, const Vector<T, C> &obj)
    {
        Vector<T, C> tmp{obj};

        for (unsigned int i{0u}; i < C; i++)
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    T Vector<T, R>::Magnitude(void) const
    {
        T tmp = static_cast<T>(0.0);

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp = SQ(this->vec[i]);
        }

        return static_cast<T>(std::sqrt(tmp));
    }

    template <class T, unsigned int R>
    void Vector<T, R>::Normalize(void)
    {
        T mag{this->Magnitude()};

        if (mag == static_cast<T>(0.0))
        {
            throw std::runtime_error("Cannot normalize a vector with magnitude of 0");
        }

        for (unsigned int i{0u}; i < R; i++)
        {
            this->vec[i] /= mag;
        }
    }
}

#endif /* E19DE42F_624A_4EBF_8117_D3009272C05E */
