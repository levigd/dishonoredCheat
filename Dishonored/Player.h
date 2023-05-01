#pragma once

#include <cstdint>

//ServerSidePlayerClass
class CPlayer
{
public:
	char pad_0000[836]; //0x0000
	int32_t iHealth; //0x0344
	char pad_0348[1816]; //0x0348
	int32_t iMana; //0x0A60
	char pad_0A64[1500]; //0x0A64
	
}; //Size: 0x1040

//ClientSidePlayerClass
class CPlayer2
{
public:
	char pad_0000[1008]; //0x0000
	int32_t iHealth; //0x03F0
	char pad_03F4[4]; //0x03F4
	int32_t iMana; //0x03F8
	char pad_03FC[3140]; //0x03FC
}; //Size: 0x1040