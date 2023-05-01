#include "HookLib.h"


void Hook(void* address, void* hook)
{
	printf("%p\n", address);
	printf("%p\n", hook);

	DWORD vprava;
	VirtualProtect(address, 5, PAGE_EXECUTE_READWRITE, &vprava);

	DWORD jmp = ((DWORD)hook - (DWORD)address) - 5; 
	*(BYTE*)address = 0xE9;
	*(DWORD*)((DWORD)address + 0x1) = jmp;

	VirtualProtect(address, 5, vprava, &vprava);
}

DWORD tramplineHook(void* address, void* hook, int size)
{
	DWORD gateway = (DWORD)VirtualAlloc(0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	printf("%ul\n", gateway);

	memcpy((LPVOID)gateway, address, size); 

	DWORD jmp = (DWORD)address - gateway - 5;
	printf("%ul\n", jmp);
	*(BYTE*)(gateway + size) = 0xE9;
	*(DWORD*)(gateway + size + 1) = jmp;

	Hook(address, hook);

	return gateway;
}

void tramplineUnHook(void* address, void* gateway, int size)
{
	DWORD prava;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &prava);

	memcpy(address, gateway, size);

	VirtualProtect(address, size, prava, &prava);
}