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
#include <map>

using namespace std;

/**
 * Filled in runtime. Contains all available scene names and pointers to the functions
 * that return their corresponding scenes
 */
map<string, function<Scene(void)>> SCENE_NAMES;

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

void PrintHelp()
{
    // TODO: Check what the default indirect ray count will be.
    cout << "Usage: [OPTION]*\n"
            "If no options are specified, a default Cornell box with 64 indirect rays will be rendered and saved as cornell.ppm.\n"
            "Available options:\n"
            "\t-h : Print this helpful text.\n"
            "\t-res <WIDTHxHEIGHT> : Select a different resolution for the result image.\n"
            "\t--indirect_steps <NUMBER>: Choose the number of indirect lighting steps to render images faster. 0 to disable indirect lighting.\n"
            "\t--indirect_rays <NUMBER> : Sets the number of indirect rays that will be used to render the image.\n"
            "\t-s [SCENE_NAME] : Selects the scene to render.\n"
            "\n"
            "Available scenes:\n";
    for (const auto &scenePair: SCENE_NAMES)
        cout << '\t' << scenePair.first << '\n';
}

void InitializeSceneNames()
{
    SCENE_NAMES["cornell"] = &CornellBox;
    SCENE_NAMES["room"] = &Room;
    SCENE_NAMES["teapot"] = &Teapot;
    SCENE_NAMES["dragon"] = &Dragon;
    SCENE_NAMES["spheres"] = &ManySpheres;
    SCENE_NAMES["infinite_mirror"] = &FacingMirrors;
    SCENE_NAMES["glass_sphere"] = &RefractionPlaneSphere;
    SCENE_NAMES["water_sphere"] = &Chess;
    SCENE_NAMES["experimental"] = &Experimental;
    SCENE_NAMES["menger_1"] = &Menger<1>;
    SCENE_NAMES["menger_2"] = &Menger<2>;
    SCENE_NAMES["menger_3"] = &Menger<3>;
    SCENE_NAMES["menger_4"] = &Menger<4>;
    SCENE_NAMES["menger_5"] = &Menger<5>;
}

int main(int argc, char * argv[])
{
    InitializeSceneNames();
    int width = -1, height = -1;
    unsigned int indirectSteps = 1, indirectRays = 64;
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
                if (i + 1 < argnum)
                {
                    int tmp = stoi(arguments[i+1]);
                    threadCount = (unsigned int) tmp;
                    i++;
                }
            }catch(invalid_argument){/*Do nothing*/}
            continue;
        }

        if (arguments[i] == "-s")
        {
            if (i + 1 < argnum)
            {
                sceneName = arguments[i+1];
            }
            else
            {
                cerr << "You need to specify a scene. Use help to see all available scenes.\n";
                return 1;
            }
            i++;
            continue;
        }
    }

    Scene chosenScene;

    if (SCENE_NAMES.find(sceneName) != SCENE_NAMES.end())
    {
        chosenScene = SCENE_NAMES[sceneName]();
    }
    else
    {
        cerr << "The scene " << sceneName << " is invalid.\n";
        return 1;
    }

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