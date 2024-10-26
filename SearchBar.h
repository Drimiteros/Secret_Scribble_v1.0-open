#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CursorSprite.h"

#define textureCount 2
#define textCount 20
#define fontCount 20
#define clockCounter 4
#define maxNoteInFolder 30
#define myTextCount 99999

using namespace sf;
using namespace std;

class SearchBar
{
private:
    //CREATE TEXTURES
    //ASSIGN NAMES TO EVERY TEXTURE (INSTEAD OF TYPING texture[0].loadFromFile("...") TYPE texture[backGroundTexture].loadFromFile("..."))
    int searchBarTexture = 0;
    int searchBarTexture2 = 1;
    Texture texture[textureCount];

    //CREATE FONT
    //ASSIGN NAMES TO EVERY FONT (INSTEAD OF TYPING font[0].loadFromFile("...") TYPE font[regular].loadFromFile("..."))
    int regular = 0;
    int thick = 1;
    int regularItalic = 3;
    int thickItalic = 4;
    Font font[fontCount];

    //CREATE TEXT
    int searchBarText = 0;
    int newNoteText = 1;
    Text text[textCount];

    //CLOCKS
    int folderSpawnClock = 0;
    int noteSpawnClock = 1;
    Clock clock[clockCounter];

    //SEARCH BAR
    Sprite searchBar; //WHEN CLICKED ALLOWS YOU TO SEARCH FOR FILES OR FOLDERS
    Sprite selectBoxSprite;

    bool canType = false;
    bool isFolderCreated = false;
    bool isFolderDeleted = false;
    bool isNoteCreated = false;

    string noteName;
    static char myText[myTextCount];

public:
    SearchBar();
    void type(string& filePath, string& enterFilePath_a, Event& eve, bool& isKeyPressed, bool& enter, 
        CursorSprite& c, int state, RenderWindow& window);
    void logic(CursorSprite& c, int state, RenderWindow& window);
    void draw(RenderWindow& window, int state);
};

