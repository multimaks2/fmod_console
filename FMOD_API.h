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
FMOD::Studio::Bank* localRadzedBank = NULL;
FMOD::Reverb3D* reverb;

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
	result = ArrayMap->mEvents[eventName]->setParameterByName(parametr, value);
	if (result == FMOD_OK)
	{
		result = ArrayMap->mEvents[eventName]->start();
		ArrayMap->mEvents[eventName]->setReverbLevel(0,2);
		if (!result == FMOD_OK)
			return false;
	}
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
		//std::cout << "\rСобытие: " << eventName << " Состояние: " << PlaybackRusName[state].Rus_Name << "\r";

		//std::cout << eventName << " playBack state = " << PlaybackRusName[state].Rus_Name << "\n";
		return state;
	}
		
	return -1;
}



bool set3DAttributes(const char* eventName, float forward_z, float up_y ,float fx, float fy, float fz)
{
	FMOD_3D_ATTRIBUTES attributes = {  };
	attributes.forward.z = forward_z;
	attributes.velocity = {0,0,0};
	attributes.up.y = up_y;
	f_studio->setListenerAttributes(1, &attributes);
	attributes.position.x = fx;
	attributes.position.y = fy;
	attributes.position.z = fz;
	ArrayMap->mEvents[eventName]->set3DAttributes(&attributes);
	return true;
}




float getEventReverbLevel(const char* eventName)
{
	float lvl = .0f;
	return lvl;
}

bool update(bool b1, bool b2);
//*@brief Set the reverb level of the event
//* @param[in] index(int) Index of the low level reverb instance(0 - 3)
//* @param[in] reverb(float) The reverb level to set it to
bool setEventReverbLevel(const char* eventName,int index,float level)
{

	result = f_system->createReverb3D(&reverb);
	FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
	reverb->setProperties(&prop2);
	FMOD_VECTOR pos = { -10.0f, 0.0f, 0.0f };
	float mindist = 10.0f;
	float maxdist = 20.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);
	FMOD_VECTOR  listenerpos = { 0.0f, 0.0f, -1.0f };
	f_system->set3DListenerAttributes(0, &listenerpos, 0, 0, 0);
   result = ArrayMap->mEvents[eventName]->setReverbLevel(index,level);
   if (FMOD_OK == result)
	 std::cout << eventName << " setEventReverbLevel int: " << index << " float: " << level <<  std::endl; // Дебаг информация
   update(true, true);
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


#include <cmath>
#include <iostream>


bool update(bool b1, bool b2) // 1 bool (core fmod) - 2 bool (studio fmod)
{
	if (b1 == true)
		f_system->update();
	if (b2 == true)
		f_studio->update();
	return true;
}

void calcXY(double angle, double radius, double& x, double& y) {
	// Convert angle from degrees to radians
	double theta = angle * 3.14159265358979323846 / 180.0;

	// Calculate x and y coordinates
	x = radius * cos(theta);
	y = radius * sin(theta);
}


void rotate(const char* evv)
{
	double angle = 0;
	double radius = 20;
	while (true) {
		angle = angle + 1;
		if (angle >= 360)
		{
			angle = 0;
		}
		double x, y;
		calcXY(angle, radius, x, y);

		std::cout << "Angle " << angle << " - " << "x: " << x << ", y: " << y << "\r";

		float forward_z = cos(angle);
		float up_y = sin(angle);
		set3DAttributes(evv, forward_z, up_y, x, y, 0); // рандом точки звука

		update(true, true);
		Sleep(100);
		if (getEventPlaybackState(evv) == 2)
		{
			PlayEvent(evv);
		}
	}
}

bool release(bool b1, bool b2) // 1 bool (core fmod) - 2 bool (studio fmod)
{
	if (b1 == true)
		f_studio->unloadAll();
	if (b2 == true)
		f_studio->release();
	return true;
}









