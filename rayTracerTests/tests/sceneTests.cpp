/* ---------------------------------------------------------------------------
** sceneTests.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <gtest/gtest.h>
#include <pinhole.hpp>
#include <scene.hpp>
#include <sphere.hpp>
#include <pointLight.hpp>
#include <plane.hpp>
#include <meshTriangle.hpp>
#include <sceneSamples.hpp>
#include <geometry/mesh.hpp>
#include <transformationMatrix.hpp>
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
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/2, 1.0, 255, 255));
    unique_ptr<Image> renderedImage = scene.Render();
    renderedImage->Save("linePlane.ppm");
}

TEST(SimpleRender, SimpleTriangle)
{ // A triangle illuminated on its front
    Scene scene;
    scene.AddLightSource(PointLight());
    scene.AddShape(Triangle(Point(0,1,3), Point(-1,-1,3), Point(1,-1,3)));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/2, 1.0, 255, 255));
    unique_ptr<Image> renderedImage = scene.Render();
    renderedImage->Save("triangle.ppm");
}

/////////////////////////////////////////////////////////////

TEST(SimpleLight, Sphere)
{ // A sphere with a light over it and slightly off to the right
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,3), 1.0));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/2, 1.0, 255, 255));
    scene.AddLightSource(PointLight(Point(1,2,3)));
    auto renderedImage = scene.Render();
    renderedImage->Save("sphere.ppm");
}

TEST(SimpleLight, SphereOnAPlane)
{ // A sphere over a plane with a light right on top of the sphere
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,10), 1.0));
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));

    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), (float)3.14159/2, 1.0, 255, 255));
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

TEST(SimpleLight, PlaneTop)
{ // A plane as seen from the top
    Scene scene;
    scene.SetCamera(Pinhole(Vect(1,0,0), Vect(0,0,1), Vect(0,-1,0), Point (0,10,0), (float)3.14159/2, 1.0, 255, 255));

    scene.AddLightSource(PointLight(Point(0,1.5,0)));
    scene.AddShape(Plane(Point(0,0,0), Vect(0,1,0)));

    auto renderedImage = scene.Render();
    renderedImage->Save("planeTop.ppm");
}

/////////////////////////////////////////////////////////////

TEST(Mesh, Tetrahedron)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation((float)3.141592/4);
    tm.SetYRotation((float)3.141592/4.5f);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (-1.6f,2.5,1), (float)3.14159/2, 1.0, 255, 255));
    auto tetrahedron = ParseObjFile("/home/mjgalindo/ClionProjects/Ray_Tracer/resources/tetrahedron.obj");
    for(unsigned int i = 0; i < tetrahedron.size(); ++i)
    {
        scene.AddShape(*tetrahedron.at(i));
    }
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));
    scene.AddLightSource(PointLight(Point(-1,5,0)));
    auto renderedImage = scene.Render();
    renderedImage->Save("tetrahedron.ppm");
}


TEST(Mesh, Teapot)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetYRotation((float)3.141592/2);
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,10,-250), (float)3.14159/2, 1.0, 20, 20));
    auto teapot = ParseObjFile("/home/mjgalindo/ClionProjects/Ray_Tracer/resources/utah_teapot.obj");
    for(unsigned int i = 0; i < teapot.size(); ++i)
    {
        scene.AddShape(*teapot.at(i));
    }

    scene.AddShape(Plane(Point(-400, 0, 0), Vect(1,0,0))); // Left wall.
    scene.AddShape(Plane(Point(400, 0, 0), Vect(-1,0,0))); // Right wall.
    scene.AddShape(Plane(Point(0, 0, 400), Vect(0,0,-1))); // Back wall

    scene.AddLightSource(PointLight(Point(0,20,-100)));
    scene.AddShape(Plane(Point(0,-50, 0), Vect(0,1,0)));
    auto renderedImage = scene.Render();
    renderedImage->Save("teapot.ppm");
}


TEST(Mesh, Woman)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetYRotation((float)3.141592);
    scene.SetCamera(Pinhole(Vect(0,0,-1), Vect(1,0,0), Vect(0,-1,0), Point (1,60,0), (float)3.14159/2, 1.0, 140, 140));
    auto woman = ParseObjFile("/home/mjgalindo/ClionProjects/Ray_Tracer/resources/woman.obj");
    for(unsigned int i = 0; i < woman.size(); ++i)
    {
        scene.AddShape(*woman.at(i));
    }

    /*scene.AddShape(Plane(Point(-400, 0, 0), Vect(1,0,0))); // Left wall.
    scene.AddShape(Plane(Point(400, 0, 0), Vect(-1,0,0))); // Right wall.
    scene.AddShape(Plane(Point(0, 0, 400), Vect(0,0,-1))); // Back wall*/

    scene.AddLightSource(PointLight(Point(0,20,-25)));
    //scene.AddShape(Plane(Point(0,-50, 0), Vect(0,1,0)));
    auto renderedImage = scene.Render();
    renderedImage->Save("woman.ppm");
}