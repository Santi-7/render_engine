#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H

// TODO: Add doc.
/**
 * .
 */
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
    Point(double x, double y, double z);

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
     * Overloads + operator to return a Point result of adding two Point objects together.
     *
     * @param p .
     * @return .
     */
    Point operator+(const Point& p);

private:

    // TODO: Add doc.
    /* */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_POINT_H