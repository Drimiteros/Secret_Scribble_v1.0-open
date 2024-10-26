#include "InternetAdapterConfig.h"

InternetAdapterConfig::InternetAdapterConfig()
{

}

void InternetAdapterConfig::displayAdaptersAndPerformAction(int state, bool& isDisconnected, bool& isReConnected, bool& isActive, bool& isDoneManagingAdapter)
{
    if (isActive == true && isDoneManagingAdapter == false)
    {
        HANDLE hClient = NULL;
        DWORD dwMaxClient = 2; // Version number for Windows Vista and later
        DWORD dwCurVersion = 0;
        DWORD dwResult = 0;
        unsigned int i;

        dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
        if (dwResult != ERROR_SUCCESS)
        {
            cerr << "Error opening WLAN handle: " << dwResult << endl;
            return;
        }

        PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
        PWLAN_INTERFACE_INFO pIfInfo = NULL;

        dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
        if (dwResult != ERROR_SUCCESS)
        {
            cerr << "Error enumerating interfaces: " << dwResult << endl;
            WlanCloseHandle(hClient, NULL);
            return;
        }

        cout << "Available network adapters:\n";
        for (i = 0; i < pIfList->dwNumberOfItems; i++)
        {
            pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];
            wcout << i + 1 << L". " << pIfInfo->strInterfaceDescription << endl;
        }

        /*int choice;
        std::cout << "Enter the number of the adapter you want to manage: ";
        std::cin >> choice;

        if (choice < 1 || choice >(int)pIfList->dwNumberOfItems) {
            std::cerr << "Invalid choice." << std::endl;
            WlanFreeMemory(pIfList);
            WlanCloseHandle(hClient, NULL);
            return;
        }*/

        pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[adapter];

        GUID InterfaceGuid = pIfInfo->InterfaceGuid;
        if (state <= 1 && isDisconnected == false)
        {
            dwResult = WlanDisconnect(hClient, &InterfaceGuid, NULL);
            if (dwResult == ERROR_SUCCESS)
            {
                cout << "Successfully disconnected the adapter. isDisconnected = " << isDisconnected << endl;
                isDisconnected = true;
            }
            else
            {
                cerr << "Failed to disconnect the adapter: " << dwResult << endl;
                adapter++;
                if (adapter < 5)
                    isDoneManagingAdapter = true;
            }
        }
        else if (state == 2 && isReConnected == false)
        {
            WLAN_AVAILABLE_NETWORK_LIST* pNetworkList = NULL;
            dwResult = WlanGetAvailableNetworkList(hClient, &InterfaceGuid, 0, NULL, &pNetworkList);
            if (dwResult != ERROR_SUCCESS)
            {
                cerr << "Error getting available network list: " << dwResult << endl;
                WlanFreeMemory(pIfList);
                WlanCloseHandle(hClient, NULL);
                isReConnected = true;
                return;
            }
            if (pNetworkList->dwNumberOfItems > 0) 
            {
                WLAN_AVAILABLE_NETWORK* pNetwork = &pNetworkList->Network[network];
                WLAN_CONNECTION_PARAMETERS connParams;
                connParams.wlanConnectionMode = wlan_connection_mode_profile;
                connParams.strProfile = pNetwork->strProfileName;
                connParams.pDot11Ssid = NULL;
                connParams.pDesiredBssidList = NULL;
                connParams.dot11BssType = pNetwork->dot11BssType;
                connParams.dwFlags = 0;

                dwResult = WlanConnect(hClient, &InterfaceGuid, &connParams, NULL);
                if (dwResult == ERROR_SUCCESS)
                {
                    cout << "Successfully reconnected to the network." << endl;
                    isReConnected = true;
                    isDoneManagingAdapter = true;
                    cout << "Done managing internet adapter" << endl;
                }
                else
                {
                    cerr << "Failed to reconnect to the network: " << dwResult << endl;
                    network++;
                    if (network <= 5)
                        isDoneManagingAdapter = true;
                }
            }
            else
            {
                cerr << "No available networks found to reconnect." << endl;
                isReConnected = true;
            }
            if (pNetworkList != NULL)
                WlanFreeMemory(pNetworkList);
        }
        else
            cerr << "Invalid state." << endl;

        WlanFreeMemory(pIfList);
        WlanCloseHandle(hClient, NULL);
    }
}

void InternetAdapterConfig::logic(int state, bool& isDisconnected, bool& reConnected, bool& isActive, bool& isDoneManagingAdapter)
{
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    displayAdaptersAndPerformAction(state, isDisconnected, reConnected, isActive, isDoneManagingAdapter);
    CoUninitialize();
}