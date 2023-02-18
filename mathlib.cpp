#include "mathlib.h"

////////////////////////////////
//                            //
// Basic function definitions //
//                            //
////////////////////////////////
inline unsigned int myMath::factorial(const unsigned int x)
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

inline int myMath::factorial(int x)
{
    x = x > 0 ? (static_cast<int>(factorial(static_cast<unsigned int>(x)))) : (-1 * static_cast<int>(factorial(static_cast<unsigned int>(x))));

    return x;
}

template <class T>
inline T myMath::SQ(const T x)
{
    return (x * x);
}

////////////////////////////////////
//                                //
// Class Vector<T, R> definitions //
//                                //
////////////////////////////////////

template <class T, unsigned int R>
inline myMath::Vector<T, R>::Vector()
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = 0.0;
    }
}

template <class T, unsigned int R>
inline myMath::Vector<T, R>::Vector(const T &x)
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = x;
    }
}

template <class T, unsigned int R>
inline myMath::Vector<T, R>::Vector(const T x[R])
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = x[i];
    }
}

template <class T, unsigned int R>
inline myMath::Vector<T, R>::Vector(const myMath::Vector<T, R> &obj)
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = obj.vec[i];
    }
}

template <class T, unsigned int R>
inline myMath::Vector<T, R>::~Vector()
{
    delete this;
}

template <class T, unsigned int R>
inline T &myMath::Vector<T, R>::operator[](unsigned int i)
{
    return this->vec[i];
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator=(const T &x)
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = x;
    }

    return *this;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator=(const T x[R])
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = x[i];
    }

    return *this;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator=(const myMath::Vector<T, R> &obj)
{
    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] = obj.vec[i];
    }

    return *this;
}

template <class T, unsigned int C>
inline myMath::Vector<T, C> operator*(const double &x, const myMath::Vector<T, C> &obj)
{
    myMath::Vector<T, C> tmp{obj};

    for (unsigned int i{0}; i < C; i++)
    {
        tmp.vec[i] *= x;
    }

    return tmp;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> myMath::Vector<T, R>::operator+(const myMath::Vector<T, R> &obj)
{
    Vector<T, R> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        tmp.vec[i] += obj.vec[i];
    }

    return tmp;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> myMath::Vector<T, R>::operator-(const myMath::Vector<T, R> &obj)
{
    Vector<T, R> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        tmp.vec[i] -= obj.vec[i];
    }

    return tmp;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> myMath::Vector<T, R>::operator*(const double &x)
{
    Vector<T, R> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        tmp.vec[i] *= x;
    }

    return tmp;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> myMath::Vector<T, R>::operator/(const double &x)
{
    Vector<T, R> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        tmp.vec[i] /= x;
    }

    return tmp;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator+=(const myMath::Vector<T, R> &obj)
{

    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] += obj.vec[i];
    }

    return *this;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator-=(const myMath::Vector<T, R> &obj)
{

    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] -= obj.vec[i];
    }

    return *this;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator*=(const double &x)
{

    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] *= x;
    }

    return *this;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> &myMath::Vector<T, R>::operator/=(const double &x)
{

    for (unsigned int i{0}; i < R; i++)
    {
        this->vec[i] /= x;
    }

    return *this;
}

template <class T, unsigned int R>
inline T myMath::Vector<T, R>::magnitude(void)
{
    T tmp = static_cast<T>(0.0);

    for (unsigned int i{0}; i < R; i++)
    {
        tmp += SQ(this->vec[i], 2);
    }
}

template <class T, unsigned int R>
inline T myMath::Vector<T, R>::dot(const myMath::Vector<T, R> &obj)
{
    T prod{static_cast<T>(0.0)};

    for (unsigned int i{0}; i < R; i++)
    {
        prod += this->vec[i] * obj.vec[i];
    }

    return prod;
}

