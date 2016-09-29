/* ---------------------------------------------------------------------------
 ** matrix.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_MATRIX_HPP
#define RAY_TRACER_MATRIX_HPP

#include <vect.hpp>

class Matrix
{

public:

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
     * .
     *
     * @param out .
     * @param m .
     * @return .
     */
    friend std::ostream& operator<< (std::ostream &out, const Matrix &m);

private:

    // TODO: Add doc.
    /* */
    float mA, mB, mC, mD,
          mE, mF, mG, mH,
          mI, mJ, mK, mL,
          mM, mN, mO, mP;
};

#endif // RAY_TRACER_MATRIX_HPP