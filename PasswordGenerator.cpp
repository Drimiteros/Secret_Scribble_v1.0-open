#include "PasswordGenerator.h"

PasswordGenerator::PasswordGenerator()
{
	iconTexture.loadFromFile("src/Textures/passwordGen.png");
	toolSelTexture.loadFromFile("src/Textures/toolsSel.png");
	regeneratePassTexture.loadFromFile("src/Textures/regenerate.png");
	exitButtonTexture.loadFromFile("src/Textures/exitButton.png");
	copyPassTexture.loadFromFile("src/Textures/copy.png");
	backgroundTexture.loadFromFile("src/Textures/optionsMenu.png");
	timerCountArrowTexture.loadFromFile("src/Textures/arrow2.png");
	checkboxTexture.loadFromFile("src/Textures/checkbox.png");
	iconSprite.setTexture(iconTexture);
	iconSprite.setScale(0.2, 0.2);
	toolSelectSprite.setTexture(toolSelTexture);
	toolSelectSprite.setScale(0.2, 0.2);
	regeneratePassSprite.setTexture(regeneratePassTexture);
	regeneratePassSprite.setScale(0.2, 0.2);
	regeneratePassSprite.setOrigin(158, 158);
	copyPassSprite.setTexture(copyPassTexture);
	copyPassSprite.setScale(0.2, 0.2);
	copyPassSprite.setOrigin(158, 158);
	exitButton.setTexture(exitButtonTexture);
	exitButton.setScale(0.2, 0.2);
	for (int i = 0; i < 4; i++)
		backGroundSprite[i].setTexture(backgroundTexture);
	timerCountArrow[0].setTexture(timerCountArrowTexture);
	timerCountArrow[0].setTextureRect(IntRect(0, 0, 174, 174));
	timerCountArrow[0].setScale(0.2, 0.2);
	timerCountArrow[1].setTexture(timerCountArrowTexture);
	timerCountArrow[1].setTextureRect(IntRect(175, 0, 174, 174));
	timerCountArrow[1].setScale(0.2, 0.2);
	for (int i = 0; i < 3; i++)
	{
		checkBox[i].setTexture(checkboxTexture);
		checkBox[i].setScale(0.15, 0.15);
	}
	background.setFillColor(Color(38, 52, 57));

	font.loadFromFile("src/Fonts/thick3.ttf");
	logoText.setFont(font);
	logoText.setString("Password Generator");
	logoText.setFillColor(Color(255, 255, 255, 200));
	logoText.setCharacterSize(15);
	menuLogoText.setFont(font);
	menuLogoText.setString("Password Generator");
	menuLogoText.setFillColor(Color::White);
	menuLogoText.setCharacterSize(30);
	menuLogoText.setOrigin(menuLogoText.getGlobalBounds().getSize().x / 2, 0);
	passwordText.setFont(font);
	passwordText.setFillColor(Color(26, 188, 156, 255));
	passwordText.setCharacterSize(30);
	passwordSizeText.setFont(font);
	passwordSizeText.setFillColor(Color::White);
	passwordSizeText.setCharacterSize(30);
	passwordSizeText2.setFont(font);
	passwordSizeText2.setFillColor(Color(255, 255, 255, 200));
	passwordSizeText2.setCharacterSize(20);
	passwordSizeText3.setFont(font);
	passwordSizeText3.setFillColor(Color(26, 188, 156, 200));
	passwordSizeText3.setCharacterSize(20);
	includeNumbersText.setFont(font);
	includeNumbersText.setFillColor(Color(255, 255, 255, 200));
	includeNumbersText.setCharacterSize(20);
	includeNumbersText.setString("Include Numbers");
	includeSymbolsText.setFont(font);
	includeSymbolsText.setFillColor(Color(255, 255, 255, 200));
	includeSymbolsText.setCharacterSize(20);
	includeSymbolsText.setString("Include Symbols");
	includeUpperText.setFont(font);
	includeUpperText.setFillColor(Color(255, 255, 255, 200));
	includeUpperText.setCharacterSize(20);
	includeUpperText.setString("Include Uppercase");
	passwordPreferencesText.setFont(font);
	passwordPreferencesText.setFillColor(Color::White);
	passwordPreferencesText.setCharacterSize(25);
	passwordPreferencesText.setString("Password Preferences");
	clipboardClearCounterText.setFont(font);
	clipboardClearCounterText.setFillColor(Color::White);
	clipboardClearCounterText.setCharacterSize(15);
	clipboardClearCounterText.setPosition(999999, 999999);
	clipboardClearCounterText.setString("Clipboard will be erased after: ");
	clipboardClearCounterText2.setFont(font);
	clipboardClearCounterText2.setFillColor(Color(26, 188, 156, 255));
	clipboardClearCounterText2.setCharacterSize(15);
	clipboardClearCounterText2.setPosition(999999, 999999);
}

