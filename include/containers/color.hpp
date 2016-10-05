/* ---------------------------------------------------------------------------
 ** color.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_COLOR_HPP
#define RAY_TRACER_COLOR_HPP

typedef unsigned char byte;

class Color {

public:

    // TODO: Add doc.
    /**
     * .
     * @param r value for red.
     * @param g value for green.
     * @param b value for blue.
     * @return .
     */
    Color(byte r, byte g, byte b);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    byte GetR();

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    byte GetG();

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    byte GetB();

private:

    // TODO: Add doc.
    /* . */
    byte mR;
    byte mG;
    byte mB;
};

#endif // RAY_TRACER_COLOR_HPP