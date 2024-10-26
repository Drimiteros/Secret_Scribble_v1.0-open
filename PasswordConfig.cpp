#include "PasswordConfig.h"

PasswordConfig::PasswordConfig()
{
    font.loadFromFile("src/Fonts/consolas.ttf");
    font2.loadFromFile("src/Fonts/thick3.ttf");
    for (int i = 0; i < textCount; i++)
    {
        if (i == 3)
        {
            text[i].setFillColor(Color(225, 225, 225, 150));
            text[i].setFont(font);
            text[i].setScale(1, 1);
            text[i].setCharacterSize(18);
        }
        else if (i == 4)
        {
            text[i].setFillColor(Color::White);
            text[i].setFont(font2);
            text[i].setScale(1, 1);
            text[i].setCharacterSize(18);
        }
        else
        {
            text[i].setFillColor(Color::White);
            text[i].setFont(font);
            text[i].setScale(1, 1);
            text[i].setCharacterSize(18);
        }
    }
    text[passwordText].setString("Enter Password: ");
    text[passwordText].setPosition(1280 / 2 - 210, 720 / 2 - 80);
    text[passwordConfirmText].setString("Confirm Password: ");
    text[passwordConfirmText].setPosition(1280 / 2 - 210, 720 / 2 + 20);
    text[advanceText].setString("Advance");
    text[advanceText].setPosition(1280 / 2 - 30, 720 / 2 + 120);
    text[passwordPowerText].setString("Password power: ");
    text[passwordPowerText].setPosition(15, 15);
    text[guideText].setString("Wellcome to Secret Scribble!");
    text[guideText_a].setString("To ensure the highest level of security, our\napplication employs the robust AES encryption\nalgorithm for both encryption and decryption\nprocesses. To utilize this feature, you must\nset a password with a length of 16, 24, or 32\ncharacters. If you forget this password, there\nwill be no way to access / recover your data.\nFor security purposes, your wireless internet\nadapter is disabled when you enter a password.");

    texture[menuBoxTexture].loadFromFile("src/Textures/passMenu.png");
    sprite[menuBoxSprite].setTexture(texture[menuBoxTexture]);
    sprite[menuBoxSprite].setScale(0.5, 0.5);
    sprite[menuBoxSprite].setPosition(1280 / 2 - 260, 720 / 2 - 130);

    texture[formTexture].loadFromFile("src/Textures/form.png");
    texture[formTexture2].loadFromFile("src/Textures/form2.png");
    for (int i = 1; i < 3; i++)
    {
        sprite[i].setTexture(texture[formTexture2]);
        sprite[i].setScale(0.2, 0.2);
    }
    sprite[formSprite].setPosition(1280 / 2 - 220, 720 / 2 - 50);
    sprite[formSprite2].setPosition(1280 / 2 - 220, 720 / 2 + 50);

    texture[eyeTexture].loadFromFile("src/Textures/eye.png");
    sprite[eyeSprite].setTexture(texture[eyeTexture]);
    sprite[eyeSprite].setScale(0.2, 0.2);
    sprite[eyeSprite].setTextureRect(IntRect(0, 0, 114, 144));
    sprite[eyeSprite].setPosition(1280 / 2 + 290, 720 / 2 - 85);
    sprite[eyeSprite_a].setTexture(texture[eyeTexture]);
    sprite[eyeSprite_a].setScale(0.2, 0.2);
    sprite[eyeSprite_a].setTextureRect(IntRect(0, 0, 114, 144));
    sprite[eyeSprite_a].setPosition(1280 / 2 + 290, 720 / 2 + 15);
}

