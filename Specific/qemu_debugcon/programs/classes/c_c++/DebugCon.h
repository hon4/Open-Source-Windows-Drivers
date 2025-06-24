/*
honCode 2025
hon QEMU DebugCon Driver Functions 4 Programs
====================================
Example usage:
	debugcon_write("Example");
	debugcon_write("Example\n");
*/

//windows.h required for the driver connection functions
#include <windows.h>
//iostream is required for the std::cout & std::cerr used for error output. -> You can modify the code and remove it.
#include <iostream>

//Definations
#define FILE_DEVICE_UNKNOWN		0x22
#define METHOD_BUFFERED			0
#define FILE_WRITE_DATA_FIX		0x2		//FILE_WRITE_DATA exists in lib, _FIX added to have different name
#define FUNCTION_PRINT_STRING	0x800

void debugcon_write(const char* str) { //const char* str: is a NULL terminated string.
	// Device Name
	const wchar_t* deviceName = L"\\\\.\\qemu_debugcon";

	// Open handle to the device for write access
	HANDLE hDevice = CreateFileW(
		deviceName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hDevice == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to open device. Error: " << GetLastError() << std::endl;
		return; //for 'int' instead of 'void' possibly: return 1;
	}

	// Define IOCTL code -> Moved to Definations Part

	DWORD IOCTL_PRINT_STRING = (FILE_DEVICE_UNKNOWN << 16) | (FILE_WRITE_DATA_FIX << 14) | (FUNCTION_PRINT_STRING << 2) | METHOD_BUFFERED;

	DWORD bytesReturned = 0;

	BOOL success = DeviceIoControl(
		hDevice,
		IOCTL_PRINT_STRING,
		(LPVOID)str,
		(DWORD)(strlen(str) + 1), // include NULL terminator
		NULL,
		0,
		&bytesReturned,
		NULL);

	if (!success) {
		std::cerr << "DeviceIoControl failed. Error: " << GetLastError() << std::endl;
		CloseHandle(hDevice);
		return; //for 'int' instead of 'void' possibly: return 1;
	}

	//Send successfull!

	CloseHandle(hDevice);
	return; //for 'int' instead of 'void' possibly: return 0;
}
