#include "Source.h"

/*
Сделать:
1. UnNop
*/

DWORD WINAPI MyThread(LPVOID lpParam)
{
	AllocConsole();
	FILE* fconsole = freopen("CONOUT$", "w", stdout);

	MODULEINFO info;
	if (GetModuleHandleA("Dishonored.exe"))
	{
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA("Dishonored.exe"), &info, sizeof(info));
	}

	DWORD moneyDecreaseFunc = patternScan((DWORD)info.lpBaseOfDll, (DWORD)info.lpBaseOfDll + info.SizeOfImage, "89 56 ?? 5b 85 d2");
	//DWORD manaDecreaseFunc = patternScan((DWORD)info.lpBaseOfDll, (DWORD)info.lpBaseOfDll + info.SizeOfImage, "51 8b cb e8 ? ? ? ? 8b 55 ? 29 93");

	DWORD hModule = (DWORD)GetModuleHandleA("Dishonored.exe");
	DWORD addr = *(DWORD*)(hModule + 0x01052DE8);
	CPlayer* player = (CPlayer*)(addr);

	
	//printf("Player addr -> %p <-\n", player);
	//printf("Addr of decrease money func -> %x <-\n", moneyDecreaseFunc);

	nop_((PVOID)moneyDecreaseFunc, 3); // Ноп функции DecreaseMoney

	while (!GetAsyncKeyState(VK_DELETE))
	{

		player->iHealth = 70;
		player->iMana = 100;

		Sleep(1);
	}

	if (fconsole)
		fclose(fconsole);

	FreeConsole();
	FreeLibraryAndExitThread((HMODULE)lpParam, 0);

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MyThread, hinstDLL, 0, 0);

		break;
	}

	return TRUE;
}