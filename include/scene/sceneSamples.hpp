/** ---------------------------------------------------------------------------
 ** sceneSamples.hpp
 ** Contains functions that return hardcoded scenes.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/
#ifndef SCENE_SAMPLES
#define SCENE_SAMPLES

#include <pinhole.hpp>
#include <scene.hpp>
#include <sphere.hpp>
#include <pointLight.hpp>
#include <plane.hpp>
#include <triangle.hpp>
#include <sceneSamples.hpp>
#include <transformationMatrix.hpp>
#include <mesh.hpp>
#include <geometry/rectangle.hpp>
#include <geometry/box.hpp>
#include <materials/checkerBoard.hpp>
#include <materials/crossHatchModifier.hpp>
#include <geometry/compositeShape.hpp>
#include <geometry/mengerSponge.hpp>
#include <ratio>
#include <lighting/simpleAreaLight.hpp>
#include <materials/simpleTexture.hpp>

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
    yellowSphere.SetMaterial(make_shared<Material>(Material(YELLOW, GRAY/4, 1.5f, BLACK, BLACK)));
    purpleSphere.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, PURPLE, BLACK)));
    cornellBox.AddShape(yellowSphere);
    cornellBox.AddShape(purpleSphere);
    // A point light illuminates the scene.
    cornellBox.AddLightSource(PointLight(Point(0, 0.6f, -0.1f), 0.5f, WHITE));

    return cornellBox;
}

Scene CornellBoxWithMedia()
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

    ParticipatingMedia fogBox(make_shared<Box>(Box(Rectangle(Vect(0,1,0), Point(0.2f,0.1f, 0.3f), Point(-0.2f,0.1f, -0.3f)), 0.3f)), 3, 0.5f);
    cornellBox.AddParticipatingMedia(fogBox);
    // Two spheres inside the box.
    Sphere yellowSphere(Sphere(Point(-0.45f, 0.1, 0.4f), 0.25f));
    Sphere purpleSphere(Sphere(Point(0.45f, 0.1, 0.4f), 0.25f));
    yellowSphere.SetMaterial(make_shared<Material>(Material(YELLOW, GRAY/4, 1.5f, BLACK, BLACK)));
    purpleSphere.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, PURPLE + GREEN/10, BLACK)));
    cornellBox.AddShape(yellowSphere);
    cornellBox.AddShape(purpleSphere);
    // A point light illuminates the scene.
    cornellBox.AddLightSource(PointLight(Point(0, 0.6f, -0.1f), 0.5f, WHITE));

    return cornellBox;
}

Scene PhongSphereSamples()
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.9f,-0.7f), PI/3, 1.0, 700, 500));

    scene.AddLightSource(PointLight(Point(-0.6f, -0.5f, -0.2f), 1.5, WHITE));
    scene.AddLightSource(PointLight(Point(0.6f, -0.5f, -0.2f), 1.5, WHITE));

    Sphere lambertian(Point(-0.35f, -0.85f, 0), 0.075f);
    lambertian.SetMaterial(LAMBERTIAN);
    scene.AddShape(lambertian);

    Sphere lobe(Point(-0.10f, -0.85f, 0), 0.075f);
    lobe.SetMaterial(SPECKLED_LAMBERTIAN);
    scene.AddShape(lobe);

    Sphere mirror(Point(0.10, -0.85f, 0), 0.075f);
    mirror.SetMaterial(MIRROR);
    scene.AddShape(mirror);

    Sphere glass(Point(0.35, -0.85f, 0), 0.075f);
    glass.SetMaterial(GLASS);
    glass.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(glass);

    CheckerBoard wallPattern(0.149f, BLACK, WHITE);
    Plane floor(Point(0, -1.0f, 0), Vect(0, 1, 0));
    floor.SetMaterial(wallPattern);
    scene.AddShape(floor);

    Plane rightWall(Point(1, 0, 0), Vect(-1, 0, 0));
    rightWall.SetMaterial(wallPattern);
    scene.AddShape(rightWall);

    Plane leftWall(Point(-1, 0, 0), Vect(1, 0, 0));
    leftWall.SetMaterial(wallPattern);
    scene.AddShape(leftWall);

    Plane backWall(Point(0, 0, 0.5), Vect(0, 0, -1));
    backWall.SetMaterial(wallPattern);
    scene.AddShape(backWall);

    return scene;
}

template <int lobeSize>
Scene SpecularLobes()
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.85f,-0.2f), PI/3, 1.0, 700, 500));

    scene.AddLightSource(PointLight(Point(0.3f, -0.3f, -0.2f), 1, WHITE));

    Sphere lobe(Point(0.0f, -0.85f, 0), 0.075f);
    lobe.SetMaterial(Material(WHITE, GRAY/4, lobeSize, BLACK, BLACK));
    scene.AddShape(lobe);

    CheckerBoard wallPattern(0.149f, BLACK, WHITE);
    Plane backWall(Point(0, 0, 0.5), Vect(0, 0, -1));
    backWall.SetEmittedLight(WHITE, 0.2f);
    scene.AddShape(backWall);

    Plane frontWall(Point(0, 0, -0.5f), Vect(0, 0, -1));
    frontWall.SetEmittedLight(WHITE, 0.2f);
    scene.AddShape(frontWall);

    return scene;
}

Scene RefractionPlaneSphere()
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.5f,-1), PI/3, 1.0, 500, 500));

    scene.AddLightSource(PointLight(Point(0.2f, 0.5f, -1), 5, WHITE));

    Sphere sphere(Point(0, -0.75f, 0), 0.25f);
    sphere.SetMaterial(Material(BLACK, BLACK, 0.0f, GRAY/10, WHITE));
    sphere.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(sphere);

    Plane floor(Point(0, -1.0f, 0), Vect(0, 1, 0));
    floor.SetMaterial(CheckerBoard(0.149f, RED, BLUE));
    scene.AddShape(floor);

    Plane rightWall(Point(1, 0, 0), Vect(-1, 0, 0));
    rightWall.SetMaterial(CheckerBoard(0.149f, GREEN, BLUE));
    scene.AddShape(rightWall);

    Plane leftWall(Point(-1, 0, 0), Vect(1, 0, 0));
    leftWall.SetMaterial(CheckerBoard(0.149f, RED, GREEN));
    scene.AddShape(leftWall);

    Plane backWall(Point(0, 0, 1), Vect(0, 0, -1));
    backWall.SetMaterial(CheckerBoard(0.149f, PURPLE, YELLOW));
    scene.AddShape(backWall);

    return scene;
}

Scene IndirectLighting()
{
    Scene scene;
    TransformationMatrix camTm;
    camTm.SetXRotation(PI/12);

    scene.SetCamera(Pinhole(camTm*Vect(0,1,0), camTm*Vect(1,0,0), camTm*Vect(0,0,1), Point(0, 0.05f, -0.6f), PI/4, 1.0f, 1280, 720));

    scene.AddLightSource(PointLight(Point(0,0.75,0.1f), 1.5, WHITE));
    scene.AddLightSource(PointLight(Point(0,0.4,-0.4f), 1.5, WHITE));

    Plane floor(Point(0,-0.5f, 0), Vect(0,1,0));
    scene.AddShape(floor);

    Plane backWall(Point(0,0,1), Vect(0,0,-1));
    scene.AddShape(backWall);

    Plane leftWall(Point(-0.5f,0, 0), Vect(1,0,0));
    scene.AddShape(leftWall);

    Plane rightWall(Point(0.5f,0, 0), Vect(-1,0,0));
    scene.AddShape(rightWall);

    Box blueBox(Rectangle(Vect(0,1,0), Point(-0.4f, -0.5f, 0.4), Point(-0.2f, -0.5f, 0.6f)), 0.5f);
    blueBox.SetMaterial(Material(BLUE, BLACK, 0.0f, BLACK, BLACK));
    scene.AddShape(blueBox);

    Box redBox(Rectangle(Vect(0,1,0), Point(0.2f, -0.5f, 0.4), Point(0.4f, -0.5f, 0.6f)), 0.5f);
    redBox.SetMaterial(Material(RED, BLACK, 0.0f, BLACK, BLACK));
    scene.AddShape(redBox);

    Box greenBox(Rectangle(Vect(0,1,0), Point(-0.1f, -0.5f, 0.8), Point(0.1f, -0.5f, 1.0f)), 0.5f);
    greenBox.SetMaterial(Material(GREEN, BLACK, 0.0f, BLACK, BLACK));
    scene.AddShape(greenBox);

    return scene;
}

Scene Teapot()
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/10);

    scene.SetCamera(
            Pinhole(camTM*Vect(0, 1, 0), camTM*Vect(1, 0, 0), camTM*Vect(0, 0, 1), Point(0, 0.5f, -0.4f),
            PI/3, 1.0, 1280, 720));

    scene.AddLightSource(PointLight(Point(0,0.65f, -0.45f), 0.5f, WHITE));

    Mesh teapot = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/utah_teapot.obj", 0.35f, Vect(0,0.2f, 0.3f));
    teapot.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, WHITE)));
    teapot.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(teapot);

    Plane floor(Point(0,-0.2f,0), Vect(0,1,0));
    scene.AddShape(floor);

    Plane ceiling(Point(0,1,0), Vect(0,1,0));
    scene.AddShape(ceiling);

    Plane rightWall(Point(1,0,0), Vect(-1,0,0));
    scene.AddShape(rightWall);

    Plane leftWall(Point(-1,0,0), Vect(1,0,0));
    scene.AddShape(leftWall);

    Plane backWall(Point(0,0,1), Vect(0,0,-1));
    scene.AddShape(backWall);

    Plane frontWall(Point(0,0,-1), Vect(0,0,1));
    scene.AddShape(frontWall);

    return scene;
}

Scene FacingMirrors()
{
    Scene scene;
    TransformationMatrix tm;
    tm.SetYRotation(PI/8);
    scene.SetCamera(Pinhole(tm*Vect(0,1,0), tm*Vect(1,0,0), tm*Vect(0,0,1), Point (-0.3f,0.2,-0.5f), PI/3, 1.0, 1000, 1000));
    scene.AddLightSource(PointLight(Point(0,0.9,0), 1.0f, WHITE));

    Plane wall(Point(0,0,1.001), Vect(0, 0, 1));
    wall.SetMaterial(Material(Color(0.8, 0.7, 0.45), BLACK, 0.0f, BLACK, BLACK));
    Rectangle mirror(Vect(0, 0, 1), Point(-0.5f, 0.0f, 1), Point(0.5f, 0.5f, 1));
    mirror.SetMaterial(MIRROR);

    Plane hiddenMirror(Point(0,0,-0.7f), Vect(0,0,1));
    hiddenMirror.SetMaterial(MIRROR);
    Plane floor(Point(0,-5,0), Vect(0,1,0));
    Sphere floatingSphere(Point(0,0,0.3), 0.15);
    floatingSphere.SetMaterial(Material(RED, BLACK, 0.0f, BLACK, BLACK));
    scene.AddShape(wall);
    scene.AddShape(mirror);
    scene.AddShape(hiddenMirror);
    scene.AddShape(floatingSphere);
    scene.AddShape(floor);
    
    return scene;
}

Scene ManySpheres()
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
    
    return scene;
}

Scene GlassSpheres()
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
    
    return scene;
}

Scene SphereCeption()
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
    
    return scene;
}

template <int refractiveType>
Scene RefractiveSphereTest()
{
    float refractiveIndex;

    switch(refractiveType)
    {
    case 1:
        refractiveIndex = GLASS_RI;
        break;
    case 2:
        refractiveIndex = WATER_RI;
        break;
    case 3:
        refractiveIndex = DIAMOND_RI;
        break;
    case 4:
        refractiveIndex = QUARTZ_RI;
        break;
    default:
        refractiveIndex = GLASS_RI;
    }

    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.5f,-0.625f), PI/3, 1.0, 500, 500));
    scene.AddLightSource(PointLight(Point(0,-0.1f,0.0f), 5, WHITE));

    auto redMat = make_shared<Material>(Material(RED, BLACK, 0.0f, BLACK, BLACK));
    auto greenMat = make_shared<Material>(Material(GREEN, BLACK, 0.0f, BLACK, BLACK));
    auto blueMat = make_shared<Material>(Material(BLUE, BLACK, 0.0f, BLACK, BLACK));

    Plane ground(Plane(Point(0,-1,0), Vect(0,1,0)));
    ground.SetMaterial(redMat);
    scene.AddShape(ground);

    Plane ceiling(Plane(Point(0,0.2f,0), Vect(0,-1,0)));
    ceiling.SetMaterial(redMat);
    scene.AddShape(ceiling);

    Plane backWall(Plane(Point(0,0,1), Vect(0,0,-1)));
    backWall.SetMaterial(greenMat);
    scene.AddShape(backWall);


    Sphere transparentSphere(Point(0,-0.5f,0), 0.1f);
    transparentSphere.SetMaterial(Material(BLACK, BLACK, 0.0f, BLACK, WHITE));
    transparentSphere.SetRefractiveIndex(refractiveIndex);
    scene.AddShape(transparentSphere);

    Sphere blueBall(Point(0,-0.5f,0.4), 0.05f);
    blueBall.SetMaterial(blueMat);
    scene.AddShape(blueBall);

    return scene;
}

Scene Experimental()
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,-0.5f,-0.73f), PI/3, 1.0, 250, 250));
    scene.AddLightSource(PointLight(Point(-1, 1, 0), 3, WHITE));
    scene.AddLightSource(PointLight(Point(1, 1, 0), 3, WHITE));

    Plane board(Plane(Point(0,-1.5f,0), Vect(0,1,0)));
    scene.AddShape(board);

    Plane wall(Point(0,0,1.5f), Vect(0,0,-1));
    scene.AddShape(wall);

    Sphere reflectiveModified(Point(0.0,-0.5f,0.3f), 0.25f);
    reflectiveModified.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, WHITE)));
    reflectiveModified.SetNormalModifier(make_shared<CrossHatchModifier>(CrossHatchModifier(100,100,100)));
    scene.AddShape(reflectiveModified);

    Sphere redStandard(Point(-0.3f,-0.5f,0.9f), 0.25f);
    redStandard.SetMaterial(make_shared<Material>(Material(RED, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(redStandard);

    Sphere greenStandard(Point(0.3f,-0.5f,0.9f), 0.25f);
    greenStandard.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(greenStandard);

    return scene;
}

Scene Room()
{
    Scene scene;

    // Real View
    scene.SetCamera(
            Pinhole(Vect(0, 1, 0), Vect(1, 0, 0), Vect(0, 0, 1), Point(0, 0.1f, -1.2f),
                    PI/3, 1.0, 750, 500));

    //////////////////////////////
    //// Making the room /////////
    //////////////////////////////

    Rectangle floor(Vect(0,1,0), Point(-1, -0.55f, -1), Point(1, -0.55f, 1));
    SimpleTexture woodText(string(PROJECT_DIR) + "/resources/wood.ppm", Y, 0.001f);
    floor.SetMaterial(make_shared<Material>(Material(Color(0.1f, 0.1f, 0.1f), GRAY, 1.5f, GRAY/3, BLACK)));
    floor.SetMaterial(woodText);
    scene.AddShape(floor);

    Rectangle ceiling(Vect(0,-1,0), Point(-1, 1.05f, -1), Point(1, 1.05f, 1));
    scene.AddShape(ceiling);

    SimpleTexture wallTextZ(string(PROJECT_DIR) + "/resources/plaster.ppm", Z, 0.001f);
    SimpleTexture wallTextX(string(PROJECT_DIR) + "/resources/plaster.ppm", X, 0.001f);
    Rectangle leftWallBot(Vect(1,0,0), Point(-1, -0.55f, -1), Point(-1, 0, 1));
    Rectangle leftWallTop(Vect(1,0,0), Point(-1, 0.75f, -1), Point(-1, 1.05f, 1));
    Rectangle leftWallLeft(Vect(1,0,0), Point(-1, 0, -1), Point(-1, 0.75f, 0.05f));
    Rectangle leftWallRight(Vect(1,0,0), Point(-1, 0, 0.85f), Point(-1, 0.75f, 1));
    leftWallBot.SetMaterial(wallTextX);
    leftWallTop.SetMaterial(wallTextX);
    leftWallLeft.SetMaterial(wallTextX);
    leftWallRight.SetMaterial(wallTextX);

    scene.AddShape(leftWallBot);
    scene.AddShape(leftWallTop);
    scene.AddShape(leftWallLeft);
    scene.AddShape(leftWallRight);

    Rectangle rightWall(Vect(-1,0,0), Point(1, -0.55f, -1), Point(1, 1.05f, 1));
    rightWall.SetMaterial(wallTextX);
    scene.AddShape(rightWall);

    Rectangle picture(Vect(0,0,-1), Point(-0.6f, 0.2f, 0.98f), Point(-0.2f, 0.79603f, 0.98f));
    float pixelSize = 0.00145f;
    SimpleTexture gioconda(string(PROJECT_DIR) + "/resources/gioconda_inv.ppm", Z, pixelSize, Vect(pixelSize * 130,  pixelSize * 271,0.0f));
    picture.SetMaterial(gioconda);
    scene.AddShape(picture);

    Rectangle backWall(Vect(0,0,-1), Point(-1, -0.55f, 1), Point(1, 1.05f, 1));
    backWall.SetMaterial(wallTextZ);
    scene.AddShape(backWall);

    Rectangle hiddenWall(Vect(0,0,1), Point(-1, -0.55f, -1.2f), Point(1, 1.05f, -1.2f));
    scene.AddShape(hiddenWall);

    //////////////////////////////
    //// Light           /////////
    //////////////////////////////

    // Sun.
    scene.AddLightSource(PointLight(Point(-1.5f, 0.9f, 0.45f), 6.0f, (RED + RED + YELLOW) / 3));
    // Fake sky
    scene.AddLightSource(SimpleAreaLight(Point(-0.99f, 0.1f, 0.15f), Vect(0.0f, 0.55f, 0.0f), 5, Vect(0.0f, 0.0f, 0.6f), 5, 0.3f, SKY_BLUE));

    //////////////////////////////
    //// Making a table //////////
    //////////////////////////////

    // To 'easily' build the table in the origin of coordinates and then move it
    Vect tableShift(-0.5f, 0, 0.5f);
    float pos = 0.2f;
    float legDim = 0.025f;
    float legDepth = 0.35f;
    float legBaseY = -0.55f;

    shared_ptr<Material> woodOrSomething = make_shared<Material>(Material(Color(0.6f, 0.3f, 0.0f), BLACK, 0.0f, BLACK, BLACK));

    Box leg1(Rectangle(Vect(0,1,0), Point(-pos, legBaseY, -pos) + tableShift, Point(-pos+legDim, legBaseY, -pos+legDim) + tableShift), legDepth);
    Box leg2(Rectangle(Vect(0,1,0), Point(pos, legBaseY, -pos) + tableShift, Point(pos+legDim, legBaseY, -pos+legDim) + tableShift), legDepth);

    float zShift = 0.5f;

    Box leg3(Rectangle(Vect(0,1,0), Point(-pos, legBaseY, pos - 0.75f) + tableShift, Point(-pos+legDim, legBaseY, pos - 0.75f + legDim) + tableShift), legDepth);
    Box leg4(Rectangle(Vect(0,1,0), Point( pos, legBaseY, pos - 0.75f) + tableShift, Point( pos+legDim, legBaseY, pos - 0.75f + legDim) + tableShift), legDepth);

    float extraTopLength = 0.05f;
    float tableTopDepth = 0.04f;
    float offsetWithLegs = 0.03f;

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
            Point(-squareSize * 4, legBaseY + legDepth + tableTopDepth - 0.02f, -squareSize * 4 - boardZOffset) + tableShift,
            Point( squareSize * 4, legBaseY + legDepth + tableTopDepth - 0.02f,  squareSize * 4 - boardZOffset) + tableShift);
    board.SetMaterial(pattern);
    wholeTable.AddShape(board);

    { // Add Meshes on top of the table and include them in the bounding box for the composite shape

        //////////////////////////////
        //// FATHER!!            /////
        //////////////////////////////
        TransformationMatrix vaderTM;
        vaderTM.SetYRotation(PI);
        Mesh vader = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/darth_head.obj", 0.1f,
                Vect(-0.45f, legDepth+tableTopDepth-0.45f, 0.35f), vaderTM);
        vader.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, GRAY/2, BLACK)));
        wholeTable.AddShape(vader);

        /// vs...

        //////////////////////////////
        //// Buddha!?            /////
        //////////////////////////////

        Mesh buddha = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/buddha.obj", 0.1f,
                Vect(-0.45f, legDepth+tableTopDepth-0.45f, -0.1f));
        buddha.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, BLACK, BLACK)));
        wholeTable.AddShape(buddha);
    }

    wholeTable.SetBoundingShape(Box(Rectangle(Vect(0,1,0),
            Point(-pos - extraTopLength, -0.5f, -pos - extraTopLength - zShift) + tableShift,
            Point(pos + extraTopLength, -0.5f,  pos + extraTopLength) + tableShift), legDepth + tableTopDepth + 0.25f));
    scene.AddShape(wholeTable);

    //////////////////////////////
    //// WINDOW              /////
    //////////////////////////////

    Box windowFrameTop(Rectangle(Vect(1,0,0), Point(-1, 0.7f, 0.85f), Point(-1, 0.75f, 0.05f)), 0.01f);
    windowFrameTop.SetMaterial(make_shared<Material>(Material(GRAY/4, GRAY/4, 1.5f, GRAY/4, BLACK)));
    Box windowFrameBottom(Rectangle(Vect(1,0,0), Point(-1, 0, 0.85f), Point(-1, 0.05f, 0.05f)), 0.01f);
    windowFrameBottom.SetMaterial(make_shared<Material>(Material(GRAY/4, GRAY/4, 1.5f, GRAY/4, BLACK)));
    Box windowFrameLeft(Rectangle(Vect(1,0,0), Point(-1, 0, 0.85f), Point(-1, 0.75f, 0.8f)), 0.01f);
    windowFrameLeft.SetMaterial(make_shared<Material>(Material(GRAY/4, GRAY/4, 1.5f, GRAY/4, BLACK)));
    Box windowFrameRight(Rectangle(Vect(1,0,0), Point(-1, 0, 0.1f), Point(-1, 0.75f, 0.05f)), 0.01f);
    windowFrameRight.SetMaterial(make_shared<Material>(Material(GRAY/4, GRAY/4, 1.5f, GRAY/4, BLACK)));

    scene.AddShape(windowFrameTop);
    scene.AddShape(windowFrameBottom);
    scene.AddShape(windowFrameLeft);
    scene.AddShape(windowFrameRight);

    //////////////////////////////
    //// RANDOM CLAIRVOYANCE /////
    //////////////////////////////
    Point ballCenter(0.1f, 0.05f, 0.3f);
    Sphere ball(ballCenter, 0.2f);
    ball.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, WHITE)));
    ball.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(ball);

    ParticipatingMedia fog(make_shared<Sphere>(Sphere(ballCenter, 0.17f)), 3,0.5f);
    scene.AddParticipatingMedia(fog);

    //////////////////////////////
    //// ENVIRONMENT         /////
    //////////////////////////////

    // The environment sphere has a transparent material to avoid storing photons in it making the render slower.
    Sphere environment(Point(0, 0, 0), 20);
    environment.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, Color(0.1f, 0.1f, 0.1f))));
    environment.SetEmittedLight(SKY_BLUE, 1);
    scene.AddShape(environment);

    return scene;
}

Scene Dragon()
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/10);
    // Real View
    scene.SetCamera(
            Pinhole(camTM*Vect(0, 1, 0), camTM*Vect(1, 0, 0), camTM*Vect(0, 0, 1), Point(0, 0.5f, -0.6f),
                    PI/3, 1.0, 1280, 720));

    scene.AddLightSource(PointLight(Point(0,0.2f, -0.2f), 1, WHITE));
    scene.AddLightSource(PointLight(Point(0,0.8f, 0.65f), 0.5, (RED + WHITE) / 2));

    TransformationMatrix dragonTM;
    dragonTM.SetYRotation(PI/2.0f);

    Mesh dragon = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/dragonFlat.obj", 0.35f, Vect(0,0.4f, 0.3f), dragonTM);
    dragon.SetMaterial(make_shared<Material>(Material(GREEN/2.0f, BLACK, 0.0f, GRAY, BLACK)));
    scene.AddShape(dragon);


    Plane floor(Point(0,-0.2f,0), Vect(0,1,0));
    scene.AddShape(floor);

    Plane ceiling(Point(0,1,0), Vect(0,1,0));
    scene.AddShape(ceiling);

    Plane rightWall(Point(1,0,0), Vect(-1,0,0));
    scene.AddShape(rightWall);

    Plane leftWall(Point(-1,0,0), Vect(1,0,0));
    scene.AddShape(leftWall);

    Plane backWall(Point(0,0,1), Vect(0,0,-1));
    scene.AddShape(backWall);

    Plane frontWall(Point(0,0,-1), Vect(0,0,1));
    scene.AddShape(frontWall);

    return scene;
}

template <int recursion>
Scene Menger()
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/6);
    camTM.SetYRotation(PI/6);

    // Real View
    scene.SetCamera(
            Pinhole(camTM*Vect(0, 1, 0), camTM*Vect(1, 0, 0), camTM*Vect(0, 0, 1), Point(-3.9f, 3.5f, -7.0f),
                    PI/4, 1.0, 2000, 2000));

    scene.AddLightSource(PointLight(Point(-3.0f,8.0f, -6.0f), 1000, WHITE));

    auto material = make_shared<Material>(Material(YELLOW, BLACK, 0.0f, BLACK, BLACK));
    MengerSponge menger(1.5f, recursion, material, Vect(0,0,0.0f));

    scene.AddShape(menger);

    
    return scene;
}

Scene ChessTexture()
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0,0.3,-0.65f), PI/3, 1.0, 2000, 2000));

    scene.AddLightSource(PointLight(Point(0,0.55f,0), 1, WHITE));

    Box container(Rectangle(Vect(0,1,0), Point(0.5f, 0.001f, -0.75f), Point(-0.5f, 0.001f, 0.75f)), 1);
    container.SetMaterial(CheckerBoard(0.13, WHITE, BLACK));
    scene.AddShape(container);

    Sphere sphere(Point(0.0f, 0.2f, 0.2f), 0.1f);
    sphere.SetMaterial(CheckerBoard(0.04999, BLUE, YELLOW));
    scene.AddShape(sphere);
    return scene;
}

/**
 * Returns a CompositeShape made of 5 boxes forming an open cabinet with the given positions, size and material.
 */
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

