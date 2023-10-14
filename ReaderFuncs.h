#pragma once
#include<Hidsdi.h>
#include<SetupAPI.h>
#include <vector>
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "Hid.lib")

using namespace std;
//Do this first to get an access to device
int GetDeviceHandle(vector<HANDLE>* res, vector<wchar_t*>* names);


