#pragma once
#include <iostream>
#include "CursorSprite.h"
#include "PasswordLogin.h"

using namespace std;

class AFK_Lock
{
private:

public:

	AFK_Lock();
	void lockTheApp(Clock& AFK_Clock, int& state, PasswordLogin& pl, bool& getIsTyping, bool& isMovingCursor, int& afkTimerCount, bool& isDisconnected, bool& isReConnected, bool& isActive, bool& isDoneManagingAdapter);
};

