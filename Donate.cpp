#include "Donate.h"

Donate::Donate()
{
	iconTexture.loadFromFile("src/Textures/donate.png");
	toolSelTexture.loadFromFile("src/Textures/toolsSel.png");
	exitButtonTexture.loadFromFile("src/Textures/exitButton.png");
	donateButtonTexture.loadFromFile("src/Textures/donateButton.png");
	iconSprite.setTexture(iconTexture);
	iconSprite.setScale(0.2, 0.2);
	toolSelectSprite.setTexture(toolSelTexture);
	toolSelectSprite.setScale(0.2, 0.2);
	donateButton.setTexture(donateButtonTexture);
	donateButton.setScale(0.4, 0.4);
	donateButton.setTextureRect(IntRect(0, 0, 520, 157));
	exitButton.setTexture(exitButtonTexture);
	exitButton.setScale(0.2, 0.2);

	font.loadFromFile("src/Fonts/thick3.ttf");
	logoText.setFont(font);
	logoText.setString("Donate");
	logoText.setFillColor(Color(255, 255, 255, 200));
	logoText.setCharacterSize(15);
	menuText1.setFont(font);
	menuText1.setString("Support the developer");
	menuText1.setFillColor(Color(255, 255, 255, 255));
	menuText1.setCharacterSize(35);
	menuText2.setFont(font);
	menuText2.setString("-Thank you for considering a donation even though my services are free!\n Your support can make a real difference in helping me continue develpoing\n this software. I deeply appreciate your generosity!\n\n-Where is your money be going?\n To help me achieve my goal into creating this piece of software, alone, I will\n be needing the funds to help me cover my electricity expences from my\n computer. I also need to cover the time spent for research, development /\n manufacturin and advertising the software.");
	menuText2.setFillColor(Color(255, 255, 255, 210));
	menuText2.setCharacterSize(20);
}

void Donate::logic(RenderWindow& window, int& state, CursorSprite& mc, bool& isPasswordGenOpen, bool& isOptionsOpen, bool& isTextFileOpen, bool& isImportOpen, bool& isDonateOpen)
{
	if (state == 2 && window.hasFocus() == true)
	{
		if (mc.cursor.getGlobalBounds().intersects(toolSelectSprite.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && clickDelayClock.getElapsedTime().asSeconds() > 0.3 && isDonateOpen == false)
		{
			isTextFileOpen = false;
			isPasswordGenOpen = false;
			isOptionsOpen = false;
			isImportOpen = false;
			isDonateOpen = true;
			clickDelayClock.restart();
		}
		if (isDonateOpen == true)
		{
			exitButton.setPosition(window.getSize().x - 50, 40);
			if (exitButton.getGlobalBounds().intersects(mc.cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isDonateOpen = false;
			menuText1.setOrigin((menuText1.getGlobalBounds().getSize().x / 2) + 20, 0);
			menuText1.setPosition((window.getSize().x + 280) / 2, 150);
			menuText2.setOrigin(menuText2.getGlobalBounds().getSize().x / 2 + 15, 0);
			menuText2.setPosition((window.getSize().x + 280) / 2, 250);
			donateButton.setPosition(window.getSize().x / 2 + 20, 550);
			if (mc.cursor.getGlobalBounds().intersects(donateButton.getGlobalBounds()))
				donateButton.setTextureRect(IntRect(520, 0, 520, 157));
			else
				donateButton.setTextureRect(IntRect(0, 0, 520, 157));
			if (mc.cursor.getGlobalBounds().intersects(donateButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				system("start https://secretscribble.42web.io/CreatorSupport.html");
		}
		else
		{
			exitButton.setPosition(999999, 999999);
			menuText1.setPosition(9999999, 999999);
			menuText2.setPosition(9999999, 999999);
			donateButton.setPosition(9999999, 999999);
		}
	}
}

void Donate::draw(RenderWindow& window, CursorSprite& mc, int& state)
{
	if (state == 2 && window.hasFocus() == true)
	{
		iconSprite.setPosition(5, window.getSize().y - 60);
		logoText.setPosition(70, window.getSize().y - 45);
		toolSelectSprite.setPosition(10, window.getSize().y - 58);

		if (mc.cursor.getGlobalBounds().intersects(toolSelectSprite.getGlobalBounds()))
			window.draw(toolSelectSprite);
		window.draw(iconSprite);
		window.draw(logoText);
		window.draw(menuText1);
		window.draw(menuText2);
		window.draw(donateButton);
		window.draw(exitButton);
	}
}