#include "DiskInfo.h"

DiskInfo::DiskInfo()
{
    driveTexture.loadFromFile("src/Textures/drive.png");
    selTexture.loadFromFile("src/Textures/sel.png");
    driveSprite.setTexture(driveTexture);
    driveSprite.setScale(0.3, 0.3);
    sel.setTexture(selTexture);
    sel.setScale(1, 1);

    font.loadFromFile("src/Fonts/thick3.ttf");
    driveNameText.setFont(font);
    driveNameText.setCharacterSize(16);
    driveNameText.setFillColor(Color::White);
    driveInfoText.setFont(font);
    driveInfoText.setCharacterSize(10);
    driveInfoText.setFillColor(Color::White);
    driveCounterText.setFont(font);
    driveCounterText.setCharacterSize(16);
    driveCounterText.setFillColor(Color::White);
    driveCounterText.setPosition(10, 335);
    driveHitBox.setSize(Vector2f(258, 105));
    driveHitBox.setFillColor(Color(255, 0, 0, 100));

    bar.setSize(Vector2f(135, 15));
    bar.setFillColor(Color(49, 64, 70));
    for (int i = 0; i < 2; i++)
    {
        cr[i].setRadius(7.5);
        cr[i].setFillColor(Color(201, 201, 201));
        cr[i].setPointCount(50);
    }
    menuBar.setFillColor(Color(72, 96, 105));
    menuBar.setPosition(0, 0);

    renderDistance.setSize(Vector2f(260, 230));
    renderDistance.setPosition(10, 100);
}

void DiskInfo::getStateInfo(int state)
{
    getState = state;
}

void DiskInfo::restartScanEvent(DiskInfo* diskInfo, vector<DiskInfo>& diskInfos, bool& enter2, bool& init, bool& isTextWindowFocused,
    RenderWindow& window)
{
    if ((getState == 2 && isTextWindowFocused == false && Keyboard::isKeyPressed(Keyboard::Enter) && enter2 == false
        && window.hasFocus() == true) || init == true)
    {
        cout << "Restarting disk scan..." << endl;
        init = false;
        enter2 = true;
        if (diskInfo != nullptr)
            delete diskInfo;
        diskInfo = new DiskInfo();
        diskInfos.clear();
        diskInfo->getDiskProperties(*diskInfo, diskInfos);
    }
}

void DiskInfo::getDiskProperties(DiskInfo& di, vector<DiskInfo>& dis)
{
    char buffer[100];  // Buffer to store drive strings
    DWORD drives = GetLogicalDriveStringsA(sizeof(buffer) - 1, buffer);
    char* drive_a = buffer;
    
    while (*drive_a) {
        char volumeName[MAX_PATH + 1] = { 0 }; // Initialize volumeName buffer
        DWORD volumeSerialNumber, maximumComponentLength, fileSystemFlags;
    
        // Get the volume information
        if (GetVolumeInformationA(drive_a, volumeName, sizeof(volumeName), &volumeSerialNumber, &maximumComponentLength, &fileSystemFlags, nullptr, 0)) {
    
            // Print volume name if available
            if (*volumeName != '\0')
                driveLabel.emplace_back(volumeName);
            else
                driveLabel.emplace_back("Local Disk");
        }
        // Move to the next drive in the buffer
        cout << "Found drive: " << drive_a << endl;
        drive_a += strlen(drive_a) + 1;
    }
    
    //GET THE DRIVES BUFFER LENGTH
    DWORD drivesBufferLength = GetLogicalDriveStrings(0, nullptr);
    cout << "Drives buffer length: " << drivesBufferLength << endl;
    vector<wchar_t> drivesBuffer(drivesBufferLength);
    
    //RESERVE A PLACE FOR THE DRIVE'S NAME
    driveName.reserve(10);
    driveFreeCapacity.reserve(10);
    driveFreeCapacity.reserve(10);
    driveUsedCapacity.reserve(10);
    
    //GET EVERY DRIVE'S LETTER
    GetLogicalDriveStrings(drivesBuffer.size(), &drivesBuffer[0]);
    
    //ASSIGN EVERY DRIVE'S LETTER TO driveName
    wchar_t* drive = &drivesBuffer[0];
    int loopCount = 0;
    while (*drive)
    {
        /*
        EVERY LOOP PROCCESS A DISK LETTER AND MOVES THE POINTER 'DRIVE'
        TO THE NEXT LETTER AFTER ASIGNING IT UNTIL 'DRIVE REACHES' THE
        CHARACTER '\0'
        */
        loopCount++;
    
        //GET DISK INFO
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string driveLetter = converter.to_bytes(drive);
        driveName.emplace_back(driveLetter);
        ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
    
        char volumeName[MAX_PATH + 1];
        DWORD volumeSerialNumber, maximumComponentLength, fileSystemFlags;
    
        if (GetDiskFreeSpaceExW(drive, &freeBytesAvailable, &totalBytes, &totalFreeBytes))
        {
            double totalSize = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);
            double freeSize = static_cast<double>(totalFreeBytes.QuadPart) / (1024 * 1024 * 1024);
            double usedSize = totalSize - freeSize;
            driveTotalCapacity.emplace_back(totalSize);
            driveFreeCapacity.emplace_back(freeSize);
            driveUsedCapacity.emplace_back(usedSize);
            bar2.emplace_back();
            dis.emplace_back(DiskInfo(di));
        }
        drive += wcslen(drive) + 1;
    }
    cout << "Drives found: " << loopCount << endl;
    driveCounterText.setString("Drives: " + to_string(driveName.size()));
}

