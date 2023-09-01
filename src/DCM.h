#ifndef BA9453AD_D478_47EC_9001_44325F419B41
#define BA9453AD_D478_47EC_9001_44325F419B41

#include "Matrix.h"

#include <cmath>

namespace myMath
{
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

        void Normalize();
        Quaternion<T> ToQuaternion() const;
    };
} // namespace myMath

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
    DCM<T>::DCM(const T (&m)[9]) : Matrix<T, 3, 3>(m)
    {
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

        q[0] = static_cast<T>(0.5) * sqrt(static_cast<T>(1) + this->mat[0][0] + this->mat[1][1] + this->mat[2][2]);
        q[1] = (this->mat[2][1] - this->mat[1][2]) / (static_cast<T>(4) * q[0]);
        q[2] = (this->mat[0][2] - this->mat[2][0]) / (static_cast<T>(4) * q[0]);
        q[3] = (this->mat[1][0] - this->mat[0][1]) / (static_cast<T>(4) * q[0]);

        return q.Normalize();
    }

} // namespace myMath

#endif /* BA9453AD_D478_47EC_9001_44325F419B41 */
