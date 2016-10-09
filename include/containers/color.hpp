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
     * Constructor with no color (black).
     *
     * @return a black Color.
     */
    constexpr Color() : mR(0), mG(0), mB(0){}

    // TODO: Add doc.
    /**
     * .
     *
     * @param r value for red.
     * @param g value for green.
     * @param b value for blue.
     * @return .
     */
    constexpr Color(const byte r, const byte g, const byte b) : mR(r), mG(g), mB(b){}

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr byte GetR() const
    {
        return mR;
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr byte GetG() const
    {
        return mG;
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr byte GetB() const
    {
        return mB;
    }

private:

    // TODO: Add doc.
    /* . */
    byte mR;
    byte mG;
    byte mB;
};

static constexpr Color WHITE    (255, 255, 255);
static constexpr Color BLACK    (0, 0, 0);
static constexpr Color RED      (255, 0, 255);
static constexpr Color GREEN    (0, 255, 0);
static constexpr Color BLUE     (0, 0, 255);

#endif // RAY_TRACER_COLOR_HPP