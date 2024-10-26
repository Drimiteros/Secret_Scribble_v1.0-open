#include "CursorSprite.h"

CursorSprite::CursorSprite()
{
	cursor.setSize(Vector2f(5, 5));
	cursor.setTextureRect(IntRect(0, 0, 5, 5));
	cursor.setOutlineColor(Color::White);
	cursor.setOutlineThickness(1);
	cursor.setFillColor(Color::Transparent);

	buildCursor.setSize(Vector2f(5, 5));
	buildCursor.setTextureRect(IntRect(0, 0, 5, 5));
	buildCursor.setOutlineColor(Color::White);
	buildCursor.setOutlineThickness(1);
	buildCursor.setFillColor(Color::Transparent);
}

CursorSprite::~CursorSprite()
{

}

void CursorSprite::storePos(bool& isMovingCursor, RenderWindow& window)
{
	if (updatePosClock.getElapsedTime().asSeconds() < 0.5 && window.hasFocus())
		cursPos[0] = cursor.getPosition();
	if (updatePosClock.getElapsedTime().asSeconds() >= 0.5)
	{
		cursPos[1] = cursor.getPosition();
		updatePosClock.restart();
	}
	if (cursPos[0] != cursPos[1])
		isMovingCursor = true;
	else
		isMovingCursor = false;
}

void CursorSprite::mainLogic(RenderWindow& window, bool& moveCursor)
{
	if (Mouse::isButtonPressed(Mouse::Left) && moveCursor == true)
		buildCursor.setPosition(cursor.getPosition());
	cursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)));
}

void CursorSprite::draw(RenderWindow& window)
{
	window.draw(cursor);
	window.draw(buildCursor);
}