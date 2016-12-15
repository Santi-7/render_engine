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
#include <triangle.hpp>
#include <sceneSamples.hpp>
#include <transformationMatrix.hpp>
#include <mesh.hpp>
#include <fstream>
#include <geometry/rectangle.hpp>
#include <geometry/box.hpp>
#include <materials/checkerBoard.hpp>
#include <thread>
#include <materials/crossHatchModifier.hpp>
#include <geometry/compositeShape.hpp>
#include <geometry/mengerSponge.hpp>

static const unsigned int THREADS = std::thread::hardware_concurrency();

/**
 * Test first pixel value is correct
 */
TEST(PinholeTest, Basic)
{
    Pinhole phc(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point(0,0,0), PI/2, 1.0, 2, 2);
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
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("dot.ppm");
}

TEST(SimpleRender, InvisiblePlane)
{ // A plane parallel to the camera (so it can't be seen)
    Scene scene;
    scene.AddLightSource(PointLight());
    scene.AddShape(Plane(Point(0,0,0), Vect(-1,0,1)));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), PI/3, 1.0, 255, 255));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("linePlane.ppm");
}

TEST(SimpleRender, SimpleTriangle)
{ // A triangle illuminated on its front
    Scene scene;
    scene.AddLightSource(PointLight());
    scene.AddShape(Triangle(Point(0,1,3), Point(-1,-1,3), Point(1,-1,3)));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), PI/3, 1.0, 255, 255));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    ofstream algo("caca.txt");
    algo << "caca";
    algo.close();
    renderedImage->Save("triangle.ppm");
}

TEST(SimpleRender, FinitePlane)
{ // Test rendering of many finite planes
    Scene scene;
    scene.AddLightSource(PointLight(Point(0,1,-1)));
    scene.AddShape(Rectangle(Vect(0,0,-1),Point(0,0,0), Point(1,1,1)));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,-3), PI/3, 1.0, 255, 255));
    unique_ptr<Image> renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("finitePlanes.ppm");
}

/////////////////////////////////////////////////////////////

TEST(SimpleLight, Sphere)
{ // A sphere with a light over it and slightly off to the right
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,3), 1.0));
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), PI/3, 1.0, 255, 255));
    scene.AddLightSource(PointLight(Point(1,2,3)));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("sphere.ppm");
}

TEST(SimpleLight, SphereOnAPlane)
{ // A sphere over a plane with a light right on top of the sphere
    Scene scene;
    scene.AddShape(Sphere(Point(0,0,10), 1.0));
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));

    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0,0), PI/3, 1.0, 255, 255));
    scene.AddLightSource(PointLight(Point(0,1.5,10)));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("soap.ppm");
}

TEST(CornellBox, BigSpheres)
{ // Cornell's box. The sides of the box are spheres
    Scene scene = CornellBox(true);
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("cornellS.ppm");
}

TEST(CornellBox, Planes)
{ // Cornell's box. The sides of the box are planes.
    Scene scene = CornellBox(false);
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("cornellP.ppm");
}

TEST(CornellBox, Colors)
{ // Cornell's box. Lights of colors distinct of white.
    Scene scene = CornellBox(false);
    scene.AddLightSource(PointLight(Point(0, 0, -5), 500.0, BLUE));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("cornellColors.ppm");
}

TEST(SimpleLight, PlaneTop)
{ // A plane as seen from the top.
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,2,-2), PI/3, 1.0, 255, 255));

    scene.AddLightSource(PointLight(Point(0,3,7), 20, WHITE));
    Plane plane(Point(0,0,0), Vect(0,1,0));
    plane.SetMaterial(SPECKLED_LAMBERTIAN);
    scene.AddShape(plane);

    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("planeTop.ppm");
}

TEST(SimpleLight, Box)
{ // A plane as seen from the .
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (1,1,-5), PI/3, 1.0, 250, 250));

    scene.AddLightSource(PointLight(Point(1.5f,1.5f,-1.5f), 20, WHITE));
    Box redBox(Rectangle(Vect(0,0,1), Point(-0.4999f, 0.0001, 0.0001), Point(0.5f, -1, 0.0001)), 0.99999);

    redBox.SetMaterial(CheckerBoard(0.24999f, Color(0.85f, 0.22f, 0.04f), Color(0.15f, 0.12f, 0.9f)));
    scene.AddShape(redBox);

    Plane wall(Point(0, 0, 1.75f), Vect(0,0,-1));
    wall.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(wall);
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("box.ppm");
}

TEST(SimpleLight, BoxTop)
{ // A plane as seen from the .
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/2);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (1,4,-0.1f), PI/3, 1.0, 250, 250));

    scene.AddLightSource(PointLight(Point(1.5f,1.5f,-1.5f), 20, WHITE));
    Box redBox(Rectangle(Vect(0,0,1), Point(-0.4999f, 0.00001f, 0.0001), Point(0.5f, -0.9999f, 0.0001)), 1);
    redBox.SetMaterial(CheckerBoard(0.24999f, Color(0.85f, 0.22f, 0.04f), Color(0.15f, 0.12f, 0.9f)));
    scene.AddShape(redBox);

    Plane wall(Point(0, 0, 1.75f), Vect(0,0,-1));
    wall.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(wall);
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("boxTop.ppm");
}

TEST(Render, XBoxes)
{ // Just renders 6 boxes, each with a different normal
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,2, -6), PI/3, 1.0, 500, 500));
    scene.AddLightSource(PointLight(Point(0,7,-0.5f), 220, WHITE));

    scene.AddShape(Plane(Point(0,-0.5f,0), Vect(0,1,0)));
    scene.AddShape(Plane(Point(0,-0.5f,8), Vect(0,0,-1)));

    scene.AddShape(Box(Rectangle(Vect(1,0,0), Point(0, 0, 0), Point(0, 1, 1)), 1));
    scene.AddShape(Box(Rectangle(Vect(-1,0,0), Point(3, 0, 1.5), Point(3, 1, 2.5)), 1));

    scene.AddShape(Box(Rectangle(Vect(0,1,0), Point(-3, 0, 1.5), Point(-2, 0, 2.5)), 1));
    scene.AddShape(Box(Rectangle(Vect(0,-1,0), Point(-1.5f, 2, 0.5), Point(-2.5f, 2, -0.5f)), 1));

    scene.AddShape(Box(Rectangle(Vect(0,0,1), Point(-3, 2, 2.5), Point(-2, 3, 2.5)), 1));
    scene.AddShape(Box(Rectangle(Vect(0,0,-1), Point(3, 1, 1.5), Point(4, 2, 1.5)), 1));


    auto image = scene.RenderMultiThread(THREADS);
    image->Save("sixBoxes.ppm");
}

