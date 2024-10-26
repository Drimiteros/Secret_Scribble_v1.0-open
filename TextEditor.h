#pragma once
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "CursorSprite.h"
#include "math.h"
#include <regex>

#pragma warning(disable : 4996)

#define textSize 999999

using namespace std;
using namespace sf;
using namespace ImGui::SFML;

class TextEditor
{
private:
    Texture buttonTexture;
    RectangleShape rec;
    RectangleShape selectRec;
    RectangleShape area;
    Sprite exitButton;
    Font font;

public:
    static char myText[textSize];
    float fontSize = 1.0;
    int size_a = 0;
    bool flag = 0;
    bool newLine = false;
    bool gen = false;
    bool editText = false;
    bool getIsTyping = false;
    Clock delayClock;
    Sprite buttonSprite;
    Text generatePassText;

    TextEditor();
    void setTypingStae(bool& isTyping);
    void getKeyboardInputIdicator(Event& eve, RenderWindow& window);
    void mainLogic(int state, bool& isTextFileOpen, ImGuiIO& io, RenderWindow& window, string& fileNameString, CursorSprite& mc, bool& isPasswordGenOpen, bool& isExportOpen);
    void popupWindow(int state, CursorSprite& mc, ImGuiIO& io, RenderWindow& window);
    void lineCounter(int& state, bool& isTextFileOpen, RenderWindow& window);
    void draw(RenderWindow& window, int& state, bool& isTextFileOpen);
};

