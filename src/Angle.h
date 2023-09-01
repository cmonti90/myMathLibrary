#ifndef B4D2FB34_E82B_4930_84AF_12D1E557452E
#define B4D2FB34_E82B_4930_84AF_12D1E557452E

#include "Vector.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    enum class EulerOrder : unsigned int
    {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX,

    };

    enum class TaitBryanOrder : unsigned int
    {
        XYX,
        XZX,
        YXY,
        YZY,
        ZXZ,
        ZYZ
    };

    enum Axis : unsigned int
    {
        ROLL,
        PITCH,
        YAW
    };

    template <typename T>
    class DCM;

    template <typename T>
    class Quaternion;

    template <typename T>
    class Angle : public Vector<T, 3u>
    {
        Angle();
        Angle(const T (&x)[3u]);
        Angle(const Vector<T, 3u> &obj);

        Angle<T> operator=(const Angle<T> &obj);
        Angle<T> operator=(const T (&x)[3u]);

        Angle<T> operator+(const Angle<T> &obj) const;
        Angle<T> operator-(const Angle<T> &obj) const;
        Angle<T> operator*(const double &x) const;
        Angle<T> operator/(const double &x) const;

        Angle<T> &operator+=(const Angle<T> &obj);
        Angle<T> &operator-=(const Angle<T> &obj);
        Angle<T> &operator*=(const double &x);
        Angle<T> &operator/=(const double &x);

        Angle<T> operator-(void) const;

        bool operator==(const Angle<T> &obj) const;
        bool operator!=(const Angle<T> &obj) const;

        void Normalize();
        DCM<T> ToDCM(const EulerOrder &rotOrder) const;
        DCM<T> ToDCM(const TaitBryanOrder &rotOrder) const;
        Quaternion<T> ToQuaternion(const EulerOrder &rotOrder) const;
        Quaternion<T> ToQuaternion(const TaitBryanOrder &rotOrder) const;
    };
} // namespace myMath

#include "DCM.h"
#include "Quaternion.h"

namespace myMath
{
    template <typename T>
    Angle<T>::Angle() : Vector<T, 3u>(static_cast<T>(0.0))
    {
    }

    template <typename T>
    Angle<T>::Angle(const T (&x)[3u]) : Vector<T, 3u>(x)
    {
    }

    template <typename T>
    Angle<T>::Angle(const Vector<T, 3u> &obj) : Vector<T, 3u>(obj)
    {
    }

    template <typename T>
    Angle<T> Angle<T>::operator=(const Angle<T> &obj)
    {
        Vector<T, 3u>::operator=(obj);
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator=(const T (&x)[3u])
    {
        Vector<T, 3u>::operator=(x);
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator+(const Angle<T> &obj) const
    {
        return Angle<T>(Vector<T, 3u>::operator+(obj));
    }

    template <typename T>
    Angle<T> Angle<T>::operator-(const Angle<T> &obj) const
    {
        return Angle<T>(Vector<T, 3u>::operator-(obj));
    }

    template <typename T>
    Angle<T> Angle<T>::operator*(const double &x) const
    {
        return Angle<T>(Vector<T, 3u>::operator*(x));
    }

    template <typename T>
    Angle<T> Angle<T>::operator/(const double &x) const
    {
        return Angle<T>(Vector<T, 3u>::operator/(x));
    }

    template <typename T>
    Angle<T> &Angle<T>::operator+=(const Angle<T> &obj)
    {
        Vector<T, 3u>::operator+=(obj);
        return *this;
    }

    template <typename T>
    Angle<T> &Angle<T>::operator-=(const Angle<T> &obj)
    {
        Vector<T, 3u>::operator-=(obj);
        return *this;
    }

    template <typename T>
    Angle<T> &Angle<T>::operator*=(const double &x)
    {
        Vector<T, 3u>::operator*=(x);
        return *this;
    }

    template <typename T>
    Angle<T> &Angle<T>::operator/=(const double &x)
    {
        Vector<T, 3u>::operator/=(x);
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator-(void) const
    {
        return static_cast<T>(-1) * (*this);
    }

    template <typename T>
    bool Angle<T>::operator==(const Angle<T> &obj) const
    {
        return Vector<T, 3u>::operator==(obj);
    }

    template <typename T>
    bool Angle<T>::operator!=(const Angle<T> &obj) const
    {
        return Vector<T, 3u>::operator!=(obj);
    }

    template <typename T>
    void Angle<T>::Normalize()
    {
        for (unsigned int i{0u}; i < 3u; i++)
        {
            this->vec[i] = fmod(this->vec[i], static_cast<T>(2.0 * M_PI));
        }
    }

    template <typename T>
    DCM<T> Angle<T>::ToDCM(const EulerOrder &rotOrder) const
    {
        DCM<T> tmp;

        switch (rotOrder)
        {
        case EulerOrder::XYZ:
        {
            tmp[0][0] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = -std::sin(this->vec[1]);
            tmp[1][0] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[0]) * std::cos(this->vec[1]);
            tmp[2][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[2][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case EulerOrder::XZY:
        {
            tmp[0][0] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[0][1] = -std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = std::sin(this->vec[1]);
            tmp[1][0] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][1] = -std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][2] = -std::sin(this->vec[0]) * std::cos(this->vec[1]);
            tmp[2][0] = -std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[2][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case EulerOrder::YXZ:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = -std::sin(this->vec[0]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][1] = -std::sin(this->vec[1]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case EulerOrder::YZX:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::sin(this->vec[0]) * std::cos(this->vec[1]);
            tmp[0][2] = std::cos(this->vec[0]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][0] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][2] = -std::sin(this->vec[1]);
            tmp[2][0] = -std::sin(this->vec[0]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case EulerOrder::ZXY:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]);
            tmp[0][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[0][2] = std::cos(this->vec[1]) * std::sin(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][0] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][2] = -std::sin(this->vec[1]);
            tmp[2][0] = -std::sin(this->vec[0]) * std::cos(this->vec[1]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[2][2] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);

            break;
        }
        case EulerOrder::ZYX:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]);
            tmp[0][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[0][2] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][0] = std::sin(this->vec[0]) * std::cos(this->vec[1]);
            tmp[1][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[2][0] = -std::sin(this->vec[1]);
            tmp[2][1] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[1]) * std::cos(this->vec[2]);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }

        return tmp;
    }

    template <typename T>
    DCM<T> Angle<T>::ToDCM(const TaitBryanOrder &rotOrder) const
    {
        DCM<T> tmp;

        switch (rotOrder)
        {
        case TaitBryanOrder::XYX:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[0][2] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][0] = std::sin(this->vec[0]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][0] = -std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[1]);

            break;
        }
        case TaitBryanOrder::XZX:
        {
            tmp[0][0] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[0][1] = std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[0][2] = -std::sin(this->vec[2]);
            tmp[1][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[1]) * std::sin(this->vec[0]);
            tmp[2][0] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[1]) * std::cos(this->vec[0]);

