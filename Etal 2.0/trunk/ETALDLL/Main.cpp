// dllmain.cpp : Defines the entry point for the DLL application.

#include <shlwapi.h>
#include "OOG.h"
//#include "Main.h"
#include "D2Pointers.h"
#include "Common.h"
#include "Constants.h"
#include "Input.h"
#include "D2Structs.h"
#include "Offset.h"


void CheckStruct()
{
	MessageBoxA(NULL, Prof.GameName, "Debug GameName", NULL);
	MessageBoxA(NULL, Prof.GamePass, "Debug GamePass", NULL);
	MessageBoxA(NULL, Prof.MpqFile, "Debug MpqFile", NULL);
	MessageBoxA(NULL, Prof.Classic, "Debug Classic", NULL);
	MessageBoxA(NULL, Prof.ScriptFile, "Debug ScriptFile", NULL);
	
}

void WaitForDlls()
{
	unsigned int v = 0;
	do {
		Sleep(100);
		if (GetModuleHandle("Bnclient.dll") && GetModuleHandle("D2Launch.dll") && GetModuleHandle("D2Net.dll") && GetModuleHandle("D2Win.dll"))
			break;
		++v;
	} while (v < 10);
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		int profsize = sizeof(Prof);//place mouse over "sizeof" to find struct size
		HANDLE hMap = OpenFileMappingA(FILE_MAP_READ, false, "D2NT Profile");
		if (!hMap) {
			MessageBoxA(NULL, "MMf not found", "Debug", NULL);
			return 0;
		}
		HANDLE mView = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, profsize);
		if (!mView) {
			CloseHandle(hMap);
			MessageBoxA(NULL, "MMf not found", "Debug", NULL);
			return 0;
		}

		memcpy(&Prof, mView, profsize);
		UnmapViewOfFile(mView);
		CloseHandle(hMap);

		DisableThreadLibraryCalls(hModule);
		WaitForDlls();

		Vars.hModule = hModule;
		GetModuleFileName(hModule, Vars.szScriptPath, MAX_PATH);
		PathRemoveFileSpec(Vars.szScriptPath);
		strcat_s(Vars.szScriptPath, MAX_PATH, "\\Scripts\\");

		if(strlen(Prof.Classic) > 15)
		{
			Vars.bzUseRawKeys = true;
		}
		else 
		{
			Vars.bzUseRawKeys = false;
		}

		Pointer::DefineOffsets();

		//CheckStruct();// comment out or remove later

		HANDLE hD2Thread;
		if ((hD2Thread = CreateThread(NULL, NULL, MainThread, NULL, NULL, NULL)) == NULL)
			//return FALSE;
		break;

	}
	return TRUE;
}

