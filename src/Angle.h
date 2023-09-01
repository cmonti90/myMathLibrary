#ifndef B4D2FB34_E82B_4930_84AF_12D1E557452E
#define B4D2FB34_E82B_4930_84AF_12D1E557452E

#include "Vector.h"

namespace myMath
{
    enum class EulerOrder : unsigned int
    {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX,

    };

    enum class TaitBryanOrder : unsigned int
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
        ROLL,
        PITCH,
        YAW
    };

    template <typename T>
    class DCM;

    template <typename T>
    class Quaternion;

    template <typename T>
    class Angle : public Vector<T, 3u>
    {
    };
} // namespace myMath

#include "DCM.h"
#include "Quaternion.h"

namespace myMath
{

}

#endif /* B4D2FB34_E82B_4930_84AF_12D1E557452E */
