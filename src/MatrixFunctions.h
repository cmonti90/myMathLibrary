#ifndef DFB7B78E_BBE0_4E90_AFE6_62E04AA66E04
#define DFB7B78E_BBE0_4E90_AFE6_62E04AA66E04

#include "BasicFunctions.h"
#include "Vector.h"
#include "Matrix.h"

namespace myMath
{
    /////////////////////////////////
    //         DECLARATIONS        //
    /////////////////////////////////
    template <class T, unsigned int R>
    T Dot(const Vector<T, R> &lhs, const Vector<T, R> &rhs);

    template <class T, unsigned int R>
    T Cross(const Vector<T, R> &lhs, const Vector<T, R> &rhs);

    template <class T, unsigned int R>
    T Magnitude(const Vector<T, R> &obj);

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, C, R> Transpose(const Matrix<T, R, C> &obj);

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> OuterProduct(const Vector<T, R> &lhs, const Vector<T, C> &rhs);

    /////////////////////////////////
    //         DEFINITIONS         //
    /////////////////////////////////
    template <class T, unsigned int R>
    T Magnitude(const Vector<T, R> &obj)
    {
        T tmp = static_cast<T>(0.0);

        for (unsigned int i{0u}; i < R; i++)
        {
            tmp += SQ(obj.vec[i], 2);
        }
    }

    template <class T, unsigned int R>
    T Dot(const Vector<T, R> &lhs, const Vector<T, R> &rhs)
    {
        T prod{static_cast<T>(0.0)};

        for (unsigned int i{0u}; i < R; i++)
        {
            prod += lhs.vec[i] * rhs.vec[i];
        }

        return prod;
    }

    template <class T, unsigned int R>
    Vector<T, R> Cross(const Vector<T, R> &lhs, const Vector<T, R> &rhs)
    {
        if (R == 2u || R == 3u)
        {
            Vector<T, R> prod{static_cast<T>(0.0)};
            Matrix<T, R, R> concat{static_cast<T>(0.0)};

            for (unsigned int i{0u}; i < R; i++)
            {
                concat.mat[0][i] = static_cast<T>(2 * ((i + 2) % 2 == 0) - 1);
                concat.mat[1][i] = lhs.vec[i];
                concat.mat[2][i] = rhs.vec[i];
            }

            for (unsigned int i{0u}; i < R; i++)
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

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, C, R> Transpose(const Matrix<T, R, C> &obj)
    {
        Matrix<T, C, R> tmp;

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp[j][i] = obj[i][j];
            }
        }

        return tmp;
    }

    template <class T, unsigned int R, unsigned int C>
    Matrix<T, R, C> OuterProduct(const Vector<T, R> &lhs, const Vector<T, C> &rhs)
    {
        Matrix<T, R, C> tmp{static_cast<T>(0.0)};

        for (unsigned int i{0u}; i < R; i++)
        {
            for (unsigned int j{0u}; j < C; j++)
            {
                tmp.mat[i][j] = lhs.vec[i] * rhs.vec[j];
            }
        }

        return tmp;
    }

} // namespace myMath

#endif /* DFB7B78E_BBE0_4E90_AFE6_62E04AA66E04 */
