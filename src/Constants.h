#pragma once

#ifndef BB985253_419B_45F5_B678_9A31FB52D408
#define BB985253_419B_45F5_B678_9A31FB52D408

namespace myMath
{

    #define DEFINE_MATH_CONSTEXPR(type, name, value) \
        static constexpr type name = value;
    namespace Constants
    {
        DEFINE_MATH_CONSTEXPR( double, PI, 3.14159265358979323846264)
        DEFINE_MATH_CONSTEXPR( double, EULERS_NUM, 2.71828182845904523536)
        DEFINE_MATH_CONSTEXPR( double, ZERO_THRESHOLD, 1.0e-12)

        // Earth Parameters
        DEFINE_MATH_CONSTEXPR( double, GRAVITY_ACCEL, 9.8067)                    // m / sec
        DEFINE_MATH_CONSTEXPR( double, EARTH_ECCENTRICITY, 0.01671)              // -
        DEFINE_MATH_CONSTEXPR( double, EARTH_FLATTENING, 1.0/298.3)              // -
        DEFINE_MATH_CONSTEXPR( double, EARTH_EQUITORIAL_RADIUS, 6378137.0)       // m
        DEFINE_MATH_CONSTEXPR( double, EARTH_POLAR_RADIUS, 6356752.314)          // m
        DEFINE_MATH_CONSTEXPR( double, EARTH_SEALEVEL_RADIUS, 6378167.0)          // m
        DEFINE_MATH_CONSTEXPR( double, EARTH_ROTATION_RATE, 7.2921159e-5)        // rad / sec
        DEFINE_MATH_CONSTEXPR( double, EARTH_MASS, 5.9722e24)                    // kg
        DEFINE_MATH_CONSTEXPR( double, EARTH_GM, 3.9860e14)                      // m^3 / sec^2
        DEFINE_MATH_CONSTEXPR( double, UNIVERSAL_GRAVITATION_CONST, 6.67430e-11) // m^3 / (kg * sec^2)

        // Astronomical Parameters
        DEFINE_MATH_CONSTEXPR( double, LIGHT_SPEED, 299792458.0)              // m / sec
        DEFINE_MATH_CONSTEXPR( double, PERMITTIVITY_VACUUM, 8.8541878128e-12) // F / m
        DEFINE_MATH_CONSTEXPR( double, PERMEABILITY_VACUUM, 1.25663706e-6)    // (m * kg) / (sec^2 * A^2)
        DEFINE_MATH_CONSTEXPR( double, ELECTROSTATIC_CONST, 8.9875517923e109) // (kg * m^3) / (sec^4 * A^2)
        DEFINE_MATH_CONSTEXPR( double, PLANKS_CONST, 6.626068e-34)            // (m^2 * kg) / sec

        // Air Parameters
        DEFINE_MATH_CONSTEXPR( double, UNIVERSAL_GAS_CONST, 8.31) // J / (mol * K)
        DEFINE_MATH_CONSTEXPR( double, MOLAR_MASS_AIR, 0.02896) // kg / mol
        DEFINE_MATH_CONSTEXPR( double, ADIABATIC_INDEX_AIR, 1.4) // -

        // Angle Conversions
        DEFINE_MATH_CONSTEXPR( double, DEG_TO_RAD, PI / 180.0)
        DEFINE_MATH_CONSTEXPR( double, RAD_TO_DEG, 180.0 / PI)

        // Distance Conversions
        DEFINE_MATH_CONSTEXPR( double, FEET_TO_METERS, 0.3048)
        DEFINE_MATH_CONSTEXPR( double, FEET_TO_MILES, 1.0 / 5280.0)
        DEFINE_MATH_CONSTEXPR( double, FEET_TO_NAUTICAL_MILES, 1.0 / 6076.11549)
        DEFINE_MATH_CONSTEXPR( double, FEET_TO_YARDS, 1.0 / 3.0)

        DEFINE_MATH_CONSTEXPR( double, METERS_TO_FEET, 1.0 / FEET_TO_METERS)
        DEFINE_MATH_CONSTEXPR( double, METERS_TO_MILES, METERS_TO_FEET * FEET_TO_MILES)
        DEFINE_MATH_CONSTEXPR( double, METERS_TO_NAUTICAL_MILES, 1.0 / 1852.0)
        DEFINE_MATH_CONSTEXPR( double, METERS_TO_YARDS, METERS_TO_FEET * FEET_TO_YARDS)

