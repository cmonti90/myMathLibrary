#ifndef DA413458_D25F_4FB0_9C74_0D7D0BBD5E25
#define DA413458_D25F_4FB0_9C74_0D7D0BBD5E25

#include "BasicFunctions.h"
#include "Vector.h"

namespace myMath
{
    template <class T, unsigned int R, unsigned int C>
    class Matrix
    {
    public:
        Vector<T, C> mat[R];

        Matrix();
        Matrix(const double &x);
        Matrix(const double x[R][C]);
        Matrix(const Matrix<T, R, C> &obj);
        ~Matrix() = default;

        Vector<T, C> &operator[](const unsigned int i);
        const Vector<T, C> &operator[](const unsigned int i) const;

        Matrix<T, R, C> &operator=(const double &x);
        Matrix<T, R, C> &operator=(const double x[R][C]);
        Matrix<T, R, C> &operator=(const Matrix<T, R, C> &obj);

        Matrix<T, R, C> operator+(const Matrix<T, R, C> &obj) const;
        Matrix<T, R, C> operator-(const Matrix<T, R, C> &obj) const;
        Matrix<T, R, C> operator*(const double &x) const;
        Vector<T, R> operator*(const Vector<T, C> &obj) const;
        Matrix<T, R, C> operator/(const double &x) const;

        Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator*=(const double &x);
        Matrix<T, R, C> &operator/=(const double &x);

        Matrix<T, R, C> Identity(void) const;
        Matrix<T, C, R> Transpose(void) const;
        void LU_Decomposition(Matrix<T, R, C> &Lmat, Matrix<T, R, C> &Umat) const;
        T Minor(unsigned int i, unsigned int j) const;
        T Determinant(void) const;
        bool Invertable(void) const;
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
                this->mat[i].vec[j] = 0.0;
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
    Matrix<T, R, C>::Matrix(const double x[R][C])
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
    Matrix<T, R, C> &Matrix<T, R, C>::operator=(const double x[R][C])
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

    template <class T, unsigned int R, unsigned int C, unsigned int C2>
    Matrix<T, R, C2> operator*(const Matrix<T, R, C> &lhs, const Matrix<T, C, C2> &rhs)
    {
        Matrix<T, R, C2> tmp;

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C2; j++)
            {
                T tmp_sum = static_cast<T>(0.0);
                for (unsigned int k{0}; k < C; k++)
                {
                    tmp_sum += lhs.mat[i].vec[k] * rhs.mat[k].vec[j];
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
                for (unsigned int k{0}; k < C; k++)
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
    Matrix<T, R, C> Matrix<T, R, C>::Identity(void) const
    {
        Matrix<T, R, C> identityMat(0.0);

        if (R == C)
        {
            for (unsigned int i{0u}; i < R; i++)
            {
                identityMat.mat[i].vec[i] = 1.0;
            }
        }

        return identityMat;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, C, R> Matrix<T, R, C>::Transpose(void) const
    {
        Matrix<T, C, R> tmp;

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i].vec[j] = this->mat[j].vec[i];
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    void Matrix<T, R, C>::LU_Decomposition(Matrix<T, R, C> &Lmat, Matrix<T, R, C> &Umat) const
    {
        // Matrix<T, R, C> LU{0.0};
        T sum{static_cast<T>(0.0)};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{i}; j < R; j++)
            {
                sum = static_cast<T>(0.0);

                for (unsigned int k{0u}; k < i; k++)
                {
                    sum += Lmat.mat[i].vec[k] * Umat.mat[k].vec[j];
                }

                Umat.mat[i].vec[j] = this->mat[i].vec[j] - sum;
            }

            for (unsigned int j{i + 1u}; j < R; j++)
            {
                sum = static_cast<T>(0.0);

                for (unsigned int k{0u}; k < i; k++)
                {
                    sum += Lmat.mat[j].vec[k] * Umat.mat[k].vec[i];
                }

                Lmat.mat[i].vec[j] = (static_cast<T>(1.0) / Umat.mat[i].vec[i]) * (this->mat[j].vec[i] - sum);
            }
        }
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
        Matrix<T, R, R> Lmat;
        Matrix<T, R, R> Umat;

        this->LU_Decomposition(Lmat, Umat);

        T det_val{static_cast<T>(1.0)};

        for (unsigned int i{0u}; i < R; i++)
        {
            det_val *= Umat[i][i];
        }

        return det_val;
    }

    template <class T, unsigned int R, unsigned int C>
    bool Matrix<T, R, C>::Invertable(void) const
    {
        if ((R != C) || ABS(this->Determinant()) < Constants::ZERO_THRESHOLD)
        {
            return false;
        }

        return true;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> Inverse(const Matrix<T, R, C> &obj)
    {
        Matrix<T, R, C> tmp{obj};

        if (0)
        {
            // TODO: Inverse Algorithm

            return tmp;
        }
        else
        {
            return obj;
        }
    }
}

#endif /* DA413458_D25F_4FB0_9C74_0D7D0BBD5E25 */
