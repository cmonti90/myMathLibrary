#pragma once

namespace myMath
{
    constexpr double PI = 3.1415926535897932384626433832;
    constexpr double e = 2.718281828459045235360287471;

    ////////////////////////////////
    //                            //
    // Basic function definitions //
    //                            //
    ////////////////////////////////
    unsigned int factorial(const unsigned int x)
    {
        unsigned int tmp = 1u;

        if (x == 0u)
        {
            return 1u;
        }

        for (unsigned int i{1u}; i <= x; i++)
        {
            tmp *= i;
        }

        return tmp;
    }

    int factorial(int x)
    {
        x = x > 0 ? (static_cast<int>(factorial(static_cast<unsigned int>(x)))) : (-1 * static_cast<int>(factorial(static_cast<unsigned int>(x))));

        return x;
    }

    template <class T>
    T SQ(const T x)
    {
        return (x * x);
    }

    template <class T, unsigned int R>
    class Vector
    {
    public:
        T vec[R];

        Vector();
        Vector(const T &x);
        Vector(const T x[R]);
        Vector(const Vector<T, R> &obj);
        ~Vector();

        T &operator[](const unsigned int i);

        Vector<T, R> &operator=(const T &x);
        Vector<T, R> &operator=(const T x[R]);
        Vector<T, R> &operator=(const Vector<T, R> &obj);

        Vector<T, R> operator+(const Vector<T, R> &obj) const;
        Vector<T, R> operator-(const Vector<T, R> &obj) const;
        Vector<T, R> operator*(const double &x) const;
        Vector<T, R> operator/(const double &x) const;

        Vector<T, R> &operator+=(const Vector<T, R> &obj);
        Vector<T, R> &operator-=(const Vector<T, R> &obj);
        Vector<T, R> &operator*=(const double &x);
        Vector<T, R> &operator/=(const double &x);

        T magnitude(void) const;
        T dot(const Vector<T, R> &obj) const;
        Vector<T, R> cross(const Vector<T, R> &obj) const;
    };

    template <class T, unsigned int R, unsigned int C>
    class Matrix
    {
    public:
        Vector<T, C> mat[R];

        Matrix();
        Matrix(const double &x);
        Matrix(const double x[R][C]);
        Matrix(const Matrix<T, R, C> &obj);
        ~Matrix();

        Vector<T, R> &operator[](const unsigned int i);

        Matrix<T, R, C> &operator=(const double &x);
        Matrix<T, R, C> &operator=(const double x[R][C]);
        Matrix<T, R, C> &operator=(const Matrix<T, R, C> &obj);

        Matrix<T, R, C> operator+(const Matrix<T, R, C> &obj) const;
        Matrix<T, R, C> operator-(const Matrix<T, R, C> &obj) const;
        // Matrix<T, R, C> operator*(const Matrix<T, R, C> &obj) const;
        Matrix<T, R, C> operator*(const double &x) const;
        Vector<T, R> operator*(const Vector<T, C> &obj) const;
        Matrix<T, R, C> operator/(const double &x) const;

        Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &obj);
        // Matrix<T, R, C> &operator*=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator*=(const double &x);
        Matrix<T, R, C> &operator/=(const double &x);

