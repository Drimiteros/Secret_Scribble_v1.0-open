#include "SearchBar.h"

SearchBar::SearchBar()
{
    //LOAD TEXTURES
    texture[searchBarTexture].loadFromFile("src/Textures/searchBar.png");
    texture[searchBarTexture2].loadFromFile("src/Textures/searchBar2.png");

    //LOAD FONTS
    font[thick].loadFromFile("src/Fonts/thick3.ttf");

    //DEFINE TEXTS
    text[searchBarText].setString("Search");
    text[searchBarText].setFont(font[thick]);
    text[searchBarText].setPosition(25, 58);
    text[searchBarText].setCharacterSize(15);
    text[searchBarText].setFillColor(Color(255, 255, 255, 200));

    //DEFINE SEARCHBAR
    searchBar.setScale(0.25, 0.25);
    searchBar.setPosition(20, 52);
    searchBar.setTexture(texture[searchBarTexture2]);
    searchBar.setColor(Color(255, 255, 255, 250));
}

void SearchBar::type(string& filePath, string& enterFilePath_a, Event& eve, bool& isKeyPressed, bool& enter, CursorSprite& c, 
    int state, RenderWindow& window)
{
    if (canType == true && state == 2 && window.hasFocus() == true)
    {
        if (eve.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Enter))
        {
            filePath += eve.text.unicode;
            isKeyPressed = true;
        }
        else
            isKeyPressed = false;

        //BACKSPACE
        if (Keyboard::isKeyPressed(Keyboard::Backspace))
        {
            enterFilePath_a = filePath.substr(0, filePath.length() - 1);
            filePath = enterFilePath_a;
        }
        if (Keyboard::isKeyPressed(Keyboard::Backspace) && Keyboard::isKeyPressed(Keyboard::LShift))
        {
            enterFilePath_a = "";
            filePath = enterFilePath_a;
        }

        //ENTER
        if (Keyboard::isKeyPressed(Keyboard::Enter) && enter == false)
            enter = true;
    }
    if (filePath.size() > 0 && filePath.size() < 28)
        text[searchBarText].setString(filePath);
    else if (filePath.size() >= 28)
        text[searchBarText].setString(filePath.substr(0, 28));
    else
        text[searchBarText].setString("Search");
}

void SearchBar::logic(CursorSprite& c, int state, RenderWindow& window)
{
    if (window.hasFocus() == true && state == 2)
    {
        if (c.buildCursor.getGlobalBounds().intersects(searchBar.getGlobalBounds()))
        {
            canType = true;
            searchBar.setTexture(texture[searchBarTexture]);
        }
        else
        {
            canType = false;
            searchBar.setTexture(texture[searchBarTexture2]);
        }
    }
}

void SearchBar::draw(RenderWindow& window, int state)
{
    if (state == 2 && window.hasFocus() == true)
    {
        window.draw(searchBar);
        for (int i = 0; i < textCount; i++)
            window.draw(text[i]);
    }
}