void DiskInfo::selectDisk(DiskInfo& ds, vector<DiskInfo>& dss, CursorSprite& mc, bool& instructionClick, bool& enter,
    string& filePath, int& scrollCounter, int& fileCount, LocatePath& lp, vector<FileIcon>& fis, int& fileScrollCounter,
    RenderWindow& window)
{
    if (getState == 2 && window.hasFocus() == true)
    {
        //SELECT PATH
        for (int i = 0; i < driveName.size(); i++)
        {
            if (mc.cursor.getGlobalBounds().intersects(sel.getGlobalBounds())
                && sel.getGlobalBounds().intersects(dss[i].driveHitBox.getGlobalBounds()) 
                && mc.cursor.getGlobalBounds().intersects(renderDistance.getGlobalBounds())
                && Mouse::isButtonPressed(Mouse::Left) && selectClock.getElapsedTime().asSeconds() > 0.2)
            {

                filePath = driveName[i];
                enter = true;
                instructionClick = true;
                //scrollCounter = 0;
                fileScrollCounter = 0;
                fileCount = 0;
                lp.fileNameStringVector.clear();
                lp.availablePathsText.clear();
                fis.clear();
                lp.type.clear();
                lp.coverClock.restart();
                selectClock.restart();
            }
        }
    }
}

void DiskInfo::visualize(DiskInfo& di, vector<DiskInfo>& dis, FPS& fps, CursorSprite& mc, int& scrollCounter, RenderWindow& window)
{
    if (getState == 2)
    {
        //VISUALIZE THE DRIVES CAPACITY BARS
        for (int i = 0; i < bar2.size(); i++)
        {
            if (((driveUsedCapacity[i] * 135) / driveTotalCapacity[i]) * speedClock.getElapsedTime().asSeconds() * speedMultiplier <= (driveUsedCapacity[i] * 135) / driveTotalCapacity[i])
            {
                barLength = speedClock.getElapsedTime().asSeconds();
                bar2[i].setSize(Vector2f(((driveUsedCapacity[i] * 135) / driveTotalCapacity[i]) * barLength * speedMultiplier, 15));
                //bar2[i].setFillColor(Color((90 + (driveUsedCapacity[i] * 135) / driveTotalCapacity[i]) * barLength * speedMultiplier, 255 - (10 + (driveUsedCapacity[i] * 135) / driveTotalCapacity[i]) * barLength * speedMultiplier, 0));
                bar2[i].setFillColor(Color(26, 188, 156, 255));
            }
            bar2[i].setPosition(30, 183 + (120 * i) + (scrollCounter * 5));
            dis[i].driveHitBox.setPosition(10, 105 + (120 * i) + (scrollCounter * 5));
        }

        for (int a = 0; a < driveName.size(); a++)
        {
            if (((dis[a].driveUsedCapacity[a] * 135) / dis[a].driveTotalCapacity[a]) * barLength * speedMultiplier >= 135)
            {
                dis[a].cr[1].setFillColor(bar2[a].getFillColor());
                dis[a].cr[0].setFillColor(bar2[a].getFillColor());
            }
            else
            {
                dis[a].cr[1].setFillColor(bar.getFillColor());
                dis[a].cr[0].setFillColor(bar2[a].getFillColor());
            }
            dis[a].cr[0].setPosition(25, 183 + (120 * a) + (scrollCounter * 5));
            dis[a].cr[1].setPosition(130 + 30, 183 + (120 * a) + (scrollCounter * 5));
        }
        menuBar.setSize(Vector2f(280, window.getSize().y));
    }
}

