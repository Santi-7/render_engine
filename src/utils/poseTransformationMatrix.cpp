/* ---------------------------------------------------------------------------
 ** poseTransformationMatrix.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <poseTransformationMatrix.hpp>

// Assuming that the initial pose's position coordinates are (0,0,0),
PoseTransformationMatrix::PoseTransformationMatrix(const Vect &x, const Vect &y,
                                                   const Vect &z, const Point &c)
: Matrix(x.GetX(), y.GetX(), z.GetX(), c.GetX(),
         x.GetY(), y.GetY(), z.GetY(), c.GetY(),
         x.GetZ(), y.GetZ(), z.GetZ(), c.GetZ(),
          Vect::H,  Vect::H,  Vect::H, Point::H)
{}

/* Based on the doctoral thesis Local Accuracy and Global
   Consistency for Efficient Visual SLAM [Hauke Strasdat, 2012]. */
PoseTransformationMatrix PoseTransformationMatrix::Inverse() const
{
    // Transposed of the rotation matrix R, cause it's orthonormal.
    Vect x(mA, mB, mC);
    Vect y(mE, mF, mG);
    Vect z(mI, mJ, mK);
    // - transposed of the rotation matrix R * translation T.
    float cX = mA * mD + mE * mH + mI * mL;
    float cY = mB * mD + mF * mH + mJ * mL;
    float cZ = mC * mD + mG * mH + mK * mL;
    Point c(-cX, -cY, -cZ);
    // Inverse pose matrix.
    return PoseTransformationMatrix(x, y, z, c);
}