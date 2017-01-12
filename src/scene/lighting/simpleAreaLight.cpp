/** ---------------------------------------------------------------------------
 ** simpleAreaLight.cpp
 ** Implementation for simpleAreaLight class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <simpleAreaLight.hpp>

SimpleAreaLight::SimpleAreaLight(const Point &corner, const Vect &dir1, const unsigned int dir1Lights,
                                 const Vect &dir2, const unsigned int dir2Lights, const float power,
                                 const Color &baseColor)
: LightSource(power / (dir1Lights * dir2Lights), baseColor)
{
    Vect increment1 = dir1 / (dir1Lights - 1);
    Vect increment2 = dir2 / (dir2Lights - 1);
    Point tmp1(corner);
    Point tmp2(corner);

    for (; tmp2 != corner + dir2 + increment2; tmp2 += increment2)
    {
        tmp1 = tmp2;
        for (; tmp1 != tmp2 + dir1 + increment1; tmp1 += increment1)
        {
            mPoints.push_back(tmp1);
        }
    }
}

Color SimpleAreaLight::GetColor(const Point &point) const
{
    Color retVal = BLACK;
    for (const Point &p : mPoints)
    {
        retVal += PointLight(p, mPower, mBaseColor).GetColor(point);
    }
    return retVal / mPoints.size();
}

vector<Point> SimpleAreaLight::GetLights() const
{
    return mPoints;
}