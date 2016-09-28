/* ---------------------------------------------------------------------------
** vect.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_VECT_HPP
#define RAY_TRACER_VECT_HPP

class Vect {

public:

    // TODO: Add doc.
    /**
     * Constructs a Vect.
     *
     * @param x .
     * @return .
     */
    Vect(const float x, const float y, const float z);

    /**
     * .
     *
     * @return .
     */
    const float GetX() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    const float GetY() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    const float GetZ() const;

    // TODO: Add doc.
    /**
     * Overloads + operator to return a Vect result
     * of adding two Vect objects together.
     *
     * @param v .
     * @return .
     */
    const Vect operator+(const Vect &v) const;

    // TODO: Add doc.
    /**
     * Overloads - operator to return a Vect result
     * of subtracting two Vect objects together.
     *
     * @param v .
     * @return .
     */
    const Vect operator-(const Vect &v) const;

    // TODO: Add doc.
    /**
     * Overloads * operator to return a Vect result
     * of .
     *
     * @param k .
     * @return .
     */
    const Vect operator*(const float k) const;

private:

    // TODO: Add doc.
    /* */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_VECT_HPP
