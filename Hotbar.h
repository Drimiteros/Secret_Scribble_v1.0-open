#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "CursorSprite.h"
#include "FileManager.h"
#include "DiskInfo.h"
#include "LocatePath.h"
#include "TextEditor.h"
#include "Secure.h"

using namespace std;
using namespace sf;

class Hotbar
{
private:
	RectangleShape bar[2];
	RectangleShape nameFileMenu;
	RectangleShape deleteFileMenu;
	RectangleShape cover;
	Sprite createFileButton;
	Sprite deleteFileButton;
	Sprite keepFileButton;
	Sprite formSprite;
	Sprite checkBox[2];
	Font font;
	Text infoText;
	Text fileNameText;
	Text createFileText;
	Text fileDeleteText;
	Text fileDeleteText2;
	Text deleteFileText;
	Text keepFileText;
	Text fileExportText[5];
	Texture texture[18];
	bool isFileNamed = false;
	bool isFileCreated = false;
	bool isFileModifyied = false;
	bool isFileDeleted = false;
	bool isFileEncrypted = false;
	string fileName;

public:
	Sprite sprite[18];
	Clock displayInfoTextDelayClock;
	Clock ButtonPressDelayClock;
	Clock updateFoldersClock;
	Text optionsText;
	Text AFKText[3];
	Text importMenuText;
	Text clipboardText[3];
	Texture timerCountArrowTexture;
	Texture backgroundSpriteTexture;
	Sprite timerCountArrow[2];
	Sprite clipboardEraceCountArrow[2];
	Sprite backgroundSprite[2];
	Sprite exitButton;
	Sprite exitButton2;
	Sprite exportButton;

	Hotbar();
	void visual(CursorSprite& c, int state, RenderWindow& window);
	void nameFile(CursorSprite& c, Event& eve);
	void createFile(CursorSprite& c, string& filePath, bool& enter, bool& instructionClick, int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis, RenderWindow& window, int state, TextEditor& textEditor);
	void saveFile(CursorSprite& c, FileManager& fileManager, RenderWindow& window, int state, bool& enter, bool& instructionClick, int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis);
	void deleteFile(CursorSprite& c, FileManager& fileManager, bool& enter, bool& instructionClick, int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lc, vector<FileIcon>& fis, bool& isTextFileOpen, RenderWindow& window, int state, string& fileNameString);
	void exportFile(int state, RenderWindow& window, bool& isExportOpen, CursorSprite& c, bool& isPasswordGenOpen, bool& isOptionsOpen, TextEditor& textEditor, bool& isTextFileOpen, string& fileNameString, ImGuiIO& io, Secure& secure, FileManager& fileManager, bool& enter, bool& instructionClick, 
		int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis, string& filePath, bool& isDonateOpen);
	void options(RenderWindow& window, CursorSprite& c, int state, TextEditor& textEditor, int& AFKTimerCount, bool& isTextFileOpen, FileManager& fm, bool& isOptionsOpen, bool& isPasswordGenOpen, bool& isImportOpen, int& clipboardEraceTime, bool& isDonateOpen);
	void reportIssue(CursorSprite& c);
	void draw(RenderWindow& window, int state);
};

