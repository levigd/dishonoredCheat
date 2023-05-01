#pragma once

#include <Windows.h>

void nop_(PVOID address, int bytes)
{
	DWORD oldPrava, newPrava;
	VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &oldPrava);
	memset(address, 0x90, bytes);
	VirtualProtect(address, bytes, oldPrava, &newPrava);
}