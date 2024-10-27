
/*
 * MIT Non-Commercial License
 *
 * Copyright (c) [2024] [Drimiteros]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software, including without limitation the rights to use, copy, modify,
 * and merge the Software, subject to the following conditions:
 *
 * 1. The Software shall be used for NON-COMMERCIAL purposes only.
 * 2. This notice and the following disclaimer shall be included in all copies or
 *    substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


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