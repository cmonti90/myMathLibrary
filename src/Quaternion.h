#ifndef BE2979E6_492C_41FF_9CAF_296D652FCB38
#define BE2979E6_492C_41FF_9CAF_296D652FCB38

#include "BasicFunctions.h"
#include "Vector.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    template <typename T>
    class DCM;

    template <typename T>
    class Angle;

    enum class TaitBryanOrder : unsigned int;
    enum class EulerOrder : unsigned int;

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
        Quaternion(const T &w, const Angle<T> &v);
        Quaternion(const Angle<T> &ang, const TaitBryanOrder &rotOrder);
        Quaternion(const Angle<T> &ang, const EulerOrder &rotOrder);
        Quaternion(const DCM<T> &dcm);
        Quaternion(const T ang, const Axis ax);

        virtual ~Quaternion();

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

        bool operator==(const Quaternion<T> &q) const;
        bool operator!=(const Quaternion<T> &q) const;

        T Magnitude(void) const;
        Quaternion<T> Conjugate(void) const;
        Quaternion<T> Inverse(void) const;
        void Normalize(void);
        DCM<T> ToDCM(void);
        Angle<T> ToEuler(const TaitBryanOrder &rotOrder);
        Angle<T> ToEuler(const EulerOrder &rotOrder);
        void getTaitBryanAngles(Angle<T> &ang);

        void set(const T &w, const T &x, const T &y, const T &z);
        void set(const DCM<T> &dcm);
        void set(const Angle<T> &ang, const TaitBryanOrder &rotOrder);
        void set(const Angle<T> &ang, const EulerOrder &rotOrder);
        void set(const Vector<T, 3u> &v);

        Angle<T> rotate(const Angle<T> &ang, const TaitBryanOrder &rotOrder, const TaitBryanOrder &rotOrder2);
        Angle<T> rotate(const Angle<T> &ang, const EulerOrder &rotOrder, const TaitBryanOrder &rotOrder2);
        Angle<T> rotate(const Angle<T> &ang, const EulerOrder &rotOrder, const EulerOrder &rotOrder2);
        DCM<T> rotate(const DCM<T> &dcm);
        Quaternion<T> rotate(const Quaternion<T> &q);
    };
} // namespace myMath

#include "Angle.h"
#include "DCM.h"
#include "Matrix.h"

namespace myMath
{
    typedef Quaternion<double> QuaternionD;
    typedef Quaternion<float> QuaternionF;

