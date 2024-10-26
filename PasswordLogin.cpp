#include "PasswordLogin.h"

PasswordLogin::PasswordLogin()
{
    formTexture.loadFromFile("src/Textures/form.png");
    formTexture2.loadFromFile("src/Textures/form2.png");
    menuTexture.loadFromFile("src/Textures/passMenu2.png");
    formSprite.setTexture(formTexture2);
    formSprite.setScale(0.2, 0.2);
    menuSprite.setTexture(menuTexture);
    menuSprite.setScale(0.5, 0.5);

    font.loadFromFile("src/Fonts/thick3.ttf");
    welcomeText.setFont(font);
    welcomeText.setString("Welcome!");
    infoText.setFont(font);
    infoText.setString("Please enter your password below:");
    infoText.setCharacterSize(15);
    advanceText.setFont(font);
    advanceText.setString("Advance");
    advanceText.setCharacterSize(20);
    passwordText.setFont(font);
    passwordText.setCharacterSize(20);
}

void PasswordLogin::getStateInfo(int state)
{
    getState = state;
}

void PasswordLogin::typeEvent(RenderWindow& window, Event& event)
{
    if (getState == 1 && window.hasFocus() == true)
    {
        if (isSelected == true)
        {
            if (event.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Enter))
            {
                passwordString += event.text.unicode;
                hiddenPasswordString += "*";
            }
            else if (event.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Enter))
            {
                passwordString = passwordString.substr(0, passwordString.size() - 1);
                hiddenPasswordString = hiddenPasswordString.substr(0, hiddenPasswordString.size() - 1);
            }
            passwordText.setString(hiddenPasswordString + "_");
        }
    }
}

void PasswordLogin::logic(RenderWindow& window, CursorSprite& cursor, FileManager& fileManager, int& state, bool& init, Secure& secure, string& password, Clock& AFK_Clock)
{
    if (getState == 1 && window.hasFocus() == true)
    {
        formSprite.setPosition(window.getSize().x / 2 - 220, window.getSize().y / 2);
        menuSprite.setPosition(window.getSize().x / 2 - 260, window.getSize().y / 2 - 130);
        welcomeText.setPosition(window.getSize().x / 2 - 220, window.getSize().y / 2 - 100);
        infoText.setPosition(window.getSize().x / 2 - 220, window.getSize().y / 2 - 60);
        passwordText.setPosition(window.getSize().x / 2 - 205, window.getSize().y / 2 + 15);

        if (cursor.buildCursor.getGlobalBounds().intersects(formSprite.getGlobalBounds()))
        {
            formSprite.setTexture(formTexture);
            isSelected = true;
        }
        else
        {
            formSprite.setTexture(formTexture2);
            isSelected = false;
        }

        if (cursor.cursor.getGlobalBounds().intersects(advanceText.getGlobalBounds()))
        {
            advanceText.setString("> Advance <");
            advanceText.setPosition(window.getSize().x / 2 - 45, window.getSize().y / 2 + 100);
        }
        else
        {
            advanceText.setString("Advance");
            advanceText.setPosition(window.getSize().x / 2 - 30, window.getSize().y / 2 + 100);
        }
        cout << passwordString << endl;
        if (cursor.buildCursor.getGlobalBounds().intersects(advanceText.getGlobalBounds()) ||
            Keyboard::isKeyPressed(Keyboard::Enter))
        {
            //LOAD SETTINGS AND PARAMENTERS
            fileManager.loadLoginInfo(passwordString, getPassword, secure);

            if (passwordString == getPassword)
            {
                AFK_Clock.restart();
                password = passwordString;
                init = true;
                state = 2;
            }
        }
    }
}

void PasswordLogin::draw(RenderWindow& window)
{
    if (getState == 1 && window.hasFocus() == true)
    {
        window.draw(menuSprite);
        window.draw(formSprite);
        window.draw(welcomeText);
        window.draw(infoText);
        window.draw(advanceText);
        window.draw(passwordText);
    }
}