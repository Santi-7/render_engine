/* ---------------------------------------------------------------------------
** sceneSamples.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <pinhole.hpp>
#include <sceneSamples.hpp>
#include <sphere.hpp>

Scene CornellBox()
{
    Scene cornellBox;
    // A pinhole camera with default configuration.
    cornellBox.SetCamera(Pinhole());
    // Five big spheres pretend the box.
    cornellBox.AddShape(Sphere(Point(-50004, 0, 2), 50000)); // Left wall.
    cornellBox.AddShape(Sphere(Point(50004, 0, 2), 50000)); // Right wall.
    cornellBox.AddShape(Sphere(Point(0, -50004, 2), 50000)); // Floor.
    cornellBox.AddShape(Sphere(Point(0, 50004, 2), 50000)); // Roof.
    cornellBox.AddShape(Sphere(Point(0, 0, 50004), 50000)); // Back wall.
    // Two spheres inside the box.
    cornellBox.AddShape(Sphere(Point(-2, -1, 2), 1));
    cornellBox.AddShape(Sphere(Point(2, -1, 2), 1));
    // TODO: Add a light source.
    return cornellBox;
}