        Matrix<T, R, C> Identity(void) const;
        Matrix<T, C, R> Transpose(void) const;
        void LU_Decomposition(Matrix<T, R, R> &Lmat, Matrix<T, R, R> &Umat) const;
        T Minor(unsigned int i, unsigned int j) const;
        T Determinant(void) const;
    };

    typedef Vector<double, 3u> Vector3d;
    typedef Vector<double, 4u> Vector4d;

    typedef Matrix<double, 2u, 2u> Matrix2d;
    typedef Matrix<double, 3u, 3u> Matrix3d;
    typedef Matrix<double, 4u, 4u> Matrix4d;

    ////////////////////////////////////
    //                                //
    // Class Vector<T, R> definitions //
    //                                //
    ////////////////////////////////////
    template <class T, unsigned int R>
    Vector<T, R>::Vector()
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = 0.0;
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const T &x)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x;
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const T x[R])
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x[i];
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::Vector(const Vector<T, R> &obj)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = obj.vec[i];
        }
    }

    template <class T, unsigned int R>
    Vector<T, R>::~Vector()
    {
        delete this;
    }

    template <class T, unsigned int R>
    T &Vector<T, R>::operator[](const unsigned int i)
    {
        return this->vec[i];
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const T &x)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const T x[R])
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = x[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator=(const Vector<T, R> &obj)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] = obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator+(const Vector<T, R> &obj) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] += obj.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator-(const Vector<T, R> &obj) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] -= obj.vec[i];
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator*(const double &x) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::operator/(const double &x) const
    {
        Vector<T, R> tmp{*this};

        for (unsigned int i{0}; i < R; i++)
        {
            tmp.vec[i] /= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator+=(const Vector<T, R> &obj)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] += obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator-=(const Vector<T, R> &obj)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] -= obj.vec[i];
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator*=(const double &x)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] *= x;
        }

        return *this;
    }

    template <class T, unsigned int R>
    Vector<T, R> &Vector<T, R>::operator/=(const double &x)
    {

        for (unsigned int i{0}; i < R; i++)
        {
            this->vec[i] /= x;
        }

        return *this;
    }

    template <class T, unsigned int C>
    Vector<T, C> operator*(const double &x, const Vector<T, C> &obj)
    {
        Vector<T, C> tmp{obj};

        for (unsigned int i{0}; i < C; i++)
        {
            tmp.vec[i] *= x;
        }

        return tmp;
    }

    template <class T, unsigned int R>
    T Vector<T, R>::magnitude(void) const
    {
        T tmp = static_cast<T>(0.0);

        for (unsigned int i{0}; i < R; i++)
        {
            tmp += SQ(this->vec[i], 2);
        }
    }

    template <class T, unsigned int R>
    T Vector<T, R>::dot(const Vector<T, R> &obj) const
    {
        T prod{static_cast<T>(0.0)};

        for (unsigned int i{0}; i < R; i++)
        {
            prod += this->vec[i] * obj.vec[i];
        }

        return prod;
    }

    template <class T, unsigned int R>
    Vector<T, R> Vector<T, R>::cross(const Vector<T, R> &obj) const
    {
        if (R == 3u)
        {
            Vector<double, 3u> prod{0.0};
            Matrix3d concat{0.0};

            for (unsigned int i{0}; i < 3u; i++)
            {
                concat.mat[0][i] = (2 * ((i + 2) % 2 == 0) - 1);
                concat.mat[1][i] = this->vec[i];
                concat.mat[2][i] = obj.vec[i];
            }

            for (unsigned int i{0}; i < 3u; i++)
            {
                prod.vec[i] = concat.Minor(0, i);
            }

            return prod;
        }
        else
        {
            Vector<T, R> tmp{0.0};

            return tmp;
        }
    }

    ///////////////////////////////////////
    //                                   //
    // Class Matrix<T, R, C> definitions //
    //                                   //
    ///////////////////////////////////////

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
    Matrix<T, R, C>::~Matrix()
    {
        delete this;
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
    Vector<T, R> &Matrix<T, R, C>::operator[](const unsigned int i)
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
    void Matrix<T, R, C>::LU_Decomposition(Matrix<T, R, R> &Lmat, Matrix<T, R, R> &Umat) const
    {
        Matrix<T, R, R> LU{0.0};
        T sum{static_cast<T>(0.0)};

        for (unsigned int i{0u}; i < R; i--)
        {
            for (unsigned int j{i}; j < R; j++)
            {
                sum = static_cast<T>(0.0);

                for (unsigned int k{0u}; k < i; k++)
                {
                    sum += LU.mat[k].vec[i] * LU.mat[j].vec[k];
                }

                LU.mat[j].vec[i] = this->mat[j].vec[i] - sum;
            }

            for (unsigned int j{i + 1u}; j < R; j++)
            {
                sum = static_cast<T>(0.0);

                for (unsigned int k{0u}; k < i; k++)
                {
                    sum += LU.mat[k].vec[j] * LU.mat[i].vec[k];
                }

                LU.mat[i].vec[j] = (static_cast<T>(1.0) / LU.mat[i].vec[i]) * (this->mat[i].vec[j] - sum);
            }
        }

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < R; j++)
            {
                double ratio{-1.0 * static_cast<float>(j) / static_cast<float>(i)};

                if (ratio == -1.0)
                {
                    Lmat.mat[j].vec[i] = static_cast<T>(1.0);
                    Umat.mat[j].vec[i] = LU.mat[j].vec[i];
                }
                else if (ratio < -1.0)
                {
                    Lmat.mat[j].vec[i] = LU.mat[j].vec[i];
                }
                else
                {
                    Umat.mat[j].vec[i] = LU.mat[j].vec[i];
                }
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
}
