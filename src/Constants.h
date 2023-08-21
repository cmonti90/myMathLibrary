#pragma once

#ifndef BB985253_419B_45F5_B678_9A31FB52D408
#define BB985253_419B_45F5_B678_9A31FB52D408

namespace myMath
{

    #define DEFINE_MATH_CONSTEXPR(type, name, value) \
        static constexpr type name = value;
    namespace Constants
    {
        DEFINE_MATH_CONSTEXPR( double, PI, 3.1415926535897932384626433832);
        DEFINE_MATH_CONSTEXPR( double, EULERS_NUM, 2.718281828459045235360287471);
        DEFINE_MATH_CONSTEXPR( double, ZERO_THRESHOLD, 1.0e-16);

        DEFINE_MATH_CONSTEXPR( double, GRAVITY_ACCEL, 9.8067);                    // m / sec
        DEFINE_MATH_CONSTEXPR( double, EARTH_ECCENTRICITY, 0.01671);              // -
        DEFINE_MATH_CONSTEXPR( double, EARTH_FLATTENING, 1.0/298.3);              // -
        DEFINE_MATH_CONSTEXPR( double, EARTH_EQUITORIAL_RADIUS, 6378137.0);       // m
        DEFINE_MATH_CONSTEXPR( double, EARTH_POLAR_RADIUS, 6356752.0);            // m
        DEFINE_MATH_CONSTEXPR( double, EARTH_ROTATION_RATE, 7.2921159e-5);        // rad / sec
        DEFINE_MATH_CONSTEXPR( double, EARTH_MASS, 5.9722e24);                    // kg
        DEFINE_MATH_CONSTEXPR( double, EARTH_GM, 3.9860e14);                      // m^3 / sec^2
        DEFINE_MATH_CONSTEXPR( double, UNIVERSAL_GRAVITATION_CONST, 6.67430e-11); // m^3 / (kg * sec^2)

        DEFINE_MATH_CONSTEXPR( double, LIGHT_SPEED, 299792458.0);              // m / sec
        DEFINE_MATH_CONSTEXPR( double, PERMITTIVITY_VACUUM, 8.8541878128e-12); // F / m
        DEFINE_MATH_CONSTEXPR( double, PERMEABILITY_VACUUM, 1.25663706e-6);    // (m * kg) / (sec^2 * A^2)
        DEFINE_MATH_CONSTEXPR( double, ELECTROSTATIC_CONST, 8.9875517923e109); // (kg * m^3) / (sec^4 * A^2)
        DEFINE_MATH_CONSTEXPR( double, PLANKS_CONST, 6.626068e-34);            // (m^2 * kg) / sec

    }
}

#endif /* BB985253_419B_45F5_B678_9A31FB52D408 */
