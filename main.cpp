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
#include <sstream>

using namespace std;

/**
 * Splits a string by the delimiter returning a vector of strings.
 * @param input input string to split by delim.
 * @param delim char by which s will be split.
 * @return vector of all the split strings in s.
 */
vector<string> split(const string &input, char delim) {
    vector<string> retVal;
    stringstream ss;
    ss.str(input);
    string item;
    while (getline(ss, item, delim)) {
        retVal.push_back(item);
    }
    return retVal;
}

const vector<string> SCENE_NAMES
        {
            "cornell",
            "room",
            "teapot",
            "dragon",
            "spheres",
            "infinite_mirror",
            "glass_sphere",
            "menger_1",
            "menger_3"
        };

Scene GetSceneWithName(const string &name)
{
    // Get the scene from sceneSamples
    return CornellBox();
}

void PrintHelp()
{
    // TODO: Check what the default indirect ray count will be.
    cout << "Usage: [OPTION]*\n"
            "If no options are specified, a default Cornell box with 256 indirect rays will be rendered and saved as cornell.ppm.\n"
            "Available options:\n"
            "\t-h : Print this helpful text.\n"
            "\t-res <WIDTHxHEIGHT> : Select a different resolution for the result image.\n"
            "\t--indirect_steps <NUMBER>: Choose the number of indirect lighting steps to render images faster. 0 to disable indirect lighting.\n"
            "\t--indirect_rays <NUMBER> : Sets the number of indirect rays that will be used to render the image.\n"
            "\t-s [SCENE_NAME] : Selects the scene to render.\n"
            "\n"
            "Available scenes:\n";
    for (const string &sceneName : SCENE_NAMES)
        cout << '\t' << sceneName << '\n';
}

int main(int argc, char * argv[])
{

    int width = -1, height = -1;
    unsigned int indirectSteps = 1, indirectRays = 256;
    unsigned int threadCount = thread::hardware_concurrency(); // Use all available threads by default.
    string sceneName = "cornell";

    // Put the arguments in a string vector to make more accessible.
    vector<string> arguments(argv + 1, argv + argc);
    unsigned long argnum = arguments.size();
    for (unsigned int i = 0; i < arguments.size(); ++i)
    {
        if (arguments[i] == "-h")
        {
            PrintHelp();
            return 0;
        }

        if (arguments[i] == "-res")
        {
            if (i + 1 >= argnum)
            {
                cerr << "You need to specify resolution as WIDTHxHEIGHT\n"; return 1;
            }
            auto widthHeight = split(arguments[i+1], 'x');
            // Knowingly not bothering to check if the arguments are ints.
            width = stoi(widthHeight[0]);
            height = stoi(widthHeight[1]);
            ++i;
            continue;
        }

        if (arguments[i] == "--indirect_steps")
        {
            indirectSteps = (unsigned int) stoi(arguments[i+1]);
            continue;
        }

        if (arguments[i] == "--indirect_rays")
        {
            indirectRays = (unsigned int) stoi(arguments[i+1]);
            i++;
            continue;
        }

        if (arguments[i] == "-j")
        {
            try
            {
                int tmp = stoi(arguments[i+1]);
                threadCount = (unsigned int) tmp;
                i++;
                continue;
            }catch(invalid_argument){/*Do nothing*/}
        }

        if (arguments[i] == "-s")
        {
            string scene = arguments[i+1];
            i++;
            continue;
        }
    }

    Scene chosenScene = GetSceneWithName(sceneName);

    if (width != -1 and height != -1)
    {
        chosenScene.SetImageDimensions((unsigned int)width, (unsigned int)height);
    }

    chosenScene.SetIndirectSteps(indirectSteps);
    chosenScene.SetIndirectRays(indirectRays);

    auto image = chosenScene.RenderMultiThread(threadCount);
    image->Save(sceneName + ".ppm");

    cout << "\nSaved image " << sceneName << ".ppm\n";
}