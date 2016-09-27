/* ---------------------------------------------------------------------------
** vect.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begue, NIA: 683482
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
    Vect(double x, double y, double z);

    /**
     * .
     *
     * @return .
     */
    double GetX();

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    double GetY();

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    double GetZ();

    // TODO: Add doc.
    /**
     * Overloads + operator to return a Vect result of adding two Vect objects together.
     *
     * @param p .
     * @return .
     */
    Vect operator+(const Vect &p);

private:

    // TODO: Add doc.
    /* */
    double mX, mY, mZ;
};

#endif //RAY_TRACER_VECT_HPP