TEST(Reflection, PlaneSphere)
{ // A sphere over a plane.
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/10);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,4,-20), PI/3, 1.0, 200, 200));

    scene.AddLightSource(PointLight(Point(3, 1.5, 4)));

    Sphere sphere(Point(0, 0.5, 4), 1);
    sphere.SetMaterial(make_shared<Material>(Material(WHITE, BLACK, 20.0f, BLACK, BLACK)));
    scene.AddShape(sphere);

    Plane plane1(Point(0, -0.5f, 0), Vect(0, 1, 0));
    plane1.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 20.0f, WHITE, BLACK)));
    scene.AddShape(plane1);

    Plane plane2(Point(0, 0, 60), Vect(0, 0, 1));
    scene.AddShape(plane2);
    Plane plane3(Point(-20, 0, 0), Vect(1, 0, 0));
    Plane plane4(Point(20, 0, 60), Vect(-1, 0,0));
    scene.AddShape(plane3);
    scene.AddShape(plane4);
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("reflection.ppm");
}

TEST(Refraction, PlaneSphere)
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.5f,-1), PI/3, 1.0, 500, 500));

    scene.AddLightSource(PointLight(Point(0.2f, 0.5f, -1), 2, WHITE));

    Sphere sphere(Point(0, -0.75f, 0), 0.25f);
    sphere.SetMaterial(Material(BLACK, BLACK, 0.0f, GRAY, GRAY));
    sphere.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(sphere);

    Plane floor(Point(0, -1.0f, 0), Vect(0, 1, 0));
    floor.SetMaterial(CheckerBoard(0.149f, RED, BLUE));
    scene.AddShape(floor);

    Plane rightWall(Point(1, 0, 0), Vect(-1, 0, 0));
    rightWall.SetMaterial(CheckerBoard(0.149f, GREEN, BLUE));
    scene.AddShape(rightWall);

    Plane leftWall(Point(-1, 0, 0), Vect(1, 0, 0));
    leftWall.SetMaterial(CheckerBoard(0.149f, GREEN, RED));
    scene.AddShape(leftWall);

    Plane backWall(Point(0, 0, 1), Vect(0, 0, -1));
    backWall.SetMaterial(CheckerBoard(0.149f, BLACK, Color(1.0f, 1.0f, 0.0f)));
    scene.AddShape(backWall);

    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("refraction.ppm");
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
    auto renderedImage = scene.RenderMultiThread(THREADS);
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


/////////////////////////////////////////////////////////////

TEST(Mesh, Tetrahedron)
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0.25f,0.25f,0), (float)3.14159/2, 1.0, 255, 255));
    Mesh tetrahedron(string(PROJECT_DIR) + "/resources/tetrahedron.obj", 0.0f, Vect(0,0,0));
    scene.AddShape(tetrahedron);
    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));
    scene.AddLightSource(PointLight(Point(-1,5,0), 30, WHITE));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("tetrahedron.ppm");
}


TEST(Mesh, Teapot)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetYRotation((float)3.141592/2);
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0.2,-0.55f), (float)3.14159/2, 1.0, 600, 600));
    Mesh teapot(string(PROJECT_DIR) + "/resources/utah_teapot.obj", 0.35f, Vect(0,0,0));
    scene.AddShape(teapot);

    scene.AddShape(Plane(Point(-1.5f, 0, 0), Vect(1,0,0))); // Left wall.
    scene.AddShape(Plane(Point(1.5f, 0, 0), Vect(-1,0,0))); // Right wall.
    scene.AddShape(Plane(Point(0, 0, 3), Vect(0,0,-1))); // Back wall

    scene.AddLightSource(PointLight(Point(0,2.5f, 0), 15, WHITE));
    scene.AddShape(Plane(Point(0,-1.5f, 0), Vect(0,1,0)));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("teapot.ppm");
}


TEST(Mesh, Woman)
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,0,1), Vect(1,0,0), Vect(0,1,0), Point (0,-0.6f,0), (float)3.14159/2, 1.0, 300, 300));
    scene.AddLightSource(PointLight(Point(0,-0.5f,0), 1, WHITE));

    Mesh woman (string(PROJECT_DIR) + "/resources/woman.obj", 0.35f, Vect(0,0,0));
    scene.AddShape(woman);

    scene.AddShape(Plane(Point(-1.5f, 0, 0), Vect(1,0,0))); // Left wall.
    scene.AddShape(Plane(Point(1.5f, 0, 0), Vect(-1,0,0))); // Right wall.
    scene.AddShape(Plane(Point(0, 0, -2), Vect(0,0,-1))); // Back wall

    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("woman.ppm");
}

TEST(Mesh, IronGiant)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetYRotation((float) 3.141592);
    scene.SetCamera(Pinhole(Vect(0, 1, 0), Vect(1, 0, 0), Vect(0, 0, -1), Point(0, 0.35f, 0.95f), (float) 3.14159 / 2, 1.0, 500, 500));
    Mesh ironGiant = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/iron_giant.obj", 0.35f, Vect(0,0,0));
    scene.AddShape(ironGiant);

    scene.AddShape(Plane(Point(-1, 0, 0), Vect(1, 0, 0))); // Left wall.
    scene.AddShape(Plane(Point(1, 0, 0), Vect(-1, 0, 0))); // Right wall.
    scene.AddShape(Plane(Point(0, 0, 1), Vect(0, 0, -1))); // Back wall*/
    scene.AddShape(Plane(Point(0, 0, -1), Vect(0, 0, 1))); // Front wall*/
    scene.AddShape(Plane(Point(0, -0.346682f, 0), Vect(0, 1, 0))); // Floor
    scene.AddShape(Plane(Point(0, 1, 0), Vect(0, -1, 0))); // Ceiling
    scene.AddLightSource(PointLight(Point(0.1, 0.2f, -0.1f), 3, WHITE));
    scene.AddLightSource(PointLight(Point(-0.2f, -0.2f, 0.1f), 3, WHITE));

    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("ironGiant.ppm");
}