void PasswordConfig::typeEvent(RenderWindow& window, Event& eve, int state)
{
    if (state == 0 && window.hasFocus() == true)
    {
        if (isPasswordSelected == true)
        {
            sprite[formSprite].setTexture(texture[formTexture]);
            sprite[formSprite2].setTexture(texture[formTexture2]);
            if (eve.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Space)
                && !Keyboard::isKeyPressed(Keyboard::Enter))
            {
                password += eve.text.unicode;
                hiddenPass.append("*");
            }
            else if (eve.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Space)
                && !Keyboard::isKeyPressed(Keyboard::Enter))
            {
                password = password.substr(0, password.size() - 1);
                hiddenPass = hiddenPass.substr(0, hiddenPass.size() - 1);
            }
        }
        else if (isConfirmPasswordSelected == true)
        {
            sprite[formSprite2].setTexture(texture[formTexture]);
            sprite[formSprite].setTexture(texture[formTexture2]);
            if (eve.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Space)
                && !Keyboard::isKeyPressed(Keyboard::Enter))
            {
                confirmPassword += eve.text.unicode;
                confirmHiddenPass.append("*");
            }
            else if (eve.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::BackSpace) && !Keyboard::isKeyPressed(Keyboard::Space)
                && !Keyboard::isKeyPressed(Keyboard::Enter))
            {
                confirmPassword = confirmPassword.substr(0, confirmPassword.size() - 1);
                confirmHiddenPass = confirmHiddenPass.substr(0, confirmHiddenPass.size() - 1);
            }
        }
        if (isHidden == false)
            text[passwordText].setString("Enter Password: \n\n " + password + "_");
        else
            text[passwordText].setString("Enter Password: \n\n " + hiddenPass + "_");
        if (isHidden_a == false)
            text[passwordConfirmText].setString("Confirm Password: \n\n " + confirmPassword + "_");
        else
            text[passwordConfirmText].setString("Confirm Password: \n\n " + confirmHiddenPass + "_");
    }
}

