#include "PatterScaner.h"

std::vector<int> patternToBytes(const char* pattern)
{
	std::vector<int> bytes;
	for (char* addr = (char*)pattern; addr < pattern + strlen(pattern); addr++)
	{
		if (*addr == '?')
		{
			++addr;
			if (*addr == '?')
			{
				++addr;
			}
			bytes.push_back(-2);
		}
		else
		{
			bytes.push_back(strtoul(addr, &addr, 16));
		}
	}
	return bytes;
}

DWORD patternScan(DWORD start, DWORD end, const char* pattern)
{
	std::vector<int> bytes = patternToBytes(pattern);
	for (DWORD addr = start; addr < end; ++addr)
	{

		BOOL found = true;
		for (int i = 0; i < bytes.size(); i++)
		{
			if (*(unsigned char*)(addr + i) != bytes.data()[i] && bytes.data()[i] != -2)
			{
				found = false;
				break;
			}
			//std::cout << addr << std::endl;
		}
		if (found)
		{
			return addr;
		}
	}
}