Scene DirectVsIndirect()
{
    Scene scene;
    TransformationMatrix camTm;
    camTm.SetXRotation(PI/12);

    scene.SetCamera(Pinhole(camTm*Vect(0,1,0), camTm*Vect(1,0,0), camTm*Vect(0,0,1), Point(0, 0.05f, -0.6f), PI/4, 1.0f, 1280, 720));

    scene.AddLightSource(PointLight(Point(100.0f,100.0f,0.6f), 40000, WHITE));

    Plane floor(Point(0,-0.5f, 0), Vect(0,1,0));
    scene.AddShape(floor);

    Rectangle leftWall(Rectangle(Vect(1,0,0), Point(-0.6f, -0.5f, 0.1f), Point(-0.6f, 0.01f, 1.1f)));
    scene.AddShape(leftWall);

    Box midWall(Rectangle(Vect(1,0,0), Point(-0.0125f, -0.5f, 0.2), Point(-0.0125f, 0.0f, 1.0f)), 0.025f);
    midWall.SetMaterial(Material((YELLOW+RED)/2, GRAY/4, 10.0f, BLACK, BLACK));
    scene.AddShape(midWall);

    TransformationMatrix dragonTM;
    dragonTM.SetYRotation(PI/2.0f);

    Mesh dragonLeft = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/dragonFlat.obj", 0.1f, Vect(-0.15f,-0.4f, 0.35f), dragonTM);
    dragonLeft.SetMaterial(make_shared<Material>(Material(GREEN, BLACK, 0.0f, BLACK, BLACK)));

    dragonTM.SetYRotation(-PI/2.0f);
    Mesh dragonRight = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/dragonFlat.obj", 0.1f, Vect(0.15,-0.4f, 0.35f), dragonTM);
    dragonRight.SetMaterial(make_shared<Material>(Material(BLUE, BLACK, 0.0f, BLACK, BLACK)));

    scene.AddShape(dragonLeft);
    scene.AddShape(dragonRight);
    return scene;
}

