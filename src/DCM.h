#ifndef BA9453AD_D478_47EC_9001_44325F419B41
#define BA9453AD_D478_47EC_9001_44325F419B41

#include "Matrix.h"

template <typename T>
class DCM : public Matrix<T, 3, 3>
{
public:
    DCM();
    DCM(const Matrix<T, 3, 3>& m) : Matrix<T, 3, 3>(m);
    DCM(const T (&m)[3][3]) : Matrix<T, 3, 3>(m);
    DCM(const T (&m)[9]) : Matrix<T, 3, 3>(m);

    DCM<T> operator=(const DCM<T>& dcm);
    DCM<T> operator=(const Matrix<T, 3, 3>& m);
    DCM<T> operator=(const T (&m)[3][3]);
    DCM<T> operator=(const T (&m)[9]);

    DCM<T> operator*(const DCM<T>& dcm);
    DCM<T> operator*(const Matrix<T, 3, 3>& m);
    DCM<T> operator*(const T (&m)[3][3]);
    DCM<T> operator*(const T (&m)[9]);

    DCM<T>& operator*=(const DCM<T>& dcm);  
    DCM<T>& operator*=(const Matrix<T, 3, 3>& m);
    DCM<T>& operator*=(const T (&m)[3][3]);
    DCM<T>& operator*=(const T (&m)[9]);

    void Transpose();
    void Inverse();
    void Normalize();

};

#endif /* BA9453AD_D478_47EC_9001_44325F419B41 */
