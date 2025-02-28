#include "FileManager.h"

FileManager::FileManager()
{

}

string generateGrade(const string& password) {
    string salt = "thisisauniquesalt"; // Change this per user/system

    SecByteBlock derivedKey(32);

    PKCS5_PBKDF2_HMAC<SHA256> pbkdf2;
    pbkdf2.DeriveKey(derivedKey, derivedKey.size(), 0, reinterpret_cast<const byte*>(password.data()), password.size(), reinterpret_cast<const byte*>(salt.data()), salt.size(), 100000);

    return string(reinterpret_cast<const char*>(derivedKey.data()), derivedKey.size());
}

void FileManager::loadStageInfo(int& stage)
{
    string line;
    ifstream textStream("src/Saves/saveStage.txt");
    while (getline(textStream, line))
    {
        rsize_t foundstage = line.find("Stage: ");
        if (foundstage != string::npos)
        {
            string result = line.substr(foundstage + 7);
            stage = stoi(result);
        }
    }
}

void FileManager::getFilePath(string& filePath)
{
    setFilePath = filePath;
}

void FileManager::saveLoginInfo(int stage, string password, Secure& secure)
{
    string plaintext = "\nPassword: " + password;
    string encryptedText, cipherText;

    string grade = generateGrade(password);

    secure.AES_Encrypt(plaintext, encryptedText, cipherText, grade);

    ofstream saveLoginInfo;
    saveLoginInfo.open("src/Saves/loginInfo.txt");
    saveLoginInfo.clear();
    saveLoginInfo << encryptedText << endl;
    saveLoginInfo.close();
    ofstream saveStage;
    saveStage.open("src/Saves/saveStage.txt");
    saveStage.clear();
    saveStage << "Stage: " + to_string(stage) << endl;
    saveStage.close();
}
void FileManager::loadLoginInfo(string& password, string& getPassword, Secure& secure)
{
    string plainText, decryptedText, cipherText;
    string line;
    ifstream readFile("src/Saves/loginInfo.txt");
    while (getline(readFile, line)) {
        plainText += line;
        if (line.find("\n") && string::npos)
            plainText += "\n";
    }
    readFile.close();

    string grade = generateGrade(password);

    secure.AES_Decrypt(plainText, decryptedText, cipherText, grade);

    string line2;
    istringstream textStream(decryptedText);
    while (getline(textStream, line2))
    {
        rsize_t foundPass = line2.find("Password: ");
        if (foundPass != string::npos)
        {
            string result = line2.substr(foundPass + 10);
            getPassword = result;
            cout << "Found " << getPassword << endl;
        }
    }
}

void FileManager::saveTextFile(TextEditor& textEditor, string key, Secure& secure, CursorSprite& c)
{
    if (saveFile == true)
    {
        string plaintext = textEditor.myText;
        string encryptedText, cipherText;

        secure.AES_Encrypt(plaintext, encryptedText, cipherText, key);
        cout << encryptedText << endl;

        ofstream saveTextFile;
        if (setFilePath.substr(setFilePath.size() - 4) == ".csv")
        {
            cout << "FOUND CSV" << endl;
            setFilePath.replace(setFilePath.size() - 3, 3, "txt");
        }
        saveTextFile.open(setFilePath);
        cout << "Saved at: " << setFilePath << endl;
        saveTextFile.clear();
        saveTextFile << encryptedText << endl;
        saveTextFile.close();
        saveFile = false;
    }
}
void FileManager::loadTextFile(string& filePath, TextEditor& textEditor, string key, Secure& secure)
{
    string line;
    string plainText, decryptedText, cipherText;
    ifstream readFile(filePath);
    while (getline(readFile, line)) 
    {
        plainText += line;
        if (line.find("\n") && string::npos)
            plainText += "\n";
    }
    cout << plainText << endl;
    readFile.close();
    getFilePath(filePath);
    cout << "Opening file: " << filePath << endl;

    secure.AES_Decrypt(plainText, decryptedText, cipherText, key);

    const char* cstr = decryptedText.c_str();
    strcpy(textEditor.myText, cstr);
}

