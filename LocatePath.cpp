#include "LocatePath.h"

FileIcon::FileIcon()
{
    folderIocnTexture.loadFromFile("src/Textures/folder2.png");
    folderIocnTextureSelected.loadFromFile("src/Textures/folder2.png");
    returnIcontexture.loadFromFile("src/Textures/arrow.png");
    musicIcontexture.loadFromFile("src/Textures/note.png");
    exeIcontexture.loadFromFile("src/Textures/file.png");
    txtIcontexture.loadFromFile("src/Textures/txt.png");
    mp4Icontexture.loadFromFile("src/Textures/video.png");
    pngIcontexture.loadFromFile("src/Textures/image.png");
    csvIcontexture.loadFromFile("src/Textures/csv.png");
}

LocatePath::LocatePath()
{
    texture.loadFromFile("src/Textures/selectBox.png");
    font.loadFromFile("src/Fonts/thick3.ttf");
    itemView.setSize(Vector2f(270, 230));
    itemView.setFillColor(Color(255, 0, 0, 100));
    itemView.setPosition(5, 380);
    fileCountText.setFont(font);
    fileCountText.setCharacterSize(16);
    fileCountText.setPosition(10, 630);
    fileCountText.setFillColor(Color::White);
}

void LocatePath::logic(string& enterFilePath, CursorSprite& mc, bool& enter, bool& instructionClick, int& fileCount, FileIcon& icon,
    vector<FileIcon>& icons, bool& isKeyPressed, FPS& fps, int& scrollCounter, int& state, TextEditor& textEditor, FileManager& fileManager,
    bool& isTextFileOpen, string password, Secure& secure, RenderWindow& window, string& fileNameString)
{
    if (state == 2 && window.hasFocus() == true)
    {
        //RESERVE A PLACE FOR ESSENTIALS
        fileNameStringVector.reserve(140);
        availablePathsText.reserve(140);
        availablePathsText_a.reserve(140);
        icons.reserve(140);
        type.reserve(140);

        if ((enter == true && oldPath != enterFilePath) || instructionClick == true)
        {
            //FIND FILE
            WIN32_FIND_DATAA findData;
            HANDLE hFind = FindFirstFileA((enterFilePath + "\\*").c_str(), &findData);

            if (hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Folder");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".lnk")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Shortcut");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".mp3")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Audio");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".wav")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Audio");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".png")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Image");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".jpg")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Image");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".exe")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("App");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if ((string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".txt")
                        || (string(findData.cFileName).length() >= 5 && string(findData.cFileName).substr(string(findData.cFileName).length() - 5) == ".html")
                        || (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".css"))
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Txt");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if ((string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".csv"))
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Csv");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".mp4")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Video");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".url")
                    {
                        fileNameStringVector.emplace_back(findData.cFileName);
                        availablePathsText.emplace_back(Text());
                        availablePathsText_a.emplace_back(Text());
                        sel.emplace_back(Sprite());
                        icons.emplace_back(FileIcon(icon));
                        type.emplace_back("Url");
                        revealDelayClock.emplace_back();
                        fileCount++;
                    }
                    else if (string(findData.cFileName).length() >= 2 && string(findData.cFileName).substr(string(findData.cFileName).length() - 2) == "..")
                        fileCount--;
                    else if (string(findData.cFileName).length() >= 1 && string(findData.cFileName).substr(string(findData.cFileName).length() - 1) == ".")
                    {
                        fileNameStringVector.erase(fileNameStringVector.begin() + 0);
                        availablePathsText.erase(availablePathsText.begin() + 0);
                        availablePathsText_a.erase(availablePathsText_a.begin() + 0);
                        sel.erase(sel.begin() + 0);
                        icons.erase(icons.begin() + 0);
                        type.erase(type.begin() + 0);
                        revealDelayClock.erase(revealDelayClock.begin() + 0);
                        fileCount--;
                    }
                    enter = false;
                    instructionClick = false;
                    oldPath = enterFilePath;
                } while (FindNextFileA(hFind, &findData) != 0);

                FindClose(hFind);
            }
        }
        if (isKeyPressed == true)
        {
            coverClock.restart();
            fileNameStringVector.clear();
            availablePathsText.clear();
            availablePathsText_a.clear();
            icons.clear();
            type.clear();
            fileCount = 0;
        }
        for (int i = 0; i < fileNameStringVector.size(); i++)
        {
            //INIT FILE PROPERTIES
            availablePathsText[i].setFont(font);
            availablePathsText[i].setString(fileNameStringVector[i]);
            availablePathsText_a[i].setString(fileNameStringVector[i]);
            if (availablePathsText[i].getString().getSize() > 20)
                availablePathsText[i].setString(availablePathsText_a[i].getString().substring(0, 13) + "...");
            else
                availablePathsText[i].setString(availablePathsText_a[i].getString());
            availablePathsText[i].setCharacterSize(16);
            availablePathsText[i].setPosition(70, 377 + (i * 36) + scrollCounter);
            availablePathsText[i].setFillColor(Color::White);
            availablePathsText[i].setOutlineThickness(0);
            sel[i].setPosition(availablePathsText[i].getPosition().x - 57, availablePathsText[i].getPosition().y - 10);
            sel[i].setTexture(texture);
            sel[i].setScale(0.2, 0.2);

            //EXECUTE FILE
            if (mc.cursor.getGlobalBounds().intersects(sel[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && sel[i].getGlobalBounds().intersects(itemView.getGlobalBounds()) && clickCooldownClock.getElapsedTime().asSeconds() > 0.3)
            {
                clickCooldownClock.restart();
                for (int r = 0; r < revealDelayClock.size(); r++)
                    revealDelayClock[r].restart().asSeconds();
                cout << "Execution" << endl;
                if (type[i].find("Folder") != string::npos)
                {
                    enterFilePath += fileNameStringVector[i] + "\\";
                    enter = true;
                    scrollCounter = 0;
                    mc.selectedClock.restart();
                    coverClock.restart();
                    fileNameStringVector.clear();
                    availablePathsText.clear();
                    availablePathsText_a.clear();
                    icons.clear();
                    type.clear();
                    fileCount = 0;
                    isTextFileOpen = false;
                    string filePath = enterFilePath + fileNameStringVector[i];
                    break;
                }
                if (type[i].find("Audio") != string::npos || type[i].find("Video") != string::npos || type[i].find("Shortcut") != string::npos
                    || type[i].find("Image") != string::npos || type[i].find("Url") != string::npos)
                {
                    enterFilePath = enterFilePath;
                    string comm = "\"\"" + enterFilePath + fileNameStringVector[i] + "\"";
                    string filePath = enterFilePath + fileNameStringVector[i];
                    system(comm.c_str());
                    enter = false;
                    isTextFileOpen = false;
                }
                if (type[i].find("Txt") != string::npos)
                {
                    fileNameString = fileNameStringVector[i];
                    enterFilePath = enterFilePath;
                    string filePath = enterFilePath + fileNameStringVector[i];
                    fileManager.loadTextFile(filePath, textEditor, password, secure);
                    enter = false;
                    isTextFileOpen = true;
                }
                if (type[i].find("Csv") != string::npos)
                {
                    fileNameString = fileNameStringVector[i];
                    enterFilePath = enterFilePath;
                    string filePath = enterFilePath + fileNameStringVector[i];
                    fileManager.loadCSVFile(filePath, textEditor, password, secure);
                    enter = false;
                    isTextFileOpen = true;
                }
                if (type[i].find("App") != string::npos)
                {
                    enterFilePath = enterFilePath;
                    wstring comm = L"" + enterFilePath + fileNameStringVector[i] + L" > NUL 2>&1";

                    //CREATING A NEW PROCCESS TO HANDLE THE EXECUTABLES
                    // Set up the STARTUPINFO structure to specify redirection
                    STARTUPINFO startupInfo = { sizeof(startupInfo) };
                    startupInfo.dwFlags = STARTF_USESHOWWINDOW;

                    // Create a PROCESS_INFORMATION structure to receive information about the new process
                    PROCESS_INFORMATION processInfo;

                    // Use CreateProcess to launch the .exe with the specified redirection and options
                    if (CreateProcess(NULL, &comm[0], NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
                        // Close the handles to the new process and thread to avoid resource leaks
                        CloseHandle(processInfo.hProcess);
                        CloseHandle(processInfo.hThread);
                    }

                    enter = false;
                    scrollCounter = 0;
                    isTextFileOpen = false;

                    string filePath = enterFilePath + fileNameStringVector[i];
                    fileManager.loadTextFile(filePath, textEditor, password, secure);
                }
            }
        }

        //INIT FILE PROPERTIES
        for (int i = 0; i < icons.size(); i++)
        {
            string fileType = availablePathsText_a[i].getString();
            size_t foundEXE = fileType.find(".exe");
            size_t foundLNK = fileType.find(".lnk");
            size_t foundWAV = fileType.find(".wav");
            size_t foundMP3 = fileType.find(".mp3");
            size_t foundTXT = fileType.find(".txt");
            size_t foundHTML = fileType.find(".html");
            size_t foundCSS = fileType.find(".css");
            size_t foundMP4 = fileType.find(".mp4");
            size_t foundPNG = fileType.find(".png");
            size_t foundJPG = fileType.find(".jpg");
            size_t foundURL = fileType.find(".url");
            size_t foundCSV = fileType.find(".csv");

            if (availablePathsText_a[i].getString() == "..")
                icons[i].icon.setTexture(icon.returnIcontexture);
            else if (foundWAV != string::npos || foundMP3 != string::npos)
                icons[i].icon.setTexture(icon.musicIcontexture);
            else if (foundEXE != string::npos || foundLNK != string::npos)
                icons[i].icon.setTexture(icon.exeIcontexture);
            else if (foundURL != string::npos || foundLNK != string::npos)
                icons[i].icon.setTexture(icon.exeIcontexture);
            else if (foundTXT != string::npos || foundHTML != string::npos || foundCSS != string::npos)
                icons[i].icon.setTexture(icon.txtIcontexture);
            else if (foundCSV != string::npos)
                icons[i].icon.setTexture(icon.csvIcontexture);
            else if (foundMP4 != string::npos)
                icons[i].icon.setTexture(icon.mp4Icontexture);
            else if (foundPNG != string::npos || foundJPG != string::npos)
                icons[i].icon.setTexture(icon.pngIcontexture);
            else
                icons[i].icon.setTexture(icon.folderIocnTexture);

            icons[i].icon.setScale(0.12, 0.12);
            icons[i].icon.setPosition(30, 375 + (i * 36) + scrollCounter);
        }

        //INIT FILE COUNT
        fileCountText.setString("Files: " + to_string(fileCount));
    }
}

void LocatePath::showFiles(RenderWindow& window, FileIcon& icon, vector<FileIcon>& icons, CursorSprite& mc, int& state)
{
    if (state == 2 && window.hasFocus() == true)
    {
        //window.draw(itemView);
        itemView.setSize(Vector2f(270, window.getSize().y - 560));
        fileCountText.setPosition(10, window.getSize().y - 150);
        for (int i = 0; i < availablePathsText.size(); i++)
        {
            if (sel[i].getGlobalBounds().intersects(itemView.getGlobalBounds()))
            {
                if (mc.cursor.getGlobalBounds().intersects(sel[i].getGlobalBounds()))
                    window.draw(sel[i]);
                for (int r = 0; r < revealDelayClock.size(); r++)
                    if (revealDelayClock[r].getElapsedTime().asSeconds() > 0.05 * i)
                    {
                        window.draw(availablePathsText[i]);
                        break;
                    }
            }
            for (int r = 0; r < revealDelayClock.size(); r++)
            {
                if (sel[i].getGlobalBounds().intersects(itemView.getGlobalBounds()))
                    if (revealDelayClock[r].getElapsedTime().asSeconds() > 0.05 * i && i < icons.size())
                    {
                        window.draw(icons[i].icon);
                        break;
                    }
            }
        }
        window.draw(fileCountText);
    }
}