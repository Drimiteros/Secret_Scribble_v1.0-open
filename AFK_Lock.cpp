#include "AFK_Lock.h"

AFK_Lock::AFK_Lock()
{

}

void AFK_Lock::lockTheApp(Clock& AFK_Clock, int& state, PasswordLogin& pl, bool& getIsTyping, bool& isMovingCursor, int& afkTimerCount, bool& isDisconnected, bool& isReConnected, bool& isActive, bool& isDoneManagingAdapter)
{
	if (getIsTyping == true || isMovingCursor == true)
		AFK_Clock.restart();

	int time = afkTimerCount * 60;

	if (state == 2 && AFK_Clock.getElapsedTime().asSeconds() > time)
	{
		state = 1;
		pl.passwordString = "";
		pl.hiddenPasswordString = "";
		pl.passwordText.setString(pl.hiddenPasswordString + "_");
		isDisconnected = false; 
		isReConnected = false; 
		isActive = false;
		isDoneManagingAdapter = false;
	}
}