#ifndef MATHLIB_H
#define MATHLIB_H

namespace myMath
{
    constexpr double PI = 3.1415926535897932384626433832;
    constexpr double e = 2.718281828459045235360287471;

    unsigned int factorial(const unsigned int x);
    int factorial(int x);

    template<class T>
    T SQ(const T x);

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

        T &operator[](unsigned int i);

        Vector<T, R> &operator=(const T &x);
        Vector<T, R> &operator=(const T x[R]);
        Vector<T, R> &operator=(const Vector<T, R> &obj);

        Vector<T, R> operator+(const Vector<T, R> &obj);
        Vector<T, R> operator-(const Vector<T, R> &obj);

        Vector<T, R> operator*(const double &x);
        Vector<T, R> operator/(const double &x);

        Vector<T, R> &operator+=(const Vector<T, R> &obj);
        Vector<T, R> &operator-=(const Vector<T, R> &obj);
        Vector<T, R> &operator*=(const double &x);
        Vector<T, R> &operator/=(const double &x);

        T magnitude(void);
        T dot(const Vector<T, R> &obj);
        Vector<T, R> cross(const Vector<T, R> &obj);
    };

    template <class T, unsigned int R, unsigned int C>
    class Matrix
    {
    public:
        myMath::Vector<T, C> mat[R];

        Matrix();
        ~Matrix();
        Matrix(const double &x);
        Matrix(const double x[R][C]);
        Matrix(const Matrix<T, R, C> &obj);

        Vector<T, C> &operator[](unsigned int i);

        Matrix<T, R, C> &operator=(const double &x);
        Matrix<T, R, C> &operator=(const double x[R][C]);
        Matrix<T, R, C> &operator=(const Matrix<T, R, C> &obj);

        Matrix<T, R, C> operator+(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> operator-(const Matrix<T, R, C> &obj);

        Matrix<T, R, C> operator*(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> operator*(const double &x);
        Vector<T, R> operator*(const Vector<T, C> &obj);
        Matrix<T, R, C> operator/(const double &x);

        Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator*=(const Matrix<T, R, C> &obj);
        Matrix<T, R, C> &operator*=(const double &x);
        Matrix<T, R, C> &operator/=(const double &x);

        Matrix<T, R, C> identity(void);
        Matrix<T, C, R> Transpose(void);
    };

    class Matrix2d : public Matrix<double, 2u, 2u>
    {
    public:
        Matrix2d();
        ~Matrix2d();
        Matrix2d(const double &x);
        Matrix2d(const double x[2][2]);
        Matrix2d(const Matrix2d &obj);
        Matrix2d(const Matrix<double, 2, 2> &obj);

        /*
                Vector<double, 2u> operator[](unsigned int i);

                Matrix2d &operator=(const double &x);
                Matrix2d &operator=(const double x[2][2]);
                Matrix2d &operator=(const Matrix<double, 2u, 2u> &obj);
                Matrix2d operator+(const Matrix2d &obj);
                Matrix2d operator-(const Matrix2d &obj);*/

        double Minor(unsigned int i, unsigned int j);
        Matrix2d Cofactor(void);
        Matrix2d Adjoint(void);
        double Determinant(void);
        Matrix2d Inverse(void);
    };

    class Matrix3d : public Matrix<double, 3u, 3u>
    {
    public:
        Matrix3d();
        ~Matrix3d();
        Matrix3d(const double &x);
        Matrix3d(const double x[3][3]);
        Matrix3d(const Matrix3d &obj);
        Matrix3d(const Matrix<double, 3, 3> &obj);

        /*
                Vector<double, 3u> operator[](unsigned int i);

                Matrix3d &operator=(const double &x);
                Matrix3d &operator=(const double x[3][3]);
                Matrix3d &operator=(const Matrix<double, 3u, 3u> &obj);
                Matrix3d operator+(const Matrix3d &obj);
                Matrix3d operator-(const Matrix3d &obj);*/

        double Minor(unsigned int i, unsigned int j);
        Matrix3d Cofactor(void);
        Matrix3d Adjoint(void);
        double Determinant(void);
        Matrix3d Inverse(void);
    };

    class Matrix4d : public Matrix<double, 4u, 4u>
    {
    public:
        Matrix4d();
        ~Matrix4d();
        Matrix4d(const double &x);
        Matrix4d(const double x[4][4]);
        Matrix4d(const Matrix4d &obj);
        Matrix4d(const Matrix<double, 4, 4> &obj);

        /*/
                Vector<double, 4u> operator[](unsigned int i);

                Matrix4d &operator=(const double &x);
                Matrix4d &operator=(const double x[4][4]);
                Matrix4d &operator=(const Matrix<double, 4u, 4u> &obj);
                Matrix4d operator+(const Matrix4d &obj);
                Matrix4d operator-(const Matrix4d &obj);*/

        double Minor(unsigned int i, unsigned int j);
        Matrix4d Cofactor(void);
        Matrix4d Adjoint(void);
        double Determinant(void);
        Matrix4d Inverse(void);
    };
}
#endif