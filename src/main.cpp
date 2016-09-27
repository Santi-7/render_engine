/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <iostream>
#include "point.hpp"
#include "vect.hpp"
using namespace std;

int main()
{
    cout << "Hello Future Ray Tracer Developer!" << '\n';

    Point point1(1,2,3);
    Point point2(3,2,1);
    Point p_result = point1 + point2;
    cout << p_result.GetX() << "," << p_result.GetY() << "," << p_result.GetZ() << '\n';

    Vect v_result1 = point1 - point2;
    cout << v_result1.GetX() << "," << v_result1.GetY() << "," << v_result1.GetZ() << '\n';

    Vect vect1(1, 2, 3);
    Vect vect2(3, 2, 1);
    Vect v_result2 = vect1 + vect2;
    cout << v_result2.GetX() << "," <<  v_result2.GetY() << "," << v_result2.GetZ() << '\n';
}