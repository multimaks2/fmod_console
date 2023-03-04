// fmod_console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"
#include "FMOD_API.h"


struct bankiInf
{
	SString bank;
};

static const SFixedArray<bankiInf, 131> tableBank =
{ {
		{getDirFile("audio\\aircraft_ambient.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_ambient.bank",getConsolePath())},
{getDirFile("audio\\aircraft_common.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_common.bank",getConsolePath())},
{getDirFile("audio\\aircraft_effects.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_effects.bank",getConsolePath())},
{getDirFile("audio\\aircraft_engines.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_engines.bank",getConsolePath())},
{getDirFile("audio\\aircraft_gui.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_gui.bank",getConsolePath())},
{getDirFile("audio\\aircraft_guns.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_guns.bank",getConsolePath())},
{getDirFile("audio\\aircraft_music.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_music.bank",getConsolePath())},
{getDirFile("audio\\aircraft_music_2.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_music_2.bank",getConsolePath())},
{getDirFile("audio\\aircraft_music_3.assets.bank",getConsolePath())},
{getDirFile("audio\\aircraft_music_3.bank",getConsolePath())},
{getDirFile("audio\\crew_dialogs_common.assets.bank",getConsolePath())},
{getDirFile("audio\\crew_dialogs_common.bank",getConsolePath())},
{getDirFile("audio\\crew_dialogs_ground.assets.bank",getConsolePath())},
{getDirFile("audio\\crew_dialogs_ground.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_cz.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_cz.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_de.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_de.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_en.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_en.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_fr.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_fr.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_he.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_he.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_hu.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_hu.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_it.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_it.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_jp.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_jp.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_ko.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_ko.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_pl.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_pl.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_pt.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_pt.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_ru.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_ru.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_sp.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_sp.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_sr.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_sr.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_sv.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_sv.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_tr.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_tr.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_vi.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_vi.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_zh.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_zh.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_zhhx.assets.bank",getConsolePath())},
{getDirFile("audio\\dialogs_chat_zhhx.bank",getConsolePath())},
{getDirFile("audio\\getfullfile.exe",getConsolePath())},
{getDirFile("audio\\masterbank.assets.bank",getConsolePath())},
{getDirFile("audio\\masterbank.bank",getConsolePath())},
{getDirFile("audio\\masterbank.strings.bank",getConsolePath())},
{getDirFile("audio\\ships_ambient.assets.bank",getConsolePath())},
{getDirFile("audio\\ships_ambient.bank",getConsolePath())},
{getDirFile("audio\\ships_effects.assets.bank",getConsolePath())},
{getDirFile("audio\\ships_effects.bank",getConsolePath())},
{getDirFile("audio\\ships_engines.assets.bank",getConsolePath())},
{getDirFile("audio\\ships_engines.bank",getConsolePath())},
{getDirFile("audio\\ships_explosions.assets.bank",getConsolePath())},
{getDirFile("audio\\ships_explosions.bank",getConsolePath())},
{getDirFile("audio\\ships_weapon.assets.bank",getConsolePath())},
{getDirFile("audio\\ships_weapon.bank",getConsolePath())},
{getDirFile("audio\\tanks_ambient.assets.bank",getConsolePath())},
{getDirFile("audio\\tanks_ambient.bank",getConsolePath())},
{getDirFile("audio\\tanks_effects.assets.bank",getConsolePath())},
{getDirFile("audio\\tanks_effects.bank",getConsolePath())},
{getDirFile("audio\\tanks_engines.assets.bank",getConsolePath())},
{getDirFile("audio\\tanks_engines.bank",getConsolePath())},
{getDirFile("audio\\tanks_explosions.assets.bank",getConsolePath())},
{getDirFile("audio\\tanks_explosions.bank",getConsolePath())},
{getDirFile("audio\\tanks_object_crash.assets.bank",getConsolePath())},
{getDirFile("audio\\tanks_object_crash.bank",getConsolePath())},
{getDirFile("audio\\tanks_weapons.assets.bank",getConsolePath())},
{getDirFile("audio\\tanks_weapons.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_common_de.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_common_de.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_common_en.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_common_en.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_common_ru.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_common_ru.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_cz.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_cz.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_de.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_de.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_en.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_en.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_fr.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_fr.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_he.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_he.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_hu.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_hu.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_it.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_it.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_jp.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_jp.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_ko.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_ko.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_pl.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_pl.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_pt.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_pt.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_ru.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_ru.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_sp.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_sp.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_sr.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_sr.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_sv.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_sv.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_tr.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_tr.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_vi.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_vi.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_zh.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_zh.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_zhhx.assets.bank",getConsolePath())},
{getDirFile("audio\\_crew_dialogs_ground_zhhx.bank",getConsolePath())},
{getDirFile("audio\\список.txt",getConsolePath())},


} };


void toyota();
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
	toyota();
	//const char* eventNamessss = "{5206e42b-ae8f-49f6-b059-d613b2947b49}"; // {3ad418ed-bf88-432d-837a-469d7468bda2}
	//if (LoadEvent(eventNamessss) )
	//{
	//	outPutConsoleMessage("Event найден и записан");
	//	
	//	if (PlayEvent(eventNamessss))
	//	{
	//		outPutConsoleMessage("Event запущен");
	//		if (createChannelGroup("game_fmod"))
	//		{
	//			outPutConsoleMessage("FMOD - Звуковая группа создана");
	//		}
	//		outPutConsoleMessage("--------------------------------");
			//setEventParameterByName(eventNamessss, "rpms", 1225);
			//set3DAttributes(eventNamessss, 0,0 ,0, 0, 0); // 2 аргумента слушателя
			//setEventVolume(eventNamessss, 30);
			//setEventReverbLevel(eventNamessss,2,10);
			//getEventReverbLevel(eventNamessss);
			//getDriver();

			//updaterSlep(eventNamessss);
		//}
	//}
}


void toyota()
{
	const char* eventNamessss = "{6df95554-0f3f-427d-95a6-303958b35dcb}";
	if (LoadEvent(eventNamessss))
	{
		outPutConsoleMessage("toyota + load");
		PlayEvent(eventNamessss);
		setEventParameterByName(eventNamessss, "action", 0.5);
		//setEventParameterByName(eventNamessss, "planes", 0.2);
		//setEventParameterByName(eventNamessss, "rpm", 1110.1f);
		//setEventParameterByName(eventNamessss, "turbo", 0.34f);
		setEventVolume(eventNamessss, 1);
		//updaterSlep(eventNamessss);
		//const char* greeting = "Привет";
		std::thread chat_thread(rotate, eventNamessss);
		chat_thread.detach();
	}
		

}

int main()
{
	//SetConsoleTitleW(L"Moon Studio - [Console FMOD]");
	SetConsoleTitleW(L"gta_sa.exe");
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