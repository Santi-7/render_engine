/* ---------------------------------------------------------------------------
 ** point.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H

#include <vect.hpp>

class Point
{

public:

    // TODO: Add doc.
    /* */
    static const float H;

    // TODO: Add doc.
    /**
     * Constructs a Point.
     *
     * @param x .
     * @param y .
     * @param z .
     * @return .
     */
    Point(const float x, const float y, const float z);

    /**
     * .
     *
     * @return .
     */
    float GetX() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    float GetY() const;

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    float GetZ() const;

    // TODO: Add doc.
    /**
     * Overloads + operator to return a Point result
     * of adding two Point objects together.
     *
     * @param p .
     * @return .
     */
    Point operator+(const Point& p) const;

    // TODO: Add doc.
    /**
     * Overloads - operator to return a Vect result
     * of subtracting two Point objects together.
     *
     * @param p .
     * @return .
     */
    Vect operator-(const Point& p) const;

    // TODO: Add doc.
    /**
     * Overloads + operator to return a Point result
     * of adding .
     *
     * @param v .
     * @return .
     */
    Point operator+(const Vect& v) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param out .
     * @param p .
     * @return .
     */
    friend std::ostream& operator<< (std::ostream &out, const Point &p);

private:

    // TODO: Add doc.
    /* */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_POINT_H