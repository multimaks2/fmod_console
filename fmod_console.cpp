// fmod_console.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "Header.h"
#include "FMOD_API.h"


struct bankiInf
{
	SString bank;
};

static const SFixedArray<bankiInf, 4> tableBank =
{ {
	{getDirFile("audio\\ks_toyota_ae86_tuned.bank", getConsolePath())},
	{getDirFile("audio\\Master.bank", getConsolePath())},
	{getDirFile("audio\\Master.strings.bank", getConsolePath())},
	{getDirFile("audio\\Vehicles.bank", getConsolePath())},
} };


void fmod_main_load()
{
	//outPutConsoleMessage(tableBank[0].bank);


	auto audio = getDirFile("audio\\4k.wav", getConsolePath());
	SString bank = getDirFile("audio\\Vehicles.bank", getConsolePath());
	
	initArray(); // �������������� ������������ ������

	if (createFmod())
	{
		outPutConsoleMessage("FMOD - ������");
	}
	if (initFmod(512, "FMOD_INIT_PROFILE_ENABLE"))
	{
		outPutConsoleMessage("FMOD - ���������������");
	}
	if (createFmodStudio())
	{
		outPutConsoleMessage("FMOD STUDIO - ������");
	}
	if (initFmodStudio(1024, "FMOD_STUDIO_INIT_LIVEUPDATE", "FMOD_INIT_PROFILE_ENABLE"))
	{
		outPutConsoleMessage("FMOD STUDIO - ���������������");
	}

	for (size_t i = 0; i < 2; i++)
	{
		outPutConsoleMessage("--------------------------------");
	}
	

	
	for (int i = 0; i < NUMELMS(tableBank); i++)
	{
		if (LoadBankFile(tableBank[i].bank))
		{
			outPutConsoleMessage(tableBank[i].bank + " -> ���������");
			std::cout << getBankLoadingState(tableBank[i].bank) << "\n";
		}


			
	}

	outPutConsoleMessage("--------------------------------");
	const char* eventNamessss = "{3ad418ed-bf88-432d-837a-469d7468bda2}"; // {3ad418ed-bf88-432d-837a-469d7468bda2}
	if (LoadEvent(eventNamessss) )
	{
		outPutConsoleMessage("Event ������ � �������");
		
		if (PlayEvent(eventNamessss))
		{
			outPutConsoleMessage("Event �������");
			if (createChannelGroup("game_fmod"))
			{
				outPutConsoleMessage("FMOD - �������� ������ �������");
			}
			outPutConsoleMessage("--------------------------------");
			set3DAttributes(eventNamessss, 0, 0, 0);
			setEventVolume(eventNamessss, .15);
			setEventReverbLevel(eventNamessss,0,30);
			getEventReverbLevel(eventNamessss);
			getDriver();

			updaterSlep();
		}
	}
	

	//if (createSound(audio))
	//{
	//	outPutConsoleMessage("FMOD - ���� ������");
	//}
}




int main()
{
	SetConsoleTitleW(L"Moon Studio - Test Console API (FMOD)");
	setlocale(LC_ALL, "Rus");

	fmod_main_load();

	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);

	if (g_hEvent)
	{
		outPutConsoleMessage("�������� �������� ����...\n");
		WaitForSingleObject(g_hEvent, INFINITE);
		CloseHandle(g_hEvent);
	}
	else
	{
		outPutConsoleMessage("������ �������� ������\n");
	}
	outPutConsoleMessage("\n������� �� ����� ������,��� ������");
	SetConsoleCtrlHandler(HandlerRoutine, FALSE);
	exit(0);
	return 0;
}