void FileManager::loadCSVFile(string& filePath, TextEditor& textEditor, string key, Secure& secure)
{
    string line;
    string plainText;
    ifstream readFile(filePath);
    while (getline(readFile, line))
    {
        plainText += line;
        if (line.find("note") != string::npos)
        {
            plainText += "\n";
            for (int i = 0; i < line.size(); i++)
                plainText += "#";
            plainText += "\n\n";
        }
        else if (line.find(",") != string::npos)
        {
            plainText += "\n";
            for (int i = 0; i < line.size(); i++)
                plainText += "_";
            plainText += "\n\n";
        }
    }
    cout << plainText << endl;
    readFile.close();
    getFilePath(filePath);
    cout << "Opening file: " << filePath << endl;

    const char* cstr = plainText.c_str();
    strcpy(textEditor.myText, cstr);
}

void FileManager::saveAutoLockPferences(int& AFKTimerCount)
{
    ofstream saveOptionPreferencesFile("src/Saves/AFKTimerPreferences.txt");
    saveOptionPreferencesFile << "App lock (min): " << AFKTimerCount << endl;
    saveOptionPreferencesFile.close();
}
void FileManager::loadAutoLockPferences(int& AFKTimerCount)
{
    ifstream loadOptionPreferencesFile("src/Saves/AFKTimerPreferences.txt");
    string line;

    while (getline(loadOptionPreferencesFile, line))
    {
        rsize_t foundPreference = line.find("App lock (min): ");
        if (foundPreference != string::npos)
        {
            AFKTimerCount = stoi(line.substr(foundPreference + 16));
            cout << "App lock (min): " << AFKTimerCount << endl;
        }
    }
}

void FileManager::saveClipboardTimePferences(int& clipboardEraceTime)
{
    ofstream saveOptionPreferencesFile("src/Saves/ClipboardTimePreferences.txt");
    saveOptionPreferencesFile << "Clipboard erase time (sec): " << clipboardEraceTime << endl;
    saveOptionPreferencesFile.close();
}
void FileManager::loadClipboardTimePferences(int& clipboardEraceTime)
{
    ifstream loadOptionPreferencesFile("src/Saves/ClipboardTimePreferences.txt");
    string line;

    while (getline(loadOptionPreferencesFile, line))
    {
        rsize_t foundPreference = line.find("Clipboard erase time (sec): ");
        if (foundPreference != string::npos)
        {
            clipboardEraceTime = stoi(line.substr(foundPreference + 28));
            cout << "Clipboard erase time (sec): " << clipboardEraceTime << endl;
        }
    }
}

void FileManager::exportRawTXT(string& filePath, string& plainText, string& fileNameString)
{
    if (saveRawFile == true)
    {
        ofstream saveTextFile;
        if (filePath.back() == '\\')
            filePath += fileNameString;
        saveTextFile.open(filePath.insert(filePath.size() - 4, "_Export"));
        cout << "Saved at: " << filePath << endl;
        saveTextFile.clear();
        saveTextFile << plainText << endl;
        saveTextFile.close();
        filePath = filePath.substr(0, filePath.size() - (fileNameString.size() + 7));
        saveRawFile = false;
    }
}

void FileManager::exportEncryptedTXT(string& filePath, TextEditor& textEditor, string key, Secure& secure, CursorSprite& c, string& fileNameString)
{
    if (saveFile == true)
    {
        string plaintext = textEditor.myText;
        string encryptedText, cipherText;

        secure.AES_Encrypt(plaintext, encryptedText, cipherText, key);

        ofstream saveTextFile;
        if (filePath.back() == '\\')
            filePath += fileNameString;
        saveTextFile.open(filePath.insert(filePath.size() - 4, "_Export"));
        cout << "Saved at: " << filePath << endl;
        saveTextFile.clear();
        saveTextFile << encryptedText << endl;
        saveTextFile.close();
        filePath = filePath.substr(0, filePath.size() - (fileNameString.size() + 7));
        saveRawFile = false;
    }
}