TEST(Mesh, Falcon)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(-PI/9);

    Mesh falcon(string(PROJECT_DIR) + "/resources/falcon2.obj", 0.35f, Vect(0,0,0));
    falcon.SetMaterial(make_shared<Material>(Material(RED / 2, BLACK, 0, BLACK, BLACK)));
    scene.AddShape(falcon);
    //scene.SetCamera(Pinhole(Vect(0,0,1), tm*Vect(1,0,0), tm*Vect(0, 1, 0), tm*Point (0, -2, 0), (float)3.14159/2, 1.0, 50, 40));
    scene.SetCamera(Pinhole(Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0, 0, 1), tm*Point (0, 0, -2), (float)3.14159/2, 1.0, 100, 100));

    scene.AddShape(Plane(Point(-2, 0, 0), Vect(1,0,0))); // Left wall.
    scene.AddShape(Plane(Point(2, 0, 0), Vect(-1,0,0))); // Right wall.
    scene.AddShape(Plane(Point(0, 0, 10), Vect(0,0,-1))); // Back wall*/
    //scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0))); // Floor

    scene.AddLightSource(PointLight(Point(0,2,-1.6f), 10, WHITE));
    scene.AddLightSource(PointLight(Point(0,1,0.6), 5, WHITE));

    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("falcon.ppm");
}


TEST(Mesh, BoundingVolumes)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetYRotation((float)3.141592/2);
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0.2,-0.55f), (float)3.14159/2, 1.0, 600, 600));
    Mesh teapot = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/darth_head.obj", 0.35, Vect(0,0,0));
    scene.AddShape(teapot);

    scene.AddShape(Plane(Point(-1.5f, 0, 0), Vect(1,0,0))); // Left wall.
    scene.AddShape(Plane(Point(1.5f, 0, 0), Vect(-1,0,0))); // Right wall.
    Plane backWall(Point(0, 0, 3), Vect(0,-1,-1));
    backWall.SetMaterial(MIRROR);
    scene.AddShape(backWall); // Back wall

    scene.AddLightSource(PointLight(Point(0,2.5f, 0), 15, WHITE));
    scene.AddShape(Plane(Point(0,-1.5f, 0), Vect(0,1,0)));
    auto renderedImage = scene.RenderMultiThread(THREADS);
    renderedImage->Save("bounding.ppm");
}

TEST(Materials, FacingMirrors)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/10);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,4,-5), PI/3, 1.0, 50, 50));
    scene.AddLightSource(PointLight(Point(0,5,6), 150, WHITE));

    Plane visibleMirror(Point(0,0,7), Vect(-0.4f, 0, 1));
    visibleMirror.SetMaterial(MIRROR);
    Plane hiddenMirror(Point(0,0,-7), Vect(-0.4f,0,1));
    hiddenMirror.SetMaterial(MIRROR);
    Plane floor(Point(0,-5,0), Vect(0,1,0));
    Sphere floatingSphere(Point(0,0,3), 1);
    scene.AddShape(visibleMirror);
    scene.AddShape(hiddenMirror);
    scene.AddShape(floatingSphere);
    scene.AddShape(floor);
    auto image = scene.RenderMultiThread(THREADS);
    image->Save("facingMirrors.ppm");
}

TEST(Materials, InsideCheckerboardBox)
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0.3,-0.65f), PI/3, 1.0, 700, 700));

    scene.AddLightSource(PointLight(Point(0,0.55f,0), 1, WHITE));

    Box container(Rectangle(Vect(0,1,0), Point(0.5f, 0.001f, -0.75f), Point(-0.5f, 0.001f, 0.75f)), 1);
    container.SetMaterial(CheckerBoard(0.14999, WHITE, BLACK));
    scene.AddShape(container);
    auto image = scene.RenderMultiThread(THREADS);
    image->Save("mirrorBox.ppm");
}

TEST(Materials, XSpheres)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/4);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,10,-12), PI/3, 1.0, 500, 500));
    scene.AddLightSource(PointLight(Point(0,12,0), 520, WHITE));

    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));

    const int SIZE = 20;

    for(int i = -SIZE/2; i < SIZE/2; ++i)
    {
        for(int j = -SIZE/2; j < SIZE/2; ++j)
        {
            Sphere tmp = Sphere(Point(i*2.5f,0,j*2.5f), 1);
            if((j % 2 == 0) ^ (i %2 != 0)) tmp.SetMaterial(MIRROR);
            scene.AddShape(tmp);
        }
    }
    auto image = scene.RenderMultiThread(THREADS);
    image->Save("spheres.ppm");
}

TEST(Materials, GlassSpheres)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/4);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,10,-12), PI/3, 1.0, 50, 50));
    scene.AddLightSource(PointLight(Point(0,12,0), 520, WHITE));

    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));

    const int SIZE = 20;

    for(int i = -SIZE/2; i < SIZE/2; ++i)
    {
        for(int j = -SIZE/2; j < SIZE/2; ++j)
        {
            Sphere tmp = Sphere(Point(i*2.5f,0,j*2.5f), 1);
            if((j % 2 == 0) ^ (i %2 != 0)) tmp.SetMaterial(GLASS);
            scene.AddShape(tmp);
        }
    }
    auto image = scene.RenderMultiThread(THREADS);
    image->Save("glassSpheres.ppm");
}

TEST(Materials, SpeckledLambiertianSpheres)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/4);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,10,-12), PI/3, 1.0, 450, 450));
    scene.AddLightSource(PointLight(Point(0,12,0), 520, WHITE));

    scene.AddShape(Plane(Point(0,-1,0), Vect(0,1,0)));

    const int SIZE = 20;

    for(int i = -SIZE/2; i < SIZE/2; ++i)
    {
        for(int j = -SIZE/2; j < SIZE/2; ++j)
        {
            Sphere tmp = Sphere(Point(i*2.5f,0,j*2.5f), 1);
            if((j % 2 == 0) ^ (i %2 != 0)) tmp.SetMaterial(SPECKLED_LAMBERTIAN);
            scene.AddShape(tmp);
        }
    }
    auto image = scene.RenderMultiThread(THREADS);
    image->Save("speckledLambertianSpheres.ppm");
}

