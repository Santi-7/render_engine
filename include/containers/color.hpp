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

    /**
     *
     * @param r value for red
     * @param g value for green
     * @param b value for blue
     * @return
     */
    Color(byte r, byte g, byte b);

    byte GetR();
    byte GetG();
    byte GetB();

private:

    byte mR;
    byte mG;
    byte mB;
};


#endif //RAY_TRACER_COLOR_HPP
