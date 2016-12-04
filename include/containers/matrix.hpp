/** ---------------------------------------------------------------------------
 ** matrix.hpp
 ** Container for a 4 by 4 matrix of floats. Also defines some useful operators
 ** with vectors and points.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATRIX_HPP
#define RAY_TRACER_MATRIX_HPP

#include <point.hpp>

class Matrix
{

public:

    /**
     * @param a value at [0,0].
     * @param b value at [0,1].
     * @param c value at [0,2].
     * @param d value at [0,3].
     * @param e value at [1,0].
     * @param f value at [1,1].
     * @param g value at [1,2].
     * @param h value at [1,3].
     * @param i value at [2,0].
     * @param j value at [2,1].
     * @param k value at [2,2].
     * @param l value at [2,3].
     * @param m value at [3,0].
     * @param n value at [3,1].
     * @param o value at [3,2].
     * @param p value at [3,3].
     * @return New matrix with the given values.
     */
    Matrix(const float a, const float b, const float c, const float d,
           const float e, const float f, const float g, const float h,
           const float i, const float j, const float k, const float l,
           const float m, const float n, const float o, const float p);

    /**
     * @param p Point to multiply by this matrix.
     * @return New point product of this matrix and the given point.
     */
    Point operator*(const Point &p) const;

    /**
     * @param v vector to multiply by this matrix.
     * @return New vector product of this matrix and the given vector.
     */
    Vect operator*(const Vect &v) const;

    /**
     * @param m matrix to multiply by this matrix.
     * @return New matrix product and this and the given matrices.
     */
    Matrix operator*(const Matrix &m) const;

    /**
     * @param m Matrix to compare with this one.
     * @return True if the given matrix is equal to this one. This means every value must be the same by '==' standards.
     */
    bool operator==(const Matrix &m) const;

    /**
     * @param m Matrix to compare with this one.
     * @return True if the given matrix is different from this one. This means every value must be the same by '=='
     * standards.
     */
    bool operator!=(const Matrix &m) const;

    /**
     * Pretty print.
     *
     * @param out Stream that will receive the matrix mat as a string.
     * @param mat Matrix to send to the stream as a string.
     * @return Stream with the new matrix.
     */
    friend std::ostream& operator<<(std::ostream &out, const Matrix &mat);

protected:

    /** This matrix's values. */
    float mA, mB, mC, mD,
          mE, mF, mG, mH,
          mI, mJ, mK, mL,
          mM, mN, mO, mP;
};

#endif // RAY_TRACER_MATRIX_HPP