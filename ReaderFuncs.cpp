#include"pch.h"
#include"ReaderFuncs.h"
#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>



int GetDeviceHandle(vector<HANDLE>* res, vector<wchar_t*>* names)
{
	GUID hidGUID;
	HDEVINFO hardwareDeviceInfoSet;
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
	PSP_INTERFACE_DEVICE_DETAIL_DATA deviceDetail;
	ULONG requiredSize;
	HIDD_ATTRIBUTES DeviceAttributes;
	HANDLE deviceHandle = INVALID_HANDLE_VALUE;
	DWORD result;
	int deviceIndex = 0;
	//Get the HID GUID value - used as mask to get list of devices
	HidD_GetHidGuid(&hidGUID);

	//Get a list of devices matching the criteria (hid interface, present)
	hardwareDeviceInfoSet = SetupDiGetClassDevs(&hidGUID,
		NULL, // Define no enumerator (global)
		NULL, // Define no
		(DIGCF_PRESENT | // Only Devices present
			DIGCF_DEVICEINTERFACE)); // Function class devices.

	deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	//здесь мы начинаем перебирать все подключенные девайсы
	while (1) {
		//Go through the list and get the interface data
		result = SetupDiEnumDeviceInterfaces(hardwareDeviceInfoSet,
			NULL, //infoData,
			&hidGUID, //interfaceClassGuid,
			deviceIndex,
			&deviceInterfaceData);

		/* Failed to get a device - possibly the index is larger than the number of devices */
		if (result == FALSE)
		{
			SetupDiDestroyDeviceInfoList(hardwareDeviceInfoSet);
			return 0;
		}

		//Get the details with null values to get the required size of the buffer
		SetupDiGetDeviceInterfaceDetail(hardwareDeviceInfoSet,
			&deviceInterfaceData,
			NULL, //interfaceDetail,
			0, //interfaceDetailSize,
			&requiredSize,
			0); //infoData))

		//Allocate the buffer
		deviceDetail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(requiredSize);
		deviceDetail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

		//Fill the buffer with the device details
		if (!SetupDiGetDeviceInterfaceDetail(hardwareDeviceInfoSet,
			&deviceInterfaceData,
			deviceDetail,
			requiredSize,
			&requiredSize,
			NULL))
		{
			SetupDiDestroyDeviceInfoList(hardwareDeviceInfoSet);
			free(deviceDetail);
			return 0;
		}

		//Open file on the device
		deviceHandle = CreateFile(deviceDetail->DevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,        // no SECURITY_ATTRIBUTES structure
			OPEN_EXISTING, // No special create flags
			FILE_FLAG_OVERLAPPED,
			NULL);       // No template file
		res->push_back(deviceHandle);
		const int len = 150;
		wchar_t* str = new wchar_t[len];

		HidD_GetProductString(deviceHandle, str, sizeof(wchar_t) * len);

		names->push_back(str);
		deviceIndex++;
	}

	SetupDiDestroyDeviceInfoList(hardwareDeviceInfoSet);
	free(deviceDetail);
	return 0;
}