Scene Caustic()
{
    Scene causticBox;
    // A pinhole camera with default configuration.
    causticBox.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1),
            Point (0,0.25f,-1.7f), PI/4, 1.0, 1920, 1080));

    Plane leftWall(Plane(Point(-1, 0, 0), Vect(1, 0, 0)));
    leftWall.SetMaterial(make_shared<Material>(RED, BLACK, 0.0f, BLACK, BLACK));
    causticBox.AddShape(leftWall);
    Plane rightWall(Plane(Point(1, 0, 0), Vect(-1, 0, 0)));
    rightWall.SetMaterial(make_shared<Material>(GREEN, BLACK, 0.0f, BLACK, BLACK));
    causticBox.AddShape(rightWall);

    causticBox.AddShape(Plane(Point(0, 1, 0), Vect(0, -1, 0))); // Roof.
    causticBox.AddShape(Plane(Point(0, -0.25f, 0), Vect(0, 1, 0))); // Floor.
    causticBox.AddShape(Plane(Point(0, 0, 1), Vect(0, 0, -1))); // Back wall

    // Two spheres inside the box.
    Sphere transparent(Sphere(Point(-0.45f, 0.1, 0.4f), 0.25f));
    Sphere purpleSphere(Sphere(Point(0.45f, 0.1, 0.4f), 0.25f));
    transparent.SetRefractiveIndex(GLASS_RI);
    purpleSphere.SetRefractiveIndex(GLASS_RI);
    transparent.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, WHITE)));
    purpleSphere.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, PURPLE)));
    causticBox.AddShape(transparent);
    causticBox.AddShape(purpleSphere);
    // A point light illuminates the scene.
    causticBox.AddLightSource(PointLight(Point(0, 0.6f, -0.1f), 2.0f, WHITE));

    return causticBox;
}

