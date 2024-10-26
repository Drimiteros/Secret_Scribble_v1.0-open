#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <locale>
#include <codecvt>
#include "FPS.h"
#include "CursorSprite.h"
#include "LocatePath.h"

using namespace sf;
using namespace std;

class DiskInfo
{
private:
    Texture driveTexture;
    Texture selTexture;
    Sprite driveSprite;
    Sprite sel;

    Font font;
    Text driveNameText;
    Text driveInfoText;
    Text driveCounterText;

    float barLength = 0;
    int speedMultiplier = 1.5;
    RectangleShape bar;
    RectangleShape driveHitBox;
    RectangleShape menuBar;
    vector<RectangleShape> bar2;
    CircleShape cr[2];

public:
    vector<string> driveName;
    vector<string> driveLabel;
    vector<float> driveTotalCapacity;
    vector<float> driveFreeCapacity;
    vector<float> driveUsedCapacity;

    Clock speedClock;
    Clock selectClock;

    RectangleShape renderDistance;
    int getState;

    DiskInfo();
    void getStateInfo(int state);
    void restartScanEvent(DiskInfo* diskInfo, vector<DiskInfo>& diskInfos, bool& enter2, bool& init, 
        bool& isTextWindowFocused, RenderWindow& window);
    void getDiskProperties(DiskInfo& di, vector<DiskInfo>& dis);
    void selectDisk(DiskInfo& ds, vector<DiskInfo>& dss, CursorSprite& mc, bool& instructionClick, 
        bool& enter, string& filePath, int& scrollCounter, int& fileCount, LocatePath& lp, 
        vector<FileIcon>& fis, int& fileScrollCounter, RenderWindow& window);
    void visualize(DiskInfo& di, vector<DiskInfo>& dis, FPS& fps, CursorSprite& mc, int& scrollCounter, RenderWindow& window);
    void draw(RenderWindow& window, DiskInfo& di, vector<DiskInfo>& dis, CursorSprite& mc, int& scrollCounter);
    void diskManagement(DiskInfo* diskInfo, vector<DiskInfo>& diskInfos, CursorSprite& cursorSprite, bool& instructionClick, bool& enter, bool& enter2, string& filePath, int& driveScrollCounter, int& fileCount, LocatePath& locatePath, vector<FileIcon>& fileIcons, FPS& fps, RenderWindow& window, int& fileScrollCounter);
    void freeMemory(DiskInfo* diskInfo);
};

