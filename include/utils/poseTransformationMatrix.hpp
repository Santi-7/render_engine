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
     * @param origin .
     * @param xAsis .
     * @param yAsis .
     * @param zAsis .
     * @return .
     */
    PoseTransformationMatrix(const Point &origin, const Vect &xAsis,
                             const Vect &yAsis, const Vect &zAsis);

    // TODO: Add doc.
    /**
     * .
     *
     * @param origin .
     * @param zAxis .
     * @return
     */
    static PoseTransformationMatrix GetPoseTransformation(const Point &origin,
                                                          const Vect &zAxis);

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    PoseTransformationMatrix Inverse() const;
};

#endif // RAY_TRACER_POSE_TRANSFORMATION_MATRIX_HPP