TEST(Materials, SphereInSphere)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/10);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,-0.1f,-1), PI/3, 1.0, 500, 500));
    scene.AddLightSource(PointLight(Point(0,4.35f,0.1f), 150, WHITE));

    Plane board(Plane(Point(0,-1,0), Vect(0,1,0)));
    auto chessMat = CheckerBoard(0.24999f, (RED + GREEN) / 2, BLACK);
    board.SetMaterial(chessMat);
    scene.AddShape(board);
    Plane redWall(Plane(Point(0,0,1), Vect(0,0,-1)));
    redWall.SetMaterial(make_shared<Material>(Material(RED/2, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(redWall);

    scene.AddShape(Plane(Point(1,0,0), Vect(-1,0,0)));
    scene.AddShape(Plane(Point(-1,0,0), Vect(1,0,0)));

    Sphere oSphere(Point(0,-0.25f,0), 0.25f);
    oSphere.SetMaterial(GLASS); oSphere.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(oSphere);

    Sphere mSphere(Point(0,-0.25f,0), 0.05f);
    mSphere.SetMaterial(GLASS); mSphere.SetRefractiveIndex(WATER_RI);
    scene.AddShape(mSphere);

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("sphereception.ppm");
}

TEST(Materials, Chess)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/6);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (0,-0.3f,-1), PI/3, 1.0, 250, 250));
    scene.AddLightSource(PointLight(Point(0,1,-0.4f), 3, WHITE));

    Plane board(Plane(Point(0,-1,0), Vect(0,1,0)));
    auto chessMat = CheckerBoard(0.49f, WHITE, BLACK);
    board.SetMaterial(chessMat);
    scene.AddShape(board);

    Sphere oSphere(Point(0,-0.75f,0), 0.25f);
    oSphere.SetMaterial(MIRROR);
    scene.AddShape(oSphere);

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("chess.ppm");
}


TEST(Materials, Wrinkled)
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.5f,-6.3f), PI/3, 1.0, 250, 250));
    scene.AddLightSource(PointLight(Point(-1, 3, 0), 3, WHITE));
    scene.AddLightSource(PointLight(Point(1, 3, 0), 3, WHITE));

    Plane board(Plane(Point(0,-1.5f,0), Vect(0,1,0)));
    //auto chessMat = CheckerBoard(0.49f, WHITE, BLACK);
    //board.SetMaterial(chessMat);
    scene.AddShape(board);

    Plane wall(Point(0,0,1.5f), Vect(0,0,-1));
    wall.SetNormalModifier(make_shared<CrossHatchModifier>(CrossHatchModifier(100,100,100)));
    scene.AddShape(wall);

    //CrossHatch oSphere(make_shared<Sphere>(Sphere(Point(0,-0.75f,0.2f), 0.55f)), 1.0f, 0.0f, 0.0f);
    Sphere oSphere(Point(0,-0.75f,0.2f), 0.55f);

    scene.AddShape(oSphere);

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("wrinkled.ppm");
}


TEST(LightShape, Desert)
{
    Scene scene;

    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point(0, 0.0005f, -0.09f), PI/3, 1.0, 250, 250));

    Plane ground(Point(0,0,0), Vect(0,1,0));
    ground.SetMaterial(make_shared<Material>(Material(Color((YELLOW + RED / 10) / 3), BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(ground);

    Sphere littleSphere(Point(0, 0.0004f, 0.05f), 0.0003f);
    littleSphere.SetMaterial(MIRROR);
    scene.AddShape(littleSphere);

    Sphere sky(Point(0,0,0), 400.0f);
    sky.SetMaterial(make_shared<Material>(Material(Color(0, 0.5f, 0.99f), BLACK, 0.0f, BLACK, WHITE * 0.9f)));
    sky.SetEmittedLight(Color(0, 0.5f, 0.99f), 1);
    scene.AddShape(sky);

    scene.AddLightSource(PointLight(Point(-20, 29, 30), 100, WHITE ));
    Sphere sun(Point(-20, 50, 30), 20.0f);
    sun.SetMaterial(make_shared<Material>(Material(WHITE + RED/1.5f + YELLOW /5, WHITE, 0.2f, WHITE, WHITE)));
    sun.SetEmittedLight(WHITE, 0.95f);
    scene.AddShape(sun);

    auto image = scene.RenderMultiThread(THREADS);

    image->Save("desert.ppm");
}

TEST(NewIndirect, Planes)
{
    Scene scene;

    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point(0, 0.0005f, -0.09f), PI/3, 1.0, 250, 250));

    scene.AddLightSource(PointLight(Point(0, 0.5, 0.3f), 4, WHITE));

    Plane ground(Point(0,-0.75f,0), Vect(0,1,0));
    ground.SetMaterial(make_shared<Material>(Material(YELLOW, BLACK, 0.0f, BLACK, BLACK)));
    ground.SetEmittedLight(ground.GetMaterial()->GetDiffuse(), 0.5f);
    scene.AddShape(ground);

    Plane ceiling(Point(0,0.75f,0), Vect(0,-1, 0));
    ceiling.SetMaterial(make_shared<Material>(Material(PURPLE, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(ceiling);

    auto image = scene.RenderMultiThread(THREADS);

    image->Save("indirectP.ppm");
}

TEST(Complex, TeaTime)
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetXRotation(PI/8);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point(0, -0.15f, -0.6f), PI/3, 1.0, 700, 700));
    scene.AddLightSource(PointLight(Point(0.3,0.3, 0), 2.3f, WHITE));

    Box table(Rectangle(Vect(0,1,0), Point(-0.25f, -0.8f, -0.2f), Point(0.25f, -0.8f, 0.4f)), 0.35f);
    //table.SetMaterial(CheckerBoard(0.0499f, RED / 2 , BLUE / 2));
    // TODO: Find out if this can be used at all...
    table.SetNormalModifier(make_shared<CrossHatchModifier>(CrossHatchModifier(4000,4000,4000)));
    scene.AddShape(table);

    Mesh teapot = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/utah_teapot.obj", 0.25f, Vect(0,0,-1));
    teapot.SetMaterial(MIRROR);
    scene.AddShape(teapot);

    Sphere environment(Point(0,0,0), 2);
    scene.AddShape(environment);

    /*Box room(Rectangle(Vect(0,1,0), Point(-1, 1, -3), Point(1, 1, 1)), 1);
    //room.SetMaterial(CheckerBoard(0.499f, WHITE, BLACK));
    scene.AddShape(room);*/

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("teaTime.ppm");
}


