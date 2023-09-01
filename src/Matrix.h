#pragma once

#ifndef DA413458_D25F_4FB0_9C74_0D7D0BBD5E25
#define DA413458_D25F_4FB0_9C74_0D7D0BBD5E25

#include "Constants.h"
#include "BasicFunctions.h"
#include "Vector.h"

#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace myMath
{
    template <class T, unsigned int R, unsigned int C>
    class Matrix
    {
    public:
        Vector<T, C> mat[R];

        Matrix();
        Matrix(const double &x);
        Matrix(const double (&x)[R][C]);
        Matrix(const Matrix<T, R, C> &obj);
        Matrix(const std::initializer_list<T> &x);
        ~Matrix() = default;

        Vector<T, C> &operator[](const unsigned int i);
        const Vector<T, C> &operator[](const unsigned int i) const;

        Matrix<T, R, C> &operator=(const double &x);
        Matrix<T, R, C> &operator=(const double (&x)[R][C]);
        Matrix<T, R, C> &operator=(const Matrix<T, R, C> &obj);

        Matrix<T, R, C> operator+(const Matrix<T, R, C> &obj) const;
        Matrix<T, R, C> operator-(const Matrix<T, R, C> &obj) const;

        template <unsigned int C2>
        Matrix<T, R, C2> operator*(const Matrix<T, C, C2> &rhs);
        Vector<T, R> operator*(const Vector<T, C> &obj) const;
        Matrix<T, R, C> operator*(const double &x) const;

        Matrix<T, R, C> operator/(const double &x) const;

        Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator*=(const double &x);
        Matrix<T, R, C> &operator/=(const double &x);

        Matrix<T, R, C> operator-() const;

        bool operator==(const Matrix<T, R, C> &obj) const;
        bool operator!=(const Matrix<T, R, C> &obj) const;

        T Minor(unsigned int i, unsigned int j) const;
        T Determinant(void) const;
        Matrix<T, R, C> Inverse(void) const;
        Matrix<T, R, C> Transpose(void) const;
        void TransposeInPlace(void);
        void Invert(void);

        static Matrix<T, R, C> Identity(void)
        {
            Matrix<T, R, C> identityMat(0.0);

            if (R == C)
            {
                for (unsigned int i{0u}; i < R; i++)
                {
                    identityMat.mat[i].vec[i] = static_cast<T>(1.0);
                }
            }

            return identityMat;
        }
    };

    typedef Matrix<double, 2u, 2u> Matrix2d;
    typedef Matrix<double, 3u, 3u> Matrix3d;
    typedef Matrix<double, 4u, 4u> Matrix4d;

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C>::Matrix()
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = static_cast<T>(0.0);
            }
        }
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C>::Matrix(const double &x)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = x;
            }
        }
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C>::Matrix(const double (&x)[R][C])
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = x[j][i];
            }
        }
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C>::Matrix(const Matrix<T, R, C> &obj)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = obj.mat[i].vec[j];
            }
        }
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C>::Matrix(const std::initializer_list<T> &x)
    {
        if (static_cast<unsigned int>(x.size()) == 1u)
        {
            std::memset(this->mat, *(x.begin()), sizeof(this->mat));
        }
        if (static_cast<unsigned int>(x.size()) != (R * C))
        {
            throw std::invalid_argument("Initializer list has incorrect size of " + std::to_string(x.size()) + " instead of " + std::to_string((R * C)) + "");
        }
        else if (x.size() == 0)
        {
            throw std::invalid_argument("Initializer list is empty");
        }
        else
        {
            std::copy(x.begin(), x.end(), this->mat);
        }
    }

    template <class T, unsigned int R, unsigned int C>
    Vector<T, C> &Matrix<T, R, C>::operator[](const unsigned int i)
    {
        return this->mat[i];
    }

    template <class T, unsigned int R, unsigned int C>
    const Vector<T, C> &Matrix<T, R, C>::operator[](const unsigned int i) const
    {
        return this->mat[i];
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator=(const double &x)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = x;
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator=(const double (&x)[R][C])
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = x[i][j];
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator=(const Matrix<T, R, C> &obj)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] = obj.mat[i].vec[j];
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::operator+(const Matrix<T, R, C> &obj) const
    {
        Matrix<T, R, C> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] += obj.mat[i].vec[j];
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::operator-(const Matrix<T, R, C> &obj) const
    {
        Matrix<T, R, C> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] -= obj.mat[i].vec[j];
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    bool Matrix<T, R, C>::operator==(const Matrix<T, R, C> &obj) const
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            if (this->mat[i] != obj.mat[i])
            {
                return false;
            }
        }

        return true;
    }

    template <class T, unsigned int R, unsigned int C>
    bool Matrix<T, R, C>::operator!=(const Matrix<T, R, C> &obj) const
    {
        return !(*this == obj);
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::operator*(const double &x) const
    {
        Matrix<T, R, C> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] *= x;
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Vector<T, R> Matrix<T, R, C>::operator*(const Vector<T, C> &obj) const
    {
        Vector<T, R> tmp{0.0};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.vec[i] += this->mat[i].vec[j] * obj.vec[j];
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::operator/(const double &x) const
    {
        Matrix<T, R, C> tmp{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] /= x;
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator+=(const Matrix<T, R, C> &obj)
    {

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] += obj.mat[i].vec[j];
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator-=(const Matrix<T, R, C> &obj)
    {

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] -= obj.mat[i].vec[j];
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator*=(const double &x)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] *= x;
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> &Matrix<T, R, C>::operator/=(const double &x)
    {
        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                this->mat[i].vec[j] /= x;
            }
        }

        return *this;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::operator-() const
    {
        return static_cast<T>(-1)**this;
    }

    template <class T, unsigned int R, unsigned int C>
    template <unsigned int C2>
    Matrix<T, R, C2> Matrix<T, R, C>::operator*(const Matrix<T, C, C2> &rhs)
    {
        Matrix<T, R, C2> tmp;

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C2; j++)
            {
                T tmp_sum = static_cast<T>(0.0);
                for (unsigned int k{0u}; k < C; k++)
                {
                    tmp_sum += this->mat[i].vec[k] * rhs.mat[k].vec[j];
                }

                tmp.mat[j].vec[i] = tmp_sum;
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> operator*(const double &x, const Matrix<T, R, C> &obj)
    {
        Matrix<T, R, C> tmp{obj};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] *= x;
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C, unsigned int C2>
    Matrix<T, R, C2> operator*=(const Matrix<T, R, C> &lhs, const Matrix<T, C, C2> &rhs)
    {
        Matrix<T, R, C2> tmp;

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C2; j++)
            {
                T tmp_sum = static_cast<T>(0.0);
                for (unsigned int k{0u}; k < C; k++)
                {
                    tmp_sum += lhs.mat[i].vec[k] * rhs.mat[k].vec[j];
                }

                tmp.mat[j].vec[i] = tmp_sum;
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> operator*=(const Matrix<T, R, C> &obj, const double &x)
    {
        Matrix<T, R, C> tmp{obj};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] *= x;
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    T Matrix<T, R, C>::Minor(unsigned int i, unsigned int j) const
    {
        Matrix<T, R, R> minor;

        for (unsigned int m{0u}; m < R; m++)
        {
            for (unsigned int n{0u}; n < R; n++)
            {
                if (m != i && n != j)
                {
                    minor.mat[m < i ? m : (m - 1u)].vec[n < j ? n : (n - 1u)] = this->mat[m].vec[n];
                }
            }
        }

        return (minor.Determinant());
    }

    template <class T, unsigned int R, unsigned int C>
    T Matrix<T, R, C>::Determinant(void) const
    {
        Matrix<T, R, C> tmpMat{*this};
        T det{static_cast<T>(1.0)};

        for (unsigned int i{0u}; i < R; i++)
        {
            unsigned int maxrow = i;

            for (unsigned int j{i + 1u}; j < R; j++)
            {
                if (ABS(tmpMat[j][i]) > ABS(tmpMat[maxrow][i]))
                {
                    maxrow = j;
                }
            }

            if (maxrow != i)
            {
                Vector<T, C> tmpRow{tmpMat[i]};

                tmpMat[i] = tmpMat[maxrow];
                tmpMat[maxrow] = tmpRow;

                det *= static_cast<T>(-1.0);
            }

            for (unsigned int j{i + 1u}; j < R; j++)
            {
                T factor = tmpMat[j][i] / tmpMat[i][i];

                for (unsigned int k{i + 1u}; k < R; k++)
                {
                    tmpMat[j][k] -= factor * tmpMat[i][k];
                }

                tmpMat[j][i] = static_cast<T>(0.0);
            }

            det *= tmpMat[i][i];
        }

        return det;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::Inverse(void) const
    {
        if (ABS(this->Determinant()) > static_cast<T>(Constants::ZERO_THRESHOLD))
        {

            Matrix<T, R, C> tmpMat{*this};
            Matrix<T, R, C> invMat{Matrix<T, R, C>::Identity()};

            for (unsigned int i{0u}; i < R; i++)
            {
                invMat[i][i] = static_cast<T>(1.0);
            }

            for (unsigned int i{0u}; i < R; i++)
            {
                unsigned int maxrow = i;

                for (unsigned int j{i + 1u}; j < R; j++)
                {
                    if (ABS(tmpMat[j][i]) > ABS(tmpMat[maxrow][i]))
                    {
                        maxrow = j;
                    }
                }

                if (maxrow != i)
                {
                    Vector<T, C> tmpRow{tmpMat[i]};

                    tmpMat[i] = tmpMat[maxrow];
                    tmpMat[maxrow] = tmpRow;

                    tmpRow = invMat[i];

                    invMat[i] = invMat[maxrow];
                    invMat[maxrow] = tmpRow;
                }

                for (unsigned int j{i + 1u}; j < R; j++)
                {
                    T factor = tmpMat[j][i] / tmpMat[i][i];

                    for (unsigned int k{i + 1u}; k < R; k++)
                    {
                        tmpMat[j][k] -= factor * tmpMat[i][k];
                    }

                    for (unsigned int k{0u}; k < R; k++)
                    {
                        invMat[j][k] -= factor * invMat[i][k];
                    }

                    tmpMat[j][i] = static_cast<T>(0.0);
                }
            }

            for (int i{static_cast<int>(R) - 1}; i >= 0; i--)
            {
                for (unsigned int j{0u}; j < R; j++)
                {
                    for (unsigned int k{static_cast<unsigned int>(i) + 1u}; k < R; k++)
                    {
                        invMat[i][j] -= tmpMat[i][k] * invMat[k][j];
                    }

                    invMat[i][j] /= tmpMat[i][i];
                }
            }

            return invMat;
        }
        else
        {
            return Matrix<T, R, C>::Identity();
        }
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Matrix<T, R, C>::Transpose(void) const
    {
        Matrix<T, R, C> tmpMat{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmpMat.mat[i].vec[j] = this->mat[j].vec[i];
            }
        }

        return tmpMat;
    }

    template <class T, unsigned int R, unsigned int C>
    void Matrix<T, R, C>::TransposeInPlace(void)
    {
        Matrix<T, R, C> tmpMat{*this};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmpMat.mat[i].vec[j] = this->mat[j].vec[i];
            }
        }

        this = tmpMat;
    }

    template <class T, unsigned int R, unsigned int C>
    void Matrix<T, R, C>::Invert(void)
    {
        if (ABS(this->Determinant()) > static_cast<T>(Constants::ZERO_THRESHOLD))
        {
            Matrix<T, R, C> tmpMat{*this};
            Matrix<T, R, C> invMat{Matrix<T, R, C>::Identity()};

            for (unsigned int i{0u}; i < R; i++)
            {
                invMat[i][i] = static_cast<T>(1.0);
            }

            for (unsigned int i{0u}; i < R; i++)
            {
                unsigned int maxrow = i;

                for (unsigned int j{i + 1u}; j < R; j++)
                {
                    if (ABS(tmpMat[j][i]) > ABS(tmpMat[maxrow][i]))
                    {
                        maxrow = j;
                    }
                }

                if (maxrow != i)
                {
                    Vector<T, C> tmpRow{tmpMat[i]};

                    tmpMat[i] = tmpMat[maxrow];
                    tmpMat[maxrow] = tmpRow;

                    tmpRow = invMat[i];

                    invMat[i] = invMat[maxrow];
                    invMat[maxrow] = tmpRow;
                }

                for (unsigned int j{i + 1u}; j < R; j++)
                {
                    T factor = tmpMat[j][i] / tmpMat[i][i];

                    for (unsigned int k{i + 1u}; k < R; k++)
                    {
                        tmpMat[j][k] -= factor * tmpMat[i][k];
                    }

                    for (unsigned int k{0u}; k < R; k++)
                    {
                        invMat[j][k] -= factor * invMat[i][k];
                    }

                    tmpMat[j][i] = static_cast<T>(0.0);
                }
            }

            for (int i{static_cast<int>(R) - 1}; i >= 0; i--)
            {
                for (unsigned int j{0u}; j < R; j++)
                {
                    for (unsigned int k{static_cast<unsigned int>(i) + 1u}; k < R; k++)
                    {
                        invMat[i][j] -= tmpMat[i][k] * invMat[k][j];
                    }

                    invMat[i][j] /= tmpMat[i][i];
                }
            }

            this = invMat;
        }
    }
}

#endif /* DA413458_D25F_4FB0_9C74_0D7D0BBD5E25 */
