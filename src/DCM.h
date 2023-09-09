#ifndef BA9453AD_D478_47EC_9001_44325F419B41
#define BA9453AD_D478_47EC_9001_44325F419B41

#include "BasicFunctions.h"
#include "Rotation.h"
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

        DCM<T> operator*(const DCM<T> &dcm) const;
        DCM<T> operator*(const Matrix<T, 3, 3> &m) const;

        template <unsigned int C>
        Matrix<T, 3, C> operator*(const Matrix<T, 3, C> &m) const;

        template <unsigned int C>
        DCM<T> operator*(const T (&m)[3][C]) const;
        DCM<T> operator*(const T (&m)[9]) const;

        DCM<T> &operator*=(const DCM<T> &dcm);

        DCM<T> &operator*=(const Matrix<T, 3, 3> &m);
        DCM<T> &operator*=(const T (&m)[3][3]);
        DCM<T> &operator*=(const T (&m)[9]);

        DCM<T> operator-(void) const;

        bool operator==(const DCM<T> &dcm) const;
        bool operator!=(const DCM<T> &dcm) const;

        static DCM<T> Identity(void)
        {
            return DCM<T>(Matrix<T, 3, 3>::Identity());
        }

        void Normalize();
        Quaternion<T> ToQuaternion() const;
        Angle<T> ToEuler(const TaitBryanOrder &rotOrder) const;
        Angle<T> ToEuler(const EulerOrder &rotOrder) const;

        Angle<T> Rotate(const Angle<T> &angle, const TaitBryanOrder &rotOrder, const TaitBryanOrder rotOrderOut) const;
        Angle<T> Rotate(const Angle<T> &angle, const EulerOrder &rotOrder, const TaitBryanOrder rotOrderOut) const;
        Angle<T> Rotate(const Angle<T> &angle, const EulerOrder &rotOrder, const EulerOrder rotOrderOut) const;
        DCM<T> Rotate(const DCM<T> &dcm) const;
        Quaternion<T> Rotate(const Quaternion<T> &q) const;
        Vector<T, 3u> Rotate(const Vector<T, 3u> &v) const;
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
    DCM<T> DCM<T>::operator*(const DCM<T> &dcm) const
    {
        return DCM<T>(Matrix<T, 3, 3>::operator*(dcm));
    }

    template <typename T>
    DCM<T> DCM<T>::operator*(const Matrix<T, 3, 3> &m) const
    {
        return DCM<T>(Matrix<T, 3, 3>::operator*(m));
    }

    template <typename T>
    template <unsigned int C>
    Matrix<T, 3, C> DCM<T>::operator*(const Matrix<T, 3, C> &m) const
    {
        return Matrix<T, 3, C>::operator*(m);
    }

    template <typename T>
    template <unsigned int C>
    DCM<T> DCM<T>::operator*(const T (&m)[3][C]) const
    {
        return DCM<T>(Matrix<T, 3, C>::operator*(m));
    }

    template <typename T>
    DCM<T> DCM<T>::operator*(const T (&rhs)[9]) const
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
        return static_cast<T>(-1) * *this;
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

        q.Normalize();

        return q;
    }

    template <typename T>
    Angle<T> DCM<T>::ToEuler(const TaitBryanOrder &rotOrder) const
    {
        Angle<T> euler;

        switch (rotOrder)
        {
        case TaitBryanOrder::XYZ:
        {
            euler[1] = std::asin(this->mat[2][0]);

            if (isZero(ABS(euler[1]) - Constants::PI / 2.0))
            {
                // std::cout << "WARNING! Gimbal Lock for XYZ rotation" << std::endl;

                euler[0] = std::atan2(this->mat[0][1], this->mat[1][1]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(-this->mat[2][1], this->mat[2][2]);
                euler[2] = std::atan2(-this->mat[1][0], this->mat[0][0]);

                if (!isZero((-std::cos(euler[1]) * std::sin(euler[0])) - (this->mat[2][1])))
                {
                    euler[1] = Constants::PI - euler[1];
                }
            }

            break;
        }
        case TaitBryanOrder::XZY:
        {
            euler[1] = std::asin(-this->mat[1][0]);

            if (isZero(ABS(euler[1]) - Constants::PI / 2.0))
            {
                // std::cout << "WARNING! Gimbal Lock for XZY rotation" << std::endl;

                euler[0] = std::atan2(this->mat[0][2], this->mat[2][2]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[1][2], this->mat[1][1]);
                euler[2] = std::atan2(this->mat[2][0], this->mat[0][0]);

                if (!isZero((std::cos(euler[0]) * std::cos(euler[1])) - (this->mat[1][1])))
                {
                    euler[1] = Constants::PI - euler[1];
                }
            }

            break;
        }
        case TaitBryanOrder::YXZ:
        {
            euler[1] = std::asin(-this->mat[2][1]);

            if (isZero(ABS(euler[1]) - Constants::PI / 2.0))
            {
                // std::cout << "WARNING! Gimbal Lock for YXZ rotation" << std::endl;

                euler[0] = std::atan2(this->mat[1][0], this->mat[0][0]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[2][0], this->mat[2][2]);
                euler[2] = std::atan2(this->mat[0][1], this->mat[1][1]);

                if (!isZero((std::cos(euler[0]) * std::cos(euler[1])) - (this->mat[2][2])))
                {
                    euler[1] = Constants::PI - euler[1];
                }
            }

            break;
        }
        case TaitBryanOrder::YZX:
        {
            euler[1] = std::asin(this->mat[0][1]);

            if (isZero(ABS(euler[1]) - Constants::PI / 2.0))
            {
                // std::cout << "WARNING! Gimbal Lock for YZX rotation" << std::endl;

                euler[0] = std::atan2(this->mat[1][2], this->mat[2][2]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(-this->mat[0][2], this->mat[0][0]);
                euler[2] = std::atan2(-this->mat[2][1], this->mat[1][1]);

                if (!isZero((std::cos(euler[0]) * std::cos(euler[1])) - (this->mat[0][0])))
                {
                    euler[1] = Constants::PI - euler[1];
                }
            }

            break;
        }
        case TaitBryanOrder::ZXY:
        {
            euler[1] = std::asin(this->mat[1][2]);

            if (isZero(ABS(euler[1]) - Constants::PI / 2.0))
            {
                // std::cout << "WARNING! Gimbal Lock for ZXY rotation" << std::endl;

                euler[0] = std::atan2(this->mat[0][1], this->mat[0][0]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(-this->mat[1][0], this->mat[1][1]);
                euler[2] = std::atan2(-this->mat[0][2], this->mat[2][2]);

                if (!isZero((std::cos(euler[0]) * std::cos(euler[1])) - (this->mat[1][1])))
                {
                    euler[1] = Constants::PI - euler[1];
                }
            }

            break;
        }
        case TaitBryanOrder::ZYX:
        {
            euler[1] = std::asin(-this->mat[0][2]);

            if (isZero(ABS(euler[1]) - Constants::PI / 2.0))
            {
                // std::cout << "WARNING! Gimbal Lock for ZYX rotation" << std::endl;

                euler[0] = std::atan2(this->mat[2][1], this->mat[1][1]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[0][1], this->mat[0][0]);
                euler[2] = std::atan2(this->mat[1][2], this->mat[2][2]);

                if (!isZero((std::cos(euler[0]) * std::cos(euler[1])) - (this->mat[0][0])))
                {
                    euler[1] = Constants::PI - euler[1];
                }
            }

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Tait-Bryan Order");
        }
        }

        euler.wrapAnglesMinusPiToPi();

        DCM<T> check = euler.ToDCM(rotOrder);

        if (*this != check)
        {
            std::cout << "WARNING! Conversion to Tait-Bryan sequence: " << static_cast<unsigned int>(rotOrder) << " is not possible!" << std::endl;
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
            euler[1] = std::acos(this->mat[0][0]);

            if (isZero(euler[1]))
            {
                euler[0] = std::atan2(this->mat[1][2], this->mat[1][1]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[0][1], -this->mat[0][2]);
                euler[2] = std::atan2(this->mat[1][0], this->mat[2][0]);

                if (isZero(euler[0]))
                {
                    euler[1] = std::atan2(-this->mat[0][2], this->mat[0][0]);
                }
                else
                {
                    euler[1] = std::atan2(this->mat[0][1] / std::sin(euler[0]), this->mat[0][0]);
                }
            }

            break;
        }
        case EulerOrder::XZX:
        {
            euler[1] = std::acos(this->mat[0][0]);

            if (isZero(euler[1]))
            {
                euler[0] = std::atan2(this->mat[1][2], this->mat[1][1]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[0][2], this->mat[0][1]);
                euler[2] = std::atan2(this->mat[2][0], -this->mat[1][0]);

                if (isZero(euler[0]))
                {
                    euler[1] = std::atan2(this->mat[0][1], this->mat[0][0]);
                }
                else
                {
                    euler[1] = std::atan2(this->mat[0][2] / std::sin(euler[0]), this->mat[0][0]);
                }
            }

            break;
        }
        case EulerOrder::YXY:
        {
            euler[1] = std::acos(this->mat[1][1]);

            if (isZero(euler[1]))
            {
                euler[0] = std::atan2(this->mat[2][0], this->mat[2][2]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[1][0], this->mat[1][2]);
                euler[2] = std::atan2(this->mat[0][1], -this->mat[2][1]);

                if (isZero(euler[0]))
                {
                    euler[1] = std::atan2(this->mat[1][2], this->mat[1][1]);
                }
                else
                {
                    euler[1] = std::atan2(this->mat[1][0] / std::sin(euler[0]), this->mat[1][1]);
                }
            }

            break;
        }
        case EulerOrder::YZY:
        {
            euler[1] = std::acos(this->mat[1][1]);

            if (isZero(euler[1]))
            {
                euler[0] = std::atan2(-this->mat[0][2], this->mat[0][0]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[1][2], -this->mat[1][0]);
                euler[2] = std::atan2(this->mat[2][1], this->mat[0][1]);

                if (isZero(euler[0]))
                {
                    euler[1] = std::atan2(-this->mat[1][0], this->mat[1][1]);
                }
                else
                {
                    euler[1] = std::atan2(this->mat[1][2] / std::sin(euler[0]), this->mat[1][1]);
                }
            }

            break;
        }
        case EulerOrder::ZXZ:
        {
            euler[1] = std::acos(this->mat[2][2]);

            if (isZero(euler[1]))
            {
                euler[0] = std::atan2(this->mat[0][1], this->mat[0][0]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[2][0], -this->mat[2][1]);
                euler[2] = std::atan2(this->mat[0][2], this->mat[1][2]);

                if (isZero(euler[0]))
                {
                    euler[1] = std::atan2(-this->mat[2][1], this->mat[2][2]);
                }
                else
                {
                    euler[1] = std::atan2(this->mat[2][0] / std::sin(euler[0]), this->mat[2][2]);
                }
            }

            break;
        }
        case EulerOrder::ZYZ:
        {
            euler[1] = std::acos(this->mat[2][2]);

            if (isZero(euler[1]))
            {
                euler[0] = std::atan2(this->mat[0][1], this->mat[0][0]);
                euler[2] = static_cast<T>(0);
            }
            else
            {
                euler[0] = std::atan2(this->mat[2][1], this->mat[2][0]);

                if (isZero(std::cos(euler[0])))
                {
                    euler[1] = std::atan2(this->mat[2][1], this->mat[2][2]);
                    euler[2] = std::atan2(this->mat[1][2], -this->mat[1][1]);
                }
                else
                {
                    euler[1] = std::atan2(this->mat[2][0] / std::cos(euler[0]), this->mat[2][2]);
                    euler[2] = std::atan2(this->mat[1][2], -this->mat[0][2]);
                }
            }

            break;
        }
        default:
        {
            throw std::invalid_argument("Invalid Euler Order");
        }
        }

        DCM<T> check = euler.ToDCM(rotOrder);

        if (*this != check)
        {
            std::cout << "WARNING! Conversion to Euler sequence: " << static_cast<unsigned int>(rotOrder) << " is not possible!" << std::endl;
        }

        return euler;
    }

    template <typename T>
    Angle<T> DCM<T>::Rotate(const Angle<T> &angle, const TaitBryanOrder &rotOrder, const TaitBryanOrder rotOrderOut) const
    {
        return ((*this) * angle.ToDCM(rotOrder)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> DCM<T>::Rotate(const Angle<T> &angle, const EulerOrder &rotOrder, const TaitBryanOrder rotOrderOut) const
    {
        return ((*this) * angle.ToDCM(rotOrder)).ToEuler(rotOrderOut);
    }

    template <typename T>
    Angle<T> DCM<T>::Rotate(const Angle<T> &angle, const EulerOrder &rotOrder, const EulerOrder rotOrderOut) const
    {
        return ((*this) * angle.ToDCM(rotOrder)).ToEuler(rotOrderOut);
    }

    template <typename T>
    DCM<T> DCM<T>::Rotate(const DCM<T> &dcm) const
    {
        return (*this) * dcm;
    }

    template <typename T>
    Quaternion<T> DCM<T>::Rotate(const Quaternion<T> &q) const
    {
        return q * ToQuaternion();
    }

    template <typename T>
    Vector<T, 3u> DCM<T>::Rotate(const Vector<T, 3u> &v) const
    {
        return (*this) * v;
    }

} // namespace myMath

#endif /* BA9453AD_D478_47EC_9001_44325F419B41 */
