#include "OOG.h"
#include "Offset.h"
Profile  Prof;
Variables Vars;

void SendCopyData(int  code, char* data)// make this bool later on
{
	HWND EtalhWnd = FindWindow(NULL, "Etal Manager");
	if (!EtalhWnd)
	{
		return;
	}
	DWORD thwnd = GetCurrentProcessId();

	char* lpszString = data;
	COPYDATASTRUCT cds;
	cds.dwData = code;
	cds.cbData = sizeof(TCHAR) * (strlen(lpszString) + 1);
	cds.lpData = lpszString;
	//bool b = SendMessage(EtalhWnd, WM_COPYDATA, thwnd, (LPARAM)&cds) != 0;
	SendMessage(EtalhWnd, WM_COPYDATA, thwnd, (LPARAM)&cds);
	return;
}


DWORD WINAPI MainThread(VOID* param)
{
	Input* input = new Input;
	input->Initialize();

	bool starter = true;
	bool ingame = false;

	#pragma region Key_Handling

	if (Vars.bzUseRawKeys == true)
	{
		if (Pointer::ADDRawKeys(Prof.KeyOwner, Prof.Classic, Prof.Lod))
		{
			SendCopyData(11, "Loaded Raw Keys");
			SendCopyData(11, Vars.szKeyOwner);
			SendCopyData(11, Vars.szClassic);
			SendCopyData(11, Vars.szLod);
		}
		else {
			SendCopyData(11, "Error Loading Raw Keys");
		}
	}
	else if (Vars.bzUseRawKeys == false)
	{
		if (Pointer::LoadCDKeyMPQ(Prof.MpqFile))
		{
			SendCopyData(11, "Loaded Key MPQ");
			SendCopyData(11, Vars.szMpqfile);
		}
		else {
			SendCopyData(11, "Error Loading Key MPQ");
		}
		
	}


	#pragma endregion

	while (true)
	{
		switch (OOG::ClientState())
		{
		case ClientStateInGame:
			if (ingame)
			{
				Sleep(10);
			}
			else
			{
				Sleep(1000);				
				ingame = true;
				starter = true;
				SetWindowText(fpGetHwnd(), "Etal - In Game");
			}
			break;
		case ClientStateMenu:
			if (starter)
			{
				starter = false;
				ingame = false;
				SetWindowText(fpGetHwnd(), "Etal");
				Sleep(1000);
			}
			Logincontrol();
			break;
		case ClientStateBusy:
			Sleep(1000);
			break;
		case ClientStateNull:
			Sleep(1000);

			break;
		}
		Sleep(100);
	}

	return 0;

}

