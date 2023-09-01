#ifndef BE2979E6_492C_41FF_9CAF_296D652FCB38
#define BE2979E6_492C_41FF_9CAF_296D652FCB38

#include "BasicFunctions.h"
#include "Vector.h"

namespace myMath
{
    template <typename T>
    class DCM;

    template <typename T>
    class Angle;

    enum class EulerOrder : unsigned int;
    enum class TaitBryanOrder : unsigned int;
    enum Axis : unsigned int;

    template <typename T>
    class Quaternion : public Vector<T, 4u>
    {
    public:
        Quaternion();
        Quaternion(const T &w, const T &x, const T &y, const T &z);
        Quaternion(const T (&q)[4]);
        Quaternion(const Quaternion<T> &q);
        Quaternion(const Vector<T, 4u> &q);
        Quaternion(const T &w, const Vector<T, 3u> &v);
        Quaternion(const Vector<T, 3u> &v);
        Quaternion(const Angle<T> &ang, const EulerOrder &rotOrder);

        ~Quaternion() = default;

        Quaternion<T> operator=(const Quaternion<T> &q);
        Quaternion<T> operator=(const Vector<T, 4u> &q);
        Quaternion<T> operator=(const T (&q)[4]);

        Quaternion<T> operator*(const Quaternion<T> &q);
        Quaternion<T> operator*(const Vector<T, 4u> &q);
        Quaternion<T> operator*(const T (&q)[4]);

        Quaternion<T> &operator*=(const Quaternion<T> &q);
        Quaternion<T> &operator*=(const Vector<T, 4u> &q);
        Quaternion<T> &operator*=(const T (&q)[4]);

        Quaternion<T> operator+(const Quaternion<T> &q);
        Quaternion<T> operator+(const Vector<T, 4u> &q);
        Quaternion<T> operator+(const T (&q)[4]);

        Quaternion<T> &operator+=(const Quaternion<T> &q);
        Quaternion<T> &operator+=(const Vector<T, 4u> &q);
        Quaternion<T> &operator+=(const T (&q)[4]);

        Quaternion<T> operator-(const Quaternion<T> &q);
        Quaternion<T> operator-(const Vector<T, 4u> &q);
        Quaternion<T> operator-(const T (&q)[4]);

        Quaternion<T> &operator-=(const Quaternion<T> &q);
        Quaternion<T> &operator-=(const Vector<T, 4u> &q);
        Quaternion<T> &operator-=(const T (&q)[4]);

        Quaternion<T> operator/(const T &q);
        Quaternion<T> &operator/=(const T &q);

        Quaternion<T> operator-(void) const;

        T Magnitude(void) const;
        Quaternion<T> Conjugate(void) const;
        Quaternion<T> Inverse(void) const;
        Quaternion<T> &Normalize(void);
        DCM<T> ToDCM(void) const;
        Angle<T> ToEuler(const EulerOrder &rotOrder) const;
        Angle<T> ToEuler(const TaitBryanOrder &rotOrder) const;

        void set(const T &w, const T &x, const T &y, const T &z);
        void set(const DCM<T> &dcm);
        void set(const Angle<T> &ang, const EulerOrder &rotOrder);
        void set(const Angle<T> &ang, const TaitBryanOrder &rotOrder);
        void set(const Vector<T, 3u> &v);
    };
} // namespace myMath

#include "Angle.h"
#include "Matrix.h"
#include "DCM.h"

namespace myMath
{
    typedef Quaternion<double> QuaternionD;
    typedef Quaternion<float> QuaternionF;

