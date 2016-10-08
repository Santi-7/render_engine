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
    /* . */
    static constexpr Color WHITE = Color(255, 255, 255);
    static constexpr Color BLACK = Color(0, 0, 0);

    /**
     * Constructor with no color (black).
     *
     * @return a black Color.
     */
    Color();

    // TODO: Add doc.
    /**
     * .
     *
     * @param r value for red.
     * @param g value for green.
     * @param b value for blue.
     * @return .
     */
    Color(const byte r, const byte g, const byte b);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    byte GetR() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    byte GetG() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    byte GetB() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param red .
     */
    void SetR(const byte red);

    // TODO: Add doc.
    /**
     * .
     *
     * @param green .
     */
    void SetG(const byte green);

    // TODO: Add doc.
    /**
     * .
     * @param blue .
     */
    void SetB(const byte blue);

private:

    // TODO: Add doc.
    /* . */
    byte mR;
    byte mG;
    byte mB;
};


#endif // RAY_TRACER_COLOR_HPP