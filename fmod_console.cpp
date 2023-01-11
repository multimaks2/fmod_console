// fmod_console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"
#include "FMOD_API.h"


struct bankiInf
{
	SString bank;
};

static const SFixedArray<bankiInf, 3> tableBank =
{ {
	//{getDirFile("audio\\ks_toyota_ae86_tuned.bank", getConsolePath())},
	{getDirFile("audio\\Master.bank", getConsolePath())},
	{getDirFile("audio\\Master.strings.bank", getConsolePath())},
	{getDirFile("audio\\Vehicles.bank", getConsolePath())},
} };


void fmod_main_load()
{
	auto audio = getDirFile("audio\\4k.wav", getConsolePath());
	SString bank = getDirFile("audio\\Vehicles.bank", getConsolePath());
	
	initArray(); // иницаилизируем динамический массив

	if (createFmod())
	{
		outPutConsoleMessage("FMOD - Создан");
	}
	if (initFmod(512, "FMOD_INIT_PROFILE_ENABLE"))
	{
		outPutConsoleMessage("FMOD - Инициализирован");
	}
	if (createFmodStudio())
	{
		outPutConsoleMessage("FMOD STUDIO - Создан");
	}
	if (initFmodStudio(1024, "FMOD_STUDIO_INIT_LIVEUPDATE", "FMOD_INIT_PROFILE_ENABLE"))
	{
		outPutConsoleMessage("FMOD STUDIO - Инициализирован");
	}

	for (size_t i = 0; i < 2; i++)
	{
		outPutConsoleMessage("--------------------------------");
	}
	

	
	for (int i = 0; i < NUMELMS(tableBank); i++)
	{
		if (LoadBankFile(tableBank[i].bank))
		{
			outPutConsoleMessage(tableBank[i].bank + " -> Загружены" );
			//std::cout << getBankLoadingState(tableBank[i].bank) << "\n";
		}	
	}

	outPutConsoleMessage("--------------------------------");
	const char* eventNamessss = "{87ebcfdb-ad26-4998-bf1b-b3087d505a45}"; // {3ad418ed-bf88-432d-837a-469d7468bda2}
	if (LoadEvent(eventNamessss) )
	{
		outPutConsoleMessage("Event найден и записан");
		
		if (PlayEvent(eventNamessss))
		{
			outPutConsoleMessage("Event запущен");
			if (createChannelGroup("game_fmod"))
			{
				outPutConsoleMessage("FMOD - Звуковая группа создана");
			}
			outPutConsoleMessage("--------------------------------");
			
			set3DAttributes(eventNamessss, 1,1 ,0, 0, 0); // 2 аргумента слушателя
			setEventVolume(eventNamessss, 60);
			setEventReverbLevel(eventNamessss,3,30.0f);
			getEventReverbLevel(eventNamessss);
			getDriver();

			updaterSlep();
		}
	}
}




int main()
{
	SetConsoleTitleW(L"Moon Studio - [Console FMOD]");
	setlocale(LC_ALL, "Rus");

	fmod_main_load();

	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);

	if (g_hEvent)
	{
		outPutConsoleMessage("Ожидание закрытия окна...\n");
		WaitForSingleObject(g_hEvent, INFINITE);
		CloseHandle(g_hEvent);
	}
	else
	{
		outPutConsoleMessage("Ошибка создания эвента\n");
	}
	outPutConsoleMessage("\nНажмите на любую кнопку,для выхода");
	SetConsoleCtrlHandler(HandlerRoutine, FALSE);
	exit(0);
	return 0;
}