using namespace std;

#include <iostream>

#include "point.cpp"

int main() {
    cout << "Hello Future Ray Tracer Developer!" << endl;

    Point point1 = Point(1,2,3);
    Point point2 = Point(3,2,1);
    Point result = point1 + point2;
    cout << result.GetX() << "," << result.GetY() << "," << result.GetZ() << endl;
}