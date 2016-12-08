/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <iostream>
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

using namespace std;

int main()
{
    // Render the dragon scene (placeholder)
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