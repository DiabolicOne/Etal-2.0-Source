//////////////////////////////////////////////////////////////////////
// OOG.h
//////////////////////////////////////////////////////////////////////
#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "D2Pointers.h"
#include "Common.h"
#include "Constants.h"
#include "Input.h"
#include "Main.h"
#include "D2Intercepts.h"


// Some buttons
#define BUTTON_SP findControl(CONTROL_BUTTON, 5106, -1, 264,324,272,35)
DWORD WINAPI MainThread(VOID*);
void LoadMPQ(const char* mpq);
void  Logincontrol();

enum ClientGameState
{
	ClientStateNull, ClientStateMenu, ClientStateInGame, ClientStateBusy
};

class OOG
{
public:
	OOG(void);
	~OOG(void);

public:
	static OOG_Location GetLocationID();

	static Control* findControl(int Type, int LocaleID, int Disabled, int PosX, int PosY, int SizeX, int SizeY);
	static Control* findControl(int Type, const char* Text, int Disabled, int PosX, int PosY, int SizeX, int SizeY);

	static bool clickControl(Control* pControl, int x = -1, int y = -1);
	static void SetControlText(Control* pControl, const char* Text);
	//bool CreateGame(const char* GameName, const char* Password, int Difficulty, int LevelDifference, char* Description);
	//static bool CreateGame(const char* GameName, const char* Password, int Difficulty);
	//static bool JoinGame(const char* GameName, const char* Password);

	//static bool CreateCharacter(char* CharName, int type, bool hardcore, bool ladder);
	static bool SelectCharacter(const char* Character);

	//static bool SendCopyData(int type, char* data);

	static ClientGameState ClientState(void);
};

struct SData
{
	char  str[255];

};

