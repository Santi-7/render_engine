/* ---------------------------------------------------------------------------
 ** poseTransformationMatrix.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <poseTransformationMatrix.hpp>

// Assuming that the initial pose's position coordinates are (0,0,0),
PoseTransformationMatrix::PoseTransformationMatrix(const Point &origin, const Vect &xAxis,
                                                   const Vect &yAxis, const Vect &zAxis)
: Matrix(xAxis.GetX(), yAxis.GetX(), zAxis.GetX(), origin.GetX(),
         xAxis.GetY(), yAxis.GetY(), zAxis.GetY(), origin.GetY(),
         xAxis.GetZ(), yAxis.GetZ(), zAxis.GetZ(), origin.GetZ(),
              Vect::H,      Vect::H,      Vect::H,     Point::H)
{}

PoseTransformationMatrix PoseTransformationMatrix::GetPoseTransformation
        (const Point &origin, const Vect &zAxis)
{
    Vect xAxis;
    // [zAxis] is not parallel to (0,0,1).
    if (zAxis.GetX() != 0 & zAxis.GetY() != 0)
    {
        xAxis = zAxis.CrossProduct(Vect(0, 0, 1));
    }
    // [zAxis] is not parallel to (0,1,0).
    else
    {
        xAxis = zAxis.CrossProduct(Vect(0, 1, 0));
    }
    Vect yAxis = xAxis.CrossProduct(zAxis);
    return PoseTransformationMatrix(origin, xAxis, yAxis, zAxis);
}

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
    return PoseTransformationMatrix(c, x, y, z);
}