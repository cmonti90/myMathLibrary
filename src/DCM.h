#ifndef BA9453AD_D478_47EC_9001_44325F419B41
#define BA9453AD_D478_47EC_9001_44325F419B41

#include "Matrix.h"

#include <cmath>
#include <stdexcept>

namespace myMath
{
    template <typename T>
    class Angle;

    template <typename T>
    class Quaternion;
    template <typename T>
    class DCM : public Matrix<T, 3, 3>
    {
    public:
        DCM();
        DCM(const Matrix<T, 3, 3> &m);
        DCM(const T (&m)[3][3]);
        DCM(const T (&m)[9]);

        DCM<T> operator=(const DCM<T> &dcm);

        DCM<T> operator=(const Matrix<T, 3, 3> &m);
        DCM<T> operator=(const T (&m)[3][3]);
        DCM<T> operator=(const T (&m)[9]);

        DCM<T> operator*(const DCM<T> &dcm);
        DCM<T> operator*(const Matrix<T, 3, 3> &m);

        template <unsigned int C>
        Matrix<T, 3, C> operator*(const Matrix<T, 3, C> &m);

        template <unsigned int C>
        DCM<T> operator*(const T (&m)[3][C]);
        DCM<T> operator*(const T (&m)[9]);

        DCM<T> &operator*=(const DCM<T> &dcm);

        DCM<T> &operator*=(const Matrix<T, 3, 3> &m);
        DCM<T> &operator*=(const T (&m)[3][3]);
        DCM<T> &operator*=(const T (&m)[9]);

        DCM<T> operator-(void) const;

        bool operator==(const DCM<T> &dcm) const;
        bool operator!=(const DCM<T> &dcm) const;

        void Normalize();
        Quaternion<T> ToQuaternion() const;
        Angle<T> ToEuler(const TaitBryanOrder &rotOrder) const;
        Angle<T> ToEuler(const EulerOrder &rotOrder) const;
    };
} // namespace myMath

#include "Angle.h"
#include "Quaternion.h"

namespace myMath
{

    typedef DCM<double> DCMd;
    typedef DCM<float> DCMf;

    template <typename T>
    DCM<T>::DCM() : Matrix<T, 3, 3>()
    {
    }

    template <typename T>
    DCM<T>::DCM(const Matrix<T, 3, 3> &m) : Matrix<T, 3, 3>(m)
    {
    }

    template <typename T>
    DCM<T>::DCM(const T (&m)[3][3]) : Matrix<T, 3, 3>(m)
    {
    }

    template <typename T>
    DCM<T>::DCM(const T (&m)[9]) : Matrix<T, 3, 3>()
    {
        for (unsigned int i{0u}; i < 3u; i++)
        {
            for (unsigned int j{0u}; j < 3u; j++)
            {
                this->mat[i][j] = m[i * 3u + j];
            }
        }
    }

