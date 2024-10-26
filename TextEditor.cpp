#include "TextEditor.h"

//RE DEFINE STATIC VARS
char TextEditor::myText[textSize];

TextEditor::TextEditor()
{
    srand(time(0));
    rec.setSize(Vector2f(300, 60));
    selectRec.setSize(Vector2f(300, 30));
    selectRec.setFillColor(Color(153, 194, 210));
    font.loadFromFile("src/Fonts/consolas.ttf");

    generatePassText.setFont(font);
    generatePassText.setCharacterSize(20);
    generatePassText.setString("Generate random password");
    generatePassText.setFillColor(Color::Black);

    buttonTexture.loadFromFile("src/Textures/exitButton.png");
    buttonTexture.setSmooth(true);
    exitButton.setTexture(buttonTexture);
    exitButton.setScale(0.1, 0.1);
}

void TextEditor::setTypingStae(bool& isTyping)
{
    isTyping = getIsTyping;
}

void TextEditor::getKeyboardInputIdicator(Event& eve, RenderWindow& window)
{
    if (eve.type == Event::KeyPressed && window.hasFocus())
        getIsTyping = true;
    else if (eve.type == Event::KeyReleased && window.hasFocus())
        getIsTyping = false;
    else if (window.hasFocus() == false)
        getIsTyping = false;
}

int LineTextCallback(ImGuiInputTextCallbackData* data)
{
    TextEditor* editor = static_cast<TextEditor*>(ImGui::GetIO().UserData);
    if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit)
    {
        data->Buf[--data->BufTextLen] = '\0';
        if (/*(ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)) || editor->size_a == 0) ||*/ editor->gen == 1)
        {
            char sizeStr[64];
            if (editor->gen == 1)
            {
                string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+~";
                string pass;
                for (int i = 0; i < 16; i++)
                {
                    int pos = rand() % 75;
                    pass += characters[pos];
                }
                sprintf(sizeStr, "%s  ", pass.c_str());
                editor->gen = 0;
            }
            /*if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)) || editor->size_a == 0)
                sprintf(sizeStr, "\n%d  ", editor->size_a);*/
            int newSize = strlen(data->Buf) + strlen(sizeStr) + 1;
            if (newSize < data->BufSize)
            {
                strcat(data->Buf, sizeStr);
                data->BufTextLen = strlen(data->Buf);
                data->CursorPos = data->BufTextLen;
                data->BufDirty = true;
            }
        }
    }
    return 0;
}

void TextEditor::mainLogic(int state, bool& isTextFileOpen, ImGuiIO& io, RenderWindow& window, string& fileNameString, CursorSprite& mc, bool& isPasswordGenOpen, bool& isExportOpen)
{
    if (state == 2 && isTextFileOpen == true && window.hasFocus() == true && editText == true)
    {
        isPasswordGenOpen = false;
        exitButton.setPosition(window.getSize().x - 35, 37);
        if (mc.cursor.getGlobalBounds().intersects(exitButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
            isTextFileOpen = false;

        if (Keyboard::isKeyPressed(Keyboard::LControl) && delayClock.getElapsedTime().asSeconds() > 0.3)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                fontSize = fontSize + 0.005;
                delayClock.restart();
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                fontSize = fontSize - 0.005;
                delayClock.restart();
            }
        }
        area.setSize(Vector2f(ImVec2(window.getSize().x - (280 + 0), window.getSize().y + 3 + (-35 * fontSize))));
        area.setPosition(ImVec2(280 + 0, -(-35 * fontSize) - 5));
        io.FontGlobalScale = fontSize;
        io.UserData = static_cast<void*>(this);
        ImGui::Begin(fileNameString.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(280 + 0, -(-35 * fontSize) - 5));
        ImGui::SetWindowSize(ImVec2(window.getSize().x - (280 + 0), window.getSize().y + 3 + (-35 * fontSize)));
        ImGui::SetWindowFocus();
        ImGui::InputTextMultiline("##input", myText, sizeof(myText), ImVec2(-1, -1), ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackEdit, LineTextCallback);
        ImGui::End();
    }
}

void TextEditor::popupWindow(int state, CursorSprite& mc, ImGuiIO& io, RenderWindow& window)
{
    if (state == 2 && window.hasFocus() == true)
    {
        generatePassText.setPosition(rec.getPosition().x + 10, rec.getPosition().y);
        if (Mouse::isButtonPressed(Mouse::Right))
            rec.setPosition(mc.cursor.getPosition());
        if (!mc.cursor.getGlobalBounds().intersects(rec.getGlobalBounds()))
            rec.setPosition(99999, 99999);
        if (mc.cursor.getGlobalBounds().intersects(generatePassText.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        {
            gen = true;
            io.AddInputCharactersUTF8(" ");
            rec.setPosition(99999, 99999);
        }
        if (mc.cursor.getGlobalBounds().intersects(generatePassText.getGlobalBounds()))
            selectRec.setPosition(rec.getPosition().x, rec.getPosition().y);
        else
            selectRec.setPosition(99999, 99999);
    }
}

void TextEditor::lineCounter(int& state, bool& isTextFileOpen, RenderWindow& window)
{
    if (state == 2 && isTextFileOpen == true && window.hasFocus() == true)
    {
        //cout << "Lines found: " << size_a << endl;
        flag = 0;
        size_a = 0;
        for (int i = 0; i < strlen(myText) && flag == 0; i++)
        {
            if (myText[i] == '\n')
                size_a++;
            if (i == strlen(myText) - 1)
            {
                flag = 1;
            }
        }
    }
}

void TextEditor::draw(RenderWindow& window, int& state, bool& isTextFileOpen)
{
    if (state == 2 && window.hasFocus() == true)
    {
        window.draw(rec);
        window.draw(selectRec);
        window.draw(generatePassText);
        if (isTextFileOpen == true)
            window.draw(exitButton);
    }
}