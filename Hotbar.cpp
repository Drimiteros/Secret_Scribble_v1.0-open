#include "Hotbar.h"

Hotbar::Hotbar()
{
	texture[0].loadFromFile("src/Textures/newFile.png");
	texture[1].loadFromFile("src/Textures/deleteFile.png");
	texture[2].loadFromFile("src/Textures/saveFile.png");
	texture[3].loadFromFile("src/Textures/options.png");
	texture[4].loadFromFile("src/Textures/createFile.png");
	texture[5].loadFromFile("src/Textures/passMenu2.png");
	texture[6].loadFromFile("src/Textures/form2.png");
	texture[7].loadFromFile("src/Textures/exitButton.png");
	texture[8].loadFromFile("src/Textures/importFile.png");
	texture[9].loadFromFile("src/Textures/checkbox.png");
	texture[10].loadFromFile("src/Textures/attention.png");
	timerCountArrowTexture.loadFromFile("src/Textures/arrow2.png");
	backgroundSpriteTexture.loadFromFile("src/Textures/optionsMenu.png");

	bar[0].setSize(Vector2f(400, 30));
	bar[0].setFillColor(Color(29, 44, 50));
	nameFileMenu.setSize(Vector2f(500, 350));
	nameFileMenu.setOrigin(150, 100);
	nameFileMenu.setTexture(&texture[5]);
	createFileButton.setTexture(texture[4]);
	createFileButton.setTextureRect(IntRect(0, 0, 520, 157));
	createFileButton.setScale(0.3, 0.3);
	exportButton.setTexture(texture[4]);
	exportButton.setTextureRect(IntRect(0, 0, 520, 157));
	exportButton.setScale(0.3, 0.3);
	formSprite.setTexture(texture[6]);
	formSprite.setScale(0.18, 0.2);
	deleteFileMenu.setSize(Vector2f(500, 350));
	deleteFileMenu.setOrigin(150, 100);
	deleteFileMenu.setTexture(&texture[5]);
	deleteFileButton.setTexture(texture[4]);
	deleteFileButton.setTextureRect(IntRect(0, 0, 520, 157));
	deleteFileButton.setScale(0.3, 0.3);
	keepFileButton.setTexture(texture[4]);
	keepFileButton.setTextureRect(IntRect(0, 0, 520, 157));
	keepFileButton.setScale(0.3, 0.3);
	timerCountArrow[0].setTexture(timerCountArrowTexture);
	timerCountArrow[0].setTextureRect(IntRect(0, 0, 174, 174));
	timerCountArrow[0].setScale(0.2, 0.2);
	timerCountArrow[1].setTexture(timerCountArrowTexture);
	timerCountArrow[1].setTextureRect(IntRect(175, 0, 174, 174));
	timerCountArrow[1].setScale(0.2, 0.2);
	clipboardEraceCountArrow[0].setTexture(timerCountArrowTexture);
	clipboardEraceCountArrow[0].setTextureRect(IntRect(0, 0, 174, 174));
	clipboardEraceCountArrow[0].setScale(0.2, 0.2);
	clipboardEraceCountArrow[1].setTexture(timerCountArrowTexture);
	clipboardEraceCountArrow[1].setTextureRect(IntRect(175, 0, 174, 174));
	clipboardEraceCountArrow[1].setScale(0.2, 0.2);
	backgroundSprite[0].setTexture(backgroundSpriteTexture);
	backgroundSprite[1].setTexture(backgroundSpriteTexture);
	exitButton.setTexture(texture[7]);
	exitButton.setScale(0.2, 0.2);
	exitButton2.setTexture(texture[7]);
	exitButton2.setScale(0.2, 0.2);
	cover.setSize(Vector2f(700, 30));
	cover.setFillColor(Color(49, 64, 70));
	for (int i = 0; i < 2; i++)
	{
		checkBox[i].setTexture(texture[9]);
		checkBox[i].setScale(0.15, 0.15);
	}

	font.loadFromFile("src/Fonts/thick3.ttf");
	infoText.setFont(font);
	infoText.setCharacterSize(15);
	infoText.setFillColor(Color(205, 255, 255, 255));
	fileNameText.setFont(font);
	fileNameText.setCharacterSize(25);
	fileNameText.setFillColor(Color::White);
	createFileText.setFont(font);
	createFileText.setCharacterSize(20);
	createFileText.setFillColor(Color::White);
	createFileText.setString("Create File");
	deleteFileText.setFont(font);
	deleteFileText.setCharacterSize(20);
	deleteFileText.setFillColor(Color::White);
	deleteFileText.setString("Delete File");
	keepFileText.setFont(font);
	keepFileText.setCharacterSize(20);
	keepFileText.setFillColor(Color::White);
	keepFileText.setString("Keep File");
	fileDeleteText.setFont(font);
	fileDeleteText.setCharacterSize(25);
	fileDeleteText.setFillColor(Color::White);
	fileDeleteText2.setFont(font);
	fileDeleteText2.setCharacterSize(25);
	fileDeleteText2.setFillColor(Color(26, 188, 156));
	fileExportText[0].setFont(font);
	fileExportText[0].setCharacterSize(30);
	fileExportText[0].setFillColor(Color::White);
	fileExportText[0].setString("File export");
	fileExportText[1].setFont(font);
	fileExportText[1].setCharacterSize(20);
	fileExportText[1].setFillColor(Color::White);
	fileExportText[1].setString("Export file: ");
	fileExportText[2].setFont(font);
	fileExportText[2].setCharacterSize(20);
	fileExportText[2].setFillColor(Color(26, 188, 156));
	fileExportText[3].setFont(font);
	fileExportText[3].setCharacterSize(20);
	fileExportText[3].setFillColor(Color::White);
	fileExportText[3].setString("Export as plain text\nExport as encrypted text");
	fileExportText[4].setFont(font);
	fileExportText[4].setCharacterSize(20);
	fileExportText[4].setFillColor(Color::White);
	fileExportText[4].setString("Export File");
	optionsText.setFont(font);
	optionsText.setCharacterSize(30);
	optionsText.setString("Options");
	AFKText[0].setFont(font);
	AFKText[1].setFont(font);
	AFKText[2].setFont(font);
	AFKText[0].setCharacterSize(30);
	AFKText[1].setCharacterSize(20);
	AFKText[2].setCharacterSize(20);
	AFKText[0].setString("App lock");
	AFKText[1].setString("The app will auto lock after : ");
	AFKText[1].setFillColor(Color(255, 255, 255, 200));
	AFKText[2].setFillColor(Color(26, 188, 156, 200));
	clipboardText[0].setFont(font);
	clipboardText[1].setFont(font);
	clipboardText[2].setFont(font);
	clipboardText[0].setCharacterSize(30);
	clipboardText[1].setCharacterSize(20);
	clipboardText[2].setCharacterSize(20);
	clipboardText[0].setString("Clipboard erase");
	clipboardText[1].setString("The clipboard will clear after : ");
	clipboardText[1].setFillColor(Color(255, 255, 255, 200));
	clipboardText[2].setFillColor(Color(26, 188, 156, 200));

	sprite[0].setTexture(texture[0]);
	sprite[0].setPosition(25, 6);
	sprite[0].setScale(0.1, 0.1);
	sprite[1].setTexture(texture[1]);
	sprite[1].setPosition(60, 6);
	sprite[1].setScale(0.1, 0.1);
	sprite[2].setTexture(texture[2]);
	sprite[2].setPosition(95, 6);
	sprite[2].setScale(0.1, 0.1);
	sprite[3].setTexture(texture[3]);
	sprite[3].setPosition(166, 6);
	sprite[3].setScale(0.1, 0.1);
	sprite[4].setTexture(texture[8]);
	sprite[4].setPosition(130, 6);
	sprite[4].setScale(0.1, 0.1);
	sprite[5].setTexture(texture[10]);
	sprite[5].setPosition(200, 6);
	sprite[5].setScale(0.1, 0.1);
}

