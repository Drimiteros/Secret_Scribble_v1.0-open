#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CursorSprite.h"
#include "FileManager.h"
#include "PasswordLogin.h"
#include "Secure.h"

#define textCount 6
#define spriteCount 5

using namespace std;
using namespace sf;

class PasswordConfig
{
private:
    Font font;
    Font font2;

    int passwordText = 0;
    int passwordConfirmText = 1;
    int advanceText = 2;
    int passwordPowerText = 3;
    int guideText = 4;
    int guideText_a = 5;
    Text text[textCount];
    string password;
    string confirmPassword;
    string hiddenPass;
    string confirmHiddenPass;
    string passwordPower;

    bool isPasswordSelected = false;
    bool isConfirmPasswordSelected = false;
    bool isPasswordReady = false;
    bool isCapsOn = false;
    bool isHidden = true;
    bool isHidden_a = true;

    int menuBoxTexture = 0;
    int formTexture = 1;
    int formTexture2 = 2;
    int eyeTexture = 3;
    Texture texture[4];

    int menuBoxSprite = 0;
    int formSprite = 1;
    int formSprite2 = 2;
    int eyeSprite = 3;
    int eyeSprite_a = 4;
    Sprite sprite[spriteCount];

    Clock hideButtonCoolDown;

public:
    PasswordConfig();
    void typeEvent(RenderWindow& window, Event& eve, int state);
    void mainLogic(CursorSprite& c, RenderWindow& window, FileManager& fm, int& state, string& get_password, 
        Secure& secure);
    void draw(RenderWindow& window, int state);
};

