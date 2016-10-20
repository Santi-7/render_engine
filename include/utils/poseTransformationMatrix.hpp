/* ---------------------------------------------------------------------------
 ** poseTransformationMatrix.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_POSE_TRANSFORMATION_MATRIX_HPP
#define RAY_TRACER_POSE_TRANSFORMATION_MATRIX_HPP

#include <matrix.hpp>

class PoseTransformationMatrix : public Matrix
{

public:

    // TODO: Add doc.
    /**
     * .
     *
     * @param x .
     * @param y .
     * @param z .
     * @param c .
     * @return .
     */
    PoseTransformationMatrix(const Vect &x, const Vect &y,
                             const Vect &z, const Point &c);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    PoseTransformationMatrix Inverse() const;
};

#endif // RAY_TRACER_POSE_TRANSFORMATION_MATRIX_HPP