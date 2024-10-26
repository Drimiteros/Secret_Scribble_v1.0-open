#pragma once
#include <iostream>
#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

using namespace std;

class InternetAdapterConfig
{
private:
    int adapter = 0;
    int network = 0;

public:
    InternetAdapterConfig();
    void displayAdaptersAndPerformAction(int state, bool& isDisconnected, bool& reConnected, bool& isActive, bool& isDoneManagingAdapter);
    void logic(int state, bool& isDisconnected, bool& reConnected, bool& isActive, bool& isDoneManagingAdapter);
};