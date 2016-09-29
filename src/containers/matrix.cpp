/* ---------------------------------------------------------------------------
** matrix.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "../../include/containers/matrix.hpp"

Vect Matrix::operator*(const Vect &v) const
{

}

std::ostream& operator<< (std::ostream &out, const Matrix &m)
{
    out << "Matrix(" << m.mA << ", " << m.mB << ", " << m.mC << ", " << m.mD << '\n'
        << "       " << m.mE << ", " << m.mF << ", " << m.mG << ", " << m.mH << '\n'
        << "       " << m.mI << ", " << m.mJ << ", " << m.mK << ", " << m.mL << '\n'
        << "       " << m.mM << ", " << m.mN << ", " << m.mO << ", " << m.mP << ")";
    return out;
}