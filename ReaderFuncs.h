#pragma once
#include<Hidsdi.h>
#include<SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "Hid.lib")


//Do this first to get an access to device
HANDLE GetDeviceHandle(HDEVINFO& hDevInfo);


