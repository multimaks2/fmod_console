#pragma once 
#include "Header.h"

#include "fmod_studio.hpp"
#include "fmod.hpp"

//// залупа
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
//// залупа


FMOD::System* f_system;
FMOD::Studio::System* f_studio;

FMOD::ChannelGroup* channelGroup = nullptr;
FMOD::Sound* sound = nullptr;
FMOD::Channel* channel = nullptr;
FMOD::Studio::Bank* vehiclesBank;
FMOD::Studio::EventDescription* eventDescription = NULL;
FMOD::Studio::EventInstance* eventInstance = NULL;
FMOD::Studio::Bank* localizedBank = NULL;

struct myArray {
	int mnNextChannelId;
	typedef std::map<SString,std::map<SString,SString> > testBank;
	typedef std::map<SString, FMOD::Studio::Bank*> BankMap;
	typedef std::map<SString, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;
	typedef std::map<SString, FMOD::Studio::EventInstance*> EventMap;

	testBank mTest;
	BankMap mBanks;
	EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannels;
};

myArray* ArrayMap = nullptr;

void initArray()
{
	ArrayMap = new myArray;
	ArrayMap->mTest["elem::user1"]["Data"] = "TestData";
	auto test = ArrayMap->mTest["elem::user11"]["Data"];
}

bool createFmod()
{
	if (FMOD::System_Create(&f_system) == FMOD_OK)

		return true;
	return false;

}

bool initFmod(int channel, const char* flag)
{
	if (f_system->init(channel, getFmodFlag(flag), nullptr) == FMOD_OK)
		return true;
	return false;
}

bool createChannelGroup(const char* GroupName)
{
	result = f_system->createChannelGroup(GroupName, &channelGroup);
	//FMODErrorCheck(result, GroupName =+ "Created");
	if (result == FMOD_OK)
		return true;
	return false;
}

bool createSound(const char* soundDir)
{
	FMOD::Sound* pSound = nullptr;
	result = f_system->createSound(soundDir, FMOD_DEFAULT, nullptr, &pSound);
	if (result == FMOD_OK)
		ArrayMap->mSounds[soundDir] = pSound;
		return true;
	return false;
}

int playSound(const char* soundDir)
{
	int nChannelID = ArrayMap->mnNextChannelId++;
	FMOD::Channel* pChannel = nullptr;

	result = f_system->playSound(ArrayMap->mSounds[soundDir], nullptr, false, &pChannel);
	ArrayMap->mChannels[nChannelID] = pChannel;
	if (result == FMOD_OK)
	{
		outPutConsoleMessage("FMOD - Звук запущен");
	}
		
	return nChannelID;
}






bool LoadBankFile(const char* bankDir)
{
	FMOD::Studio::Bank* pBank;
	result = f_studio->loadBankFile(bankDir, FMOD_STUDIO_LOAD_BANK_NORMAL,&pBank);
	if (result == FMOD_OK)
		ArrayMap->mBanks[bankDir] = pBank;
		return true;
}

bool UnloadBankFile(const char* bankDir)
{
	result = ArrayMap->mBanks[bankDir]->unload();
	if (result == FMOD_OK)
	{
		if (ArrayMap->mBanks.erase(bankDir))
		{
			return true;
		}
	}
	return false;
}

int getBankLoadingState(const char* bankDir)
{
	FMOD_STUDIO_LOADING_STATE state;
	result = ArrayMap->mBanks[bankDir]->getLoadingState(&state);
	if (result == FMOD_OK)
		return state;
	return -1;
}

bool LoadEvent(const char* eventName)
{
	FMOD::Studio::EventDescription* pEventDescription = NULL;
	result = f_studio->getEvent(eventName, &pEventDescription);
	if (pEventDescription)
	{
		FMOD::Studio::EventInstance* pEventInstance = NULL;
		pEventDescription->createInstance(&pEventInstance);
		if (pEventInstance)
		{
			ArrayMap->mEvents[eventName] = pEventInstance;
			return true;
		}
	}
	return false;
}

bool PlayEvent(const char* eventName)
{
	//auto localEvent = ArrayMap->mEvents.find(eventName);
	ArrayMap->mEvents[eventName]->start();
	return true;
}

bool StopEvent(const char* eventName, bool bImmediate)
{
	auto localEvent = ArrayMap->mEvents.find(eventName);
	FMOD_STUDIO_STOP_MODE eMode;
	eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
	localEvent->second->stop(eMode);
	return true;
}