void Hotbar::visual(CursorSprite& c, int state, RenderWindow& window)
{
	for (int i = 0; i < 6 && state == 2 && window.hasFocus() == true; i++)
	{
		if (c.cursor.getGlobalBounds().intersects(sprite[i].getGlobalBounds()))
		{
			if (displayInfoTextDelayClock.getElapsedTime().asSeconds() > 0.6)
				infoText.setPosition(c.cursor.getPosition().x, c.cursor.getPosition().y + 20);
			sprite[i].setColor(Color(255, 255, 255, 255));
			if (i == 0)
			{
				infoText.setString("<New File>");
				break;
			}
			else if (i == 1)
			{
				infoText.setString("<Delete File>");
				break;
			}
			else if (i == 2)
			{
				infoText.setString("<Save File>");
				break;
			}
			else if (i == 3)
			{
				infoText.setString("<Options>");
				break;
			}
			else if (i == 4)
			{
				infoText.setString("<Export File>");
				break;
			}
			else if (i == 5)
			{
				infoText.setString("<Report Issue>");
				break;
			}
			break;
		}
		else
		{
			sprite[i].setColor(Color(195, 195, 195, 255));
			if (i == 5)
				displayInfoTextDelayClock.restart();
			infoText.setPosition(999999999, 999999999);
		}
	}
}

