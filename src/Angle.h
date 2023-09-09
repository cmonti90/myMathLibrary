#ifndef B4D2FB34_E82B_4930_84AF_12D1E557452E
#define B4D2FB34_E82B_4930_84AF_12D1E557452E

#include "BasicFunctions.h"
#include "Rotation.h"
#include "Vector.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    template <typename T>
    class DCM;

    template <typename T>
    class Quaternion;

    template <typename T>
    class Angle : public Vector<T, 3u>
    {
    public:
        Angle();
        Angle(const T x);
        Angle(const T (&x)[3u]);
        Angle(const Vector<T, 3u> &obj);
        Angle(const Angle<T> &obj);

        virtual ~Angle();

        Angle<T> operator=(const T x);
        Angle<T> operator=(const T (&x)[3u]);
        Angle<T> operator=(const Vector<T, 3u> &obj);
        Angle<T> operator=(const Angle<T> &obj);

        Angle<T> operator+(const Angle<T> &obj) const;
        Angle<T> operator-(const Angle<T> &obj) const;
        Angle<T> operator*(const T x) const;
        Angle<T> operator/(const T x) const;

        Angle<T> &operator+=(const Angle<T> &obj);
        Angle<T> &operator-=(const Angle<T> &obj);
        Angle<T> &operator*=(const T x);
        Angle<T> &operator/=(const T x);

        Angle<T> operator-(void) const;

        bool operator==(const Angle<T> &obj) const;
        bool operator!=(const Angle<T> &obj) const;

        void Normalize();

        DCM<T> ToDCM(const TaitBryanOrder &rotOrder) const;
        DCM<T> ToDCM(const EulerOrder &rotOrder) const;

        Quaternion<T> ToQuaternion(const TaitBryanOrder &rotOrder) const;
        Quaternion<T> ToQuaternion(const EulerOrder &rotOrder) const;

        Angle<T> Rotate(const TaitBryanOrder &rotOrder, const Angle<T> &ang, const TaitBryanOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const;
        Angle<T> Rotate(const TaitBryanOrder &rotOrder, const Angle<T> &ang, const EulerOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const;
        Angle<T> Rotate(const EulerOrder &rotOrder, const Angle<T> &ang, const TaitBryanOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const;
        Angle<T> Rotate(const EulerOrder &rotOrder, const Angle<T> &ang, const EulerOrder &rotOrder2, const EulerOrder &rotOrderOut) const;
        Angle<T> Rotate(const EulerOrder &rotOrder, const Angle<T> &ang, const EulerOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const;

        Vector<T, 3u> Rotate(const TaitBryanOrder &rotOrder, const Vector<T, 3u> &vec) const;
        Vector<T, 3u> Rotate(const EulerOrder &rotOrder, const Vector<T, 3u> &vec) const;
        DCM<T> Rotate(const TaitBryanOrder &rotOrder, const DCM<T> &dcm) const;
        DCM<T> Rotate(const EulerOrder &rotOrder, const DCM<T> &dcm) const;
        Quaternion<T> Rotate(const TaitBryanOrder &rotOrder, const Quaternion<T> &q) const;
        Quaternion<T> Rotate(const EulerOrder &rotOrder, const Quaternion<T> &q) const;

        void wrapAnglesZeroToTwoPi(const Axis ax = Axis::ALL);
        void wrapAnglesMinusPiToPi(const Axis ax = Axis::ALL);
    };
} // namespace myMath

#include "DCM.h"
#include "Quaternion.h"

namespace myMath
{
    typedef Angle<double> AngleD;
    typedef Angle<float> AngleF;

    template <typename T>
    Angle<T>::Angle() : Vector<T, 3u>(static_cast<T>(0.0))
    {
    }

    template <typename T>
    Angle<T>::Angle(const T x) : Vector<T, 3u>(x)
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
    Angle<T>::Angle(const Angle<T> &ang) : Vector<T, 3u>(static_cast<Vector<T, 3u>>(static_cast<Vector<T, 3u>>(ang)))
    {
    }

    template <typename T>
    Angle<T>::~Angle()
    {
    }

    template <typename T>
    Angle<T> Angle<T>::operator=(const T x)
    {
        Vector<T, 3u>::operator=(x);
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator=(const T (&x)[3u])
    {
        Vector<T, 3u>::operator=(x);
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator=(const Vector<T, 3u> &obj)
    {
        Vector<T, 3u>::operator=(obj);
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator=(const Angle<T> &obj)
    {
        Vector<T, 3u>::operator=(static_cast<Vector<T, 3u>>(obj));
        return *this;
    }

    template <typename T>
    Angle<T> Angle<T>::operator+(const Angle<T> &obj) const
    {
        return Angle<T>(Vector<T, 3u>::operator+(static_cast<Vector<T, 3u>>(obj)));
    }

    template <typename T>
    Angle<T> Angle<T>::operator-(const Angle<T> &obj) const
    {
        return Angle<T>(Vector<T, 3u>::operator-(obj));
    }

    template <typename T>
    Angle<T> Angle<T>::operator*(const T x) const
    {
        return Angle<T>(Vector<T, 3u>::operator*(x));
    }

    template <typename T>
    Angle<T> Angle<T>::operator/(const T x) const
    {
        return Angle<T>(Vector<T, 3u>::operator/(x));
    }

    template <typename T>
    Angle<T> &Angle<T>::operator+=(const Angle<T> &obj)
    {
        Vector<T, 3u>::operator+=(static_cast<Vector<T, 3u>>(obj));
        return *this;
    }

    template <typename T>
    Angle<T> &Angle<T>::operator-=(const Angle<T> &obj)
    {
        Vector<T, 3u>::operator-=(static_cast<Vector<T, 3u>>(obj));
        return *this;
    }

    template <typename T>
    Angle<T> &Angle<T>::operator*=(const T x)
    {
        Vector<T, 3u>::operator*=(x);
        return *this;
    }

    template <typename T>
    Angle<T> &Angle<T>::operator/=(const T x)
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
        return Vector<T, 3u>::operator==(static_cast<Vector<T, 3u>>(obj));
    }

    template <typename T>
    bool Angle<T>::operator!=(const Angle<T> &obj) const
    {
        return Vector<T, 3u>::operator!=(static_cast<Vector<T, 3u>>(obj));
    }

    template <typename T>
    void Angle<T>::Normalize()
    {
        for (unsigned int i{0u}; i < 3u; i++)
        {
            this->vec[i] = fmod(this->vec[i], static_cast<T>(2.0 * Constants::PI));
        }
    }

    template <typename T>
    DCM<T> Angle<T>::ToDCM(const TaitBryanOrder &rotOrder) const
    {
        DCM<T> tmp;

        switch (rotOrder)
        {
        case TaitBryanOrder::XYZ:
        {
            tmp[0][0] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[2]) * std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[0][2] = std::sin(this->vec[0]) * std::sin(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[2]) * std::sin(this->vec[1]);

            tmp[1][0] = -std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[2]) * std::sin(this->vec[0]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);

            tmp[2][0] = std::sin(this->vec[1]);
            tmp[2][1] = -std::cos(this->vec[1]) * std::sin(this->vec[0]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case TaitBryanOrder::XZY:
        {
            tmp[0][0] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[0][1] = std::sin(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]) * std::sin(this->vec[1]);
            tmp[0][2] = std::cos(this->vec[2]) * std::sin(this->vec[0]) * std::sin(this->vec[1]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);

            tmp[1][0] = -std::sin(this->vec[1]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[1]);
            tmp[1][2] = std::sin(this->vec[0]) * std::cos(this->vec[1]);

            tmp[2][0] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);

            break;
        }
        case TaitBryanOrder::YXZ:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);

            tmp[1][0] = std::cos(this->vec[2]) * std::sin(this->vec[0]) * std::sin(this->vec[1]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::cos(this->vec[2]) * std::sin(this->vec[1]);

            tmp[2][0] = std::cos(this->vec[1]) * std::sin(this->vec[0]);
            tmp[2][1] = -std::sin(this->vec[1]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]);

            break;
        }
        case TaitBryanOrder::YZX:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]);
            tmp[0][1] = std::sin(this->vec[1]);
            tmp[0][2] = -std::sin(this->vec[0]) * std::cos(this->vec[1]);

            tmp[1][0] = std::sin(this->vec[0]) * std::sin(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[2]) * std::sin(this->vec[1]);
            tmp[1][1] = std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[2]) * std::sin(this->vec[1]);

            tmp[2][0] = std::sin(this->vec[0]) * std::cos(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[2]) * std::sin(this->vec[1]);
            tmp[2][1] = -std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]) * std::sin(this->vec[1]);

            break;
        }
        case TaitBryanOrder::ZXY:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[2]) * std::sin(this->vec[0]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = -std::cos(this->vec[1]) * std::sin(this->vec[2]);

            tmp[1][0] = -std::cos(this->vec[1]) * std::sin(this->vec[0]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[1]);
            tmp[1][2] = std::sin(this->vec[1]);

            tmp[2][0] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[2]) * std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[2]) * std::sin(this->vec[1]);
            tmp[2][2] = std::cos(this->vec[1]) * std::cos(this->vec[2]);

            break;
        }
        case TaitBryanOrder::ZYX:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]);
            tmp[0][1] = std::cos(this->vec[1]) * std::sin(this->vec[0]);
            tmp[0][2] = -std::sin(this->vec[1]);

            tmp[1][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[2]) + std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[1]) * std::sin(this->vec[2]);

            tmp[2][0] = std::sin(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[1]) * std::cos(this->vec[2]);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Tait-Bryan Order");
        }
        }

        return tmp;
    }

    template <typename T>
    DCM<T> Angle<T>::ToDCM(const EulerOrder &rotOrder) const
    {
        DCM<T> tmp;

        switch (rotOrder)
        {
        case EulerOrder::XYX:
        {
            tmp[0][0] = std::cos(this->vec[1]);
            tmp[0][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[0][2] = -std::cos(this->vec[0]) * std::sin(this->vec[1]);

            tmp[1][0] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[2]) * std::sin(this->vec[0]) + std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);

            tmp[2][0] = std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][1] = -std::cos(this->vec[0]) * std::sin(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);

            break;
        }
        case EulerOrder::XZX:
        {
            tmp[0][0] = std::cos(this->vec[1]);
            tmp[0][1] = std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[0][2] = std::sin(this->vec[0]) * std::sin(this->vec[1]);

            tmp[1][0] = -std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]);

            tmp[2][0] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][1] = -std::sin(this->vec[0]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);

            break;
        }
        case EulerOrder::YXY:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][1] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = -std::sin(this->vec[0]) * std::cos(this->vec[2]) - std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);

            tmp[1][0] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[1][1] = std::cos(this->vec[1]);
            tmp[1][2] = std::cos(this->vec[0]) * std::sin(this->vec[1]);

            tmp[2][0] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::sin(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][1] = -std::sin(this->vec[1]) * std::cos(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);

            break;
        }
        case EulerOrder::YZY:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[2]) * std::sin(this->vec[1]);
            tmp[0][2] = -std::cos(this->vec[0]) * std::sin(this->vec[2]) - std::cos(this->vec[1]) * std::cos(this->vec[2]) * std::sin(this->vec[0]);

            tmp[1][0] = -std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[1][1] = std::cos(this->vec[1]);
            tmp[1][2] = std::sin(this->vec[0]) * std::sin(this->vec[1]);

            tmp[2][0] = std::cos(this->vec[2]) * std::sin(this->vec[0]) + std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][1] = std::sin(this->vec[1]) * std::sin(this->vec[2]);
            tmp[2][2] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::cos(this->vec[1]) * std::sin(this->vec[0]) * std::sin(this->vec[2]);

            break;
        }
        case EulerOrder::ZXZ:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::cos(this->vec[1]) * std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[2]) * std::sin(this->vec[0]) + std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[0][2] = std::sin(this->vec[1]) * std::sin(this->vec[2]);

            tmp[1][0] = -std::cos(this->vec[0]) * std::sin(this->vec[2]) - std::cos(this->vec[1]) * std::cos(this->vec[2]) * std::sin(this->vec[0]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][2] = std::cos(this->vec[2]) * std::sin(this->vec[1]);

            tmp[2][0] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][1] = -std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][2] = std::cos(this->vec[1]);

            break;
        }
        case EulerOrder::ZYZ:
        {
            tmp[0][0] = std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::cos(this->vec[2]) - std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[0][1] = std::cos(this->vec[0]) * std::sin(this->vec[2]) + std::cos(this->vec[1]) * std::cos(this->vec[2]) * std::sin(this->vec[0]);
            tmp[0][2] = -std::cos(this->vec[2]) * std::sin(this->vec[1]);

            tmp[1][0] = -std::cos(this->vec[2]) * std::sin(this->vec[0]) - std::cos(this->vec[0]) * std::cos(this->vec[1]) * std::sin(this->vec[2]);
            tmp[1][1] = std::cos(this->vec[0]) * std::cos(this->vec[2]) - std::cos(this->vec[1]) * std::sin(this->vec[0]) * std::sin(this->vec[2]);
            tmp[1][2] = std::sin(this->vec[1]) * std::sin(this->vec[2]);

            tmp[2][0] = std::cos(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][1] = std::sin(this->vec[0]) * std::sin(this->vec[1]);
            tmp[2][2] = std::cos(this->vec[1]);

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
    Quaternion<T> Angle<T>::ToQuaternion(const TaitBryanOrder &rotOrder) const
    {
        Quaternion<T> qat;

        Quaternion<T> qx;
        Quaternion<T> qy;
        Quaternion<T> qz;

        switch (rotOrder)
        {
        case TaitBryanOrder::XYZ:
        {
            qx = Quaternion<T>(this->vec[0], Axis::X);
            qy = Quaternion<T>(this->vec[1], Axis::Y);
            qz = Quaternion<T>(this->vec[2], Axis::Z);

            qat = qx * qy * qz;

            break;
        }
        case TaitBryanOrder::XZY:
        {
            qx = Quaternion<T>(this->vec[0], Axis::X);
            qz = Quaternion<T>(this->vec[1], Axis::Z);
            qy = Quaternion<T>(this->vec[2], Axis::Y);

            qat = qx * qz * qy;

            break;
        }
        case TaitBryanOrder::YXZ:
        {
            qy = Quaternion<T>(this->vec[0], Axis::Y);
            qx = Quaternion<T>(this->vec[1], Axis::X);
            qz = Quaternion<T>(this->vec[2], Axis::Z);

            qat = qy * qx * qz;

            break;
        }
        case TaitBryanOrder::YZX:
        {
            qy = Quaternion<T>(this->vec[0], Axis::Y);
            qz = Quaternion<T>(this->vec[1], Axis::Z);
            qx = Quaternion<T>(this->vec[2], Axis::X);

            qat = qy * qz * qx;

            break;
        }
        case TaitBryanOrder::ZXY:
        {
            qz = Quaternion<T>(this->vec[0], Axis::Z);
            qx = Quaternion<T>(this->vec[1], Axis::X);
            qy = Quaternion<T>(this->vec[2], Axis::Y);

            qat = qz * qx * qy;

            break;
        }
        case TaitBryanOrder::ZYX:
        {
            qz = Quaternion<T>(this->vec[0], Axis::Z);
            qy = Quaternion<T>(this->vec[1], Axis::Y);
            qx = Quaternion<T>(this->vec[2], Axis::X);

            qat = qz * qy * qx;

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Tait-Bryan Order");
        }
        }

        return qat;
    }

    template <typename T>
    Quaternion<T> Angle<T>::ToQuaternion(const EulerOrder &rotOrder) const
    {
        Quaternion<T> q1;
        Quaternion<T> q2;
        Quaternion<T> q3;

        switch (rotOrder)
        {
        case EulerOrder::XYX:
        {
            q1 = Quaternion<T>(this->vec[0], Axis::X);
            q2 = Quaternion<T>(this->vec[1], Axis::Y);
            q3 = Quaternion<T>(this->vec[2], Axis::X);

            break;
        }
        case EulerOrder::XZX:
        {
            q1 = Quaternion<T>(this->vec[0], Axis::X);
            q2 = Quaternion<T>(this->vec[1], Axis::Z);
            q3 = Quaternion<T>(this->vec[2], Axis::X);

            break;
        }
        case EulerOrder::YXY:
        {
            q1 = Quaternion<T>(this->vec[0], Axis::Y);
            q2 = Quaternion<T>(this->vec[1], Axis::X);
            q3 = Quaternion<T>(this->vec[2], Axis::Y);

            break;
        }
        case EulerOrder::YZY:
        {
            q1 = Quaternion<T>(this->vec[0], Axis::Y);
            q2 = Quaternion<T>(this->vec[1], Axis::Z);
            q3 = Quaternion<T>(this->vec[2], Axis::Y);

            break;
        }
        case EulerOrder::ZXZ:
        {
            q1 = Quaternion<T>(this->vec[0], Axis::Z);
            q2 = Quaternion<T>(this->vec[1], Axis::X);
            q3 = Quaternion<T>(this->vec[2], Axis::Z);

            break;
        }
        case EulerOrder::ZYZ:
        {
            q1 = Quaternion<T>(this->vec[0], Axis::Z);
            q2 = Quaternion<T>(this->vec[1], Axis::Y);
            q3 = Quaternion<T>(this->vec[2], Axis::Z);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }

        return (q1 * q2 * q3);
    }

    template <typename T>
    Angle<T> Angle<T>::Rotate(const TaitBryanOrder &rotOrder, const Angle<T> &ang, const TaitBryanOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const
    {
        return (ToDCM(rotOrder) * ang.ToDCM(rotOrder2)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> Angle<T>::Rotate(const TaitBryanOrder &rotOrder, const Angle<T> &ang, const EulerOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const
    {
        return (ToDCM(rotOrder) * ang.ToDCM(rotOrder2)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> Angle<T>::Rotate(const EulerOrder &rotOrder, const Angle<T> &ang, const TaitBryanOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const
    {
        return (ToDCM(rotOrder) * ang.ToDCM(rotOrder2)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> Angle<T>::Rotate(const EulerOrder &rotOrder, const Angle<T> &ang, const EulerOrder &rotOrder2, const EulerOrder &rotOrderOut) const
    {
        return (ToDCM(rotOrder) * ang.ToDCM(rotOrder2)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> Angle<T>::Rotate(const EulerOrder &rotOrder, const Angle<T> &ang, const EulerOrder &rotOrder2, const TaitBryanOrder &rotOrderOut) const
    {
        return (ToDCM(rotOrder) * ang.ToDCM(rotOrder2)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Vector<T, 3u> Angle<T>::Rotate(const TaitBryanOrder &rotOrder, const Vector<T, 3u> &vec) const
    {
        return (ToDCM(rotOrder) * vec);
    }

    template <typename T>
    Vector<T, 3u> Angle<T>::Rotate(const EulerOrder &rotOrder, const Vector<T, 3u> &vec) const
    {
        return (ToDCM(rotOrder) * vec);
    }

    template <typename T>
    DCM<T> Angle<T>::Rotate(const TaitBryanOrder &rotOrder, const DCM<T> &dcm) const
    {
        return (ToDCM(rotOrder) * dcm);
    }

    template <typename T>
    DCM<T> Angle<T>::Rotate(const EulerOrder &rotOrder, const DCM<T> &dcm) const
    {
        return (ToDCM(rotOrder) * dcm);
    }

    template <typename T>
    Quaternion<T> Angle<T>::Rotate(const TaitBryanOrder &rotOrder, const Quaternion<T> &qat) const
    {
        return (qat * ToQuaternion(rotOrder));
    }

    template <typename T>
    Quaternion<T> Angle<T>::Rotate(const EulerOrder &rotOrder, const Quaternion<T> &qat) const
    {
        return (qat * ToQuaternion(rotOrder));
    }

    template <typename T>
    void Angle<T>::wrapAnglesZeroToTwoPi(const Axis ax)
    {
        if (ax == Axis::ALL)
        {
            wrapAnglesZeroToTwoPi(Axis::X);
            wrapAnglesZeroToTwoPi(Axis::Y);
            wrapAnglesZeroToTwoPi(Axis::Z);
        }
        else
        {
            if (ax > Axis::Z)
            {
                throw std::invalid_argument("Invalid Axis");
            }

            this->vec[ax] = wrapZeroToTwoPi(this->vec[ax]);
        }
    }

    template <typename T>
    void Angle<T>::wrapAnglesMinusPiToPi(const Axis ax)
    {
        if (ax == Axis::ALL)
        {
            wrapAnglesMinusPiToPi(Axis::X);
            wrapAnglesMinusPiToPi(Axis::Y);
            wrapAnglesMinusPiToPi(Axis::Z);
        }
        else
        {
            if (ax > Axis::Z)
            {
                throw std::invalid_argument("Invalid Axis");
            }

            this->vec[ax] = wrapMinusPiToPi(this->vec[ax]);
        }
    }

} // namespace myMath

#endif /* B4D2FB34_E82B_4930_84AF_12D1E557452E */
