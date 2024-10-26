#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CursorSprite.h"
#include "FPS.h"
#include "TextEditor.h"
#include "FileManager.h"
#include "Secure.h"

using namespace sf;
using namespace std;

class FileIcon
{
private:

public:
	Texture folderIocnTexture;
	Texture folderIocnTextureSelected;
	Texture returnIcontexture;
	Texture musicIcontexture;
	Texture exeIcontexture;
	Texture txtIcontexture;
	Texture mp4Icontexture;
	Texture pngIcontexture;
	Texture csvIcontexture;
	Sprite icon;
	FileIcon();
};

class LocatePath
{
private:
	Font font;
	Texture texture;

public:
	int size = 0;
    string oldPath;
	string getFileName;
    vector<string> fileNameStringVector;
    vector<string> type;
	vector<Text> availablePathsText;
	vector<Text> availablePathsText_a;
	Text fileCountText;
	RectangleShape itemView;
	vector<Sprite> sel;
	Clock coverClock;
	Clock clickCooldownClock;
	vector<Clock> revealDelayClock;

    LocatePath();
    void logic(string& filePath, CursorSprite& mc, bool& enter, bool& instructionClick, int& fileCount, FileIcon& icon, vector<FileIcon>& icons, bool& isKeyPressed, FPS& fps, int& scrollCounter, int& state, TextEditor& textEditor,FileManager& fileManager, bool& isTextFileOpen, string password, Secure& secure, RenderWindow& window, string& fileNameString);
    void showFiles(RenderWindow& window, FileIcon& icon, vector<FileIcon>& icons, CursorSprite& mc, int& state);
};

