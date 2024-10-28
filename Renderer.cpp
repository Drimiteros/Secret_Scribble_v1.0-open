#include "Renderer.h"

Renderer::Renderer()
{
    //CREATE WINDOW
    window.create(VideoMode(1480, 815), "Secret Scribble v. 1.1 open");
    window.setFramerateLimit(144);
    icon.loadFromFile("src/Textures/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    Init(window, false);

    ImWchar additionalRanges[] = 
    {
        0x0020, 0x007F, // Basic Latin (ASCII)
        0x00A0, 0x00FF, // Latin-1 Supplement
        0x0100, 0x017F, // Latin Extended-A
        0x0180, 0x024F, // Latin Extended-B
        0x0250, 0x02AF, // IPA Extensions
        0x0400, 0x04FF, // Cyrillic
        0x0370, 0x03FF, // Greek and Coptic
        0x0590, 0x05FF, // Hebrew
        0x0600, 0x06FF, // Arabic
        0x0900, 0x097F, // Devanagari
        0x3040, 0x309F, // Hiragana
        0x30A0, 0x30FF, // Katakana
        0x1100, 0x11FF, // Hangul Jamo
        0x0E00, 0x0E7F, // Thai
        0x10A0, 0x10FF, // Georgian
        0x0530, 0x058F, // Armenian
        0x0980, 0x09FF, // Bengali
        0x0B80, 0x0BFF, // Tamil
        0x0C00, 0x0C7F, // Telugu
        0x4E00, 0x9FFF, // CJK Unified Ideographs
        0 // Null-terminated
    };
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 25.0f;
    io.Fonts->AddFontFromFileTTF("src/Fonts/consolas.TTF", io.FontGlobalScale, nullptr, additionalRanges);
    ImGui::SFML::UpdateFontTexture();

    //LOAD START VALUES
    fileManager.loadStageInfo(state);
    fileManager.loadAutoLockPferences(AFKTimerCount);
    fileManager.loadClipboardTimePferences(clipboardEraceTime);

    //GET DISK PROPERTIES
    diskInfo->getDiskProperties(*diskInfo, diskInfos);
}

void Renderer::events()
{
    while (window.pollEvent(event))
    {
        ProcessEvent(event);

        //TERMINATE WINDOW
        if (event.type == Event::Closed)
            window.close();

        //RESIZE WINDOW
        if (event.type == Event::Resized)
        {
            Vector2u newSize = window.getSize();
            Vector2i newPos = window.getPosition();
            window.close();
            window.create(VideoMode(newSize.x, newSize.y), "Password Manager v.6");
            window.setPosition(newPos);
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
            window.setFramerateLimit(144);
        }

        //TYPE VENTS
        {
            textEditor.getKeyboardInputIdicator(event, window);
            passwordConfig.typeEvent(window, event, state);
            passwordLogin.typeEvent(window, event);
            searchBar.type(filePath, filePath, event, isKeyPressed, enter, cursorSprite, state, window);
            hotbar.nameFile(cursorSprite, event);
        }

        //MOUSE WEEL EVENTS
        {
            if (event.type == Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                    scroll = 1;
                else if (event.mouseWheelScroll.delta < 0)
                    scroll = -1;
            }
            if (scroll == 1 && !Keyboard::isKeyPressed(Keyboard::LControl))
            {
                if (cursorSprite.cursor.getGlobalBounds().intersects(diskInfo->renderDistance.getGlobalBounds()) && driveScrollCounter < 0)
                    driveScrollCounter = driveScrollCounter + 24;
                if (cursorSprite.cursor.getGlobalBounds().intersects(locatePath.itemView.getGlobalBounds()) && fileScrollCounter < 0)
                    fileScrollCounter = fileScrollCounter + 36;
                scroll = 0;
            }
            else if (scroll == -1 && !Keyboard::isKeyPressed(Keyboard::LControl))
            {
                if (cursorSprite.cursor.getGlobalBounds().intersects(diskInfo->renderDistance.getGlobalBounds()))
                    driveScrollCounter = driveScrollCounter - 24;
                if (cursorSprite.cursor.getGlobalBounds().intersects(locatePath.itemView.getGlobalBounds()))
                    fileScrollCounter = fileScrollCounter - 36;
                scroll = 0;
            }
        }

        //RESTART DISK SCANNING
        {
            diskInfo->restartScanEvent(diskInfo, diskInfos, enter2, init, isTextFileOpen, window);
        }
    }
}

void Renderer::stylizeWindow()
{
    line.setFillColor(Color(255, 255, 255, 150));
    line.setPosition(0, 363);
    line2.setFillColor(Color(255, 255, 255, 150));
    line2.setPosition(0, window.getSize().y - 120);
    if (window.getSize().x >= 1280)
    {
        line.setSize(Vector2f(280, 2));
        line2.setSize(Vector2f(280, 2));
    }
}

void Renderer::updateLogic()
{
    Update(window, seconds(1.0f / 144.0f));
    stylizeWindow();
    afkLock.lockTheApp(AFK_Clock, state, passwordLogin, isTyping, isMovingCursor, AFKTimerCount, isDisconnected, reConnected, isActive, isDoneManagingAdapter);
    internetAdapterConfig.logic(state, isDisconnected, reConnected, isActive, isDoneManagingAdapter);
    cursorSprite.storePos(isMovingCursor, window);
    cursorSprite.mainLogic(window, moveCursor);
    passwordConfig.mainLogic(cursorSprite, window, fileManager, state, password, secure);
    passwordLogin.getStateInfo(state);
    passwordLogin.logic(window, cursorSprite, fileManager, state, init, secure, password, AFK_Clock);
    diskInfo->getStateInfo(state);
    diskInfo->diskManagement(diskInfo, diskInfos, cursorSprite, instructionClick, enter, enter2, filePath, driveScrollCounter, fileCount, locatePath, fileIcons, fps, window, fileScrollCounter);
    locatePath.logic(filePath, cursorSprite, enter, instructionClick, fileCount, fileIcon, fileIcons, isKeyPressed, fps, fileScrollCounter, state, textEditor, fileManager, isTextFileOpen, password, secure, window, fileNameString);
    textEditor.setTypingStae(isTyping);
    textEditor.mainLogic(state, isTextFileOpen, ImGui::GetIO(), window, fileNameString, cursorSprite, isPasswordGenOpen, isExportOpen);
    textEditor.popupWindow(state, cursorSprite, ImGui::GetIO(), window);
    textEditor.lineCounter(state, isTextFileOpen, window);
    searchBar.logic(cursorSprite, state, window);
    fileManager.saveTextFile(textEditor, password, secure, cursorSprite);
    hotbar.createFile(cursorSprite, filePath, enter, instructionClick, fileScrollCounter, fileCount, *diskInfo, locatePath, fileIcons, window, state, textEditor);
    hotbar.saveFile(cursorSprite, fileManager, window, state, enter, instructionClick, fileScrollCounter, fileCount, *diskInfo, locatePath, fileIcons);
    hotbar.deleteFile(cursorSprite, fileManager, enter, instructionClick, fileScrollCounter, fileCount, *diskInfo, locatePath, fileIcons, isTextFileOpen, window, state, fileNameString);
    hotbar.visual(cursorSprite, state, window);
    hotbar.exportFile(state, window, isExportOpen, cursorSprite, isPasswordGenOpen, isOptionsOpen, textEditor, isTextFileOpen, fileNameString, ImGui::GetIO(), secure, fileManager, enter, instructionClick, fileScrollCounter, fileCount, *diskInfo, locatePath, fileIcons, filePath, isDonateOpen);
    hotbar.options(window,cursorSprite, state, textEditor, AFKTimerCount, isTextFileOpen, fileManager, isOptionsOpen, isPasswordGenOpen, isExportOpen, clipboardEraceTime, isDonateOpen);
    hotbar.reportIssue(cursorSprite);
    passwordGenerator.menuLogic(window, state, isPasswordGenOpen, cursorSprite, isOptionsOpen, timeTrackClipboardDataClock, clipboardEraceTime, isTextFileOpen, isExportOpen, isDonateOpen);
    donate.logic(window, state, cursorSprite, isPasswordGenOpen, isOptionsOpen, isTextFileOpen, isExportOpen, isDonateOpen);
}

void Renderer::mainLoop()
{
    while (window.isOpen())
    {
        events();

        window.clear(Color(49, 64, 70, 200));

        updateLogic();

        drawLayer1();
        drawLayer2();

        window.display();
    }
    Shutdown();
    diskInfo->freeMemory(diskInfo);
}

void Renderer::drawLayer1()
{
    passwordConfig.draw(window, state);
    passwordLogin.draw(window);
    diskInfo->draw(window, *diskInfo, diskInfos, cursorSprite, driveScrollCounter);
    locatePath.showFiles(window, fileIcon, fileIcons, cursorSprite, state);
    searchBar.draw(window, state);
    if (state == 2 && window.hasFocus() == true) { window.draw(line);  window.draw(line2); }
}

void Renderer::drawLayer2()
{
    //cursorSprite.draw(window);
    Render(window);

    hotbar.draw(window, state);
    passwordGenerator.draw(window, cursorSprite, state);
    donate.draw(window, cursorSprite, state);
    textEditor.draw(window, state, isTextFileOpen);
}