void PasswordConfig::mainLogic(CursorSprite& c, RenderWindow& window, FileManager& fm, int& state, string& get_password, 
    Secure& secure)
{
    if (state == 0 && window.hasFocus() == true)
    {
        //UPDATE POSITION OF ELEMENTS
        text[passwordText].setPosition(window.getSize().x / 2 + 40, window.getSize().y / 2 - 130);
        text[passwordConfirmText].setPosition(window.getSize().x / 2 + 40, window.getSize().y / 2 - 30);
        text[guideText].setPosition(window.getSize().x / 2 - 510 + 40, window.getSize().y / 2 - 145);
        text[guideText_a].setPosition(window.getSize().x / 2 - 510 + 40, window.getSize().y / 2 - 105);
        sprite[menuBoxSprite].setPosition(window.getSize().x / 2 - 560 + 40, window.getSize().y / 2 - 180);
        sprite[formSprite].setPosition(window.getSize().x / 2 - 20 + 40, window.getSize().y / 2 - 100);
        sprite[formSprite2].setPosition(window.getSize().x / 2 - 20 + 40, window.getSize().y / 2);
        sprite[eyeSprite].setPosition(window.getSize().x / 2 + 440, window.getSize().y / 2 - 85);
        sprite[eyeSprite_a].setPosition(window.getSize().x / 2 + 440, window.getSize().y / 2 + 15);
        if (c.cursor.getGlobalBounds().intersects(text[advanceText].getGlobalBounds()))
            text[advanceText].setPosition(window.getSize().x / 2 + 170 + 40, window.getSize().y / 2 + 80);
        else
            text[advanceText].setPosition(window.getSize().x / 2 + 190 + 40, window.getSize().y / 2 + 80);

        //SELECT TEXT TO EDIT
        if (c.buildCursor.getGlobalBounds().intersects(sprite[formSprite].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        {
            isPasswordSelected = true;
            isConfirmPasswordSelected = false;
        }
        else if (c.buildCursor.getGlobalBounds().intersects(sprite[formSprite2].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        {
            isPasswordSelected = false;
            isConfirmPasswordSelected = true;
        }

        //CLCULATE PASSWORD POWER
        int passPower = 0;
        if (password.size() > 4)
        {
            passPower++;
            for (char p : password)
                if (islower(p))
                {
                    passPower++;
                    break;
                }
            for (char p : password)
                if (isupper(p))
                {
                    passPower++;
                    break;
                }
            for (char p : password)
                if (isdigit(p))
                {
                    passPower++;
                    break;
                }
            for (char p : password)
                if (ispunct(p))
                {
                    passPower++;
                    break;
                }
        }
        for (int i = 0; i < passPower + 1; i++)
        {
            if (i <= 1)
                passwordPower = "Weak";
            else if (i == 2)
                passwordPower = "Medium";
            else if (i == 3)
                passwordPower = "Good";
            else if (i == 4)
                passwordPower = "Strong";
            else if (i >= 5)
                passwordPower = "Very Strong";
        }
        WCHAR language[KL_NAMELENGTH];
        if (GetKeyboardLayoutName(language))
        {
            if (wcsstr(language, L"00000409") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Eng");
            else if (wcsstr(language, L"00000408") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Gre");
            else if (wcsstr(language, L"00000407") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Ger");
            else if (wcsstr(language, L"00000410") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Ita");
            else if (wcsstr(language, L"0000040C") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Fre");
            else if (wcsstr(language, L"00000C0A") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Spa");
            else if (wcsstr(language, L"0000041F") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Tur");
            else if (wcsstr(language, L"00000419") != nullptr)
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Rus");
            else
                text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Failed to identify...");
        }
        else
            text[passwordPowerText].setString("Password power: " + passwordPower + "\nLanguage: Failed to find...");

        //ADVANCE TO LOGIN STAGE
        if (c.cursor.getGlobalBounds().intersects(text[advanceText].getGlobalBounds()))
            text[advanceText].setString("> Advance <");
        else
            text[advanceText].setString("Advance");
        if ((c.cursor.getGlobalBounds().intersects(text[advanceText].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) 
            || Keyboard::isKeyPressed(Keyboard::Enter)) && password == confirmPassword 
            && (password.size() == 16 || password.size() == 24 || password.size() == 32))
        {
            state = 1;
            get_password = password;
            fm.saveLoginInfo(state, password, secure);
        }

        if (c.cursor.getGlobalBounds().intersects(sprite[eyeSprite].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) &&
            isHidden == false && hideButtonCoolDown.getElapsedTime().asSeconds() > 0.3)
        {
            isHidden = true;
            hideButtonCoolDown.restart();
            sprite[eyeSprite].setTextureRect(IntRect(0, 0, 114, 144));
        }
        if (c.cursor.getGlobalBounds().intersects(sprite[eyeSprite].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) &&
            isHidden == true && hideButtonCoolDown.getElapsedTime().asSeconds() > 0.3)
        {
            isHidden = false;
            hideButtonCoolDown.restart();
            sprite[eyeSprite].setTextureRect(IntRect(114, 0, 114, 144));
        }
        if (c.cursor.getGlobalBounds().intersects(sprite[eyeSprite_a].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) &&
            isHidden_a == false && hideButtonCoolDown.getElapsedTime().asSeconds() > 0.3)
        {
            isHidden_a = true;
            hideButtonCoolDown.restart();
            sprite[eyeSprite_a].setTextureRect(IntRect(0, 0, 114, 144));
        }
        if (c.cursor.getGlobalBounds().intersects(sprite[eyeSprite_a].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) &&
            isHidden_a == true && hideButtonCoolDown.getElapsedTime().asSeconds() > 0.3)
        {
            isHidden_a = false;
            hideButtonCoolDown.restart();
            sprite[eyeSprite_a].setTextureRect(IntRect(114, 0, 114, 144));
        }
    }
}

void PasswordConfig::draw(RenderWindow& window, int state)
{
    if (state == 0 && window.hasFocus() == true)
    {
        for (int i = 0; i < spriteCount; i++)
            window.draw(sprite[i]);
        for (int i = 0; i < textCount; i++)
            window.draw(text[i]);
    }
}