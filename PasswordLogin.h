#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CursorSprite.h"
#include "FileManager.h"
#include "Secure.h"

using namespace sf;
using namespace std;

class PasswordLogin
{
private:
    Texture formTexture;
    Texture formTexture2;
    Texture menuTexture;
    Sprite formSprite;
    Sprite menuSprite;
    Font font;
    Text welcomeText;
    Text infoText;
    Text advanceText;

    string getPassword;
    int getState;
    bool isSelected = false;

public:
    Text passwordText;
    string hiddenPasswordString;
    string passwordString;

    PasswordLogin();
    void getStateInfo(int state);
    void getPasswordInfo(string password);
    void typeEvent(RenderWindow& window, Event& event);
    void logic(RenderWindow& window, CursorSprite& cursor, FileManager& fileManager, int& state, bool& init, Secure& secure, string& password, Clock& AFK_Clock);
    void draw(RenderWindow& window);
};

