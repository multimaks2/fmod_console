#pragma once
typedef unsigned int   uint;

#include <stdio.h>
#include <Windows.h>
#include <windows.h>
#include <tchar.h>
#include <Wincon.h>
#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <comdef.h> 

#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_common.h"
#include "fmod_errors.h"
#include "SString.h"

#include <iostream>
#include <cctype>
#include <cstring>
#define is_delim(c) (std::isspace((c)) || std::ispunct((c)))
#define NUMELMS(aa) (sizeof(aa)/sizeof((aa)[0]))
FMOD_RESULT result;

//FMOD_CAPS caps;
char name[256];
int mChannel = 8;

char* remove_words(char* s, const char* w)
{
	char* t = s;
	if ((s = std::strstr(s, w)) == NULL)
		return t;

	const size_t n = std::strlen(w);
	for (char* p = s; *s; *s = *p) {
		if (!std::strncmp(p, w, n) && (p == t || is_delim(*(p - 1))) && (!*(p + n) || is_delim(*(p + n))))
			p += n;
		else {
			++s;
			++p;
		}
	}
	return t;
}

SString fullFileSoundDir(SString val1, const char* result)
{
	val1 += result;
	SString C = val1.c_str();
	return C;
}

char arrc[9000] = { 0 };



SString getDirFile(const char* searchFile, const char* consolePath)
{
	strncpy_s(arrc, consolePath, 9000);
	const char* clearDir = remove_words(arrc, "fmod_console.exe");
	return fullFileSoundDir(clearDir, searchFile);
}




auto outPutConsoleMessage(const char* msg)
{

	std::cout << msg << "\n";
}


void FMODErrorCheck(FMOD_RESULT result, const char* funcName)
{
	if (result == FMOD_OK)
	{
		std::cout << "[" << funcName << "] - FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		//exit(-1);
	}
}
TCHAR szFileName[MAX_PATH], szPath[MAX_PATH];

int ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}


bool release(bool b1, bool b2);

bool closeConsoleFmod(int timer)
{
	int timers = timer;
	while (timers != 0)
	{
		timers = timers - 1;
		std::cout << "До закрытия - " << timers + 1 << "sec.\n";
		Sleep(1000);
		if (timers == 0)
		{

			release(true, true);
			Sleep(750);
			exit(0);
		}

	}
	return true;
}



HANDLE g_hEvent = 0;
int timers = 1;
BOOL WINAPI HandlerRoutine(
	DWORD dwCtrlType   //  control signal type
)
{
	if (!g_hEvent)
		return FALSE;

	switch (dwCtrlType)
	{
	case CTRL_C_EVENT:

		release(true, true);
		SetEvent(g_hEvent);
		break;
	case CTRL_BREAK_EVENT:
		outPutConsoleMessage("Ctrl+Break pressed");
		SetEvent(g_hEvent);
		break;
	case CTRL_CLOSE_EVENT:
		outPutConsoleMessage("Close pressed");
		SetEvent(g_hEvent);
		break;
	case CTRL_LOGOFF_EVENT:
		outPutConsoleMessage("User logoff");
		SetEvent(g_hEvent);
		break;
	case CTRL_SHUTDOWN_EVENT:
		outPutConsoleMessage("System shutdown");
		SetEvent(g_hEvent);
		break;
	}

	return TRUE; // as we handle the event
}









template <class T, int SIZE>
struct SFixedArray
{
	T& operator[](uint uiIndex)
	{
		assert(uiIndex < SIZE);
		return data[uiIndex];
	}

	const T& operator[](uint uiIndex) const
	{
		assert(uiIndex < SIZE);
		return data[uiIndex];
	}

	T data[SIZE];
};



struct flagfmodinit
{
	const char* Flag_Name;
	unsigned int flag;
};