template <int camPos>
Scene BasicMediaScene()
{
    Scene scene;
    switch (camPos)
    {
    case 0:
        scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0, 0.0f,-0.7f), PI/3, 1.0, 700, 500));
        break;
    case 1:
    {
        TransformationMatrix camTM;
        camTM.SetYRotation(PI/6);
        scene.SetCamera(Pinhole(camTM * Vect(0,0,-1), camTM * Vect(0,1,0), camTM * Vect(-1,0,0), Point (0.6f, 0.0f,0.0f), PI/3, 1.0, 700, 500));
        break;
    }
    default:
        throw invalid_argument("Position not supported.\n");
    }

    scene.AddLightSource(PointLight(Point(0.0f, 0.0f, -0.4f), 0.5f, WHITE));

    ParticipatingMedia fog(make_shared<Sphere>(Sphere(Point(0,0,0.1f), 0.3f)), 3, 0.5f);
    scene.AddParticipatingMedia(fog);

    CheckerBoard wallPattern(0.149f, GREEN, BLUE);
    Plane backWall(Point(0, 0, 0.5), Vect(0, 0, -1));
    backWall.SetMaterial(wallPattern);
    scene.AddShape(backWall);

    return scene;
}

Scene MediaCaustic()
{
    Scene scene;
    scene.SetCamera(Pinhole(Vect(0,1,0), Vect(1,0,0), Vect(0,0,1), Point (0.0f, 0.4f,-2.0f), PI/6, 1.0, 700, 500));

    scene.AddLightSource(PointLight(Point(0.25f, 0.6f, 0.2f), 0.5f, WHITE));

    Sphere glassSphere(Point(0.0f, 0.35f, 0.2f), 0.2f);
    glassSphere.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, Color(0.95f, 0.95f, 0.95f))));
    glassSphere.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(glassSphere);
    //scene.mBeamRadius = 0.02f;

    //ParticipatingMedia fog(make_shared<Sphere>(Sphere(Point(0,0,0.1f), 2.0f)), 0.55f, 0.5f);
    ParticipatingMedia fog(make_shared<Box>(Box(Rectangle(Vect(0,1,0), Point(-0.4f, -0.4f,0.2f), Point(0.4f, -0.4f, 0.5f)), 1.3f)), 2.55f, 0.5f);
    scene.AddParticipatingMedia(fog);

    return scene;
}

