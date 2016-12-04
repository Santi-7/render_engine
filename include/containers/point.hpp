/** ---------------------------------------------------------------------------
 ** point.hpp
 ** Contains a 3D point and defines operations with vectors. Every 3D shape needs
 ** a point in one way or another making this class a vital component of the ray
 ** tracer.
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

    /** Value that defines a container of three floats as a point.*/
    static constexpr float H = 1;

    /** When comparing float values we want to consider that
     * two values that differ by this threshold are equal. */
    // TODO: Check what this value is for. We might have solved whatever problem this used to solve in some other way.
    static constexpr float TH = 0.00025;

    /**
     * @return New point at [0, 0, 0].
     */
    Point();

    /**
     * @param x Value for x.
     * @param y Value for y.
     * @param z Value for z.
     * @return New point at [x, y, z].
     */
    Point(const float x, const float y, const float z);

    /**
     * @param to Point which distance with respect to this one will be returned.
     * @return Absolute distance from this point to the point to.
     */
    float Distance(const Point &to) const;

    /**
     * @return Value for x.
     */
    float GetX() const;

    /**
     * @return Value for y.
     */
    float GetY() const;

    /**
     * @return Value for z.
     */
    float GetZ() const;

    /**
     * @param p Point which values will be added to this one's.
     * @return New point sum of this and p.
     */
    Point operator+(const Point& p) const;

    /**
     * @param p Point which values will be subtracted to this one's.
     * @return New point from this minus p.
     */
    Vect operator-(const Point& p) const;

    /**
     * @param p Point by which this Point will be multiplied.
     * @return Product of this point and p.
     */
    float operator*(const Point& p) const;

    /**
     * @param v Vector by which this point will be moved.
     * @return New point result of moving this one in the direction and magnitude v.
     */
    Point operator+(const Vect& v) const;

    /**
     * @param v Vector by which this point will be moved.
     */
    void operator+=(const Vect& v);

    /**
     * @param v Vector by which this point will be moved.
     * @return New point result of moving this one in the opposite direction of v and magnitude v.
     */
    Point operator-(const Vect& v) const;

    /**
     * @param v Vector opposite to that by which this point will be moved.
     */
    void operator-=(const Vect& v);

    /**
     * @param p Point to compare with this one.
     * @return True if this Point is the same as p.
     */
    bool operator==(const Point& p) const;

    /**
     * @param p Point to compare with this one.
     * @return True if this POint is different from p.
     */
    bool operator!=(const Point& p) const;

    /**
     * @param p Point to compare with this one.
     * @return True if all the values in p are greater or equal to the values in this Point.
     */
    bool operator<=(const Point& p) const;

    /**
     * @param p Point to compare with this one.
     * @return True if all the values in p are smaller or equal to the values in this Point.
     */
    bool operator>=(const Point& p) const;

    /**
     * Pretty print.
     *
     * @param out Stream that will receive the point p as a string.
     * @param p Point to send to the stream as a string.
     * @return Stream with the string p.
     */
    friend std::ostream& operator<<(std::ostream &out, const Point &p);

protected:

    /** Values in this Point . */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_POINT_H