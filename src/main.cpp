/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begue, NIA: 683482
** -------------------------------------------------------------------------*/

#include <iostream>
#include "point.hpp"
#include "vect.hpp"
using namespace std;

int main()
{
    cout << "Hello Future Ray Tracer Developer!" << endl;

    Point point1(1,2,3);
    Point point2(3,2,1);
    Point result = point1 + point2;
    cout << result.GetX() << "," << result.GetY() << "," << result.GetZ() << '\n';

    Vect vect1(1, 2, 3);
    Vect vect2(3, 2, 1);
    Vect v_result = vect1 + vect2;
    cout << v_result.GetX() << "," <<  v_result.GetY() << "," << v_result.GetZ() << '\n';
}