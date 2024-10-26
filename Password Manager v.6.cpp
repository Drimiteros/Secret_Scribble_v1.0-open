#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "Renderer.h"
#include "DiskInfo.h"

using namespace std;
using namespace sf;

int main()
{
    //INITALIZE RENDERER
    Renderer renderer;
    renderer.mainLoop(); //RUN MAIN LOOP
}