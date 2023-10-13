#include"pch.h"
#include"ReaderFuncs.h"




HANDLE GetDeviceHandle(HDEVINFO& hDevInfo)
{
	GUID guid;
	HidD_GetHidGuid(&guid);

	
	hDevInfo = SetupDiGetClassDevs(&guid,
		NULL,
		NULL,
		(DIGCF_PRESENT | DIGCF_DEVICEINTERFACE)
	);

	SP_DEVICE_INTERFACE_DATA DevData;
	DevData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	if (SetupDiEnumDeviceInterfaces(hDevInfo, 0, &guid, 0, &DevData) == FALSE)
	{
		MessageBoxW(NULL, L"Не удалось получить устройство.", L"Ошибка", MB_ICONERROR);
		SetupDiDestroyDeviceInfoList(hDevInfo);
		return INVALID_HANDLE_VALUE;
	}
	SP_DEVICE_INTERFACE_DETAIL_DATA DevDetData;
	DevDetData.cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
	if (SetupDiGetDeviceInterfaceDetailW(hDevInfo, &DevData, &DevDetData, 1024, NULL, NULL) == FALSE)
	{
		MessageBoxW(NULL, L"Не удалось получить точную информацию об устройстве.", L"Ошибка", MB_ICONERROR);
		SetupDiDestroyDeviceInfoList(hDevInfo);
		return INVALID_HANDLE_VALUE;
	}

	HANDLE DevHandle = CreateFileW(DevDetData.DevicePath,
		0,                                      		
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING,
		0,
		NULL
	);
	if (DevHandle == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(NULL, L"Не удалось связаться с устройством.", L"Ошибка", MB_ICONERROR);
		SetupDiDestroyDeviceInfoList(hDevInfo);
		return INVALID_HANDLE_VALUE;
	}
	return DevHandle;
}