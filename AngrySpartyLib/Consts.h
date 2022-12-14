/**
 * @file Consts.h
 * @author Western Tanager
 *
 * Useful constants to use for conversion and other calculations.
 */

#ifndef ANGRY_SPARTAN_CONSTS_H
#define ANGRY_SPARTAN_CONSTS_H

/**
 * Defines constants that are used for conversion and calculations.
 */
class Consts {
public:
    /// Conversion of meters to centimeter display dimensions
    static constexpr double MtoCM = 100.0;

    /// Conversion of degrees to radians
    static constexpr double DtoR = 0.0174532925199;

    /// Convert of radians to degrees
    static constexpr double RtoD = 57.2957795131;
};

#endif //ANGRY_SPARTAN_CONSTS_H