void CopyTextToClipboard(const std::string& text, bool& isPasswordGenOpen)
{
	if (isPasswordGenOpen == true)
	{
		// Open the clipboard to access it
		if (!OpenClipboard(nullptr))
			return;

		// Empty the clipboard before copying new data
		EmptyClipboard();

		// Allocate global memory to hold the text
		HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
		if (!hGlob)
		{
			CloseClipboard();
			return;
		}

		// Lock the memory and copy the text into it
		char* pGlob = static_cast<char*>(GlobalLock(hGlob));
		if (pGlob)
		{
			memcpy(pGlob, text.c_str(), text.size() + 1);
			GlobalUnlock(hGlob);
		}

		// Set the clipboard data to the text we copied
		SetClipboardData(CF_TEXT, hGlob);

		// Close the clipboard
		CloseClipboard();
	}
}

void clearClipboard(const std::string& text, bool& isPasswordGenOpen)
{
	if (isPasswordGenOpen == true)
	{
		// Open the clipboard to access it
		if (!OpenClipboard(nullptr))
			return;

		// Empty the clipboard before copying new data
		EmptyClipboard();

		// Close the clipboard
		CloseClipboard();
	}
}

void PasswordGenerator::generate()
{
	string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+~";
	if (password.getSize() < passwordSize)
	{
		for (int i = 0; i < passwordSize; i++)
		{
			int pos = rand() % 75;
			if (hasUppercase == false && pos >= 26 && pos <= 51)
				i--;
			else if (hasNumbers == false && pos >= 52 && pos <= 61)
				i--;
			else if (hasSymbols == false && pos >= 62)
				i--;
			else 
				password += characters[pos];
		}
	}
}

