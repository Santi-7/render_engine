/* ---------------------------------------------------------------------------
 ** matrix.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATRIX_HPP
#define RAY_TRACER_MATRIX_HPP

#include <point.hpp>
#include <vect.hpp>

class Matrix
{

public:

    // TODO: Add doc.
    /**
     * Constructs a Matrix.
     *
     * @param a .
     * @param b .
     * @param c .
     * @param d .
     * @param e .
     * @param f .
     * @param g .
     * @param h .
     * @param i .
     * @param j .
     * @param k .
     * @param l .
     * @param m .
     * @param n .
     * @param o .
     * @param p .
     * @return .
     */
    Matrix(const float a, const float b, const float c, const float d,
           const float e, const float f, const float g, const float h,
           const float i, const float j, const float k, const float l,
           const float m, const float n, const float o, const float p);

    // TODO: Add doc.
    /**
     * Overloads * operator to return a Point result
     * of .
     *
     * @param p .
     * @return .
     */
    Point operator*(const Point &p) const;

    // TODO: Add doc.
    /**
     * Overloads * operator to return a Vect result
     * of .
     *
     * @param v .
     * @return .
     */
    Vect operator*(const Vect &v) const;

    // TODO: Add doc.
    /**
     * Overloads * operator to return a Matrix result
     * of .
     *
     * @param m .
     * @return .
     */
    Matrix operator*(const Matrix &m) const;

    /**
     * Overloads == operator returning true if both matrices are equal
     * of .
     *
     * @param m .
     * @return .
     */
    bool operator==(const Matrix &m) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param out .
     * @param mat .
     * @return .
     */
    friend std::ostream& operator<< (std::ostream &out, const Matrix &mat);

protected:

    // TODO: Add doc.
    /* */
    float mA, mB, mC, mD,
          mE, mF, mG, mH,
          mI, mJ, mK, mL,
          mM, mN, mO, mP;
};

#endif // RAY_TRACER_MATRIX_HPP