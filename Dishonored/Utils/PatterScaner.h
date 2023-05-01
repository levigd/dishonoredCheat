#pragma once

#include <cstring>
#include <Windows.h>
#include <psapi.h>
#include <vector>

std::vector<int> patternToBytes(const char* pattern);

DWORD patternScan(DWORD start, DWORD end, const char* pattern);