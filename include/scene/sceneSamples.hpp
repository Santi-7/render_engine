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
#include <geometry/compositeShape.hpp>
#include <geometry/box.hpp>

// TODO: Add doc.
/**
 * .
 *
 * @return .
 */
Scene CornellBox()
{
    Scene cornellBox;
    // A pinhole camera with default configuration.
    cornellBox.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1),
                                 Point (0,0.25f,-1.7f), PI/4, 1.0, 1920, 1080));

    Plane leftWall(Plane(Point(-1, 0, 0), Vect(1, 0, 0)));
    leftWall.SetMaterial(make_shared<Material>(RED, BLACK, 0.0f, BLACK, BLACK));
    cornellBox.AddShape(leftWall);
    Plane rightWall(Plane(Point(1, 0, 0), Vect(-1, 0, 0)));
    rightWall.SetMaterial(make_shared<Material>(GREEN, BLACK, 0.0f, BLACK, BLACK));
    cornellBox.AddShape(rightWall);

    cornellBox.AddShape(Plane(Point(0, 1, 0), Vect(0, -1, 0))); // Roof.
    cornellBox.AddShape(Plane(Point(0, -0.25f, 0), Vect(0, 1, 0))); // Floor.
    cornellBox.AddShape(Plane(Point(0, 0, 1), Vect(0, 0, -1))); // Back wall

    // Two spheres inside the box.
    Sphere yellowSphere(Sphere(Point(-0.45f, 0.1, 0.4f), 0.25f));
    Sphere purpleSphere(Sphere(Point(0.45f, 0.1, 0.4f), 0.25f));
    yellowSphere.SetMaterial(make_shared<Material>(Material(YELLOW, GRAY, 0.2f, BLACK, BLACK)));
    purpleSphere.SetMaterial(make_shared<Material>(Material(PURPLE, BLACK, 0.0f, WHITE, BLACK)));
    cornellBox.AddShape(yellowSphere);
    cornellBox.AddShape(purpleSphere);
    // A point light illuminates the scene.
    cornellBox.AddLightSource(PointLight(Point(0, 0.6f, -0.1f), 2.0f, WHITE));

    return cornellBox;
}

CompositeShape Cabinet(const float cornerDistFromCenter, const float panelWidth,
                       const Vect &position, const shared_ptr<Material> material)
{
    Box backPanel(
            Rectangle(
                    Vect(0, 0, -1),
                    Point(-cornerDistFromCenter, -cornerDistFromCenter, cornerDistFromCenter) + position,
                    Point(cornerDistFromCenter, cornerDistFromCenter, cornerDistFromCenter) + position),
            panelWidth);

    backPanel.SetMaterial(material);

    Box leftPanel(
            Rectangle(
                    Vect(1, 0, 0),
                    Point(-cornerDistFromCenter, -cornerDistFromCenter, -cornerDistFromCenter) + position,
                    Point(-cornerDistFromCenter, cornerDistFromCenter, cornerDistFromCenter) + position),
            panelWidth);

    leftPanel.SetMaterial(material);

    Box rightPanel(
            Rectangle(
                    Vect(-1, 0, 0),
                    Point(cornerDistFromCenter, -cornerDistFromCenter, -cornerDistFromCenter) + position,
                    Point(cornerDistFromCenter, cornerDistFromCenter, cornerDistFromCenter) + position),
            panelWidth);

    rightPanel.SetMaterial(material);

    Box topPanel(
            Rectangle(
                    Vect(0, -1, 0),
                    Point(-cornerDistFromCenter, cornerDistFromCenter, -cornerDistFromCenter) + position,
                    Point(cornerDistFromCenter, cornerDistFromCenter, cornerDistFromCenter) + position),
            panelWidth);

    topPanel.SetMaterial(material);

    Box bottomPanel(
            Rectangle(
                    Vect(0, 1, 0),
                    Point(-cornerDistFromCenter, -cornerDistFromCenter, -cornerDistFromCenter) + position,
                    Point(cornerDistFromCenter, -cornerDistFromCenter, cornerDistFromCenter) + position),
            panelWidth);

    bottomPanel.SetMaterial(material);

    CompositeShape wholeCabinet;
    wholeCabinet.AddShape(backPanel);
    wholeCabinet.AddShape(leftPanel);
    wholeCabinet.AddShape(rightPanel);
    wholeCabinet.AddShape(topPanel);
    wholeCabinet.AddShape(bottomPanel);

    wholeCabinet.SetBoundingShape(
            Box(
                    Rectangle(
                    Vect(0, 1, 0),
                    Point(-cornerDistFromCenter, -cornerDistFromCenter, -cornerDistFromCenter) + position,
                    Point(cornerDistFromCenter, -cornerDistFromCenter, cornerDistFromCenter) + position),
                    (cornerDistFromCenter+panelWidth)*2));

    return wholeCabinet;
}