#pragma once
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "CursorSprite.h"
#include "PasswordConfig.h"
#include "DiskInfo.h"
#include "FileManager.h"
#include "LocatePath.h"
#include "FPS.h"
#include "PasswordLogin.h"
#include "TextEditor.h"
#include "SearchBar.h"
#include "Hotbar.h"
#include <cryptlib.h>
#include <aes.h>
#include <filters.h>
#include <modes.h>
#include <hex.h>
#include <secblock.h>
#include "Secure.h"
#include "InternetAdapterConfig.h"
#include "AFK_Lock.h"
#include "PasswordGenerator.h"
#include "Donate.h"

using namespace std;
using namespace sf;
using namespace ImGui::SFML;
using namespace CryptoPP;

class Renderer
{
private:
    //CREATE WINDOW AND DEFINE ITS PREPORTIES
    RenderWindow window;
    Event event;
    ImFont* mainFont;
    FPS fps;
    RectangleShape line;
    RectangleShape line2;
    static const ImWchar additionalRanges[];

    //TEXTURES
    //ASSIGN NAMES TO EVERY TEXTURE (INSTEAD OF TYPING texture[0].loadFromFile("...") TYPE texture[terminateButtonTexture].loadFromFile("..."))
    int terminateButtonTexture = 0;
    int minimizeButtonTexture = 1;
    int titleBarTexture = 2;
    Texture texture[textureCount]; //CREATE AS MANY TEXTURES AS textureCount

    //INIT CURSOR
    CursorSprite cursorSprite;

    //INIT FILE MANAGER
    FileManager fileManager;

    //INIT PASSWORD CONFIG MENU
    PasswordConfig passwordConfig;

    //INIT LOGIN STAGE
    PasswordLogin passwordLogin;

    //INIT DISK INFO
    DiskInfo* diskInfo = new DiskInfo();
    vector<DiskInfo> diskInfos;

    //INIT LOCATE PATH
    LocatePath locatePath;
    vector<LocatePath> locatePaths;
    FileIcon fileIcon;
    vector<FileIcon> fileIcons;

    //INIT TEXT EDITOR
    TextEditor textEditor;

    //INIT SEARCH BAR
    SearchBar searchBar;

    //INIT HOTBAR
    Hotbar hotbar;

    //SECURE
    Secure secure;
    
    //Init IntenetAdapter
    InternetAdapterConfig internetAdapterConfig;

    //INIT AFK LOCK
    AFK_Lock afkLock;

    //INIT PASSWORD GEN
    PasswordGenerator passwordGenerator;

    //INIT DONATE
    Donate donate;

public:
    //GENERAL VARS
    int state = 0;
    int driveScrollCounter = 0;
    int fileScrollCounter = 0;
    int scroll = 0;
    int fileCount;
    int AFKTimerCount = 5;
    int clipboardEraceTime = 10;
    bool isTyping = false;
    bool isMovingCursor = false;
    bool moveCursor = true;
    bool instructionClick = false;
    bool isKeyPressed = false;
    bool enter;
    bool init = false;
    bool enter2 = false;
    bool enter3 = false;
    bool isTextFileOpen = false;
    bool isDisconnected = false;
    bool reConnected = false;
    bool isActive = true;
    bool isDoneManagingAdapter = false;
    bool isOptionsOpen = false;
    bool isExportOpen = false;
    bool isPasswordGenOpen = false;
    bool isDonateOpen = false;
    string password;
    string filePath;
    string fileNameString;
    Clock AFK_Clock;
    Clock timeTrackClipboardDataClock;

    Renderer();
    void events();
    void stylizeWindow();
    void updateLogic();
    void mainLoop();
    void drawLayer1();
    void drawLayer2();
};

