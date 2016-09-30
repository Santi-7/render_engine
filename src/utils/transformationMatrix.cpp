/* ---------------------------------------------------------------------------
 ** transformationMatrix.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <cmath>
#include <transformationMatrix.hpp>

TransformationMatrix::TransformationMatrix() : Matrix(1, 0, 0, 0,
                                                      0, 1, 0, 0,
                                                      0, 0, 1, 0,
                                                      0, 0, 0, 1){}

void TransformationMatrix::SetXTranslation(float units)
{
    mD = units;
}

void TransformationMatrix::SetYTranslation(float units)
{
    mH = units;
}

void TransformationMatrix::SetZTranslation(float units)
{
    mL = units;
}

void TransformationMatrix::SetXScale(float factor)
{
    mA *= factor;
}

void TransformationMatrix::SetYScale(float factor)
{
    mF *= factor;
}

void TransformationMatrix::SetZScale(float factor)
{
    mK *= factor;
}

void TransformationMatrix::SetXYPlaneSymmetry()
{
    mK = -1;
}

void TransformationMatrix::SetXZPlaneSymmetry()
{
    mF = -1;
}

void TransformationMatrix::SetYZPlaneSymmetry()
{
    mA = -1;
}

void TransformationMatrix::SetXAxisSymmetry()
{
    mF = -1;
    mK = -1;
}

void TransformationMatrix::SetYAxisSymmetry()
{
    mA = -1;
    mK = -1;
}

void TransformationMatrix::SetZAxisSymmetry()
{
    mA = -1;
    mF = -1;
}

void TransformationMatrix::SetOriginSymmetry()
{
    mA = -1;
    mF = -1;
    mK = -1;
}

void TransformationMatrix::SetXRotation(float angle)
{
    mF = (float) cos(angle);
    mG = (float) -sin(angle);
    mJ = (float) sin(angle);
    mK = (float) cos(angle);
}

void TransformationMatrix::SetYRotation(float angle)
{
    mA = (float) cos(angle);
    mC = (float) sin(angle);
    mI = (float) -sin(angle);
    mK = (float) cos(angle);
}

void TransformationMatrix::SetZRotation(float angle)
{
    mA = (float) cos(angle);
    mB = (float) -sin(angle);
    mE = (float) sin(angle);
    mF = (float) cos(angle);
}