TEST(Award, Exposition)
{
    Scene scene;

    scene.SetCamera(
            Pinhole(Vect(0, 1, 0), Vect(1, 0, 0), Vect(0, 0, 1), Point(0.0f, 0.3f, -0.55f), PI/3, 1.0, 100, 100));

    scene.AddLightSource(PointLight(Point(0.0f, 0.4f, -0.9f), 3, WHITE));

    auto reflWhite(make_shared<Material>(Material(WHITE, BLACK, 0.0f, BLACK, BLACK)));

    Plane backWall(Point(0, 0, 1), Vect(0, 0, -1));
    backWall.SetMaterial(reflWhite);
    scene.AddShape(backWall);

    float shift = 0.35f;
    float cabinetSize = 0.15f;
    float currentX = -0.3f, currentY = 0.4f, currentZ = 0.8f;

    TransformationMatrix turnAroundY;
    turnAroundY.SetYRotation(PI);

    TransformationMatrix halfTurnY;
    halfTurnY.SetYRotation(PI/2);

    TransformationMatrix falcon;
    falcon.SetXRotation(PI/2);
    falcon.SetYRotation(PI/4);

    CompositeShape cabinet1 = Cabinet(cabinetSize, cabinetSize/10, Vect(currentX, currentY, currentZ), reflWhite);
    Mesh item1 = Mesh::LoadObjFile(string(PROJECT_DIR)+"/resources/darth_head.obj", 0.1f, Vect(currentX, currentY, currentZ), turnAroundY);
    item1.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, WHITE/2, BLACK)));
    cabinet1.AddShape(item1);
    currentX += shift;

    CompositeShape cabinet2 = Cabinet(cabinetSize, cabinetSize/10, Vect(currentX, currentY, currentZ), reflWhite);
    Mesh item2 = Mesh::LoadObjFile(string(PROJECT_DIR)+"/resources/utah_teapot.obj", 0.1f, Vect(currentX, currentY-0.04f, currentZ));
    item2.SetMaterial(MIRROR);
    cabinet2.AddShape(item2);
    currentX += shift;

    CompositeShape cabinet3 = Cabinet(cabinetSize, cabinetSize/10, Vect(currentX, currentY, currentZ), reflWhite);
    Mesh item3 = Mesh::LoadObjFile(string(PROJECT_DIR)+"/resources/dragonFlat.obj", 0.1f, Vect(currentX, currentY, currentZ), halfTurnY);
    item3.SetMaterial(make_shared<Material>(Material(RED, BLACK, 0.0f, WHITE/1.2f, BLACK)));
    cabinet3.AddShape(item3);
    currentX -= shift * 2;
    currentY -= shift;

    CompositeShape cabinet4 = Cabinet(cabinetSize, cabinetSize/10, Vect(currentX, currentY, currentZ), reflWhite);
    Mesh item4 = Mesh::LoadObjFile(string(PROJECT_DIR)+"/resources/falcon.obj", 0.15f, Vect(currentX-0.1f, currentY+0.1f, currentZ), falcon);
    cabinet4.AddShape(item4);
    currentX += shift;

    CompositeShape cabinet5 = Cabinet(cabinetSize, cabinetSize/10, Vect(currentX, currentY, currentZ), reflWhite);
    Mesh item5 = Mesh::LoadObjFile(string(PROJECT_DIR)+"/resources/electric_rat.obj", 0.08f, Vect(currentX, currentY-0.01f, currentZ), turnAroundY);
    item5.SetMaterial(make_shared<Material>(Material(YELLOW, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(item5);
    currentX += shift;

    CompositeShape cabinet6 = Cabinet(cabinetSize, cabinetSize/10, Vect(currentX, currentY, currentZ), reflWhite);
    Mesh item6 = Mesh::LoadObjFile(string(PROJECT_DIR)+"/resources/buddha.obj", 0.1f, Vect(currentX+0.05f, currentY, currentZ), turnAroundY);
    item6.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, WHITE/1.2f, BLACK)));
    cabinet6.AddShape(item6);

    scene.AddShape(cabinet1);
    scene.AddShape(cabinet2);
    scene.AddShape(cabinet3);
    scene.AddShape(cabinet4);
    scene.AddShape(cabinet5);
    scene.AddShape(cabinet6);

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("exposition.ppm");
}