template <class T, unsigned int R>
inline myMath::Vector<T, R> myMath::Vector<T, R>::cross(const myMath::Vector<T, R> &obj)
{
    if (R == 3u)
    {
        Vector<double, 3u> prod{0.0};
        Matrix3d concat{0.0};

        for (unsigned int i{0}; i < 3u; i++)
        {
            concat.mat[0][i] = (2*((i + 2) % 2 == 0) - 1);
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
inline myMath::Matrix<T, R, C>::Matrix()
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = 0.0;
        }
    }
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C>::~Matrix()
{
    delete this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C>::Matrix(const double &x)
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = x;
        }
    }
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C>::Matrix(const double x[R][C])
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = x[i][j];
        }
    }
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C>::Matrix(const myMath::Matrix<T, R, C> &obj)
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Vector<T, C> &myMath::Matrix<T, R, C>::operator[](unsigned int i)
{
    return this->mat[i];
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator=(const double &x)
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = x;
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator=(const double x[R][C])
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = x[i][j];
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator=(const myMath::Matrix<T, R, C> &obj)
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> myMath::Matrix<T, R, C>::operator+(const myMath::Matrix<T, R, C> &obj)
{
    Matrix<T, R, C> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            tmp.mat[i].vec[j] += obj.mat[i].vec[j];
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> myMath::Matrix<T, R, C>::operator-(const myMath::Matrix<T, R, C> &obj)
{
    Matrix<T, R, C> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            tmp.mat[i].vec[j] -= obj.mat[i].vec[j];
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> myMath::Matrix<T, R, C>::operator*(const myMath::Matrix<T, R, C> &obj)
{
    myMath::Matrix<T, R, C> tmp;

    for (unsigned int i{0}; i < R; i++)
    {

        for (unsigned int j{0}; j < C; j++)
        {
            T tmp_sum = static_cast<T>(0.0);
            for (unsigned int k{0}; k < C; k++)
            {
                tmp_sum += this->mat[i].vec[k] * obj.mat[k].vec[j];
            }

            tmp.mat[i].vec[j] = tmp_sum;
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C, unsigned int C2>
inline myMath::Matrix<T, R, C2> operator*(const myMath::Matrix<T, R, C> &lhs, const myMath::Matrix<T, C, C2> &rhs)
{
    myMath::Matrix<T, R, C2> tmp;

    for (unsigned int i{0}; i < R; i++)
    {

        for (unsigned int j{0}; j < C2; j++)
        {
            T tmp_sum = static_cast<T>(0.0);
            for (unsigned int k{0}; k < C; k++)
            {
                tmp_sum += lhs.mat[i].vec[k] * rhs.mat[k].vec[j];
            }

            tmp.mat[i].vec[j] = tmp_sum;
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> myMath::Matrix<T, R, C>::operator*(const double &x)
{
    Matrix<T, R, C> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            tmp.mat[i].vec[j] *= x;
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Vector<T, R> myMath::Matrix<T, R, C>::operator*(const myMath::Vector<T, C> &obj)
{
    myMath::Vector<T, R> tmp{0.0};

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            tmp.vec[i] += this->mat[i].vec[j] * obj.vec[j];
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> operator*(const double &x, const myMath::Matrix<T, R, C> &obj)
{
    myMath::Matrix<T, R, C> tmp{obj};

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            tmp.mat[i].vec[j] *= x;
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> myMath::Matrix<T, R, C>::operator/(const double &x)
{
    myMath::Matrix<T, R, C> tmp{*this};

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            tmp.mat[i].vec[j] /= x;
        }
    }

    return tmp;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator+=(const myMath::Matrix<T, R, C> &obj)
{

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] += obj.mat[i].vec[j];
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator-=(const myMath::Matrix<T, R, C> &obj)
{

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] -= obj.mat[i].vec[j];
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator*=(const myMath::Matrix<T, R, C> &obj)
{
    Matrix<T, R, C> tmp;

    for (unsigned int i{0}; i < R; i++)
    {

        for (unsigned int j{0}; j < C; j++)
        {
            T tmp_sum = static_cast<T>(0.0);
            for (unsigned int k{0}; k < C; k++)
            {
                tmp_sum += this->mat[i].vec[k] * obj.mat[k].vec[j];
            }

            tmp.mat[i].vec[j] = tmp_sum;
        }
    }

    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] = tmp.mat[i].vec[j];
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator*=(const double &x)
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] *= x;
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> &myMath::Matrix<T, R, C>::operator/=(const double &x)
{
    for (unsigned int i{0}; i < R; i++)
    {
        for (unsigned int j{0}; j < C; j++)
        {
            this->mat[i].vec[j] /= x;
        }
    }

    return *this;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, R, C> myMath::Matrix<T, R, C>::identity(void)
{
    myMath::Matrix<T, R, C> identityMat(0.0);

    if (R == C)
    {
        for (unsigned int i{0}; i < R; i++)
        {
            identityMat.mat[i].vec[i] = 1.0;
        }
    }

    return identityMat;
}

template <class T, unsigned int R, unsigned int C>
inline myMath::Matrix<T, C, R> myMath::Matrix<T, R, C>::Transpose(void)
{
    myMath::Matrix<T, C, R> tmp;

    for (unsigned int i{0}; i < C; i++)
    {
        for (unsigned int j{0}; j < R; j++)
        {
            tmp.mat[i].vec[j] = this->mat[j].vec[i];
        }
    }

    return tmp;
}

////////////////////////////////
//                            //
// Class Matrix2d definitions //
//                            //
////////////////////////////////
inline myMath::Matrix2d::Matrix2d()
{
    for (unsigned int i{0}; i < 2u; i++)
    {
        for (unsigned int j{0}; j < 2u; j++)
        {
            this->mat[i].vec[j] = 0.0;
        }
    }
}

inline myMath::Matrix2d::~Matrix2d()
{
    delete this;
}

inline myMath::Matrix2d::Matrix2d(const double &x)
{
    for (unsigned int i{0}; i < 2u; i++)
    {
        for (unsigned int j{0}; j < 2u; j++)
        {
            this->mat[i].vec[j] = x;
        }
    }
}

inline myMath::Matrix2d::Matrix2d(const double x[2][2])
{
    for (unsigned int i{0}; i < 2u; i++)
    {
        for (unsigned int j{0}; j < 2u; j++)
        {
            this->mat[i].vec[j] = x[i][j];
        }
    }
}

inline myMath::Matrix2d::Matrix2d(const myMath::Matrix2d &obj) : Matrix<double, 2, 2>()
{
    for (unsigned int i{0}; i < 2u; i++)
    {
        for (unsigned int j{0}; j < 2u; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

inline myMath::Matrix2d::Matrix2d(const myMath::Matrix<double, 2, 2> &obj)
{
    for (unsigned int i{0}; i < 2u; i++)
    {
        for (unsigned int j{0}; j < 2u; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

inline double myMath::Matrix2d::Minor(unsigned int i, unsigned int j)
{
    return (this->mat[(i == 1u) ? (0u) : (1u)].vec[(j == 1u) ? (0u) : (1u)]);
}

inline myMath::Matrix2d myMath::Matrix2d::Cofactor(void)
{
    Matrix2d tmp;

    for (unsigned int m{0}; m < 2u; m++)
    {
        for (unsigned int n{0}; n < 2u; n++)
        {
            tmp.mat[m].vec[n] = Minor(m, n) * (2*((m + n + 2) % 2 == 0) - 1);
        }
    }

    return tmp;
}

inline myMath::Matrix2d myMath::Matrix2d::Adjoint(void)
{
    Matrix2d adj;

    adj = Cofactor();

    adj = adj.Transpose();

    return adj;
}

inline double myMath::Matrix2d::Determinant(void)
{
    return (this->mat[0].vec[0] * this->mat[1].vec[1] - this->mat[1].vec[0] * this->mat[0].vec[1]);
}

inline myMath::Matrix2d myMath::Matrix2d::Inverse(void)
{
    Matrix2d tmp;
    if (this->Determinant() != 0.0)
    {
        if (this->Determinant() != 0.0)
        {
            tmp = this->Adjoint() / this->Determinant();
        }
        else
        {
            tmp = 0.0;
        }
    }
    return tmp;
}

////////////////////////////////
//                            //
// Class Matrix3d definitions //
//                            //
////////////////////////////////
inline myMath::Matrix3d::Matrix3d()
{
    for (unsigned int i{0}; i < 3u; i++)
    {
        for (unsigned int j{0}; j < 3u; j++)
        {
            this->mat[i].vec[j] = 0.0;
        }
    }
}

inline myMath::Matrix3d::~Matrix3d()
{
    delete this;
}

inline myMath::Matrix3d::Matrix3d(const double &x)
{
    for (unsigned int i{0}; i < 3u; i++)
    {
        for (unsigned int j{0}; j < 3u; j++)
        {
            this->mat[i].vec[j] = x;
        }
    }
}

inline myMath::Matrix3d::Matrix3d(const double x[3][3])
{
    for (unsigned int i{0}; i < 3u; i++)
    {
        for (unsigned int j{0}; j < 3u; j++)
        {
            this->mat[i].vec[j] = x[i][j];
        }
    }
}

inline myMath::Matrix3d::Matrix3d(const myMath::Matrix3d &obj) : Matrix<double, 3, 3>()
{
    for (unsigned int i{0}; i < 3u; i++)
    {
        for (unsigned int j{0}; j < 3u; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

inline myMath::Matrix3d::Matrix3d(const myMath::Matrix<double, 3, 3> &obj)
{
    for (unsigned int i{0}; i < 3u; i++)
    {
        for (unsigned int j{0}; j < 3u; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

inline double myMath::Matrix3d::Minor(unsigned int i, unsigned int j)
{
    Matrix3d minor;

    for (unsigned int m{0}; m < 3u; m++)
    {
        for (unsigned int n{0}; n < 3u; n++)
        {
            if (m != i && n != j)
            {
                minor.mat[m < i ? m : (m - 1u)].vec[n < j ? n : (n - 1u)] = this->mat[m].vec[n];
            }
        }
    }

    return (minor.mat[0].vec[0] * minor.mat[1].vec[1] - minor.mat[0].vec[1] * minor.mat[1].vec[0]);
}

inline myMath::Matrix3d myMath::Matrix3d::Cofactor(void)
{
    Matrix3d tmp;

    for (unsigned int m{0}; m < 3u; m++)
    {
        for (unsigned int n{0}; n < 2u; n++)
        {
            tmp.mat[m].vec[n] = Minor(m, n) * (2*((m + n + 2) % 2 == 0) - 1);
        }
    }

    return tmp;
}

inline myMath::Matrix3d myMath::Matrix3d::Adjoint(void)
{
    Matrix3d adj;

    adj = Cofactor();

    adj = adj.Transpose();

    return adj;
}

inline double myMath::Matrix3d::Determinant(void)
{
    double determ{0.0};
    for (unsigned int j{0}; j < 3u; j++)
    {
        determ += this->mat[0].vec[j] * (2*((j + 2) % 2 == 0) - 1) * this->Minor(0, j);
    }

    return determ;
}

inline myMath::Matrix3d myMath::Matrix3d::Inverse(void)
{
    Matrix3d tmp;
    if (this->Determinant() != 0.0)
    {
        if (this->Determinant() != 0.0)
        {
            tmp = this->Adjoint() / this->Determinant();
        }
        else
        {
            tmp = 0.0;
        }
    }
    return tmp;
}

////////////////////////////////
//                            //
// Class Matrix4d definitions //
//                            //
////////////////////////////////
inline myMath::Matrix4d::Matrix4d()
{
    for (unsigned int i{0}; i < 3u; i++)
    {
        for (unsigned int j{0}; j < 3u; j++)
        {
            this->mat[i].vec[j] = 0.0;
        }
    }
}

inline myMath::Matrix4d::~Matrix4d()
{
    delete this;
}

inline myMath::Matrix4d::Matrix4d(const double &x)
{
    for (unsigned int i{0}; i < 4u; i++)
    {
        for (unsigned int j{0}; j < 4u; j++)
        {
            this->mat[i].vec[j] = x;
        }
    }
}

inline myMath::Matrix4d::Matrix4d(const double x[4][4])
{
    for (unsigned int i{0}; i < 4u; i++)
    {
        for (unsigned int j{0}; j < 4u; j++)
        {
            this->mat[i].vec[j] = x[i][j];
        }
    }
}

inline myMath::Matrix4d::Matrix4d(const myMath::Matrix4d &obj) : Matrix<double, 4, 4>()
{
    for (unsigned int i{0}; i < 4u; i++)
    {
        for (unsigned int j{0}; j < 4u; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

inline myMath::Matrix4d::Matrix4d(const myMath::Matrix<double, 4, 4> &obj)
{
    for (unsigned int i{0}; i < 4u; i++)
    {
        for (unsigned int j{0}; j < 4u; j++)
        {
            this->mat[i].vec[j] = obj.mat[i].vec[j];
        }
    }
}

inline double myMath::Matrix4d::Minor(unsigned int i, unsigned int j)
{
    Matrix3d minor;

    for (unsigned int m{0}; m < 4u; m++)
    {
        for (unsigned int n{0}; n < 4u; n++)
        {
            if (m != i && n != j)
            {
                minor.mat[m < i ? m : (m - 1u)].vec[n < j ? n : (n - 1u)] = this->mat[m].vec[n];
            }
        }
    }

    return minor.Determinant();
}

inline myMath::Matrix4d myMath::Matrix4d::Cofactor(void)
{
    Matrix4d tmp;

    for (unsigned int m{0}; m < 4u; m++)
    {
        for (unsigned int n{0}; n < 4u; n++)
        {
            tmp.mat[m].vec[n] = Minor(m, n) * (2*((m + n + 2) % 2 == 0) - 1);
        }
    }

    return tmp;
}

inline myMath::Matrix4d myMath::Matrix4d::Adjoint(void)
{
    Matrix4d adj;

    adj = Cofactor();

    adj = adj.Transpose();

    return adj;
}

inline double myMath::Matrix4d::Determinant(void)
{
    double determ{0.0};
    for (unsigned int j{0}; j < 4u; j++)
    {
        determ += this->mat[0].vec[j] * (2*((j + 2) % 2 == 0) - 1) * this->Minor(0, j);
    }

    return determ;
}

inline myMath::Matrix4d myMath::Matrix4d::Inverse(void)
{
    Matrix4d tmp;
    if (this->Determinant() != 0.0)
    {
        if (this->Determinant() != 0.0)
        {
            tmp = this->Adjoint() / this->Determinant();
        }
        else
        {
            tmp = 0.0;
        }
    }
    return tmp;
}