        DEFINE_MATH_CONSTEXPR( double, MILES_TO_FEET, 5280.0)
        DEFINE_MATH_CONSTEXPR( double, MILES_TO_METERS, 1.0 / METERS_TO_MILES)
        DEFINE_MATH_CONSTEXPR( double, MILES_TO_NAUTICAL_MILES, 1.0 / 1.15077945)
        DEFINE_MATH_CONSTEXPR( double, MILES_TO_YARDS, MILES_TO_FEET * FEET_TO_YARDS)

        DEFINE_MATH_CONSTEXPR( double, NAUTICAL_MILES_TO_METERS, 1.0 / METERS_TO_NAUTICAL_MILES)
        DEFINE_MATH_CONSTEXPR( double, NAUTICAL_MILES_TO_MILES, 1.0 / MILES_TO_NAUTICAL_MILES)
        DEFINE_MATH_CONSTEXPR( double, NAUTICAL_MILES_TO_FEET, 6076.11549)
        DEFINE_MATH_CONSTEXPR( double, NAUTICAL_MILES_TO_YARDS, NAUTICAL_MILES_TO_FEET * FEET_TO_YARDS)

        // Mass and Weight Conversions
        DEFINE_MATH_CONSTEXPR( double, KG_TO_LBS, 2.2046226218488)
        DEFINE_MATH_CONSTEXPR( double, LBS_TO_KG, 1.0 / KG_TO_LBS)

        // Pressure Conversions
        DEFINE_MATH_CONSTEXPR( double, ATM_TO_PASCALS, 101325.0)
        DEFINE_MATH_CONSTEXPR( double, ATM_TO_BAR, 1.01325)
        DEFINE_MATH_CONSTEXPR( double, ATM_TO_PSI, 14.695948775513)
        DEFINE_MATH_CONSTEXPR( double, ATM_TO_TORR, 760.0)

        DEFINE_MATH_CONSTEXPR( double, PASCALS_TO_ATM, 1.0 / ATM_TO_PASCALS)
        DEFINE_MATH_CONSTEXPR( double, PASCALS_TO_BAR, 1.0e-5)
        DEFINE_MATH_CONSTEXPR( double, PASCALS_TO_PSI, 1.0 / 6894.757293168)
        DEFINE_MATH_CONSTEXPR( double, PASCALS_TO_TORR, 1.0 / 133.32236842105)

        DEFINE_MATH_CONSTEXPR( double, BAR_TO_ATM, 1.0 / ATM_TO_BAR)
        DEFINE_MATH_CONSTEXPR( double, BAR_TO_PASCALS, 1.0 / PASCALS_TO_BAR)
        DEFINE_MATH_CONSTEXPR( double, BAR_TO_PSI, 14.503773773022)
        DEFINE_MATH_CONSTEXPR( double, BAR_TO_TORR, 750.06156130264)

        DEFINE_MATH_CONSTEXPR( double, PSI_TO_ATM, 1.0 / ATM_TO_PSI)
        DEFINE_MATH_CONSTEXPR( double, PSI_TO_PASCALS, 1.0 / PASCALS_TO_PSI)
        DEFINE_MATH_CONSTEXPR( double, PSI_TO_BAR, 1.0 / BAR_TO_PSI)
        DEFINE_MATH_CONSTEXPR( double, PSI_TO_TORR, 51.7149325724)

        DEFINE_MATH_CONSTEXPR( double, TORR_TO_ATM, 1.0 / ATM_TO_TORR)
        DEFINE_MATH_CONSTEXPR( double, TORR_TO_PASCALS, 1.0 / PASCALS_TO_TORR)
        DEFINE_MATH_CONSTEXPR( double, TORR_TO_BAR, 1.0 / BAR_TO_TORR)
        DEFINE_MATH_CONSTEXPR( double, TORR_TO_PSI, 1.0 / PSI_TO_TORR)

        // Temperature Conversions
        #define K_TO_C(temp) \
            (temp - 273.15)

        #define K_TO_F(temp) \
            (temp * 9.0 / 5.0 - 459.67)

        #define K_TO_R(temp) \
            (temp * 9.0 / 5.0)

        #define C_TO_K(temp) \
            (temp + 273.15)

        #define C_TO_F(temp) \
            (temp * 9.0 / 5.0 + 32.0)

        #define C_TO_R(temp) \
            (temp * 9.0 / 5.0 + 491.67)

        #define F_TO_K(temp) \
            ((temp + 459.67) * 5.0 / 9.0)

        #define F_TO_C(temp) \
            ((temp - 32.0) * 5.0 / 9.0)

        #define F_TO_R(temp) \
            (temp + 459.67)

        

    }
}

#endif /* BB985253_419B_45F5_B678_9A31FB52D408 */