Scene RatInGlass()
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/4.5f);
    camTM.SetYRotation(PI/7);
    scene.SetCamera(Pinhole(camTM*Vect(0,1,0), camTM*Vect(1,0,0), camTM*Vect(0,0,1), Point (-0.7f, 1.2f,-1.45f), PI/6, 1.0, 700, 700));

    scene.AddLightSource(PointLight(Point(0.25f, 0.7f, -0.3f), 1.0f, WHITE));

    Box glassBox(Rectangle(Vect(0,1,0), Point(-0.2f, -0.05f, -0.2f), Point(0.2f, -0.05f, 0.2f)), 0.4f);
    glassBox.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, WHITE)));
    glassBox.SetRefractiveIndex(1.1f);
    scene.AddShape(glassBox);

    TransformationMatrix ratTM;
    ratTM.SetYRotation(PI/2);
    Mesh electricRat = Mesh::LoadObjFile(string(PROJECT_DIR) + "/resources/electric_rat.obj", 0.15f, Vect(0,0.15f,0),ratTM);
    electricRat.SetMaterial(make_shared<Material>(Material(YELLOW, BLACK, 0.0f, BLACK, BLACK)));
    scene.AddShape(electricRat);

    //floor
    scene.AddShape(Plane(Point(0,0.0f,0), Vect(0,1,0)));
    //back wall
    scene.AddShape(Plane(Point(0,0,0.8f), Vect(0,0,-1)));

    return scene;
}

Scene DetailLoss()
{
    Scene scene;
    TransformationMatrix camTM;
    camTM.SetXRotation(PI/3.6f);
    scene.SetCamera(Pinhole(camTM*Vect(0,1,0), camTM*Vect(1,0,0), camTM*Vect(0,0,1), Point (-0.3f, 0.8f,-0.5f), PI/6, 1.0, 500, 500));

    scene.AddLightSource(PointLight(Point(-0.3f, 0.6f, 0.5f), 1.0f, WHITE));

    Rectangle redGlass(Vect(0,0,-1), Point(-0.5f, 0.0f, 0.3f), Point(-0.1f, 0.2f, 0.3f));
    redGlass.SetMaterial(make_shared<Material>(Material(BLACK, BLACK, 0.0f, BLACK, RED)));
    redGlass.SetRefractiveIndex(GLASS_RI);
    scene.AddShape(redGlass);

    SimpleTexture text(string(PROJECT_DIR) + "/resources/text.ppm", Y, 0.0005f);
    Plane floor(Point(0,-0.01f,0), Vect(0,1,0));
    floor.SetMaterial(text);
    scene.AddShape(floor);

    return scene;
}

#endif // SCENE_SAMPLES