    template <typename T>
    DCM<T> DCM<T>::operator=(const DCM<T> &dcm)
    {
        Matrix<T, 3, 3>::operator=(dcm);
        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator=(const Matrix<T, 3, 3> &m)
    {
        Matrix<T, 3, 3>::operator=(m);
        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator=(const T (&m)[3][3])
    {
        Matrix<T, 3, 3>::operator=(m);
        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator=(const T (&m)[9])
    {
        for (unsigned int i{0u}; i < 3u; i++)
        {
            for (unsigned int j{0u}; j < 3u; j++)
            {
                this->mat[i][j] = m[i * 3u + j];
            }
        }

        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator*(const DCM<T> &dcm)
    {
        return DCM<T>(Matrix<T, 3, 3>::operator*(dcm));
    }

    template <typename T>
    DCM<T> DCM<T>::operator*(const Matrix<T, 3, 3> &m)
    {
        return DCM<T>(Matrix<T, 3, 3>::operator*(m));
    }

    template <typename T>
    template <unsigned int C>
    Matrix<T, 3, C> DCM<T>::operator*(const Matrix<T, 3, C> &m)
    {
        return Matrix<T, 3, C>::operator*(m);
    }

    template <typename T>
    template <unsigned int C>
    DCM<T> DCM<T>::operator*(const T (&m)[3][C])
    {
        return DCM<T>(Matrix<T, 3, C>::operator*(m));
    }

    template <typename T>
    DCM<T> DCM<T>::operator*(const T (&rhs)[9])
    {
        return *this * DCM<T>(rhs);
    }

    template <typename T>
    DCM<T> &DCM<T>::operator*=(const DCM<T> &dcm)
    {
        Matrix<T, 3, 3>::operator*=(dcm);
        return *this;
    }

    template <typename T>
    DCM<T> &DCM<T>::operator*=(const Matrix<T, 3, 3> &m)
    {
        Matrix<T, 3, 3>::operator*=(m);
        return *this;
    }

    template <typename T>
    DCM<T> &DCM<T>::operator*=(const T (&m)[3][3])
    {
        Matrix<T, 3, 3>::operator*=(m);
        return *this;
    }

    template <typename T>
    DCM<T> &DCM<T>::operator*=(const T (&m)[9])
    {
        Matrix<T, 3, 3>::operator*=(m);
        return *this;
    }

    template <typename T>
    DCM<T> DCM<T>::operator-(void) const
    {
        return static_cast<T>(-1)**this;
    }

    template <typename T>
    bool DCM<T>::operator==(const DCM<T> &dcm) const
    {
        return Matrix<T, 3, 3>::operator==(dcm);
    }

    template <typename T>
    bool DCM<T>::operator!=(const DCM<T> &dcm) const
    {
        return Matrix<T, 3, 3>::operator!=(dcm);
    }

    template <typename T>
    void DCM<T>::Normalize()
    {
        for (unsigned int i{0u}; i < 3u; i++)
        {
            this->mat[i].Normalize();
        }
    }

    template <typename T>
    Quaternion<T> DCM<T>::ToQuaternion() const
    {
        Quaternion<T> q;

        T q0_mag = std::sqrt((static_cast<T>(1) + this->mat[0][0] + this->mat[1][1] + this->mat[2][2])) / static_cast<T>(2);
        T q1_mag = std::sqrt((static_cast<T>(1) + this->mat[0][0] - this->mat[1][1] - this->mat[2][2])) / static_cast<T>(2);
        T q2_mag = std::sqrt((static_cast<T>(1) - this->mat[0][0] + this->mat[1][1] - this->mat[2][2])) / static_cast<T>(2);
        T q3_mag = std::sqrt((static_cast<T>(1) - this->mat[0][0] - this->mat[1][1] + this->mat[2][2])) / static_cast<T>(2);

        T q_max = MAX(q0_mag, MAX(q1_mag, MAX(q2_mag, q3_mag)));

        if (q_max == q0_mag)
        {
            q[0] = q0_mag;
            q[1] = (this->mat[1][2] - this->mat[2][1]) / (static_cast<T>(4) * q0_mag);
            q[2] = (this->mat[2][0] - this->mat[0][2]) / (static_cast<T>(4) * q0_mag);
            q[3] = (this->mat[0][1] - this->mat[1][0]) / (static_cast<T>(4) * q0_mag);
        }
        else if (q_max == q1_mag)
        {
            q[0] = (this->mat[1][2] - this->mat[2][1]) / (static_cast<T>(4) * q1_mag);
            q[1] = q1_mag;
            q[2] = (this->mat[0][1] + this->mat[1][0]) / (static_cast<T>(4) * q1_mag);
            q[3] = (this->mat[2][0] + this->mat[0][2]) / (static_cast<T>(4) * q1_mag);
        }
        else if (q_max == q2_mag)
        {
            q[0] = (this->mat[2][0] - this->mat[0][2]) / (static_cast<T>(4) * q2_mag);
            q[1] = (this->mat[0][1] + this->mat[1][0]) / (static_cast<T>(4) * q2_mag);
            q[2] = q2_mag;
            q[3] = (this->mat[1][2] + this->mat[2][1]) / (static_cast<T>(4) * q2_mag);
        }
        else
        {
            q[0] = (this->mat[0][1] - this->mat[1][0]) / (static_cast<T>(4) * q3_mag);
            q[1] = (this->mat[2][0] + this->mat[0][2]) / (static_cast<T>(4) * q3_mag);
            q[2] = (this->mat[1][2] + this->mat[2][1]) / (static_cast<T>(4) * q3_mag);
            q[3] = q3_mag;
        }


        return q.Normalize();
    }

    template <typename T>
    Angle<T> DCM<T>::ToEuler(const TaitBryanOrder &rotOrder) const
    {
        Angle<T> euler;

        switch (rotOrder)
        {
        case TaitBryanOrder::XYZ:
        {
            euler[0] = atan2(this->mat[1][2], this->mat[2][2]);
            euler[1] = atan2(-this->mat[0][2], sqrt(this->mat[0][0] * this->mat[0][0] + this->mat[0][1] * this->mat[0][1]));
            euler[2] = atan2(this->mat[0][1], this->mat[0][0]);

            break;
        }
        case TaitBryanOrder::XZY:
        {
            euler[0] = atan2(-this->mat[2][1], this->mat[1][1]);
            euler[1] = atan2(this->mat[0][2], sqrt(this->mat[0][0] * this->mat[0][0] + this->mat[0][2] * this->mat[0][2]));
            euler[2] = atan2(-this->mat[0][2], this->mat[0][0]);

            break;
        }
        case TaitBryanOrder::YXZ:
        {
            euler[0] = atan2(-this->mat[0][2], this->mat[2][2]);
            euler[1] = atan2(this->mat[1][2], sqrt(this->mat[1][0] * this->mat[1][0] + this->mat[1][1] * this->mat[1][1]));
            euler[2] = atan2(-this->mat[1][0], this->mat[1][1]);

            break;
        }
        case TaitBryanOrder::YZX:
        {
            euler[0] = atan2(this->mat[2][0], this->mat[0][0]);
            euler[1] = atan2(-this->mat[1][0], sqrt(this->mat[1][1] * this->mat[1][1] + this->mat[1][2] * this->mat[1][2]));
            euler[2] = atan2(this->mat[1][2], this->mat[1][1]);

            break;
        }
        case TaitBryanOrder::ZXY:
        {
            euler[0] = atan2(this->mat[1][0], this->mat[0][0]);
            euler[1] = atan2(-this->mat[2][0], sqrt(this->mat[2][1] * this->mat[2][1] + this->mat[2][2] * this->mat[2][2]));
            euler[2] = atan2(this->mat[2][1], this->mat[2][2]);

            break;
        }
        case TaitBryanOrder::ZYX:
        {
            euler[0] = atan2(-this->mat[0][1], this->mat[1][1]);
            euler[1] = atan2(this->mat[2][0], sqrt(this->mat[2][1] * this->mat[2][1] + this->mat[2][2] * this->mat[2][2]));
            euler[2] = atan2(-this->mat[2][1], this->mat[2][2]);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Tait-Bryan Order");
        }
        }

        return euler;
    }

    template <typename T>
    Angle<T> DCM<T>::ToEuler(const EulerOrder &rotOrder) const
    {
        Angle<T> euler;

        switch (rotOrder)
        {
        case EulerOrder::XYX:
        {
            euler[0] = atan2(this->mat[0][1], -this->mat[0][2]);
            euler[1] = acos(this->mat[0][0]);
            euler[2] = atan2(this->mat[1][0], this->mat[2][0]);

            break;
        }
        case EulerOrder::XZX:
        {
            euler[0] = atan2(this->mat[0][2], this->mat[0][1]);
            euler[1] = acos(this->mat[0][0]);
            euler[2] = atan2(this->mat[2][0], -this->mat[1][0]);

            break;
        }
        case EulerOrder::YXY:
        {
            euler[0] = atan2(this->mat[1][0], this->mat[1][2]);
            euler[1] = acos(this->mat[1][1]);
            euler[2] = atan2(this->mat[0][1], -this->mat[2][1]);

            break;
        }
        case EulerOrder::YZY:
        {
            euler[0] = atan2(this->mat[1][2], -this->mat[1][0]);
            euler[1] = acos(this->mat[1][1]);
            euler[2] = atan2(this->mat[2][1], this->mat[0][1]);

            break;
        }
        case EulerOrder::ZXZ:
        {
            euler[0] = atan2(this->mat[2][1], this->mat[2][0]);
            euler[1] = acos(this->mat[2][2]);
            euler[2] = atan2(this->mat[1][2], -this->mat[0][2]);

            break;
        }
        case EulerOrder::ZYZ:
        {
            euler[0] = atan2(this->mat[2][0], -this->mat[2][1]);
            euler[1] = acos(this->mat[2][2]);
            euler[2] = atan2(this->mat[0][2], this->mat[1][2]);

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }

        return euler;
    }

} // namespace myMath

#endif /* BA9453AD_D478_47EC_9001_44325F419B41 */