TEST(Award, Room)
{
    Scene scene;

    // Real View
    scene.SetCamera(
            Pinhole(Vect(0, 1, 0), Vect(1, 0, 0), Vect(0, 0, 1), Point(0, 0.1f, -1.2f),
                    PI/3, 1.0, 1500, 1000));

    // Top View (To adjust stuff)
    /*scene.SetCamera(
            Pinhole(Vect(0, 0, 1), Vect(1, 0, 0), Vect(0, -1, 0), Point(0.1f, 3.9f, -0.1f),
                    PI/4, 1.0, 500, 500));*/

    //////////////////////////////
    //// Making the room /////////
    //////////////////////////////

    Rectangle floor(Vect(0,1,0), Point(-1, -0.55f, -1), Point(1, -0.55f, 1));
    floor.SetMaterial(make_shared<Material>(Material(Color(0.1f, 0.1f, 0.1f), GRAY, 10.0f, GRAY/3, BLACK)));
    scene.AddShape(floor);

    Rectangle ceiling(Vect(0,-1,0), Point(-1, 1.05f, -1), Point(1, 1.05f, 1));
    scene.AddShape(ceiling);

    Rectangle leftWallBot(Vect(1,0,0), Point(-1, -0.55f, -1), Point(-1, 0, 1));
    Rectangle leftWallTop(Vect(1,0,0), Point(-1, 0.75f, -1), Point(-1, 1.05f, 1));
    Rectangle leftWallLeft(Vect(1,0,0), Point(-1, 0, -1), Point(-1, 0.75f, 0.05f));
    Rectangle leftWallRight(Vect(1,0,0), Point(-1, 0, 0.85f), Point(-1, 0.75f, 1));
    scene.AddShape(leftWallBot);
    scene.AddShape(leftWallTop);
    scene.AddShape(leftWallLeft);
    scene.AddShape(leftWallRight);

    Rectangle rightWall(Vect(-1,0,0), Point(1, -0.55f, -1), Point(1, 1.05f, 1));
    scene.AddShape(rightWall);

    Rectangle backWall(Vect(0,0,-1), Point(-1, -0.55f, 1), Point(1, 1.05f, 1));
    scene.AddShape(backWall);

    Rectangle hiddenWall(Vect(0,0,1), Point(-1, -0.55f, -1.2f), Point(1, 1.05f, -1.2f));
    scene.AddShape(hiddenWall);

    // Cover the room to avoid thresholds on edges.

    Rectangle floorCover(Vect(0,1,0), Point(-1.1f, -0.6f, -1.1f), Point(1.1f, -0.6f, 1.1f));
    floorCover.SetMaterial(NONE);
    scene.AddShape(floorCover);

    Rectangle ceilingCover(Vect(0,-1,0), Point(-1.1f, 1.1f, -1.1f), Point(1.1f, 1.1f, 1.1f));
    ceilingCover.SetMaterial(NONE);
    scene.AddShape(ceilingCover);

    Rectangle leftCoverBot(Vect(1,0,0), Point(-1.05f, -0.65f, -1.05f), Point(-1.05f, -0.05f, 1.05f));
    Rectangle leftCoverTop(Vect(1,0,0), Point(-1.05f, 0.8f, -1.05f), Point(-1.05f, 1.15f, 1.05f));
    Rectangle leftCoverLeft(Vect(1,0,0), Point(-1.05f, -0.05f, -1.05f), Point(-1.05f, 0.8f, 0));
    Rectangle leftCoverRight(Vect(1,0,0), Point(-1.05f, -0.05f, 0.9f), Point(-1.05f, 0.8f, 1.05f));
    leftCoverBot.SetMaterial(NONE);
    leftCoverTop.SetMaterial(NONE);
    leftCoverLeft.SetMaterial(NONE);
    leftCoverRight.SetMaterial(NONE);
    scene.AddShape(leftCoverBot);
    scene.AddShape(leftCoverTop);
    scene.AddShape(leftCoverLeft);
    scene.AddShape(leftCoverRight);

    Rectangle rightCover(Vect(-1,0,0), Point(1.05, -0.65f, -1.05f), Point(1.05, 1.15f, 1.05f));
    rightCover.SetMaterial(NONE);
    scene.AddShape(rightCover);

    Rectangle backCover(Vect(0,0,-1), Point(-1.1f, -0.65f, 1.05f), Point(1.1f, 1.15f, 1.05f));
    backCover.SetMaterial(NONE);
    scene.AddShape(backCover);

    //////////////////////////////
    //// Light           /////////
    //////////////////////////////

    /*scene.AddLightSource(PointLight(Point(-0.5f, 0.55f, -0.4f), 5, WHITE));
    scene.AddLightSource(PointLight(Point(-0.5f, 0.55f,  0.4f), 5, WHITE));
    scene.AddLightSource(PointLight(Point( 0.5f, 0.55f, -0.4f), 5, WHITE));
    //scene.AddLightSource(PointLight(Point( 0.4f, 0.85f,  0.4f), 4, WHITE));

    scene.AddLightSource(PointLight(Point(0.5f, 0, -0.4f), 5, WHITE));*/

    // Sun.
    scene.AddLightSource(PointLight(Point(-1.5f, 0.9f, 0.45f), 100, (RED + RED + YELLOW) / 3));

    /* This could have looked pretty... on hold
     * Sphere lightBulb(Point(0,1,0), 0.15f);
    lightBulb.SetEmittedLight(Color(1.0f, 0.8f, 0.6));
    scene.AddShape(lightBulb);*/

    //////////////////////////////
    //// Making a table //////////
    //////////////////////////////

    // To 'easily' build the table in the origin of coordinates and then move it
    Vect tableShift(-0.5f, 0, 0.5f);
    float pos = 0.2f;
    float legDim = 0.025f;
    float legDepth = 0.3f;
    float legBaseY = -0.5f;

    shared_ptr<Material> woodOrSomething = make_shared<Material>(Material(Color(0.6f, 0.3f, 0.0f), BLACK, 0.0f, BLACK, BLACK));

    Box leg1(Rectangle(Vect(0,1,0), Point(-pos, legBaseY, -pos) + tableShift, Point(-pos+legDim, legBaseY, -pos+legDim) + tableShift), legDepth);
    Box leg2(Rectangle(Vect(0,1,0), Point(pos, legBaseY, -pos) + tableShift, Point(pos+legDim, legBaseY, -pos+legDim) + tableShift), legDepth);

    float zShift = 0.5f;

    Box leg3(Rectangle(Vect(0,1,0), Point(-pos, legBaseY, pos - zShift) + tableShift, Point(-pos+legDim, legBaseY, pos - zShift + legDim) + tableShift), legDepth);
    Box leg4(Rectangle(Vect(0,1,0), Point( pos, legBaseY, pos - zShift) + tableShift, Point( pos+legDim, legBaseY, pos - zShift + legDim) + tableShift), legDepth);

    float extraTopLength = 0.05f;
    float tableTopDepth = 0.04f;
    float offsetWithLegs = 0.005f;

    Box tableTop(
            Rectangle(
                    Vect(0,1,0),
                    Point(-pos - extraTopLength, legBaseY + legDepth - offsetWithLegs, -pos - extraTopLength - zShift) + tableShift,
                    Point( pos + extraTopLength, legBaseY + legDepth - offsetWithLegs,  pos + extraTopLength) + tableShift),
            tableTopDepth
    );

    leg1.SetMaterial(woodOrSomething);
    leg2.SetMaterial(woodOrSomething);
    leg3.SetMaterial(woodOrSomething);
    leg4.SetMaterial(woodOrSomething);
    tableTop.SetMaterial(woodOrSomething);

    CompositeShape wholeTable;
    wholeTable.AddShape(leg1);
    wholeTable.AddShape(leg2);
    wholeTable.AddShape(leg3);
    wholeTable.AddShape(leg4);
    wholeTable.AddShape(tableTop);

    // Making a chessBoard on the table

    float squareSize = 0.055f;
    float boardZOffset = 0.25f;
    CheckerBoard pattern(squareSize, BLACK, WHITE, GRAY/2);

    Rectangle board(Vect(0,1,0),
            Point(-squareSize * 4, legBaseY + legDepth + tableTopDepth, -squareSize * 4 - boardZOffset) + tableShift,
            Point( squareSize * 4, legBaseY + legDepth + tableTopDepth,  squareSize * 4 - boardZOffset) + tableShift);
    board.SetMaterial(pattern);
    wholeTable.AddShape(board);

    { // Add Meshes on top of the table and include them in the bounding box for the composite shape

        //////////////////////////////
        //// FATHER!!            /////
        //////////////////////////////
        TransformationMatrix vaderTM;
        vaderTM.SetYRotation(PI);
        Mesh vader = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/darth_head.obj", 0.1f,
                Vect(-0.45f, legDepth+tableTopDepth+0.1f-0.48f, 0.35f), vaderTM);
        vader.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, GRAY/2, BLACK)));
        wholeTable.AddShape(vader);

        /// vs...

        //////////////////////////////
        //// Buddha!?            /////
        //////////////////////////////

        Mesh buddha = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/buddha.obj", 0.1f,
                Vect(-0.45f, legDepth+tableTopDepth+0.1f-0.48f, -0.1f));
        buddha.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, GRAY/3.5f, BLACK)));
        wholeTable.AddShape(buddha);
    }

    wholeTable.SetBoundingShape(Box(Rectangle(Vect(0,1,0),
                                              Point(-pos - extraTopLength, -0.5f, -pos - extraTopLength - zShift) + tableShift,
                                              Point(pos + extraTopLength, -0.5f,  pos + extraTopLength) + tableShift), legDepth + tableTopDepth + 0.25f));
    scene.AddShape(wholeTable);

    //////////////////////////////
    //// TEAPOT!!            /////
    //////////////////////////////

    /*Mesh teapot = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/utah_teapot.obj", 0.0f, Vect(0.5f,0.85f,0.85f));
    teapot.SetMaterial(MIRROR);
    scene.AddShape(teapot);*/

    //////////////////////////////
    //// ShowCase            /////
    //////////////////////////////

    /*CompositeShape wholeShowcase;

    Box backShowCase(Rectangle(Vect(0,0,-1), Point(0.3f, -0.55f, 1), Point(0.95f, 0.7f, 1)), 0.2f);
    backShowCase.SetMaterial(woodOrSomething);
    wholeShowcase.AddShape(backShowCase);*/

    /* Shelf Top 0 */

    /*Box shelf0(Rectangle(Vect(0,1,0), Point(0.3f, 0.65f, 0.8), Point(0.95f, 0.65f, 0.5)), 0.05f);
    shelf0.SetMaterial(woodOrSomething);
    wholeShowcase.AddShape(shelf0);*/

    /* Shelf 1 */

    /*Box shelf1(Rectangle(Vect(0,1,0), Point(0.3f, 0.35f, 0.8), Point(0.95f, 0.35f, 0.5)), 0.05f);
    shelf1.SetMaterial(woodOrSomething);
    wholeShowcase.AddShape(shelf1);

    Sphere s1_1(Point(0.425f, 0.475f, 0.65f), 0.075f);
    s1_1.SetMaterial(make_shared<Material>(Material(WHITE, GRAY, 1.0f, BLACK, BLACK)));
    wholeShowcase.AddShape(s1_1);

    Sphere s1_2(Point(0.625f, 0.475f, 0.65f), 0.075f);
    s1_2.SetMaterial(make_shared<Material>(Material(GRAY, BLACK, 0.0f, GRAY, BLACK)));
    wholeShowcase.AddShape(s1_2);

    Sphere s1_3(Point(0.825f, 0.475f, 0.65f), 0.075f);
    s1_3.SetMaterial(make_shared<Material>(Material(GRAY, GRAY, 0.0f, BLACK, GRAY)));
    wholeShowcase.AddShape(s1_3);*/

    /* Shelf 2 */

    /*Box shelf2(Rectangle(Vect(0,1,0), Point(0.3f, 0.05f, 0.8), Point(0.95f, 0.05f, 0.5)), 0.05f);
    shelf2.SetMaterial(woodOrSomething);
    wholeShowcase.AddShape(shelf2);

    Sphere s2_1(Point(0.425f, 0.175f, 0.65f), 0.075f);
    s2_1.SetMaterial(GLASS);
    s2_1.SetRefractiveIndex(GLASS_RI);
    wholeShowcase.AddShape(s2_1);

    Sphere s2_2(Point(0.625f, 0.175f, 0.65f), 0.075f);
    s2_2.SetMaterial(GLASS);
    s2_2.SetRefractiveIndex(WATER_RI);
    wholeShowcase.AddShape(s2_2);

    Sphere s2_3(Point(0.825f, 0.175f, 0.65f), 0.075f);
    s2_3.SetMaterial(GLASS);
    s2_3.SetRefractiveIndex(WATER_RI);
    s2_3.SetNormalModifier(make_shared<VectorModifier>(CrossHatchModifier(1000, 1000, 1000)));
    wholeShowcase.AddShape(s2_3);*/

    /* Shelf 3 */

    /*Box shelf3(Rectangle(Vect(0,1,0), Point(0.3f, -0.25f, 0.8), Point(0.95f, -0.25f, 0.5)), 0.05f);
    shelf3.SetMaterial(woodOrSomething);
    wholeShowcase.AddShape(shelf3);

    Sphere s3_1(Point(0.425f, -0.125f, 0.65f), 0.075f);
    wholeShowcase.AddShape(s3_1);

    Sphere s3_2(Point(0.625f, -0.125f, 0.65f), 0.075f);
    wholeShowcase.AddShape(s3_2);

    Sphere s3_3(Point(0.825f, -0.125f, 0.65f), 0.075f);
    wholeShowcase.AddShape(s3_3);*/

    /* Shelf 4 */

    /*Box shelf4(Rectangle(Vect(0,1,0), Point(0.3f, -0.55f, 0.8), Point(0.95f, -0.55f, 0.5)), 0.05f);
    shelf4.SetMaterial(woodOrSomething);
    wholeShowcase.AddShape(shelf4);

    Sphere s4_1(Point(0.425f, -0.425f, 0.65f), 0.075f);
    wholeShowcase.AddShape(s4_1);

    Sphere s4_2(Point(0.625f, -0.425f, 0.65f), 0.075f);
    wholeShowcase.AddShape(s4_2);

    Sphere s4_3(Point(0.825f, -0.425f, 0.65f), 0.075f);
    wholeShowcase.AddShape(s4_3);

    wholeShowcase.SetBoundingShape(Box(Rectangle(Vect(0,1,0), Point(0.3f, -0.55f, 0.5f), Point(0.95f, -0.55f, 1.0f)), 1.55f ));
    scene.AddShape(wholeShowcase);*/

    //////////////////////////////
    //// WINDOW              /////
    //////////////////////////////

    Box windowFrameTop(Rectangle(Vect(1,0,0), Point(-1, 0.7f, 0.85f), Point(-1, 0.75f, 0.05f)), 0.01f);
    windowFrameTop.SetMaterial(make_shared<Material>(Material(GRAY, WHITE, 10.0f, GRAY/4, BLACK)));
    Box windowFrameBottom(Rectangle(Vect(1,0,0), Point(-1, 0, 0.85f), Point(-1, 0.05f, 0.05f)), 0.01f);
    windowFrameBottom.SetMaterial(make_shared<Material>(Material(GRAY, WHITE, 10.0f, GRAY/4, BLACK)));
    Box windowFrameLeft(Rectangle(Vect(1,0,0), Point(-1, 0, 0.85f), Point(-1, 0.75f, 0.8f)), 0.01f);
    windowFrameLeft.SetMaterial(make_shared<Material>(Material(GRAY, WHITE, 10.0f, GRAY/4, BLACK)));
    Box windowFrameRight(Rectangle(Vect(1,0,0), Point(-1, 0, 0.1f), Point(-1, 0.75f, 0.05f)), 0.01f);
    windowFrameRight.SetMaterial(make_shared<Material>(Material(GRAY, WHITE, 10.0f, GRAY/4, BLACK)));

    scene.AddShape(windowFrameTop);
    scene.AddShape(windowFrameBottom);
    scene.AddShape(windowFrameLeft);
    scene.AddShape(windowFrameRight);

    //////////////////////////////
    //// ENVIRONMENT         /////
    //////////////////////////////

    Sphere environment(Point(0, 0, 0), 20);
    environment.SetEmittedLight(SKY_BLUE, 40);
    scene.AddShape(environment);

    //////////////////////////////
    //// FALCON!             /////
    //////////////////////////////

    //TransformationMatrix falconTM;
    //falconTM.SetXRotation(PI);
    //falconTM.SetYRotation(PI/4);
    //Mesh falcon = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/falcon.obj", 0.2f, Vect(-0.45f, 1.0f, 1.4f), falconTM);
    //scene.AddShape(falcon);

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("award.ppm");
}

