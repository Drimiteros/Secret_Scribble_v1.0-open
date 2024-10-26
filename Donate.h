#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "CursorSprite.h"
#include "Windows.h"

using namespace std;
using namespace sf;

class Donate
{
private:
	Texture iconTexture;
	Texture toolSelTexture;
	Texture exitButtonTexture;
	Texture donateButtonTexture;
	Clock clickDelayClock;

public:
	Sprite iconSprite;
	Sprite toolSelectSprite;
	Sprite exitButton;
	Sprite donateButton;

	Font font;
	Text logoText;
	Text menuText1;
	Text menuText2;

	Donate();
	void logic(RenderWindow& windowint, int& state, CursorSprite& mc, bool& isPasswordGenOpen, bool& isOptionsOpen, bool& isTextFileOpen, bool& isImportOpen, bool& isDonateOpen);
	void draw(RenderWindow& window, CursorSprite& mc, int& state);
};

