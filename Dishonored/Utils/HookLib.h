#pragma once

#include <Windows.h>
#include <cstdio>

void Hook(void* address, void* hook);

DWORD tramplineHook(void* address, void* hook, int size = 5);

void tramplineUnHook(void* address, void* gateway, int size = 5);