TEST(MaterialMesh, Dragon)
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/10);
    // Real View
    scene.SetCamera(
            Pinhole(camTM*Vect(0, 1, 0), camTM*Vect(1, 0, 0), camTM*Vect(0, 0, 1), Point(0, 0.5f, -0.6f),
                    PI/3, 1.0, 1280, 720));

    scene.AddLightSource(PointLight(Point(0,0.2f, -0.2f), 4, WHITE));
    scene.AddLightSource(PointLight(Point(0,0.8f, 0.65f), 2, (RED + WHITE) / 2));

    TransformationMatrix dragonTM;
    dragonTM.SetYRotation(PI/2.0f);

    Mesh dragon = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/dragonFlat.obj", 0.35f, Vect(0,0.4f, 0.3f), dragonTM);
    dragon.SetMaterial(make_shared<Material>(Material(GREEN/2.0f, BLACK, 0.0f, GRAY, BLACK)));
    scene.AddShape(dragon);

    auto appleWhite(make_shared<Material>(Material(WHITE, BLACK, 0.0f, WHITE, BLACK)));

    Plane floor(Point(0,-0.2f,0), Vect(0,1,0));
    floor.SetMaterial(appleWhite);
    scene.AddShape(floor);
    Plane ceiling(Point(0,1,0), Vect(0,1,0));
    ceiling.SetMaterial(appleWhite);

    Plane rightWall(Point(1,0,0), Vect(-1,0,0));
    rightWall.SetMaterial(appleWhite);
    scene.AddShape(rightWall);

    Plane leftWall(Point(-1,0,0), Vect(1,0,0));
    leftWall.SetMaterial(appleWhite);
    scene.AddShape(leftWall);

    Plane backWall(Point(0,0,1), Vect(0,0,-1));
    backWall.SetMaterial(appleWhite);
    scene.AddShape(backWall);

    Plane frontWall(Point(0,0,-1), Vect(0,0,1));
    frontWall.SetMaterial(appleWhite);
    scene.AddShape(frontWall);

    auto image = scene.RenderMultiThread(4);
    image->Save("dragon.ppm");
}

TEST(Weird, Menger)
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/10);
    camTM.SetYRotation(PI/10);

    // Real View
    scene.SetCamera(
            Pinhole(camTM*Vect(0, 1, 0), camTM*Vect(1, 0, 0), camTM*Vect(0, 0, 1), Point(-0.3f, 0.25f, -0.6f),
                    PI/4, 1.0, 1000, 1000));

    scene.AddLightSource(PointLight(Point(-0.3f,0.8f, -0.6f), 4, WHITE));

    auto material = make_shared<Material>(Material(YELLOW, BLACK, 0.0f, BLACK, BLACK));
    MengerSponge menger(0.15f, 1, material, Vect(0,0,0.25f));

    scene.AddShape(menger);

    auto image = scene.RenderMultiThread(THREADS);
    image->Save("menger.ppm");
}