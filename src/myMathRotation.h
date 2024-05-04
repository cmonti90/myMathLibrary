#ifndef MYMATH_ROTATION_H
#define MYMATH_ROTATION_H

namespace myMath
{
    typedef unsigned int RotOrderType;

    enum class TaitBryanOrder : RotOrderType
    {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    enum class EulerOrder : RotOrderType
    {
        XYX,
        XZX,
        YXY,
        YZY,
        ZXZ,
        ZYZ
    };

    enum Axis : unsigned int
    {
        X,
        Y,
        Z,
        ALL
    };

    enum class RotType : unsigned int
    {
        ACTIVE,
        PASSIVE
    };
}

#endif // MYMATH_ROTATION_H