    template <typename T>
    Quaternion<T>::Quaternion() : Vector<T, 4u>()
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T &w, const T &x, const T &y, const T &z) : Vector<T, 4u>({w, x, y, z})
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T (&q)[4]) : Vector<T, 4u>(q)
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Quaternion<T> &q) : Vector<T, 4u>(q)
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 4u> &q) : Vector<T, 4u>(q)
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T &w, const Vector<T, 3u> &v) : Vector<T, 4u>({w, v[0], v[1], v[2]})
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 3u> &v) : Vector<T, 4u>({static_cast<T>(0.0), v[0], v[1], v[2]})
    {
        Normalize();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Angle<T> &ang, const EulerOrder &rotOrder) : Vector<T, 4u>()
    {
        switch (rotOrder)
        {
        case EulerOrder::ZYX:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::YZX:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[3] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::ZXY:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::YXZ:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::XZY:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::XYZ:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[3] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));
            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }

        Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator=(const Quaternion<T> &q)
    {
        std::memcpy(this->vec, q.vec, 4 * sizeof(T));
        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator=(const Vector<T, 4u> &q)
    {
        std::memcpy(this->vec, q.vec, 4 * sizeof(T));
        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator=(const T (&q)[4])
    {
        std::memcpy(this->vec, q, 4 * sizeof(T));
        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &q)
    {
        Quaternion<T> tmp;

        tmp[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        tmp[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        tmp[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        tmp[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const Vector<T, 4u> &q)
    {
        Quaternion<T> tmp;

        tmp[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        tmp[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        tmp[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        tmp[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const T (&q)[4])
    {
        Quaternion<T> tmp;

        tmp[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        tmp[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        tmp[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        tmp[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const Quaternion<T> &q)
    {
        Quaternion<T> tmp{*this};

        this->vec[0] = tmp[0] * q[0] - tmp[1] * q[1] - tmp[2] * q[2] - tmp[3] * q[3];
        this->vec[1] = tmp[0] * q[1] + tmp[1] * q[0] + tmp[2] * q[3] - tmp[3] * q[2];
        this->vec[2] = tmp[0] * q[2] - tmp[1] * q[3] + tmp[2] * q[0] + tmp[3] * q[1];
        this->vec[3] = tmp[0] * q[3] + tmp[1] * q[2] - tmp[2] * q[1] + tmp[3] * q[0];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const Vector<T, 4u> &q)
    {
        Quaternion<T> tmp{*this};

        this->vec[0] = tmp[0] * q[0] - tmp[1] * q[1] - tmp[2] * q[2] - tmp[3] * q[3];
        this->vec[1] = tmp[0] * q[1] + tmp[1] * q[0] + tmp[2] * q[3] - tmp[3] * q[2];
        this->vec[2] = tmp[0] * q[2] - tmp[1] * q[3] + tmp[2] * q[0] + tmp[3] * q[1];
        this->vec[3] = tmp[0] * q[3] + tmp[1] * q[2] - tmp[2] * q[1] + tmp[3] * q[0];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const T (&q)[4])
    {
        Quaternion<T> tmp{*this};

        this->vec[0] = tmp[0] * q[0] - tmp[1] * q[1] - tmp[2] * q[2] - tmp[3] * q[3];
        this->vec[1] = tmp[0] * q[1] + tmp[1] * q[0] + tmp[2] * q[3] - tmp[3] * q[2];
        this->vec[2] = tmp[0] * q[2] - tmp[1] * q[3] + tmp[2] * q[0] + tmp[3] * q[1];
        this->vec[3] = tmp[0] * q[3] + tmp[1] * q[2] - tmp[2] * q[1] + tmp[3] * q[0];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator+(const Quaternion<T> &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] += q[0];
        tmp[1] += q[1];
        tmp[2] += q[2];
        tmp[3] += q[3];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator+(const Vector<T, 4u> &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] += q[0];
        tmp[1] += q[1];
        tmp[2] += q[2];
        tmp[3] += q[3];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator+(const T (&q)[4])
    {
        Quaternion<T> tmp{*this};

        tmp[0] += q[0];
        tmp[1] += q[1];
        tmp[2] += q[2];
        tmp[3] += q[3];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator+=(const Quaternion<T> &q)
    {
        this->vec[0] += q[0];
        this->vec[1] += q[1];
        this->vec[2] += q[2];
        this->vec[3] += q[3];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator+=(const Vector<T, 4u> &q)
    {
        this->vec[0] += q[0];
        this->vec[1] += q[1];
        this->vec[2] += q[2];
        this->vec[3] += q[3];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator+=(const T (&q)[4])
    {
        this->vec[0] += q[0];
        this->vec[1] += q[1];
        this->vec[2] += q[2];
        this->vec[3] += q[3];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(const Quaternion<T> &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] -= q[0];
        tmp[1] -= q[1];
        tmp[2] -= q[2];
        tmp[3] -= q[3];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(const Vector<T, 4u> &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] -= q[0];
        tmp[1] -= q[1];
        tmp[2] -= q[2];
        tmp[3] -= q[3];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(const T (&q)[4])
    {
        Quaternion<T> tmp{*this};

        tmp[0] -= q[0];
        tmp[1] -= q[1];
        tmp[2] -= q[2];
        tmp[3] -= q[3];

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator-=(const Quaternion<T> &q)
    {
        this->vec[0] -= q[0];
        this->vec[1] -= q[1];
        this->vec[2] -= q[2];
        this->vec[3] -= q[3];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator-=(const Vector<T, 4u> &q)
    {
        this->vec[0] -= q[0];
        this->vec[1] -= q[1];
        this->vec[2] -= q[2];
        this->vec[3] -= q[3];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator-=(const T (&q)[4])
    {
        this->vec[0] -= q[0];
        this->vec[1] -= q[1];
        this->vec[2] -= q[2];
        this->vec[3] -= q[3];

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator/(const T &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] /= q;
        tmp[1] /= q;
        tmp[2] /= q;
        tmp[3] /= q;

        return tmp.Normalize();
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator/=(const T &q)
    {
        this->vec[0] /= q;
        this->vec[1] /= q;
        this->vec[2] /= q;
        this->vec[3] /= q;
        
        Normalize();

        return this->Normalize();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(void) const
    {
        Quaternion<T> tmp;

        tmp[0] = -this->vec[0];
        tmp[1] = -this->vec[1];
        tmp[2] = -this->vec[2];
        tmp[3] = -this->vec[3];

        return tmp;
    }

    template <typename T>
    T Quaternion<T>::Magnitude(void) const
    {
        return std::sqrt(SQ(this->vec[0]) + SQ(this->vec[1]) + SQ(this->vec[2]) + SQ(this->vec[3]));
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::Conjugate(void) const
    {
        Quaternion<T> tmp;

        tmp[0] = this->vec[0];
        tmp[1] = -this->vec[1];
        tmp[2] = -this->vec[2];
        tmp[3] = -this->vec[3];

        return tmp;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::Inverse(void) const
    {
        Quaternion<T> tmp = this->Conjugate();

        tmp /= SQ(this->Magnitude());

        return tmp;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::Normalize(void)
    {
        return *this /= this->Magnitude();
    }

    template <typename T>
    DCM<T> Quaternion<T>::ToDCM(void) const
    {
        DCM<T> tmp;

        tmp[0][0] = SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]);
        tmp[0][1] = static_cast<T>(2.0) * (this->vec[1] * this->vec[2] - this->vec[0] * this->vec[3]);
        tmp[0][2] = static_cast<T>(2.0) * (this->vec[1] * this->vec[3] + this->vec[0] * this->vec[2]);

        tmp[1][0] = static_cast<T>(2.0) * (this->vec[1] * this->vec[2] + this->vec[0] * this->vec[3]);
        tmp[1][1] = SQ(this->vec[0]) - SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[3]);
        tmp[1][2] = static_cast<T>(2.0) * (this->vec[2] * this->vec[3] - this->vec[0] * this->vec[1]);

        tmp[2][0] = static_cast<T>(2.0) * (this->vec[1] * this->vec[3] - this->vec[0] * this->vec[2]);
        tmp[2][1] = static_cast<T>(2.0) * (this->vec[2] * this->vec[3] + this->vec[0] * this->vec[1]);
        tmp[2][2] = SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]);

        return tmp;
    }

    template <typename T>
    Angle<T> Quaternion<T>::ToEuler(const EulerOrder &rotOrder) const
    {
        Angle<T> tmp;

        switch (rotOrder)
        {
        case EulerOrder::ZYX:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]));

            tmp[1] = std::asin(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[3] + this->vec[1] * this->vec[2]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            break;
        }
        case EulerOrder::YZX:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[3] - this->vec[1] * this->vec[2]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[1] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] + this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::asin(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] - this->vec[2] * this->vec[3]));

            break;
        }
        case EulerOrder::ZXY:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[3] + this->vec[1] * this->vec[2]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]));

            tmp[1] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::asin(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]));

            break;
        }
        case EulerOrder::YXZ:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] + this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[1] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[3] - this->vec[1] * this->vec[2]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::asin(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] - this->vec[2] * this->vec[3]));

            break;
        }
        case EulerOrder::XZY:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]));

            tmp[1] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[3] + this->vec[1] * this->vec[2]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::asin(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]));

            break;
        }
        case EulerOrder::XYZ:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]));

            tmp[1] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::asin(static_cast<T>(2.0) * (this->vec[0] * this->vec[3] + this->vec[1] * this->vec[2]));

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
    Angle<T> Quaternion<T>::ToEuler(const TaitBryanOrder &rotOrder) const
    {
        Angle<T> tmp;

        switch (rotOrder)
        {
        case TaitBryanOrder::XYX:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[1] = std::acos(SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] - this->vec[2] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[3]));

            break;
        }
        case TaitBryanOrder::XZX:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[2]) - SQ(this->vec[1]) - SQ(this->vec[3]));

            tmp[1] = std::acos(SQ(this->vec[0]) + SQ(this->vec[2]) - SQ(this->vec[1]) - SQ(this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] + this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[2]) + SQ(this->vec[1]) - SQ(this->vec[3]));

            break;
        }
        case TaitBryanOrder::YXY:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] - this->vec[2] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[1] = std::acos(SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[3]));

            break;
        }
        case TaitBryanOrder::YZY:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[1] * this->vec[2] - this->vec[0] * this->vec[3]),
                                SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[0]) - SQ(this->vec[3]));

            tmp[1] = std::acos(SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[0]) - SQ(this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[1] * this->vec[2] + this->vec[0] * this->vec[3]),
                                SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[0]) - SQ(this->vec[3]));

            break;
        }
        case TaitBryanOrder::ZXZ:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] + this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) + SQ(this->vec[2]) - SQ(this->vec[1]) - SQ(this->vec[3]));

            tmp[1] = std::acos(SQ(this->vec[0]) + SQ(this->vec[2]) - SQ(this->vec[1]) - SQ(this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]),
                                SQ(this->vec[0]) - SQ(this->vec[2]) + SQ(this->vec[1]) - SQ(this->vec[3]));

            break;
        }
        case TaitBryanOrder::ZYZ:
        {
            tmp[0] = std::atan2(static_cast<T>(2.0) * (this->vec[1] * this->vec[2] + this->vec[0] * this->vec[3]),
                                SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[0]) - SQ(this->vec[3]));

            tmp[1] = std::acos(SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[0]) - SQ(this->vec[3]));

            tmp[2] = std::atan2(static_cast<T>(2.0) * (this->vec[1] * this->vec[2] - this->vec[0] * this->vec[3]),
                                SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[0]) - SQ(this->vec[3]));

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
    void Quaternion<T>::set(const T &w, const T &x, const T &y, const T &z)
    {
        this->vec[0] = w;
        this->vec[1] = x;
        this->vec[2] = y;
        this->vec[3] = z;
        
        Normalize();
    }

    template <typename T>
    void Quaternion<T>::set(const DCM<T> &dcm)
    {
        this->vec[0] = std::sqrt(static_cast<T>(1.0) + dcm[0][0] + dcm[1][1] + dcm[2][2]) / static_cast<T>(2.0);
        this->vec[1] = (dcm[2][1] - dcm[1][2]) / (static_cast<T>(4.0) * this->vec[0]);
        this->vec[2] = (dcm[0][2] - dcm[2][0]) / (static_cast<T>(4.0) * this->vec[0]);
        this->vec[3] = (dcm[1][0] - dcm[0][1]) / (static_cast<T>(4.0) * this->vec[0]);
        
        Normalize();
    }

    template <typename T>
    void Quaternion<T>::set(const Angle<T> &ang, const EulerOrder &rotOrder)
    {
        switch (rotOrder)
        {
        case EulerOrder::XYZ:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::XZY:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::YXZ:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::YZX:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::ZXY:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        case EulerOrder::ZYX:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2));

            this->vec[3] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::sin(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));
            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }
        
        Normalize();
    }

    template <typename T>
    void Quaternion<T>::set(const Angle<T> &ang, const TaitBryanOrder &rotOrder)
    {
        switch (rotOrder)
        {
        case TaitBryanOrder::XYX:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2));

            break;
        }
        case TaitBryanOrder::XZX:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2));

            break;
        }
        case TaitBryanOrder::YXY:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2));

            break;
        }
        case TaitBryanOrder::YZY:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2));

            break;
        }
        case TaitBryanOrder::ZXZ:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2));

            break;
        }
        case TaitBryanOrder::ZYZ:
        {
            this->vec[0] = std::cos(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2));

            this->vec[1] = std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) +
                           std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2));

            this->vec[2] = std::cos(ang[0] / static_cast<T>(2)) * std::sin(ang[1] / static_cast<T>(2)) * std::cos(ang[2] / static_cast<T>(2)) -
                           std::sin(ang[0] / static_cast<T>(2)) * std::cos(ang[1] / static_cast<T>(2));

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Tait-Bryan Order");
        }
        }

        Normalize();
    }

    template <typename T>
    void Quaternion<T>::set(const Vector<T, 3u> &v)
    {
        this->vec[0] = static_cast<T>(0.0);
        this->vec[1] = v[0];
        this->vec[2] = v[1];
        this->vec[3] = v[2];

        Normalize();
    }

} // namespace myMath

#endif /* BE2979E6_492C_41FF_9CAF_296D652FCB38 */