bool setEventParameterByName(const char* eventName,const char* parametr,float value)
{
	ArrayMap->mEvents[eventName]->setParameterByName(parametr,value);
	ArrayMap->mEvents[eventName]->start();
	return true;
}

struct PlaybackStateInfo
{
	SString Rus_Name;
};

static const SFixedArray<PlaybackStateInfo, 6> PlaybackRusName =
{{
	{"Запущен"},
	{"Ожидание?"},
	{"Остановлен"},
	{"Запуск"},
	{"Останавливается"},
	{"Принудительное включение"},
}};

int getEventPlaybackState(const char* eventName)
{
	// Воспроизведение 0, поддержание 1, остановка 2, запуск 3, остановка 4, принудительное включение 5
	FMOD_STUDIO_PLAYBACK_STATE state ;
	if (ArrayMap->mEvents[eventName]->getPlaybackState(&state) == FMOD_OK)
	{
		std::cout << "\rСобытие: " << eventName << " Состояние: " << PlaybackRusName[state].Rus_Name;

		//std::cout << eventName << " playBack state = " << PlaybackRusName[state].Rus_Name << "\n";
		return state;
	}
		
	return -1;
}



void set3DAttributes(const char* eventName, float forward_z, float up_y ,float fx, float fy, float fz)
{
	FMOD_3D_ATTRIBUTES attributes = { { 0 } };
	attributes.forward.z = forward_z;
	attributes.up.y = up_y;
	f_studio->setListenerAttributes(0, &attributes);
	attributes.position.x = fx;
	attributes.position.y = fy;
	attributes.position.z = fz;
	ArrayMap->mEvents[eventName]->set3DAttributes(&attributes);

	//return true;
}

float getEventReverbLevel(const char* eventName)
{
	float lvl = .0f;
	return lvl;
}

bool setEventReverbLevel(const char* eventName,int index,float level)
{
   result = ArrayMap->mEvents[eventName]->setReverbLevel(index,level);
   //if (FMOD_OK == result)
	 //std::cout << eventName << " setEventReverbLevel " << index << " " << level <<  std::endl;
}

bool setEventVolume(const char* name,float value)
{
	ArrayMap->mEvents[name]->setVolume(value);
	return true;
}

int getDriver()
{
	int driver = 0;
	f_system->getDriver(&driver);
	return driver;
}

void setDriver(int id)
{
	f_system->setDriver(id);
}

float getBusVolume()
{
	float volume = 0.0f;
	//checkErrors(bus->value()->getVolume(&volume));
	return volume;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

bool createFmodStudio()
{
	if (FMOD::Studio::System::create(&f_studio) == FMOD_OK)
		return true;
	return false;
}

void* extraDriverData = NULL;

bool initFmodStudio(int channel, const char* oneFlag, const char* twoFlag)
{
	if (f_studio->initialize(channel, getFmodStudioFlag(oneFlag), getFmodFlag(twoFlag), extraDriverData) == FMOD_OK)
		return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////






bool update(bool b1, bool b2) // 1 bool (core fmod) - 2 bool (studio fmod)
{
	if (b1 == true)
		f_system->update();
	if (b2 == true)
		f_studio->update();
	return true;
}


void updaterSlep()
{
	float localI = 0;
	bool reverse = false;
	do
	{
		if (reverse == false)
		{
			localI = localI + 0.1;
			if ((int)localI >= 3)
			{
				reverse = true;
			}
		}
		else if (reverse == true)
		{
			localI = localI - 0.1;
			if ((int)localI <= -3)
			{
				reverse = false;
			}
		}
		//std::cout << localI << "\r";
		set3DAttributes("{3ad418ed-bf88-432d-837a-469d7468bda2}", 1, 1, localI, localI, localI); // рандом точки звука
		if (getEventPlaybackState("{3ad418ed-bf88-432d-837a-469d7468bda2}") == 2)
		{
			PlayEvent("{3ad418ed-bf88-432d-837a-469d7468bda2}");
		}


		update(true, true);

		
		Sleep(100);
	} while (true);
}

bool release(bool b1, bool b2) // 1 bool (core fmod) - 2 bool (studio fmod)
{
	if (b1 == true)
		f_studio->unloadAll();
	if (b2 == true)
		f_studio->release();

	return true;
}









