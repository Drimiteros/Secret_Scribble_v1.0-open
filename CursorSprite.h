#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class CursorSprite
{
private:

public:
	RectangleShape cursor;
	RectangleShape buildCursor;
	int state = 0;
	bool start = false;
	Vector2f cursPos[2];
	Clock selectedClock;
	Clock updatePosClock;

	CursorSprite();
	~CursorSprite();
	void storePos(bool& isMovingCursor, RenderWindow& window);
	void mainLogic(RenderWindow& window, bool& moveCursor);
	void draw(RenderWindow& window);
};

