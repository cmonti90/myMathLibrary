#ifndef CE567BC9_6D10_45E7_9AE9_CC170D04C3B9
#define CE567BC9_6D10_45E7_9AE9_CC170D04C3B9

#include "BasicFunctions.h"
#include <cmath>

namespace myMath
{
    template <class T>
    class Complex
    {
    public:
        T vec[2];

        Complex();
        Complex(const T &x);
        Complex(const T (&x)[2]);
        Complex(const Complex<T> &obj);
        ~Complex() = default;

        T &operator[](const unsigned int i);
        const T &operator[](const unsigned int i) const;

        Complex<T> &operator=(const T &x);
        Complex<T> &operator=(const T (&x)[2]);
        Complex<T> &operator=(const Complex<T> &obj);

        Complex<T> operator+(const Complex<T> &obj) const;
        Complex<T> operator-(const Complex<T> &obj) const;
        Complex<T> operator*(const Complex<T> &obj) const;
        Complex<T> operator/(const Complex<T> &obj) const;
        Complex<T> operator*(const double &x) const;
        Complex<T> operator/(const double &x) const;

        Complex<T> &operator+=(const Complex<T> &obj);
        Complex<T> &operator-=(const Complex<T> &obj);
        Complex<T> &operator*=(const double &x);
        Complex<T> &operator/=(const double &x);

        T Magnitude(void) const;
        T Angle(void) const;
    };

    template <class T>
    Complex<T>::Complex()
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = static_cast<T>(0.0);
        }
    }

    template <class T>
    Complex<T>::Complex(const T &x)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = x;
        }
    }

    template <class T>
    Complex<T>::Complex(const T (&x)[2])
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = x[i];
        }
    }

    template <class T>
    Complex<T>::Complex(const Complex<T> &obj)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = obj.vec[i];
        }
    }

    template <class T>
    T &Complex<T>::operator[](const unsigned int i)
    {
        return this->vec[i];
    }

    template <class T>
    const T &Complex<T>::operator[](const unsigned int i) const
    {
        return this->vec[i];
    }

    template <class T>
    Complex<T> &Complex<T>::operator=(const T &x)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = x;
        }

        return *this;
    }

    template <class T>
    Complex<T> &Complex<T>::operator=(const T (&x)[2])
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = x[i];
        }

        return *this;
    }

    template <class T>
    Complex<T> &Complex<T>::operator=(const Complex<T> &obj)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] = obj.vec[i];
        }

        return *this;
    }

    template <class T>
    Complex<T> Complex<T>::operator+(const Complex<T> &obj) const
    {
        Complex<T> temp;

        for (unsigned int i{0u}; i < 2u; i++)
        {
            temp.vec[i] = this->vec[i] + obj.vec[i];
        }

        return temp;
    }

    template <class T>
    Complex<T> Complex<T>::operator-(const Complex<T> &obj) const
    {
        Complex<T> temp;

        for (unsigned int i{0u}; i < 2u; i++)
        {
            temp.vec[i] = this->vec[i] - obj.vec[i];
        }

        return temp;
    }

    template <class T>
    Complex<T> Complex<T>::operator*(const Complex<T> &obj) const
    {
        Complex<T> temp;

        temp.vec[0] = this->vec[0] * obj.vec[0] - this->vec[1] * obj.vec[1];
        temp.vec[1] = this->vec[0] * obj.vec[1] + this->vec[1] * obj.vec[0];

        return temp;
    }

    template <class T>
    Complex<T> Complex<T>::operator*(const double &x) const
    {
        Complex<T> temp;

        for (unsigned int i{0u}; i < 2u; i++)
        {
            temp.vec[i] = this->vec[i] * x;
        }

        return temp;
    }

    template <class T>
    Complex<T> Complex<T>::operator/(const Complex<T> &obj) const
    {
        Complex<T> temp;

        temp.vec[0] = (this->vec[0] * obj.vec[0] + this->vec[1] * obj.vec[1]) / (obj.vec[0] * obj.vec[0] + obj.vec[1] * obj.vec[1]);
        temp.vec[1] = (this->vec[1] * obj.vec[0] - this->vec[0] * obj.vec[1]) / (obj.vec[0] * obj.vec[0] + obj.vec[1] * obj.vec[1]);

        return temp;
    }

    template <class T>
    Complex<T> Complex<T>::operator/(const double &x) const
    {
        Complex<T> temp;

        for (unsigned int i{0u}; i < 2u; i++)
        {
            temp.vec[i] = this->vec[i] / x;
        }

        return temp;
    }

    template <class T>
    Complex<T> &Complex<T>::operator+=(const Complex<T> &obj)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] += obj.vec[i];
        }

        return *this;
    }

    template <class T>
    Complex<T> &Complex<T>::operator-=(const Complex<T> &obj)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] -= obj.vec[i];
        }

        return *this;
    }

    template <class T>
    Complex<T> &Complex<T>::operator*=(const double &x)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] *= x;
        }

        return *this;
    }

    template <class T>
    Complex<T> &Complex<T>::operator/=(const double &x)
    {
        for (unsigned int i{0u}; i < 2u; i++)
        {
            this->vec[i] /= x;
        }

        return *this;
    }

    template <class T>
    T Complex<T>::Magnitude(void) const
    {
        return static_cast<T>(std::sqrt(myMath::SQ(this->vec[0]) + myMath::SQ(this->vec[1])));
    }

    template <class T>
    T Complex<T>::Angle(void) const
    {
        return static_cast<T>(std::atan2(this->vec[1], this->vec[0]));
    }
}

#endif /* CE567BC9_6D10_45E7_9AE9_CC170D04C3B9 */