    template <typename T>
    Quaternion<T>::Quaternion() : Vector<T, 4u>()
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T &w, const T &x, const T &y, const T &z) : Vector<T, 4u>({w, x, y, z})
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T (&q)[4]) : Vector<T, 4u>(q)
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Quaternion<T> &q) : Vector<T, 4u>(q)
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 4u> &q) : Vector<T, 4u>(q)
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T &w, const Vector<T, 3u> &v) : Vector<T, 4u>({w, v[0], v[1], v[2]})
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 3u> &v) : Vector<T, 4u>({static_cast<T>(0.0), v[0], v[1], v[2]})
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T &w, const Angle<T> &ang) : Vector<T, 4u>({w, ang[0], ang[1], ang[2]})
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Angle<T> &ang, const TaitBryanOrder &rotOrder) : Vector<T, 4u>()
    {
        *this = ang.ToQuaternion(rotOrder);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Angle<T> &ang, const EulerOrder &rotOrder) : Vector<T, 4u>()
    {
        *this = ang.ToQuaternion(rotOrder);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const DCM<T> &dcm) : Vector<T, 4u>()
    {
        *this = dcm.ToQuaternion();
    }

    template <typename T>
    Quaternion<T>::Quaternion(const T ang, const Axis ax) : Vector<T, 4u>()
    {
        switch (ax)
        {
        case Axis::X:
        {
            this->vec[0] = std::cos(ang / static_cast<T>(2));
            this->vec[1] = std::sin(ang / static_cast<T>(2));
            this->vec[2] = static_cast<T>(0);
            this->vec[3] = static_cast<T>(0);

            break;
        }
        case Axis::Y:
        {
            this->vec[0] = std::cos(ang / static_cast<T>(2));
            this->vec[1] = static_cast<T>(0);
            this->vec[2] = std::sin(ang / static_cast<T>(2));
            this->vec[3] = static_cast<T>(0);

            break;
        }
        case Axis::Z:
        {
            this->vec[0] = std::cos(ang / static_cast<T>(2));
            this->vec[1] = static_cast<T>(0);
            this->vec[2] = static_cast<T>(0);
            this->vec[3] = std::sin(ang / static_cast<T>(2));

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Axis");

            break;
        }
        }
    }

    template <typename T>
    Quaternion<T>::~Quaternion()
    {
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator=(const Quaternion<T> &q)
    {
        std::memcpy(this->vec, q.vec, 4 * sizeof(T));

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator=(const Vector<T, 4u> &q)
    {
        std::memcpy(this->vec, q.vec, 4 * sizeof(T));

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator=(const T (&q)[4])
    {
        std::memcpy(this->vec, q, 4 * sizeof(T));

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &q)
    {
        Quaternion<T> qat;

        qat[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        qat[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        qat[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        qat[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        qat.Normalize();

        return qat;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const Vector<T, 4u> &q)
    {
        Quaternion<T> qat;

        qat[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        qat[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        qat[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        qat[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        qat.Normalize();

        return qat;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const T (&q)[4])
    {
        Quaternion<T> qat;

        qat[0] = this->vec[0] * q[0] - this->vec[1] * q[1] - this->vec[2] * q[2] - this->vec[3] * q[3];
        qat[1] = this->vec[0] * q[1] + this->vec[1] * q[0] + this->vec[2] * q[3] - this->vec[3] * q[2];
        qat[2] = this->vec[0] * q[2] - this->vec[1] * q[3] + this->vec[2] * q[0] + this->vec[3] * q[1];
        qat[3] = this->vec[0] * q[3] + this->vec[1] * q[2] - this->vec[2] * q[1] + this->vec[3] * q[0];

        qat.Normalize();

        return qat;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const Quaternion<T> &q)
    {
        Quaternion<T> qat{*this};

        this->vec[0] = qat[0] * q[0] - qat[1] * q[1] - qat[2] * q[2] - qat[3] * q[3];
        this->vec[1] = qat[0] * q[1] + qat[1] * q[0] + qat[2] * q[3] - qat[3] * q[2];
        this->vec[2] = qat[0] * q[2] - qat[1] * q[3] + qat[2] * q[0] + qat[3] * q[1];
        this->vec[3] = qat[0] * q[3] + qat[1] * q[2] - qat[2] * q[1] + qat[3] * q[0];

        Normalize();

        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const Vector<T, 4u> &q)
    {
        Quaternion<T> tmp{*this};

        this->vec[0] = tmp[0] * q[0] - tmp[1] * q[1] - tmp[2] * q[2] - tmp[3] * q[3];
        this->vec[1] = tmp[0] * q[1] + tmp[1] * q[0] + tmp[2] * q[3] - tmp[3] * q[2];
        this->vec[2] = tmp[0] * q[2] - tmp[1] * q[3] + tmp[2] * q[0] + tmp[3] * q[1];
        this->vec[3] = tmp[0] * q[3] + tmp[1] * q[2] - tmp[2] * q[1] + tmp[3] * q[0];

        Normalize();

        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const T (&q)[4])
    {
        Quaternion<T> tmp{*this};

        this->vec[0] = tmp[0] * q[0] - tmp[1] * q[1] - tmp[2] * q[2] - tmp[3] * q[3];
        this->vec[1] = tmp[0] * q[1] + tmp[1] * q[0] + tmp[2] * q[3] - tmp[3] * q[2];
        this->vec[2] = tmp[0] * q[2] - tmp[1] * q[3] + tmp[2] * q[0] + tmp[3] * q[1];
        this->vec[3] = tmp[0] * q[3] + tmp[1] * q[2] - tmp[2] * q[1] + tmp[3] * q[0];

        Normalize();

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator+(const Quaternion<T> &q)
    {
        Quaternion<T> qat{*this};

        qat[0] += q[0];
        qat[1] += q[1];
        qat[2] += q[2];
        qat[3] += q[3];

        return qat;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator+(const Vector<T, 4u> &q)
    {
        Quaternion<T> qat{*this};

        qat[0] += q[0];
        qat[1] += q[1];
        qat[2] += q[2];
        qat[3] += q[3];

        return qat;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator+(const T (&q)[4])
    {
        Quaternion<T> qat{*this};

        qat[0] += q[0];
        qat[1] += q[1];
        qat[2] += q[2];
        qat[3] += q[3];

        return qat;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator+=(const Quaternion<T> &q)
    {
        this->vec[0] += q[0];
        this->vec[1] += q[1];
        this->vec[2] += q[2];
        this->vec[3] += q[3];

        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator+=(const Vector<T, 4u> &q)
    {
        this->vec[0] += q[0];
        this->vec[1] += q[1];
        this->vec[2] += q[2];
        this->vec[3] += q[3];

        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator+=(const T (&q)[4])
    {
        this->vec[0] += q[0];
        this->vec[1] += q[1];
        this->vec[2] += q[2];
        this->vec[3] += q[3];

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(const Quaternion<T> &q)
    {
        Quaternion<T> qat{*this};

        qat[0] -= q[0];
        qat[1] -= q[1];
        qat[2] -= q[2];
        qat[3] -= q[3];

        return qat;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(const Vector<T, 4u> &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] -= q[0];
        tmp[1] -= q[1];
        tmp[2] -= q[2];
        tmp[3] -= q[3];

        return tmp;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator-(const T (&q)[4])
    {
        Quaternion<T> tmp{*this};

        tmp[0] -= q[0];
        tmp[1] -= q[1];
        tmp[2] -= q[2];
        tmp[3] -= q[3];

        return tmp;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator-=(const Quaternion<T> &q)
    {
        this->vec[0] -= q[0];
        this->vec[1] -= q[1];
        this->vec[2] -= q[2];
        this->vec[3] -= q[3];

        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator-=(const Vector<T, 4u> &q)
    {
        this->vec[0] -= q[0];
        this->vec[1] -= q[1];
        this->vec[2] -= q[2];
        this->vec[3] -= q[3];

        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator-=(const T (&q)[4])
    {
        this->vec[0] -= q[0];
        this->vec[1] -= q[1];
        this->vec[2] -= q[2];
        this->vec[3] -= q[3];

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator/(const T &q)
    {
        Quaternion<T> tmp{*this};

        tmp[0] /= q;
        tmp[1] /= q;
        tmp[2] /= q;
        tmp[3] /= q;

        return tmp;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator/=(const T &q)
    {
        this->vec[0] /= q;
        this->vec[1] /= q;
        this->vec[2] /= q;
        this->vec[3] /= q;

        return *this;
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
    bool Quaternion<T>::operator==(const Quaternion<T> &q) const
    {
        return Vector<T, 4>::operator==(q);
    }

    template <typename T>
    bool Quaternion<T>::operator!=(const Quaternion<T> &q) const
    {
        return Vector<T, 4>::operator!=(q);
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
        Quaternion<T> tmp = Conjugate();

        tmp /= SQ(Magnitude());

        return tmp;
    }

    template <typename T>
    void Quaternion<T>::Normalize(void)
    {
        if (Magnitude() != static_cast<T>(0))
        {
            *this /= Magnitude();
        }
    }

    template <typename T>
    DCM<T> Quaternion<T>::ToDCM(void)
    {
        Normalize();

        DCM<T> dcm;

        dcm[0][0] = SQ(this->vec[0]) + SQ(this->vec[1]) - SQ(this->vec[2]) - SQ(this->vec[3]);
        dcm[0][1] = static_cast<T>(2) * (this->vec[1] * this->vec[2] + this->vec[0] * this->vec[3]);
        dcm[0][2] = static_cast<T>(2) * (this->vec[1] * this->vec[3] - this->vec[0] * this->vec[2]);

        dcm[1][0] = static_cast<T>(2) * (this->vec[1] * this->vec[2] - this->vec[0] * this->vec[3]);
        dcm[1][1] = SQ(this->vec[0]) - SQ(this->vec[1]) + SQ(this->vec[2]) - SQ(this->vec[3]);
        dcm[1][2] = static_cast<T>(2) * (this->vec[2] * this->vec[3] + this->vec[0] * this->vec[1]);

        dcm[2][0] = static_cast<T>(2) * (this->vec[1] * this->vec[3] + this->vec[0] * this->vec[2]);
        dcm[2][1] = static_cast<T>(2) * (this->vec[2] * this->vec[3] - this->vec[0] * this->vec[1]);
        dcm[2][2] = SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]);

        return dcm;
    }

    template <typename T>
    Angle<T> Quaternion<T>::ToEuler(const TaitBryanOrder &rotOrder)
    {
        Normalize();

        return ToDCM().ToEuler(rotOrder);
    }

    template <typename T>
    Angle<T> Quaternion<T>::ToEuler(const EulerOrder &rotOrder)
    {
        Normalize();

        std::cout << "ToDCM() = " << std::endl;
        std::cout << ToDCM()[0][0] << "  " << ToDCM()[0][1] << "  " << ToDCM()[0][2] << std::endl;
        std::cout << ToDCM()[1][0] << "  " << ToDCM()[1][1] << "  " << ToDCM()[1][2] << std::endl;
        std::cout << ToDCM()[2][0] << "  " << ToDCM()[2][1] << "  " << ToDCM()[2][2] << std::endl
                  << std::endl;

        return ToDCM().ToEuler(rotOrder);
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
        this->vec[0] = std::sqrt(static_cast<T>(1) + dcm[0][0] + dcm[1][1] + dcm[2][2]) / static_cast<T>(2);
        this->vec[1] = (dcm[2][1] - dcm[1][2]) / (static_cast<T>(4) * this->vec[0]);
        this->vec[2] = (dcm[0][2] - dcm[2][0]) / (static_cast<T>(4) * this->vec[0]);
        this->vec[3] = (dcm[1][0] - dcm[0][1]) / (static_cast<T>(4) * this->vec[0]);

        Normalize();
    }

    template <typename T>
    void Quaternion<T>::set(const Angle<T> &ang, const TaitBryanOrder &rotOrder)
    {
        *this = ang.ToQuaternion(rotOrder);

        Normalize();
    }

    template <typename T>
    void Quaternion<T>::set(const Angle<T> &ang, const EulerOrder &rotOrder)
    {
        *this = ang.ToQuaternion(rotOrder);

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

    template <typename T>
    Angle<T> Quaternion<T>::rotate(const Angle<T> &ang, const TaitBryanOrder &rotOrder, const TaitBryanOrder &rotOrderOut)
    {
        Normalize();

        return (*this * ang.ToQuaternion(rotOrder)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> Quaternion<T>::rotate(const Angle<T> &ang, const EulerOrder &rotOrder, const TaitBryanOrder &rotOrderOut)
    {
        Normalize();

        return (*this * ang.ToQuaternion(rotOrder)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> Quaternion<T>::rotate(const Angle<T> &ang, const EulerOrder &rotOrder, const EulerOrder &rotOrderOut)
    {
        Normalize();

        return (*this * ang.ToQuaternion(rotOrder)).ToEuler(rotOrderOut);
    }

    template <typename T>
    DCM<T> Quaternion<T>::rotate(const DCM<T> &dcm)
    {
        Normalize();

        return ((*this) * dcm.ToQuaternion()).ToDCM();
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::rotate(const Quaternion<T> &q)
    {
        Normalize();

        Quaternion<T> q_rot = (*this) * q;

        q_rot.Normalize();

        return q_rot;
    }

    template <typename T>
    void Quaternion<T>::getTaitBryanAngles(Angle<T> &ang)
    {
        Normalize();

        ang[0] = std::atan2(static_cast<T>(2) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]),
                            SQ(this->vec[0]) - SQ(this->vec[1]) - SQ(this->vec[2]) + SQ(this->vec[3]));

        ang[1] = std::asin(static_cast<T>(2) * (this->vec[0] * this->vec[2] - this->vec[1] * this->vec[3]));

        ang[2] = std::atan2(static_cast<T>(2) * (this->vec[0] * this->vec[1] + this->vec[2] * this->vec[3]),
                            SQ(this->vec[0]) + SQ(this->vec[3]) - SQ(this->vec[1]) - SQ(this->vec[2]));
    }

} // namespace myMath

#endif /* BE2979E6_492C_41FF_9CAF_296D652FCB38 */
