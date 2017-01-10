/** ---------------------------------------------------------------------------
 ** checkerBoard.hpp
 ** Generated 3D texture material. Repeated square pattern of changing colors. Basically
 ** gives the appearance of a checker board to any plane aligned to an axis.
 ** Funny patterns appear on other shapes so it's best to just use it on planes
 ** or boxes.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_CHECKBOARD_HPP
#define RAY_TRACER_CHECKBOARD_HPP

#include <materials/material.hpp>

class CheckerBoard : public Material
{

public:

    /**
     * Creates a checkerboard pattern with the given squareSize. Keep in mind that
     * this texture is prone to causing noise due to floating point errors. Make sure
     * that a surface that uses this texture doesn't begin or end at the same time
     * as the pattern or some strange patterns will appear.
     *
     * @param squareSize Size of the squares of the pattern.
     * @param color1 One of the Colors in the pattern.
     * @param color2 The other color in the pattern.
     * @return New CheckerBoard material.
     */
    CheckerBoard(const float squareSize, Color color1, Color color2);

    /**
     * Creates a checkerboard pattern with the given squareSize. Keep in mind that
     * this texture is prone to causing noise due to floating point errors. Make sure
     * that a surface that uses this texture doesn't begin or end at the same time
     * as the pattern or some strange patterns will appear.
     *
     * @param squareSize Size of the squares of the pattern.
     * @param color1 One of the Colors in the pattern.
     * @param color2 The other color in the pattern.
     * @param reflective Specular value for this material.
     * @return New CheckerBoard material.
     */
    CheckerBoard(const float squareSize, Color color1, Color color2, Color reflective);

    /**
     * @return This material's color at the given point. Depends on the point's values relative to the world's axis
     *  and the colors in this material.
     */
    Color GetDiffuse(const Point &point) const;

private:

    /** The two colors that form the pattern in this 3D texture. */
    Color mColor1;
    Color mColor2;

    /** Size of the squares in this 3D texture. */
    float mSquareSize;
};

#endif // RAY_TRACER_CHECKBOARD_HPP