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
     * Overloads + operator to return a Point result
     * of adding two Point objects together.
     *
     * @param p .
     * @return .
     */
    Point operator+(const Point& p);

    // TODO: Add doc.
    /**
     * Overloads - operator to return a Vect result
     * of subtracting two Point objects together.
     *
     * @param p .
     * @return .
     */
    Vect operator-(const Point& p);

    // TODO: Add doc.
    /**
     * Overloads * operator to return a Point result
     * of .
     *
     * @param k .
     * @return .
     */
    Point operator*(const float k);

private:

    // TODO: Add doc.
    /* */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_POINT_H