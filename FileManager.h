#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <cryptlib.h>
#include <pwdbased.h>
#include <secblock.h>
#include <sha.h>
#include "TextEditor.h"
#include "Secure.h"
#include "CursorSprite.h"

#pragma warning(disable : 4996)

using namespace std;

class FileManager
{
private:

public:
    bool saveFile = false;
    bool saveRawFile = false;
    string setFilePath;

    FileManager();
    void getFilePath(string& filePath);
    void loadStageInfo(int& state);
    void saveLoginInfo(int stage, string password, Secure& secure);
    void loadLoginInfo(string& password, string& getPassword, Secure& secure);
    void saveTextFile(TextEditor& textEditor, string key, Secure& secure, CursorSprite& c);
    void loadTextFile(string& filePath, TextEditor& textEditor, string key, Secure& secure);
    void saveCSVFile(TextEditor& textEditor, string key, Secure& secure, CursorSprite& c);
    void loadCSVFile(string& filePath, TextEditor& textEditor, string key, Secure& secure);
    void saveAutoLockPferences(int& AFKTimerCount);
    void loadAutoLockPferences(int& AFKTimerCount);
    void saveClipboardTimePferences(int& clipboardEraceTime);
    void loadClipboardTimePferences(int& clipboardEraceTime);
    void exportRawTXT(string& filePath, string& plainText, string& fileNameString);
    void exportEncryptedTXT(string& filePath, TextEditor& textEditor, string key, Secure& secure, CursorSprite& c, string& fileNameString);
};

