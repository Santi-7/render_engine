/* ---------------------------------------------------------------------------
** sceneTests.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <pinhole.hpp>
#include <plane.hpp>
#include <pointLight.hpp>
#include <scene.hpp>
#include <sceneSamples.hpp>
#include <transformationMatrix.hpp>
#include <triangle.hpp>

/**
 * Test first pixel value is correct
 */
TEST(PinholeTest, Basic)
{
    Pinhole phc(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point(0,0,0), (float)3.141592/2, 1.0, 2, 2);
    Point lr(phc.GetFirstPixel());
    EXPECT_LT(lr.GetX() - (-0.5), 0.0001);
    EXPECT_LT(lr.GetY() - (0.5), 0.0001);
    EXPECT_LT(lr.GetZ() - (1), 0.0001);
}
/////////////////////////////////////////////////////////////
// These tests will not work when proper lighting is added //
/////////////////////////////////////////////////////////////
TEST(SimpleRender, Sphere)
{
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,3), 1.0));
    scene.AddLightSource(PointLight());
    scene.SetCamera(Pinhole());
    unique_ptr<Image> renderedImage = scene.Render();
    renderedImage->Save("dot.ppm");
}

TEST(SimpleRender, InvisiblePlane)
{ // A plane parallel to the camera (so it can't be seen)
    Scene scene;
    scene.AddLightSource(PointLight());
    scene.AddShape(Plane(Point(0,0,0), Vect(-1,0,1)));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/3, 1.0, 255, 255));
    unique_ptr<Image> renderedImage = scene.Render();
    renderedImage->Save("linePlane.ppm");
}

TEST(SimpleRender, SimpleTriangle)
{ // A triangle illuminated on its front
    Scene scene;
    scene.AddLightSource(PointLight());
    scene.AddShape(Triangle(Point(0,1,3), Point(-1,-1,3), Point(1,-1,3)));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/3, 1.0, 255, 255));
    unique_ptr<Image> renderedImage = scene.Render();
    renderedImage->Save("triangle.ppm");
}

/////////////////////////////////////////////////////////////

TEST(SimpleLight, Sphere)
{ // A sphere with a light over it and slightly off to the right
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,3), 1.0));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/3, 1.0, 255, 255));
    scene.AddLightSource(PointLight(Point(1,2,3)));
    auto renderedImage = scene.Render();
    renderedImage->Save("sphere.ppm");
}

TEST(SimpleLight, SphereOnAPlane)
{ // A sphere over a plane with a light right on top of the sphere
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,10), 1.0));
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));

    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/3, 1.0, 255, 255));
    scene.AddLightSource(PointLight(Point(0,1.5,10)));
    auto renderedImage = scene.Render();
    renderedImage->Save("soap.ppm");
}

TEST(CornellBox, BigSpheres)
{ // Cornell's box. The sides of the box are spheres
    Scene scene = CornellBox(true);
    auto renderedImage = scene.Render();
    renderedImage->Save("cornellS.ppm");
}

TEST(CornellBox, Planes)
{ // Cornell's box. The sides of the box are planes
    Scene scene = CornellBox(false);
    auto renderedImage = scene.Render();
    renderedImage->Save("cornellP.ppm");
}

TEST(CornellBox, Colors)
{ // Cornell's box. Lights of colors distinct of white.
    Scene scene = CornellBox(false);
    scene.AddLightSource(PointLight(Point(0, 0, -5), 500.0, BLUE));
    auto renderedImage = scene.Render();
    renderedImage->Save("cornellColors.ppm");
}

TEST(SimpleLight, PlaneTop)
{ // A plane as seen from the top
    Scene scene;
    scene.SetCamera(Pinhole(Vect(1,0,0), Vect(0,0,1), Vect(0,-1,0), Point (0,10,0), (float)3.14159/3, 1.0, 255, 255));

    scene.AddLightSource(PointLight(Point(0,1.5,0)));
    scene.AddShape(Plane(Point(0,0,0), Vect(0,1,0)));

    auto renderedImage = scene.Render();
    renderedImage->Save("planeTop.ppm");
}

TEST(Reflection, PlaneSphere)
{ // A sphere over a plane.
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation((float)3.141592/10);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,4,-20), (float)3.14159/3, 1.0, 1920, 1080));

    scene.AddLightSource(PointLight(Point(3, 1.5, 4)));

    Sphere sphere(Point(0, 0.5, 4), 1);
    sphere.SetMaterial(Material(0));
    scene.AddShape(sphere);

    Plane plane1(Point(0, -0.5f, 0), Vect(0, 1, 0));
    plane1.SetMaterial(Material(1));
    scene.AddShape(plane1);

    Plane plane2(Point(0, 0, 60), Vect(0, 0, 1));
    scene.AddShape(plane2);
    Plane plane3(Point(-20, 0, 0), Vect(1, 0, 0));
    Plane plane4(Point(20, 0, 60), Vect(-1, 0,0));
    scene.AddShape(plane3);
    scene.AddShape(plane4);
    auto renderedImage = scene.Render();
    renderedImage->Save("reflection.ppm");
}

TEST(HiddenLight, AfterPlane)
{ // A camera, a plane, and a light.
    Scene scene;
    // The camera is in first place.
    scene.SetCamera(Pinhole());
    // Then the plane.
    scene.AddShape(Plane(Point(0,0,3), Vect(0,0,1)));
    // And then a light, that should be hidden by the plane.
    scene.AddLightSource(PointLight(Point(0,0,6)));
    auto renderedImage = scene.Render();
    renderedImage->Save("hiddenLight.ppm");

    // Same scene but with normal of the plane declared in the other direction.
    Scene scene2;
    // The camera is in first place.
    scene2.SetCamera(Pinhole());
    // Then the plane.
    scene2.AddShape(Plane(Point(0,0,3), Vect(0,0,-1)));
    // And then a light, that should be hidden by the plane.
    scene2.AddLightSource(PointLight(Point(0,0,6)));
    auto renderedImage2 = scene2.Render();
    renderedImage2->Save("hiddenLight2.ppm");
}