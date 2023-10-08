#ifndef AF5B087C_AEE8_44A9_A31B_D2AA6668F2A5
#define AF5B087C_AEE8_44A9_A31B_D2AA6668F2A5

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

#endif /* AF5B087C_AEE8_44A9_A31B_D2AA6668F2A5 */