void PasswordGenerator::menuLogic(RenderWindow& window, int& state, bool& isPasswordGenOpen, CursorSprite& mc, bool& isOptionsOpen, Clock& timeTrackClipboardDataClock, int& clipboardEraceTime, bool& isTextFileOpen, bool& isImportOpen, bool& isDonateOpen)
{
	if (state == 2 && window.hasFocus() == true)
	{
		if (mc.cursor.getGlobalBounds().intersects(toolSelectSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && clickDelayClock.getElapsedTime().asSeconds() > 0.3 && isPasswordGenOpen == false)
		{
			isTextFileOpen = false;
			isDonateOpen = false;
			isPasswordGenOpen = true;
			isOptionsOpen = false;
			isImportOpen = false;
			clickDelayClock.restart();
		}
		if (isPasswordGenOpen == true)
		{
			menuLogoText.setPosition((window.getSize().x + 280) / 2, 40);
			regeneratePassSprite.setPosition((window.getSize().x + 190) / 2, 300);
			copyPassSprite.setPosition((window.getSize().x + 370) / 2, 300);
			backGroundSprite[0].setPosition(330, 400);
			backGroundSprite[1].setPosition(920, 400);
			passwordSizeText.setPosition(360, 420);
			passwordSizeText.setString("Password Size");
			passwordSizeText2.setPosition(360, 460);
			passwordSizeText2.setString("Set the password size in letters:");
			passwordSizeText3.setPosition(360, 490);
			passwordSizeText3.setString(to_string(passwordSize) + " letters");
			timerCountArrow[0].setPosition(700, 458);
			timerCountArrow[1].setPosition(750, 458);
			passwordPreferencesText.setPosition(950, 420);
			includeNumbersText.setPosition(950, 450);
			includeSymbolsText.setPosition(950, 475);
			includeUpperText.setPosition(950, 500);
			checkBox[0].setPosition(1150, 450);
			checkBox[2].setPosition(1150, 477);
			checkBox[1].setPosition(1150, 504);
			clipboardClearCounterText.setOrigin(clipboardClearCounterText.getGlobalBounds().getSize().x / 2, 0);

			generate();
			exitButton.setPosition(window.getSize().x - 50, 40);
			passwordText.setPosition((window.getSize().x + 280) / 2, 150);
			passwordText.setOrigin(passwordText.getGlobalBounds().getSize().x / 2, 0);
			passwordText.setString(password);
			background.setSize(Vector2f(window.getSize().x - 280, 140));
			background.setPosition(280, 100);

			if (exitButton.getGlobalBounds().intersects(mc.cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isPasswordGenOpen = false;

			if (regeneratePassSprite.getGlobalBounds().intersects(mc.cursor.getGlobalBounds()))
				regeneratePassSprite.setColor(Color(255, 255, 255, 255));
			else
				regeneratePassSprite.setColor(Color(255, 255, 255, 200));
			if (regeneratePassSprite.getGlobalBounds().intersects(mc.cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				password.clear();

			if (copyPassSprite.getGlobalBounds().intersects(mc.cursor.getGlobalBounds()))
				copyPassSprite.setColor(Color(255, 255, 255, 255));
			else
				copyPassSprite.setColor(Color(255, 255, 255, 200));
			if (copyPassSprite.getGlobalBounds().intersects(mc.cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				timeTrackClipboardDataClock.restart();
				CopyTextToClipboard(password, isPasswordGenOpen);
				isCopyiedToClipboard = true;
			}

			if (mc.cursor.getGlobalBounds().intersects(timerCountArrow[0].getGlobalBounds()))
				timerCountArrow[0].setColor(Color(255, 255, 255, 255));
			else
				timerCountArrow[0].setColor(Color(255, 255, 255, 200));
			if (mc.cursor.getGlobalBounds().intersects(timerCountArrow[1].getGlobalBounds()))
				timerCountArrow[1].setColor(Color(255, 255, 255, 255));
			else
				timerCountArrow[1].setColor(Color(255, 255, 255, 200));
			if (mc.cursor.getGlobalBounds().intersects(timerCountArrow[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && clickDelayClock.getElapsedTime().asSeconds() > 0.3 && passwordSize > 0)
			{
				clickDelayClock.restart();
				passwordSize--;
			}
			if (mc.cursor.getGlobalBounds().intersects(timerCountArrow[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && clickDelayClock.getElapsedTime().asSeconds() > 0.3 && passwordSize < 60)
			{
				clickDelayClock.restart();
				passwordSize++;
			}
			for (int i = 0; i < 3; i++)
			{
				if (mc.cursor.getGlobalBounds().intersects(checkBox[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && clickDelayClock.getElapsedTime().asSeconds() > 0.3)
				{
					if (i == 0 && hasNumbers == true)
					{
						hasNumbers = false;
						clickDelayClock.restart();
					}
					else if (i == 0 && hasNumbers == false)
					{
						hasNumbers = true;
						clickDelayClock.restart();
					}
					if (i == 1 && hasUppercase == true)
					{
						hasUppercase = false;
						clickDelayClock.restart();
					}
					else if (i == 1 && hasUppercase == false)
					{
						hasUppercase = true;
						clickDelayClock.restart();
					}
					if (i == 2 && hasSymbols == true)
					{
						hasSymbols = false;
						clickDelayClock.restart();
					}
					else if (i == 2 && hasSymbols == false)
					{
						hasSymbols = true;
						clickDelayClock.restart();
					}
				}
			}
			if (hasNumbers == true)
				checkBox[0].setTextureRect(IntRect(174, 0, 174, 174));
			else
				checkBox[0].setTextureRect(IntRect(0, 0, 174, 174));
			if (hasUppercase == true)
				checkBox[1].setTextureRect(IntRect(174, 0, 174, 174));
			else
				checkBox[1].setTextureRect(IntRect(0, 0, 174, 174));
			if (hasSymbols == true)
				checkBox[2].setTextureRect(IntRect(174, 0, 174, 174));
			else
				checkBox[2].setTextureRect(IntRect(0, 0, 174, 174));
		}
		else
		{
			exitButton.setPosition(999999, 999999);
			menuLogoText.setPosition(999999, 999999);
			passwordText.setPosition(999999, 999999);
			background.setPosition(999999, 999999);
			regeneratePassSprite.setPosition(999999, 999999);
			copyPassSprite.setPosition(999999, 999999);
			backGroundSprite[0].setPosition(999999, 999999);
			backGroundSprite[1].setPosition(999999, 999999);
			passwordSizeText.setPosition(999999, 999999);
			passwordSizeText2.setPosition(999999, 999999);
			passwordSizeText3.setPosition(999999, 999999);
			timerCountArrow[0].setPosition(999999, 999999);
			timerCountArrow[1].setPosition(999999, 999999);
			includeNumbersText.setPosition(999999, 999999);
			includeSymbolsText.setPosition(999999, 999999);
			includeUpperText.setPosition(999999, 999999);
			passwordPreferencesText.setPosition(999999, 999999);
			for (int i = 0; i < 3; i++)
				checkBox[i].setPosition(999999, 999999);
		}

		if (isCopyiedToClipboard == true)
		{
			clipboardClearCounterText.setPosition((window.getSize().x + 280) / 2 - 20, 5);
			clipboardClearCounterText2.setPosition(clipboardClearCounterText.getPosition().x + clipboardClearCounterText.getGlobalBounds().getSize().x / 2, 5);
		}
		else
		{
			clipboardClearCounterText.setPosition(999999, 999999);
			clipboardClearCounterText2.setPosition(999999, 999999);
		}
		clipboardClearCounterText2.setString(to_string(int(clipboardEraceTime - timeTrackClipboardDataClock.getElapsedTime().asSeconds())) + " sec");
	}
	if (timeTrackClipboardDataClock.getElapsedTime().asSeconds() > clipboardEraceTime)
	{
		clearClipboard(password, isPasswordGenOpen);
		isCopyiedToClipboard = false;
	}
}

void PasswordGenerator::draw(RenderWindow& window, CursorSprite& mc, int& state)
{
	if (state == 2 && window.hasFocus() == true)
	{
		iconSprite.setPosition(5, window.getSize().y - 110);
		logoText.setPosition(70, window.getSize().y - 95);
		toolSelectSprite.setPosition(10, window.getSize().y - 108);
		if (mc.cursor.getGlobalBounds().intersects(toolSelectSprite.getGlobalBounds()))
			window.draw(toolSelectSprite);
		window.draw(iconSprite);
		window.draw(logoText);
		window.draw(menuLogoText);
		window.draw(background);
		window.draw(passwordText);
		window.draw(regeneratePassSprite);
		window.draw(copyPassSprite);
		window.draw(exitButton);
		window.draw(backGroundSprite[0]);
		window.draw(backGroundSprite[1]);
		window.draw(passwordSizeText);
		window.draw(passwordSizeText2);
		window.draw(passwordSizeText3);
		window.draw(timerCountArrow[0]);
		window.draw(timerCountArrow[1]);
		window.draw(includeNumbersText);
		window.draw(includeSymbolsText);
		window.draw(includeUpperText);
		window.draw(passwordPreferencesText);
		for (int i = 0; i < 3; i++)
			window.draw(checkBox[i]);
		window.draw(clipboardClearCounterText);
		window.draw(clipboardClearCounterText2);
	}
}