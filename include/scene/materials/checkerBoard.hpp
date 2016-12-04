/* ---------------------------------------------------------------------------
** checkerBoard.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_CHECKBOARD_HPP
#define RAY_TRACER_CHECKBOARD_HPP

#include "material.hpp"

class CheckerBoard : public Material
{

public:

    //TODO: Add doc
    /**
     * Creates a checkerboard pattern with the given squareSize. Keep in mind that
     * this texture is prone to causing noise due to floating point errors. Make sure
     * that a surface that uses this texture doesn't begin or end at the same time
     * as the pattern or some strange patterns will appear.
     *
     * @param squareSize
     * @param color
     * @return
     */
    CheckerBoard(const float squareSize, Color color1, Color color2);

    //TODO: Add doc
    /**
     *
     *
     * @param squareSize
     * @param color
     * @param specular
     * @return
     */
    CheckerBoard(const float squareSize, Color color1, Color color2, Color specular);

    //TODO: Add doc
    /**
     * Returns this material's .
     *
     * @return  of this material.
     */
    Color GetDiffuse(const Point &point) const;

private:

    // TODO: Add doc.
    /* . */
    Color mColor1;
    Color mColor2;

    // TODO: Add doc.
    /* . */
    float mSquareSize;
};

#endif // RAY_TRACER_CHECKBOARD_HPP