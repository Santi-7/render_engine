/* ---------------------------------------------------------------------------
 ** color.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_COLOR_HPP
#define RAY_TRACER_COLOR_HPP

#include <algorithm>
#include <climits>

using namespace std;

// TODO: Add doc.
/* . */
static constexpr float COLOR_MAX = 1.0f;

class Color
{

public:

    /**
     * Constructor with no color (black).
     *
     * @return a black Color.
     */
    constexpr Color()
    : mR(0), mG(0), mB(0)
    {}

    // TODO: Add doc.
    /**
     * .
     *
     * @param r value for red.
     * @param g value for green.
     * @param b value for blue.
     * @return .
     */
    constexpr Color(const float r, const float g, const float b)
    : mR(r), mG(g), mB(b)
    {}

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr float GetR() const
    {
        return min(mR, COLOR_MAX);
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr float GetG() const
    {
        return min(mG, COLOR_MAX);
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr float GetB() const
    {
        return min(mB, COLOR_MAX);
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads + operator to .
     *
     * @param color .
     * @return .
     */
    Color operator+(const Color &color) const
    {
        return Color(mR + color.mR,
                     mG + color.mG,
                     mB + color.mB);
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads += operator to add the RGB values
     * of the new color to this one's.
     *
     * @param color .
     */
    void operator+=(const Color &color)
    {
        mR += color.mR;
        mG += color.mG;
        mB += color.mB;
    }

    // TODO: Add doc.
    /**
     * Overloads * operator to .
     *
     * @param color .
     * @return .
     */
    Color operator*(const Color &color) const
    {
        return Color(mR * color.mR / COLOR_MAX,
                     mG * color.mG / COLOR_MAX,
                     mB * color.mB / COLOR_MAX);
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads * operator to return a Color result
     * of multiplying all values in this Color by k.
     *
     * @param k .
     * @return New color result of multiplying the
     *         RGB values in this color by k.
     */
    Color operator*(const float k) const
    {
        return Color(mR*k, mG*k, mB*k);
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads *= operator to multiply all
     * values of this color by k.
     *
     * @param k .
     */
    void operator*=(const float k)
    {
        mR *= k;
        mG *= k;
        mB *= k;
    }

    // TODO: Add doc. k must be > 0
    /**
     * Overloads / operator to return a Color result
     * of dividing all values in this Color by k.
     *
     * @param k .
     * @return New color result of dividing the
     *         RGB values in this color by k.
     */
    Color operator/(const float k) const
    {
        return Color(mR/k, mG/k, mB/k);
    }

private:

    // TODO: Add doc.
    /* . */
    float mR;
    float mG;
    float mB;
};

// TODO: Add doc.
/* . */
static constexpr Color WHITE    (1.0f, 1.0f, 1.0f);
static constexpr Color GRAY     (0.5f, 0.5f, 0.5f);
static constexpr Color BLACK    (0.0f, 0.0f, 0.0f);
static constexpr Color RED      (1.0f, 0.0f, 0.0f);
static constexpr Color GREEN    (0.0f, 1.0f, 0.0f);
static constexpr Color BLUE     (0.0f, 0.0f, 1.0f);

#endif // RAY_TRACER_COLOR_HPP