            break;
        }
        case TaitBryanOrder::YXY:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = std::sin(this->vec[0]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][0] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][2] = -std::sin(this->vec[1]);
            tmp[2][0] = -std::cos(this->vec[0]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case TaitBryanOrder::YZY:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][1] = std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][2] = -std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][0] = -std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][1] = -std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][2] = std::cos(this->vec[1]);

            break;
        }
        case TaitBryanOrder::ZXZ:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[0][2] = -std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[1][0] = std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][1] = std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][0] = std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[1]);

            break;
        }
        case TaitBryanOrder::ZYZ:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][2] = -std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][0] = std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[2][0] = std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[1]);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Tait-Bryan Order");
        }
        }
    }

    template <typename T>
    Quaternion<T> Angle<T>::ToQuaternion(const EulerOrder &rotOrder) const
    {
        Quaternion<T> tmp;

        switch (rotOrder)
        {
        case EulerOrder::XYZ:
        {
            tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

            break;
        }
        case EulerOrder::XZY:
        {
            tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

            break;
        }
        case EulerOrder::YXZ:
        {
            tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

            break;
        }
        case EulerOrder::YZX:
        {
            tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

            break;
        }
        case EulerOrder::ZXY:
        {
            tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

            break;
        }
        case EulerOrder::ZYX:
        {
            tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
            tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }
    }

    template <typename T>
    Quaternion<T> Angle<T>::ToQuaternion(const TaitBryanOrder &rotOrder) const
    {
        Quaternion<T> tmp;

        switch (rotOrder)
        {
            case TaitBryanOrder::XYX:
            {
                tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

                break;
            }
            case TaitBryanOrder::XZX:
            {
                tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[1] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::cos(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);
                tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

                break;
            }
            case TaitBryanOrder::YXY:
            {
                tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[1] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[2] / 2.0);
                tmp[2] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::cos(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);

                break;
            }
            case TaitBryanOrder::YZY:
            {
                tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[1] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[2] / 2.0);
                tmp[2] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::cos(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);

                break;
            }
            case TaitBryanOrder::ZXZ:
            {
                tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[1] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::cos(this->vec[2] / 2.0);
                tmp[2] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);
                tmp[3] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0);

                break;
            }
            case TaitBryanOrder::ZYZ:
            {
                tmp[0] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) + std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[1] = std::cos(this->vec[0] / 2.0) * std::sin(this->vec[1] / 2.0) * std::cos(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::cos(this->vec[2] / 2.0);
                tmp[2] = std::sin(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) + std::cos(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);
                tmp[3] = std::cos(this->vec[0] / 2.0) * std::cos(this->vec[1] / 2.0) * std::sin(this->vec[2] / 2.0) - std::sin(this->vec[0] / 2.0) * std::sin(this->vec[2] / 2.0);

                break;
            }
            default:
            {
                throw std::invalid_argument("Invalid Tait-Bryan Order");
            }
        }
    }

} // namespace myMath

#endif /* B4D2FB34_E82B_4930_84AF_12D1E557452E */
