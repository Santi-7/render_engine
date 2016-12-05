/** ---------------------------------------------------------------------------
 ** vect.hpp
 ** Contains a 3D vector. Represents unbound directionality an magnitude. Also
 ** contains methods to normalise a vector and calculate dot and cross products
 ** with other vectors.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_VECT_HPP
#define RAY_TRACER_VECT_HPP

#include <ostream>

class Vect {

public:

    /** Value that defines a container of three floats as a vector.*/
    static constexpr float H = 0;

    /**
     * @return New empty vector with values [0, 0, 0].
     */
    Vect();

    /**
     * @param x Value for x.
     * @param y Value for y.
     * @param z Value for z.
     * @return New vector with values [x, y, z].
     */
    Vect(const float x, const float y, const float z);

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
     * @return The size (magnitude) of this vector.
     */
    float Abs() const;

    /**
     * @return New vector result of normalising this vector (dividing each value by the vector's magnitude).
     */
    Vect Normalise() const;

    /**
     * @param k Value by which this vector will be multiplied.
     * @return New vector product of this one and k.
     */
    Vect operator*(const float k) const;

    /**
     * @param k Value by which this vector will be divided.
     * @return New vector result of dividing this vector by k.
     */
    Vect operator/(const float k) const;

    /**
     * @param v Vector to add to this one.
     * @return New vector result of adding v to this vector.
     */
    Vect operator+(const Vect &v) const;

    /**
     * @param v Vector to subtract to this one.
     * @return New vector result of subtracting v from this vector.
     */
    Vect operator-(const Vect &v) const;

    /**
     * @param v Vector by which this one will be multiplied.
     * @return Value result of multiplying this vector by v.
     */
    float DotProduct(const Vect &v) const;

    /**
     * @param v Vector by which this one will be multiplied.
     * @return New vector result of multiplying this vector by v. A vector perpendicular to this and v.
     */
    Vect CrossProduct(const Vect &v) const;

    /**
     * @param m Vector to compare this one to.
     * @return True if this vector and v are the same.
     */
    bool operator==(const Vect &v) const;

    /**
     * @param m Vector to compare this one to.
     * @return True if this vector and v are different.
     */
    bool operator!=(const Vect &v) const;

    /**
     * Pretty print.
     *
     * @param out Stream that will receive the vector v as a string.
     * @param v vector to send to the stream as a string.
     * @return Stream with a string version of v.
     */
    friend std::ostream& operator<<(std::ostream &out, const Vect &v);

private:

    /** Values in this vector. */
    float mX, mY, mZ;
};

#endif // RAY_TRACER_VECT_HPP