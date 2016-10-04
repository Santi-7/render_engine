/* ---------------------------------------------------------------------------
** matrix.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <matrix.hpp>

Matrix::Matrix(const float a, const float b, const float c, const float d,
               const float e, const float f, const float g, const float h,
               const float i, const float j, const float k, const float l,
               const float m, const float n, const float o, const float p)
{
    mA = a; mB = b; mC = c; mD = d;
    mE = e; mF = f; mG = g; mH = h;
    mI = i; mJ = j; mK = k; mL = l;
    mM = m; mN = n; mO = o; mP = p;
}

Point Matrix::operator*(const Point &p) const
{
    float x = mA * p.GetX() + mB * p.GetY() + mC * p.GetZ() + mD * Point::H;
    float y = mE * p.GetX() + mF * p.GetY() + mG * p.GetZ() + mH * Point::H;
    float z = mI * p.GetX() + mJ * p.GetY() + mK * p.GetZ() + mL * Point::H;
    float h = mM * p.GetX() + mN * p.GetY() + mO * p.GetZ() + mP * Point::H;
    return Point(x/h, y/h, z/h);
}

Vect Matrix::operator*(const Vect &v) const
{
    float x = mA * v.GetX() + mB * v.GetY() + mC * v.GetZ() + mD * Vect::H;
    float y = mE * v.GetX() + mF * v.GetY() + mG * v.GetZ() + mH * Vect::H;
    float z = mI * v.GetX() + mJ * v.GetY() + mK * v.GetZ() + mL * Vect::H;
    return Vect(x, y, z);
}

Matrix Matrix::operator*(const Matrix &mat) const
{
    float a = mA * mat.mA + mB * mat.mE + mC * mat.mI + mD * mat.mM;
    float b = mA * mat.mB + mB * mat.mF + mC * mat.mJ + mD * mat.mN;
    float c = mA * mat.mC + mB * mat.mG + mC * mat.mK + mD * mat.mO;
    float d = mA * mat.mD + mB * mat.mH + mC * mat.mL + mD * mat.mP;
    float e = mE * mat.mA + mF * mat.mE + mG * mat.mI + mH * mat.mM;
    float f = mE * mat.mB + mF * mat.mF + mG * mat.mJ + mH * mat.mN;
    float g = mE * mat.mC + mF * mat.mG + mG * mat.mK + mH * mat.mO;
    float h = mE * mat.mD + mF * mat.mH + mG * mat.mL + mH * mat.mP;
    float i = mI * mat.mA + mJ * mat.mE + mK * mat.mI + mL * mat.mM;
    float j = mI * mat.mB + mJ * mat.mF + mK * mat.mJ + mL * mat.mN;
    float k = mI * mat.mC + mJ * mat.mG + mK * mat.mK + mL * mat.mO;
    float l = mI * mat.mD + mJ * mat.mH + mK * mat.mL + mL * mat.mP;
    float m = mM * mat.mA + mN * mat.mE + mO * mat.mI + mP * mat.mM;
    float n = mM * mat.mB + mN * mat.mF + mO * mat.mJ + mP * mat.mN;
    float o = mM * mat.mC + mN * mat.mG + mO * mat.mK + mP * mat.mO;
    float p = mM * mat.mD + mN * mat.mH + mO * mat.mL + mP * mat.mP;
    return Matrix(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
}

bool Matrix::operator==(const Matrix &m) const
{
    return mA == m.mA & mB == m.mB & mC == m.mC & mD == m.mD &
           mE == m.mE & mF == m.mF & mG == m.mG & mH == m.mH &
           mI == m.mI & mJ == m.mJ & mK == m.mK & mL == m.mL &
           mM == m.mM & mN == m.mN & mO == m.mO & mP == m.mP;
}

bool Matrix::operator!=(const Matrix &m) const
{
    return !(*this == m);
}

std::ostream& operator<< (std::ostream &out, const Matrix &m)
{
    out << "Matrix(" << m.mA << ", " << m.mB << ", " << m.mC << ", " << m.mD << '\n'
        << "       " << m.mE << ", " << m.mF << ", " << m.mG << ", " << m.mH << '\n'
        << "       " << m.mI << ", " << m.mJ << ", " << m.mK << ", " << m.mL << '\n'
        << "       " << m.mM << ", " << m.mN << ", " << m.mO << ", " << m.mP << ")";
    return out;
}