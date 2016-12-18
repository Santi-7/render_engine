/* ---------------------------------------------------------------------------
 ** poseTransformationMatrix.hpp
 ** This class manages the transformation matrix that changes from world
 ** to a new local coordinates, and vice versa.
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

    /**
     * @param origin of the new local coordinates.
     * @param xAxis X axis of the new local coordinates.
     * @param yAxis Y axis of the new local coordinates.
     * @param zAxis Z axis of the new local coordinates.
     * @return the transformation matrix that changes from world coordinates
     * (assuming O = (0,0,0)) to local coordinates with O = [origin] and the
     * three axis as [xAxis], [yAxis] and [zAxis].
     */
    PoseTransformationMatrix(const Point &origin, const Vect &xAxis,
                             const Vect &yAxis, const Vect &zAxis);

    /**
     * @param origin of the new local coordinates.
     * @param zAxis Z axis of the new local coordinates.
     * @return a transformation matrix that changes from world coordinates
     * (assuming O = (0,0,0)) to local coordinates with O = [origin] and the
     * Z axis as [zAxis]. The X and Y axis are calculated are calculated in
     * order that they form an orthonormal basis.
     */
    static PoseTransformationMatrix GetPoseTransformation(const Point &origin,
                                                          const Vect &zAxis);

    /**
     * @return The transformation matrix inverse of this one, this is, the
     * transformation matrix that changes from these local coordinates to global.
     */
    PoseTransformationMatrix Inverse() const;
};

#endif // RAY_TRACER_POSE_TRANSFORMATION_MATRIX_HPP