static const SFixedArray<flagfmodinit, 13> getFmodFlags = { {
	{"FMOD_INIT_NORMAL", FMOD_INIT_NORMAL},
	{"FMOD_INIT_STREAM_FROM_UPDATE", FMOD_INIT_STREAM_FROM_UPDATE},
	{"FMOD_INIT_MIX_FROM_UPDATE", FMOD_INIT_MIX_FROM_UPDATE},
	{"FMOD_INIT_3D_RIGHTHANDED", FMOD_INIT_3D_RIGHTHANDED},
	{"FMOD_INIT_CHANNEL_LOWPASS", FMOD_INIT_CHANNEL_LOWPASS},
	{"FMOD_INIT_CHANNEL_DISTANCEFILTER", FMOD_INIT_CHANNEL_DISTANCEFILTER},
	{"FMOD_INIT_PROFILE_ENABLE", FMOD_INIT_PROFILE_ENABLE},
	{"FMOD_INIT_VOL0_BECOMES_VIRTUAL", FMOD_INIT_VOL0_BECOMES_VIRTUAL},
	{"FMOD_INIT_GEOMETRY_USECLOSEST", FMOD_INIT_GEOMETRY_USECLOSEST},
	{"FMOD_INIT_PREFER_DOLBY_DOWNMIX", FMOD_INIT_PREFER_DOLBY_DOWNMIX},
	{"FMOD_INIT_THREAD_UNSAFE", FMOD_INIT_THREAD_UNSAFE},
	{"FMOD_INIT_PROFILE_METER_ALL", FMOD_INIT_PROFILE_METER_ALL},
	{"FMOD_INIT_MEMORY_TRACKING", FMOD_INIT_MEMORY_TRACKING},
} };




unsigned int getFmodFlag(const char* flagName)
{
	for (unsigned int i = 0; i <= (12); i++)
	{
		if (_stricmp(flagName, getFmodFlags[i].Flag_Name) == 0 || (getFmodFlags[i].Flag_Name && _stricmp(flagName, getFmodFlags[i].Flag_Name) == 0))
		{
			return getFmodFlags[i].flag;
		}
	}
	return getFmodFlags[0].flag;
}




struct flagfmodstudioinit
{
	const char* Flag_Name;
	unsigned int flag;
};

static const SFixedArray<flagfmodstudioinit, 7> getFmodStudioFlags = { {
	{"FMOD_STUDIO_INIT_NORMAL"                ,FMOD_STUDIO_INIT_NORMAL},
	{"FMOD_STUDIO_INIT_LIVEUPDATE"            ,FMOD_STUDIO_INIT_LIVEUPDATE},
	{"FMOD_STUDIO_INIT_ALLOW_MISSING_PLUGINS" ,FMOD_STUDIO_INIT_ALLOW_MISSING_PLUGINS},
	{"FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE"    ,FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE},
	{"FMOD_STUDIO_INIT_DEFERRED_CALLBACKS"    ,FMOD_STUDIO_INIT_DEFERRED_CALLBACKS},
	{"FMOD_STUDIO_INIT_LOAD_FROM_UPDATE"      ,FMOD_STUDIO_INIT_LOAD_FROM_UPDATE},
	{"FMOD_STUDIO_INIT_MEMORY_TRACKING"       ,FMOD_STUDIO_INIT_MEMORY_TRACKING},
} };

unsigned int getFmodStudioFlag(const char* flagName)
{
	for (unsigned int i = 0; i <= (6); i++)
	{
		if (_stricmp(flagName, getFmodStudioFlags[i].Flag_Name) == 0 || (getFmodStudioFlags[i].Flag_Name && _stricmp(flagName, getFmodStudioFlags[i].Flag_Name) == 0))
		{
			return getFmodStudioFlags[i].flag;
		}
	}
	return getFmodStudioFlags[0].flag;
}




char* wchar_to_char(const wchar_t* pwchar)
{
	// get the number of characters in the string.
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	// allocate a new block of memory size char (1 byte) instead of wide char (2 bytes)
	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		// convert to char (1 byte)
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}

const char* getConsolePath()
{
	WCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, sizeof(buffer) / sizeof(buffer[0]));
	auto res = wchar_to_char(buffer);

	return res;
}

