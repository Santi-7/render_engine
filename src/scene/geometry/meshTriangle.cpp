/* ---------------------------------------------------------------------------
** meshTriangle.cpp
** Implementation for MeshTriangle class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <meshTriangle.hpp>

MeshTriangle::MeshTriangle(const Point &a, const Point &b, const Point &c,
                           const Vect &nA, const Vect &nB, const Vect &nC)
: Triangle(a, b, c), mNormalA(nA), mNormalB(nB), mNormalC(nC)
{}

Vect MeshTriangle::GetNormal(const Point &point) const
{
    // Get the barycentric coordinates for the point with respect to the triangle.
    Vect v2 = point - mA;
    float d20 = v2.DotProduct(v0);
    float d21 = v2.DotProduct(v1);
    // Barycentric coordinates.
    float alpha = (d11 * d20 - d01 * d21) / denominator;
    float beta = (d00 * d21 - d01 * d20) / denominator;
    float gamma = 1.0f - alpha - beta;
    // Normal interpolation.
    return mNormalA * gamma + mNormalB * alpha + mNormalC * beta;
}