void DiskInfo::draw(RenderWindow& window, DiskInfo& di, vector<DiskInfo>& dis, CursorSprite& mc, int& scrollCounter)
{
    if (getState == 2 && window.hasFocus() == true)
    {
        window.draw(menuBar);
        for (int i = 0; i < di.driveName.size(); i++)
        {
            //SELECT DISK
            if (mc.cursor.getGlobalBounds().intersects(dis[i].driveHitBox.getGlobalBounds()) && dis[i].driveHitBox.getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
            {
                sel.setPosition(dis[i].driveHitBox.getPosition().x - 0, dis[i].driveHitBox.getPosition().y - 7);
                window.draw(sel);
            }
            //window.draw(dis[i].driveHitBox);
            di.driveSprite.setPosition(25, 110 + (120 * i) + (scrollCounter * 5));
            if (di.driveSprite.getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(driveSprite);
            driveNameText.setPosition(85, 110 + (120 * i) + (scrollCounter * 5));
            driveNameText.setString(driveLabel[i] + " (" + driveName[i] + ")");
            if (driveNameText.getString().getSize() >= 20 && driveNameText.getString().getSize() < 40)
                driveNameText.setCharacterSize(13);
            else if (driveNameText.getString().getSize() >= 40)
                driveNameText.setCharacterSize(10);
            else
                driveNameText.setCharacterSize(16);
            if (driveNameText.getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(driveNameText);
            driveInfoText.setPosition(85, 135 + (120 * i) + (scrollCounter * 5));
            driveInfoText.setString("Total Size: " + to_string(driveTotalCapacity[i]).substr(0, 7) + " GB\nFree Size: "
                + to_string(driveFreeCapacity[i]).substr(0, 7) + " GB\nUsed Size: " + to_string(driveUsedCapacity[i]).substr(0, 7) + " GB");
            if (driveInfoText.getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(driveInfoText);
            bar.setPosition(30, 183 + (120 * i) + (scrollCounter * 5));
            if (bar.getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(bar);
            if (bar2[i].getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(bar2[i]);
            if (dis[i].cr[0].getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(dis[i].cr[0]);
            if (dis[i].cr[1].getGlobalBounds().intersects(renderDistance.getGlobalBounds()))
                window.draw(dis[i].cr[1]);
        }
        window.draw(driveCounterText);
        //window.draw(renderDistance);
    }
}

void DiskInfo::diskManagement(DiskInfo* diskInfo, vector<DiskInfo>& diskInfos, CursorSprite& cursorSprite, bool& instructionClick, bool& enter, bool& enter2, string& filePath, int& driveScrollCounter, int& fileCount, LocatePath& locatePath, vector<FileIcon>& fileIcons, FPS& fps, RenderWindow& window, int& fileScrollCounter)
{
    if (getState == 2)
    {
        if (&diskInfo != nullptr) //IF THE DISKINFO ADDRESS IS POINTING TO A VALID MEMORY LOCATION EXECUTE THE FOLLOWING CODE 
        {
            //SELECT THE DISK YOU WANT ACCESS
            diskInfo->selectDisk(*diskInfo, diskInfos, cursorSprite, instructionClick, enter, filePath, driveScrollCounter, fileCount, locatePath, fileIcons, fileScrollCounter, window);
            //ANIMATE THE DISK CAPACITY BAR
            diskInfo->visualize(*diskInfo, diskInfos, fps, cursorSprite, driveScrollCounter, window);
            enter2 = false;
        }
    }
}

void DiskInfo::freeMemory(DiskInfo *diskInfo)
{
    delete diskInfo;
    diskInfo = nullptr;
}