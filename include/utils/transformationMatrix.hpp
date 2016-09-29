/* ---------------------------------------------------------------------------
 ** transformationMatrix.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_TRANSFORMATION_MATRIX_HPP
#define RAY_TRACER_TRANSFORMATION_MATRIX_HPP

#include <matrix.hpp>

class TransformationMatrix : Matrix
{

public:

    // TODO: Add doc.
    /**
     * Constructs a TransformationMatrix.
     *
     * @return .
     */
    TransformationMatrix();

    // TODO: Add doc.
    /**
     * .
     *
     * @param d .
     */
    void SetXTranslation(float d);

    // TODO: Add doc.
    /**
     * .
     *
     * @param h .
     */
    void SetYTranslation(float h);

    // TODO: Add doc.
    /**
     * .
     *
     * @param l .
     */
    void SetZTranslation(float l);

    // TODO: Add doc.
    /**
     * .
     *
     * @param a .
     */
    void SetXScale(float a);

    // TODO: Add doc.
    /**
     * .
     *
     * @param f .
     */
    void SetYScale(float f);

    // TODO: Add doc.
    /**
     * .
     *
     * @param k .
     */
    void SetZScale(float k);

    // TODO: Add doc.
    /**
     * .
     */
    void SetXYPlaneSymmetry();

    // TODO: Add doc.
    /**
     * .
     */
    void SetXZPlaneSymmetry();

    // TODO: Add doc.
    /**
     * .
     */
    void SetYZPlaneSymmetry();

    // TODO: Add doc.
    /**
     * .
     */
    void SetXAxisSymmetry();

    // TODO: Add doc.
    /**
     * .
     */
    void SetYAxisSymmetry();

    // TODO: Add doc.
    /**
     * .
     */
    void SetZAxisSymmetry();

    // TODO: Add doc.
    /**
     * .
     */
    void SetOriginSymmetry();

    // TODO: Add doc.
    /**
     * .
     *
     * @param angle .
     */
    void SetXRotation(float angle);

    // TODO: Add doc.
    /**
     * .
     *
     * @param angle .
     */
    void SetYRotation(float angle);

    // TODO: Add doc.
    /**
     * .
     *
     * @param angle .
     */
    void SetZRotation(float angle);
};

#endif // RAY_TRACER_TRANSFORMATION_MATRIX_HPP