void  Logincontrol()
{

	switch (OOG::GetLocationID())
	{

	case OOG_MAIN_MENU:
		{
			
			if (Prof.Realm == 0)//SinglePlayer
			{
				Control* pControl = OOG::findControl(CONTROL_BUTTON, (char *)NULL, -1, 264, 324, 272, 35);
				if (pControl && pControl->wText2) {
					OOG::clickControl(pControl, 295, 315);
					Sleep(1000);
				}
				return;
			}


			Control* pControl = OOG::findControl(CONTROL_BUTTON, (char *)NULL, -1, 264, 391, 272, 25);
			if (pControl && pControl->wText2) {
				char* cstr = "";
				char* szLine = wchart_to_char(pControl->wText2);

				if (Prof.Realm == 1) { cstr = "GATEWAY: U.S. WEST";}
				if (Prof.Realm == 2) { cstr = "GATEWAY: U.S. EAST";}
				if (Prof.Realm == 3) { cstr = "GATEWAY: ASIA";}
				if (Prof.Realm == 4) { cstr = "GATEWAY: EUROPE";}

				if (strcmp(cstr, szLine) != 0) {
					if (!OOG::clickControl(pControl, 364, 375))
						return;

					Sleep(750);
					if (!OOG::clickControl(pControl, -1, 320 + ((Prof.Realm * 24) + 12))) { return; }

					//OK Button
					pControl = OOG::findControl(CONTROL_BUTTON, (char *)NULL, -1, 281, 538, 96, 32);
					if (pControl) {
						if (!OOG::clickControl(pControl, 281, 515)) { return; }
					}
					Sleep(750);
				}
				// Bnet connect
				pControl = OOG::findControl(CONTROL_BUTTON, "BATTLE.NET", -1, -1, -1, -1, -1);

				if (pControl) {
					Sleep(50);
					Input::SendMouseClick(295, 355, 0);
					Sleep(50);
				}
				while (true) {
					Sleep(250);
					if (OOG::GetLocationID() == 9) { break; }
				}

			}
		}
		break;

	case OOG_CHAR_SELECT:
		Sleep(2000);

			switch (int(Prof.Charloc))
			{
			case 0:
				Input::SendMouseClick(150, 120, 0);
				Sleep(120);
				Input::SendMouseClick(150, 120, 0);
				break;
			case 1:
				Input::SendMouseClick(370, 120, 0);
				Sleep(120);
				Input::SendMouseClick(370, 120, 0);
				break;
			case 2:
				Input::SendMouseClick(150, 220, 0);
				Sleep(120);
				Input::SendMouseClick(150, 220, 0);
				break;
			case 3:
				Input::SendMouseClick(370, 220, 0);
				Sleep(120);
				Input::SendMouseClick(370, 220, 0);
				break;
			case 4:
				Input::SendMouseClick(150, 310, 0);
				Sleep(120);
				Input::SendMouseClick(150, 310, 0);
				break;
			case 5:
				Input::SendMouseClick(370, 310, 0);
				Sleep(120);
				Input::SendMouseClick(370, 310, 0);
				break;
			case 6:
				Input::SendMouseClick(150, 400, 0);
				Sleep(120);
				Input::SendMouseClick(150, 400, 0);
				break;
			case 7:
				Input::SendMouseClick(370, 400, 0);
				Sleep(120);
				Input::SendMouseClick(370, 400, 0);
				break;
			default:
				break;
			}
			//Sleep(50);
			//Input::SendMouseClick(695, 555, 0);
		Sleep(750);
		break;

	case OOG_DIFFICULTY:// Single Player difficulty select
		if (Prof.Difficulty == 0)
			Input::SendMouseClick(398, 280, 0);
		if (Prof.Difficulty == 1)
			Input::SendMouseClick(398, 322, 0);
		if (Prof.Difficulty == 2)
			Input::SendMouseClick(398, 366, 0);
		Sleep(750);
		break;

	case OOG_LOGIN:
	{
		Sleep(1000);
		// enter Account name
		Control* pControl = OOG::findControl(1, (char *)NULL, -1, 322, 342, 162, 19);
		if (!pControl)
			return;
				
		OOG::SetControlText(pControl, Prof.Account);
		Sleep(750);

		// enter pass
		pControl = OOG::findControl(1, (char *)NULL, -1, 322, 396, 162, 19);
		if (!pControl)
			return;

		OOG::SetControlText(pControl, Prof.AccPass);
		Sleep(1200);
		// click login
		pControl = OOG::findControl(6, (char *)NULL, -1, 264, 484, 272, 35);
		if (pControl)
		{
			OOG::clickControl(pControl, 264, 470);
		}
		Sleep(500);
	}
		break;
	case	OOG_D2SPLASH://	//18 Spash
		SetWindowText(fpGetHwnd(), "Etal Test");
		Sleep(50);
		Input::SendMouseClick(10, 10, 0);
		Sleep(2000);
		break;
	case OOG_LOGIN_ERROR:
		//char* temp = Prof.Account;
		//
		//if (Prof.Realm == 1)
		//	strcat_s(temp, 125, ", USWest");
		//if (Prof.Realm == 2)
		//	strcat_s(temp, 125, ", USEast");
		//if (Prof.Realm == 3)
		//	strcat_s(temp, 125, ", Asia");
		//if (Prof.Realm == 4)
		//	strcat_s(temp, 125, ", Europe");
		//char temp1[125];
		//strcpy_s(temp1, temp);
		//SendCopyData(10, temp1);		
		break;
	}	

	return;
}

