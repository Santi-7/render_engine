/* ---------------------------------------------------------------------------
 ** point.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H

#include "vect.hpp"

class Point
{

public:

    // TODO: Add doc.
    /**
     * Constructs a Point.
     *
     * @param x .
     * @return .
     */
    Point(const float x, const float y, const float z);

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
     * Overloads + operator to return a Point result
     * of adding two Point objects together.
     *
     * @param p .
     * @return .
     */
    const Point operator+(const Point& p) const;

    // TODO: Add doc.
    /**
     * Overloads - operator to return a Vect result
     * of subtracting two Point objects together.
     *
     * @param p .
     * @return .
     */
    const Vect operator-(const Point& p) const;

    // TODO: Add doc.
    /**
     * Overloads + operator to return a Point result
     * of adding .
     *
     * @param v .
     * @return .
     */
    const Point operator+(const Vect& v) const;

private:

    // TODO: Add doc.
    /* */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_POINT_H