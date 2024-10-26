#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CursorSprite.h"
#include "Windows.h"

using namespace std;
using namespace sf;

class PasswordGenerator
{
private:
	Texture iconTexture;
	Texture toolSelTexture;
	Texture regeneratePassTexture;
	Texture copyPassTexture;
	Texture exitButtonTexture;
	Texture backgroundTexture;
	Texture timerCountArrowTexture;
	Texture checkboxTexture;
	Font font;
	Clock clickDelayClock;

public:
	Sprite iconSprite;
	Sprite toolSelectSprite;
	Sprite regeneratePassSprite;
	Sprite copyPassSprite;
	Sprite exitButton;
	Sprite backGroundSprite[3];
	Sprite timerCountArrow[2];
	Sprite checkBox[3];
	RectangleShape background;
	Text logoText;
	Text menuLogoText;
	Text passwordText;
	Text passwordSizeText;
	Text passwordSizeText2;
	Text passwordSizeText3;
	Text passwordPreferencesText;
	Text includeNumbersText;
	Text includeSymbolsText;
	Text includeUpperText;
	Text clipboardClearCounterText;
	Text clipboardClearCounterText2;
	String password;

	int passwordSize = 32;
	bool hasNumbers = true;
	bool hasUppercase = true;
	bool hasSymbols = true;
	bool isCopyiedToClipboard = false;

	PasswordGenerator();
	void generate();
	void menuLogic(RenderWindow& window, int& state, bool& isPasswordGenOpen, CursorSprite& mc, bool& isOptionsOpen, Clock& timeTrackClipboardDataClock, int& clipboardEraceTime, bool& isTextFileOpen, bool& isImportOpen, bool& isDonateOpen);
	void draw(RenderWindow& window, CursorSprite& mc, int& state);
};

