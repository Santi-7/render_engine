/* ---------------------------------------------------------------------------
** sceneSamples.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <scene.hpp>
#include <sphere.hpp>
#include <mathConstants.hpp>

// TODO: Add doc.
/**
 * .
 *
 * @return .
 */
Scene CornellBox(bool useSpheresAsWalls)
{
    Scene cornellBox;
    // A pinhole camera with default configuration.
    cornellBox.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1),
                                 Point (0,-0.25f,-1.5f), PI/3, 1.0, 300, 200));
    // Five big spheres pretend the box.
    if (useSpheresAsWalls)
    {
        cornellBox.AddShape(Sphere(Point(-50004, 0, 2), 50000)); // Left wall.
        cornellBox.AddShape(Sphere(Point(50004, 0, 2), 50000)); // Right wall.
        cornellBox.AddShape(Sphere(Point(0, -50004, 2), 50000)); // Floor.
        cornellBox.AddShape(Sphere(Point(0, 50004, 2), 50000)); // Roof.
        cornellBox.AddShape(Sphere(Point(0, 0, 50004), 50000)); // Back wall.
    }
    // The walls of the box are planes.
    else
    {
        cornellBox.AddShape(Plane(Point(-1, 0, 0), Vect(1,0,0))); // Left wall.
        cornellBox.AddShape(Plane(Point(1, 0, 0), Vect(-1,0,0))); // Right wall.
        cornellBox.AddShape(Plane(Point(0, 1, 0), Vect(0,-1,0))); // Roof.
        cornellBox.AddShape(Plane(Point(0, -1, 0), Vect(0,1,0))); // Floor.
        cornellBox.AddShape(Plane(Point(0, 0, 1), Vect(0,0,-1))); // Back wall

        cornellBox.AddShape(Plane(Point(0, 0, -4.5f), Vect(0,0,1))); // Back wall

    }
    // Two spheres inside the box.
    Sphere redSphere(Sphere(Point(-0.4f, -0.75f, 0.5f), 0.25f));
    Sphere greenSphere(Sphere(Point(0.4f, -0.75f, 0.5f), 0.25f));
    redSphere.SetMaterial(make_shared<Material>(Material(Color(0.5, 0.1,0.05), GRAY, 2.0f, BLACK, BLACK)));
    greenSphere.SetMaterial(make_shared<Material>(Material(Color(0.1, 0.05,0.5), BLACK, 2.0f, BLACK, BLACK)));
    cornellBox.AddShape(redSphere);
    cornellBox.AddShape(greenSphere);
    // A point light illuminates the scene.
    cornellBox.AddLightSource(PointLight(Point(0, 0.35f, 0), 2.0f, Color(1.0f, 1.0f, 0.95f)));

    return cornellBox;
}