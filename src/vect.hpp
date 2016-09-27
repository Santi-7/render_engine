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
    Vect(float x, float y, float z);

    /**
     * .
     *
     * @return .
     */
    float GetX();

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    float GetY();

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    float GetZ();

    // TODO: Add doc.
    /**
     * Overloads + operator to return a Vect result
     * of adding two Vect objects together.
     *
     * @param p .
     * @return .
     */
    Vect operator+(const Vect &v);

private:

    // TODO: Add doc.
    /* */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_VECT_HPP