void Hotbar::nameFile(CursorSprite& c, Event& eve)
{
	if (isFileNamed == true)
	{
		if (eve.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::BackSpace)
			&& !Keyboard::isKeyPressed(Keyboard::Enter))
			fileName += eve.text.unicode;
		if (eve.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::BackSpace)
			&& !Keyboard::isKeyPressed(Keyboard::Enter))
			fileName = fileName.substr(0, fileName.size() - 1);
		if (c.cursor.getGlobalBounds().intersects(createFileButton.getGlobalBounds()))
			createFileButton.setTextureRect(IntRect(520, 0, 520, 157));
		else
			createFileButton.setTextureRect(IntRect(0, 0, 520, 157));
		if (c.cursor.getGlobalBounds().intersects(createFileButton.getGlobalBounds()) 
			&& Mouse::isButtonPressed(Mouse::Left) && fileName.size() > 0)
			isFileCreated = true;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			isFileNamed = false;
	}
}

void Hotbar::createFile(CursorSprite& c, string& filePath, bool& enter, bool& instructionClick, int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis, RenderWindow& window, int state, TextEditor& textEditor)
{
	if (state == 2 && window.hasFocus() == true)
	{
		for (int i = 0; i < di.driveName.size(); i++)
		{
			if (c.cursor.getGlobalBounds().intersects(sprite[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isFileNamed = true;
		}
		if (isFileNamed == true)
		{
			nameFileMenu.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 70);
			textEditor.editText = false;
		}
		if (isFileNamed == false)
		{
			nameFileMenu.setPosition(99999, 99999);
			textEditor.editText = true;
		}
		createFileButton.setPosition(nameFileMenu.getPosition().x + 20, nameFileMenu.getPosition().y + 170);
		createFileText.setPosition(createFileButton.getPosition().x + 25, createFileButton.getPosition().y + 10);
		fileNameText.setPosition(nameFileMenu.getPosition().x - 80, nameFileMenu.getPosition().y - 60);
		fileNameText.setString("Name your file:\n\n" + fileName + "<");
		formSprite.setPosition(nameFileMenu.getPosition().x - 110, nameFileMenu.getPosition().y - 10);

		if (isFileCreated == true)
		{
			string extension = ".txt";
			string filePath_a = filePath + fileName + extension;
			cout << filePath_a << endl;
			ofstream outfile(filePath_a);
			if (outfile.is_open())
			{
				cout << "File created and written successfully at " << filePath_a << endl;
				enter = true;
				instructionClick = true;
				fileScrollCounter = 0;
				fileCount = 0;
				lp.fileNameStringVector.clear();
				lp.availablePathsText.clear();
				fis.clear();
				lp.type.clear();
				lp.coverClock.restart();
				di.selectClock.restart();
			}
			else
				cerr << "Error opening file for writing." << endl;
			isFileCreated = false;
			isFileNamed = false;
		}
	}
}

void Hotbar::saveFile(CursorSprite& c, FileManager& fileManager, RenderWindow& window, int state, bool& enter, bool& instructionClick, int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis)
{
	if (state == 2 && window.hasFocus() == true)
	{
		if ((Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::S))
			|| c.cursor.getGlobalBounds().intersects(sprite[2].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		{
			fileManager.saveFile = true;
			updateFoldersClock.restart();
		}
		if (fileManager.saveFile == false && updateFoldersClock.getElapsedTime().asSeconds() < 0.1)
		{
			enter = true;
			instructionClick = true;
			fileScrollCounter = 0;
			fileCount = 0;
			lp.fileNameStringVector.clear();
			lp.availablePathsText.clear();
			fis.clear();
			lp.type.clear();
			lp.coverClock.restart();
			di.selectClock.restart();
		}
	}
}

void Hotbar::deleteFile(CursorSprite& c, FileManager& fileManager, bool& enter, bool& instructionClick, int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis, bool& isTextFileOpen, RenderWindow& window, int state, string& fileNameString)
{
	if (state == 2 && window.hasFocus() == true)
	{
		if (c.cursor.getGlobalBounds().intersects(sprite[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			isFileModifyied = true;
		if (isFileModifyied == true)
		{
			deleteFileMenu.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 70);
			if (c.cursor.getGlobalBounds().intersects(deleteFileButton.getGlobalBounds()))
				deleteFileButton.setTextureRect(IntRect(520, 0, 520, 157));
			else
				deleteFileButton.setTextureRect(IntRect(0, 0, 520, 157));
			if (c.cursor.getGlobalBounds().intersects(keepFileButton.getGlobalBounds()))
				keepFileButton.setTextureRect(IntRect(520, 0, 520, 157));
			else
				keepFileButton.setTextureRect(IntRect(0, 0, 520, 157));
			if (c.cursor.getGlobalBounds().intersects(deleteFileButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isFileDeleted = true;
			if (c.cursor.getGlobalBounds().intersects(keepFileButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isFileModifyied = false;
		}
		else
		{
			isFileModifyied = false;
			deleteFileMenu.setPosition(999999, 99999);
		}
		deleteFileButton.setPosition(deleteFileMenu.getPosition().x - 100, deleteFileMenu.getPosition().y + 170);
		keepFileButton.setPosition(deleteFileMenu.getPosition().x + 150, deleteFileMenu.getPosition().y + 170);
		deleteFileText.setPosition(deleteFileButton.getPosition().x + 23, deleteFileButton.getPosition().y + 12);
		keepFileText.setPosition(keepFileButton.getPosition().x + 28, keepFileButton.getPosition().y + 12);
		fileDeleteText.setPosition(deleteFileMenu.getPosition().x - 100, deleteFileMenu.getPosition().y - 50);
		fileDeleteText.setString("Delete the file: \n");
		fileDeleteText2.setPosition(deleteFileMenu.getPosition().x - 100, deleteFileMenu.getPosition().y - 20);
		fileDeleteText2.setString("\"" + fileNameString + "\" ?");

		if (isFileDeleted == true)
		{
			const char* filePath = fileManager.setFilePath.c_str();

			if (remove(filePath) == 0)
			{
				for (int i = 0; i < di.driveName.size(); i++)
				{
					cout << "File deleted successfully." << endl;
					fileManager.setFilePath = di.driveName[i];
					enter = true;
					instructionClick = true;
					fileScrollCounter = 0;
					fileCount = 0;
					lp.fileNameStringVector.clear();
					lp.availablePathsText.clear();
					fis.clear();
					lp.type.clear();
					lp.coverClock.restart();
					di.selectClock.restart();
					isFileModifyied = false;
					isTextFileOpen = false;
					isFileDeleted = false;
					break;
				}
			}
			else
				perror("Error deleting file");
		}
	}
}

void Hotbar::exportFile(int state, RenderWindow& window, bool& isExportOpen, CursorSprite& c, bool& isPasswordGenOpen, bool& isOptionsOpen, TextEditor& textEditor, bool& isTextFileOpen, string& fileNameString, ImGuiIO& io, Secure& secure, FileManager& fileManager, bool& enter, bool& instructionClick, 
	int& fileScrollCounter, int& fileCount, DiskInfo& di, LocatePath& lp, vector<FileIcon>& fis, string& filePath, bool& isDonateOpen)
{
	if (state == 2 && window.hasFocus() == true)
	{
		if (c.cursor.getGlobalBounds().intersects(sprite[4].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		{
			isExportOpen = true;
			isPasswordGenOpen = false;
		}
		if (c.cursor.getGlobalBounds().intersects(exitButton2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			isExportOpen = false;
		if (isExportOpen == true)
		{
			isFileNamed = false;
			isFileCreated = false;
			isFileModifyied = false;
			isFileDeleted = false;
			textEditor.editText = false;
			isTextFileOpen = false;
			isOptionsOpen = false;
			isDonateOpen = false;

			exportButton.setPosition(300, 710);
			if (c.cursor.getGlobalBounds().intersects(exportButton.getGlobalBounds()))
				exportButton.setTextureRect(IntRect(520, 0, 520, 157));
			else
				exportButton.setTextureRect(IntRect(0, 0, 520, 157));
			exitButton2.setPosition(window.getSize().x - 50, 40);
			fileExportText[0].setPosition(window.getSize().x / 2, 40);
			fileExportText[1].setPosition(300, 140);
			fileExportText[2].setPosition(410, 140);
			fileExportText[3].setPosition(300, 470);
			fileExportText[4].setPosition(320, 720);
			checkBox[0].setPosition(580, 470);
			checkBox[1].setPosition(580, 500);
			fileExportText[2].setString(fileNameString);
			cover.setPosition(300, 140);
			io.FontGlobalScale = 1.0;
			io.UserData = static_cast<void*>(this);
			ImGui::Begin(fileNameString.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::SetWindowPos(ImVec2(300, 140));
			ImGui::SetWindowSize(ImVec2(700, 300));
			ImGui::SetWindowFocus();
			ImGui::TextWrapped("%s", textEditor.myText);
			ImGui::End();

			if (c.cursor.getGlobalBounds().intersects(checkBox[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isFileEncrypted = false;
			if (c.cursor.getGlobalBounds().intersects(checkBox[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				isFileEncrypted = true;
			if (isFileEncrypted == false)
			{
				checkBox[1].setTextureRect(IntRect(0, 0, 174, 174));
				checkBox[0].setTextureRect(IntRect(174, 0, 174, 174));

				if (c.cursor.getGlobalBounds().intersects(exportButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && ButtonPressDelayClock.getElapsedTime().asSeconds() > 0.3)
				{
					ButtonPressDelayClock.restart();
					fileManager.saveRawFile = true;
					string plaintext = textEditor.myText;
					fileManager.exportRawTXT(filePath, plaintext, fileNameString);
					updateFoldersClock.restart();
				}
				if (fileManager.saveFile == false && updateFoldersClock.getElapsedTime().asSeconds() < 0.1)
				{
					enter = true;
					instructionClick = true;
					fileScrollCounter = 0;
					fileCount = 0;
					lp.fileNameStringVector.clear();
					lp.availablePathsText.clear();
					fis.clear();
					lp.type.clear();
					lp.coverClock.restart();
					di.selectClock.restart();
					isExportOpen = false;
				}
			}
			else
			{
				checkBox[0].setTextureRect(IntRect(0, 0, 174, 174));
				checkBox[1].setTextureRect(IntRect(174, 0, 174, 174));
				if (c.cursor.getGlobalBounds().intersects(exportButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && ButtonPressDelayClock.getElapsedTime().asSeconds() > 0.3)
				{
					ButtonPressDelayClock.restart();
					string encryptedText, cipherText;
					string grade = "32ewdfs45667a*76";
					fileManager.saveFile = true;
					fileManager.exportEncryptedTXT(filePath, textEditor, grade, secure, c, fileNameString);
					updateFoldersClock.restart();
				}
				if (fileManager.saveFile == false && updateFoldersClock.getElapsedTime().asSeconds() < 0.1)
				{
					enter = true;
					instructionClick = true;
					fileScrollCounter = 0;
					fileCount = 0;
					lp.fileNameStringVector.clear();
					lp.availablePathsText.clear();
					fis.clear();
					lp.type.clear();
					lp.coverClock.restart();
					di.selectClock.restart();
					isExportOpen = false;
				}
			}
		}
		else 
		{
			fileExportText[0].setPosition(999999, 999999);
			fileExportText[1].setPosition(999999, 999999);
			fileExportText[2].setPosition(999999, 999999);
			fileExportText[3].setPosition(999999, 999999);
			fileExportText[4].setPosition(999999, 999999);
			cover.setPosition(999999, 999999);
			exitButton2.setPosition(9999999, 999999);
			checkBox[0].setPosition(9999999, 9999999);
			checkBox[1].setPosition(9999999, 9999999);
			exportButton.setPosition(99999, 99999);
		}
	}
}

void Hotbar::options(RenderWindow& window, CursorSprite& c, int state, TextEditor& textEditor, int& AFKTimerCount, bool& isTextFileOpen, FileManager& fm, bool& isOptionsOpen, bool& isPasswordGenOpen, bool& isImportOpen, int& clipboardEraceTime, bool& isDonateOpen)
{
	if (state == 2 && window.hasFocus() == true)
	{
		if (c.cursor.getGlobalBounds().intersects(sprite[3].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		{
			isOptionsOpen = true;
			isPasswordGenOpen = false;
		}
		if (c.cursor.getGlobalBounds().intersects(exitButton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			isOptionsOpen = false;
		if (isOptionsOpen == true)
		{
			isFileNamed = false;
			isFileCreated = false;
			isFileModifyied = false;
			isFileDeleted = false;
			textEditor.editText = false;
			isTextFileOpen = false;
			isImportOpen = false;

			AFKText[2].setString(to_string(AFKTimerCount) + " min");
			clipboardText[2].setString(to_string(clipboardEraceTime) + " sec");
			optionsText.setPosition(window.getSize().x / 2, 40);
			timerCountArrow[0].setPosition(660, 170);
			timerCountArrow[1].setPosition(710, 170);
			clipboardEraceCountArrow[0].setPosition(660, 345);
			clipboardEraceCountArrow[1].setPosition(710, 345);
			AFKText[0].setPosition(330, 130);
			AFKText[1].setPosition(330, 170);
			AFKText[2].setPosition(330, 195);
			clipboardText[0].setPosition(330, 305);
			clipboardText[1].setPosition(330, 345);
			clipboardText[2].setPosition(330, 370);
			backgroundSprite[0].setPosition(300, 110);
			backgroundSprite[1].setPosition(300, 285);
			exitButton.setPosition(window.getSize().x - 50, 40);

			if (c.cursor.getGlobalBounds().intersects(timerCountArrow[0].getGlobalBounds()))
				timerCountArrow[0].setColor(Color(255, 255, 255, 255));
			else
				timerCountArrow[0].setColor(Color(255, 255, 255, 200));
			if (c.cursor.getGlobalBounds().intersects(timerCountArrow[1].getGlobalBounds()))
				timerCountArrow[1].setColor(Color(255, 255, 255, 255));
			else
				timerCountArrow[1].setColor(Color(255, 255, 255, 200));
			if (c.cursor.getGlobalBounds().intersects(timerCountArrow[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && AFKTimerCount > 1 && ButtonPressDelayClock.getElapsedTime().asSeconds() > 0.3)
			{
				AFKTimerCount--;
				ButtonPressDelayClock.restart();
				fm.saveAutoLockPferences(AFKTimerCount);
			}
			if (c.cursor.getGlobalBounds().intersects(timerCountArrow[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && ButtonPressDelayClock.getElapsedTime().asSeconds() > 0.3)
			{
				AFKTimerCount++;
				ButtonPressDelayClock.restart();
				fm.saveAutoLockPferences(AFKTimerCount);
			}

			if (c.cursor.getGlobalBounds().intersects(clipboardEraceCountArrow[0].getGlobalBounds()))
				clipboardEraceCountArrow[0].setColor(Color(255, 255, 255, 255));
			else
				clipboardEraceCountArrow[0].setColor(Color(255, 255, 255, 200));
			if (c.cursor.getGlobalBounds().intersects(clipboardEraceCountArrow[1].getGlobalBounds()))
				clipboardEraceCountArrow[1].setColor(Color(255, 255, 255, 255));
			else
				clipboardEraceCountArrow[1].setColor(Color(255, 255, 255, 200));
			if (c.cursor.getGlobalBounds().intersects(clipboardEraceCountArrow[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && clipboardEraceTime > 1 && ButtonPressDelayClock.getElapsedTime().asSeconds() > 0.3)
			{
				clipboardEraceTime--;
				ButtonPressDelayClock.restart();
				fm.saveClipboardTimePferences(clipboardEraceTime);
			}
			if (c.cursor.getGlobalBounds().intersects(clipboardEraceCountArrow[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && ButtonPressDelayClock.getElapsedTime().asSeconds() > 0.3)
			{
				clipboardEraceTime++;
				ButtonPressDelayClock.restart();
				fm.saveClipboardTimePferences(clipboardEraceTime);
			}
		}
		else
		{
			textEditor.editText = true;
			optionsText.setPosition(999999, 999999);
			AFKText[0].setPosition(999999, 999999);
			AFKText[1].setPosition(999999, 999999);
			AFKText[2].setPosition(999999, 999999);
			clipboardText[0].setPosition(999999, 999999);
			clipboardText[1].setPosition(999999, 999999);
			clipboardText[2].setPosition(999999, 999999);
			timerCountArrow[0].setPosition(999999, 999999);
			timerCountArrow[1].setPosition(999999, 999999);
			clipboardEraceCountArrow[0].setPosition(999999, 999999);
			clipboardEraceCountArrow[1].setPosition(999999, 999999);
			backgroundSprite[0].setPosition(999999, 999999);
			backgroundSprite[1].setPosition(999999, 999999);
			exitButton.setPosition(9999999, 999999);
		}
	}
}

void Hotbar::reportIssue(CursorSprite& c)
{
	if (c.cursor.getGlobalBounds().intersects(sprite[5].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		system("start https://tally.so/r/wzeMva");
}

void Hotbar::draw(RenderWindow& window, int state)
{
	if (state == 2 && window.hasFocus() == true)
	{
		window.draw(bar[0]);
		bar[0].setSize(Vector2f(window.getSize().x, 30));
		for (int i = 0; i < 18; i++)
			window.draw(sprite[i]);
		window.draw(backgroundSprite[0]);
		window.draw(backgroundSprite[1]);
		window.draw(nameFileMenu);
		window.draw(deleteFileMenu);
		window.draw(formSprite);
		window.draw(createFileButton);
		window.draw(exportButton);
		window.draw(deleteFileButton);
		window.draw(keepFileButton);
		window.draw(fileNameText);
		window.draw(createFileText);
		window.draw(deleteFileText);
		window.draw(keepFileText);
		window.draw(fileDeleteText);
		window.draw(fileDeleteText2);
		window.draw(infoText);
		window.draw(optionsText);
		window.draw(AFKText[0]);
		window.draw(AFKText[1]);
		window.draw(AFKText[2]);
		window.draw(clipboardText[0]);
		window.draw(clipboardText[1]);
		window.draw(clipboardText[2]);
		window.draw(timerCountArrow[0]);
		window.draw(timerCountArrow[1]);
		window.draw(clipboardEraceCountArrow[0]);
		window.draw(clipboardEraceCountArrow[1]);
		window.draw(exitButton);
		window.draw(exitButton2);
		window.draw(cover);
		window.draw(fileExportText[0]);
		window.draw(fileExportText[1]);
		window.draw(fileExportText[2]);
		window.draw(fileExportText[3]);
		window.draw(fileExportText[4]);
		window.draw(checkBox[0]);
		window.draw(checkBox[1]);
	}
}