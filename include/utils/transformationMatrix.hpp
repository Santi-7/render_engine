/** ---------------------------------------------------------------------------
 ** transformationMatrix.hpp
 ** Extends Matrix to define methods to apply any combination of movement, rotation,
 ** scale and axis, plane and origin symmetry to Points and Vects.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_TRANSFORMATION_MATRIX_HPP
#define RAY_TRACER_TRANSFORMATION_MATRIX_HPP

#include <matrix.hpp>

class TransformationMatrix : public Matrix
{

public:

    /**
     * Constructs a new identity TransformationMatrix.
     */
    TransformationMatrix();

    /**
     * Sets the translation in the X axis to units.
     *
     * @param units How much this TransformationMatrix will translate an object in the X axis.
     */
    void SetXTranslation(float units);

    /**
     * Sets the translation in the Y axis to units
     *
     * @param units How much this TransformationMatrix will translate an object in the Y axis.
     */
    void SetYTranslation(float units);

    /**
     * Sets the translation in the Z axis to units.
     *
     * @param units How much this TransformationMatrix will translate an object in the Z axis.
     */
    void SetZTranslation(float units);

    /**
     * Sets the scale in the X axis to factor.
     *
     * @param factor How much this TransformationMatrix will scale an object in the X axis.
     */
    void SetXScale(float factor);

    /**
     * Sets the scale in the Y axis to factor.
     *
     * @param factor How much this TransformationMatrix will scale an object in the Y axis.
     */
    void SetYScale(float factor);

    /**
     * Sets the scale in the Z axis to factor.
     *
     * @param factor How much this TransformationMatrix will scale an object in the Z axis.
     */
    void SetZScale(float factor);

    /**
     * Sets XY plane symmetry to this TransformationMatrix.
     */
    void SetXYPlaneSymmetry();

    /**
     * Sets XZ plane symmetry to this TransformationMatrix.
     */
    void SetXZPlaneSymmetry();

    /**
     * Sets YZ plane symmetry to this TransformationMatrix.
     */
    void SetYZPlaneSymmetry();

    /**
     * Sets X axis symmetry to this TransformationMatrix.
     */
    void SetXAxisSymmetry();

    /**
     * Sets Y axis symmetry to this TransformationMatrix.
     */
    void SetYAxisSymmetry();

    /**
     * Sets Z axis symmetry to this TransformationMatrix.
     */
    void SetZAxisSymmetry();

    /**
     * Sets origin symmetry to this TransformationMatrix.
     */
    void SetOriginSymmetry();

    /**
     * Sets X axis rotation to this TransformationMatrix.
     * @param angle Angle in radians by which an object will be rotated around the X axis.
     */
    void SetXRotation(float angle);

    /**
     * Sets Y axis rotation to this TransformationMatrix.
     * @param angle Angle in radians by which an object will be rotated around the Y axis.
     */
    void SetYRotation(float angle);

    /**
     * Sets Y axis rotation to this TransformationMatrix.
     * @param angle Angle in radians by which an object will be rotated around the Y axis.
     */
    void SetZRotation(float angle);
};

#endif // RAY_TRACER_TRANSFORMATION_MATRIX_HPP