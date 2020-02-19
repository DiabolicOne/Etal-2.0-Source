//////////////////////////////////////////////////////////////////////
// Pointers.h
//////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __D2PTRS_H__
#define __D2PTRS_H__
#endif
#include <Windows.h>
#include "D2Structs.h"

class Pointer
{
public:
	Pointer();
	~Pointer();

	static void DefineOffsets();
	static DWORD GetDllOffset(const char* DLL_NAME, int OFFSET);
	static DWORD GetDllOffset(int num);
	static BOOL LoadCDKeyMPQ(const char* mpq);
	static BOOL ADDRawKeys(const char* owner, const char* classic, const char* lod);
	static void InstallRawInfo();
	static void RemoveRawInfo();
	static BOOL WriteBytes(void *pAddr, void *pData, DWORD dwLen);
	static void FillBytes(void *pAddr, BYTE bFill, DWORD dwLen);
	static void InterceptLocalCode(BYTE bInst, DWORD pAddr, DWORD pFunc, DWORD dwLen);
	static void PatchCall(DWORD dwAddr, DWORD dwFunc, DWORD dwLen);
	static void PatchJmp(DWORD dwAddr, DWORD dwFunc, DWORD dwLen);
	static void PatchBytes(DWORD dwAddr, DWORD dwValue, DWORD dwLen);
private:

};

//////////////////////////////////////////////////////////////////////
// Pointer declarations
//////////////////////////////////////////////////////////////////////
#ifdef DEFINE_POINTERS
enum { DLLNO_D2CLIENT, DLLNO_D2COMMON, DLLNO_D2GFX, DLLNO_D2LANG, DLLNO_D2WIN, DLLNO_D2NET, DLLNO_D2GAME, DLLNO_D2LAUNCH, DLLNO_FOG, DLLNO_BNCLIENT, DLLNO_STORM, DLLNO_D2CMP, DLLNO_D2MULTI };

#define DLLOFFSET(a1,b1) ((DLLNO_##a1)|((b1)<<8))
#define FUNCPTR(d1,v1,t1,t2,o1)	typedef t1 d1##_##v1##_t t2; d1##_##v1##_t *d1##_##v1 = (d1##_##v1##_t *)DLLOFFSET(d1,o1);
#define FPTR(CALL_TYPE, FUNC_NAME, PARAMETERS, DLL, OFFSET) typedef CALL_TYPE fp##FUNC_NAME##_t PARAMETERS; fp##FUNC_NAME##_t* fp##FUNC_NAME = (fp##FUNC_NAME##_t*)Pointer::GetDllOffset(DLL, OFFSET);
#define VPTR(VAR_TYPE, VAR_NAME, DLL, OFFSET) typedef VAR_TYPE VAR_NAME##_t; VAR_NAME##_t* vp##VAR_NAME = (VAR_NAME##_t*)Pointer::GetDllOffset(DLL, OFFSET);
#define APTR(ASM_NAME, DLL, OFFSET) extern DWORD ap##ASM_NAME;
#define VARPTR(d1,v1,t1,o1)		typedef t1 d1##_##v1##_t;    d1##_##v1##_t *p_##d1##_##v1 = (d1##_##v1##_t *)DLLOFFSET(d1,o1);
#define ASMPTR(d1,v1,o1)            DWORD d1##_##v1 = DLLOFFSET(d1,o1);
//#define APTR(ASM_NAME, DLL, OFFSET) extern DWORD* Asm_##dll##_##name##(VOID); static DWORD dll##_##name = *Asm_##dll##_##name##();
#else
#define FPTR(CALL_TYPE, FUNC_NAME, PARAMETERS, DLL, OFFSET) typedef CALL_TYPE fp##FUNC_NAME##_t PARAMETERS; extern fp##FUNC_NAME##_t* fp##FUNC_NAME;
#define VPTR(VAR_TYPE, VAR_NAME, DLL, OFFSET) typedef VAR_TYPE VAR_NAME##_t; extern VAR_NAME##_t* vp##VAR_NAME;
#define APTR(ASM_NAME, DLL, OFFSET) extern DWORD ap##ASM_NAME;
#define VARPTR(d1,v1,t1,o1)		typedef t1 d1##_##v1##_t;    extern d1##_##v1##_t *p_##d1##_##v1;
#define FUNCPTR(d1,v1,t1,t2,o1)	typedef t1 d1##_##v1##_t t2; extern d1##_##v1##_t *d1##_##v1;
#define ASMPTR(d1,v1,o1)            extern DWORD d1##_##v1;

//#define APTR(ASM_NAME, DLL, OFFSET) extern DWORD* Asm_##dll##_##name##(VOID); static DWORD dll##_##name = *Asm_##dll##_##name##();
#endif

//////////////////////////////////////////////////////////////////////
// D2Client Function Pointers
//////////////////////////////////////////////////////////////////////
FPTR(void* __stdcall, GetQuestInfo, (void), "D2Client.dll", 0x78A80)
FPTR(void __fastcall, SubmitItem, (DWORD dwItemID), "D2Client.dll", 0x79670)
FPTR(void __fastcall, Transmute, (void), "D2Client.dll", 0x94370)
FPTR(void __fastcall, ExitGame, (void), "D2Client.dll", 0x43870)
FPTR(void __fastcall, CloseNPCInteract, (void), "D2Client.dll", 0x7BC10)
FPTR(void __stdcall, CloseNPCTalk, (void* unk), "D2Client.dll", 0x77AB0)
//FPTR(void __fastcall, ClearScreen, (void), "D2Client.dll", 0x7AB80)
FPTR(void __fastcall, CloseInteract, (void), "D2Client.dll", 0x44980)
FPTR(void __stdcall, ClickMap, (DWORD MouseFlag, DWORD x, DWORD y, DWORD Type), "D2Client.dll", 0x2B420);
FPTR(void __stdcall, ClickItem, (UnitAny* pPlayer, Inventory* pInventory, int x, int y, DWORD dwClickType, InventoryLayout* pLayout, DWORD Location), "D2Client.dll", 0x9AFF0)
FPTR(DWORD __fastcall, GetMouseXOffset, (void), "D2Client.dll", 0x5BC20)
FPTR(DWORD __fastcall, GetMouseYOffset, (void), "D2Client.dll", 0x5BC30)
FPTR(void __stdcall, PrintChat, (const wchar_t* msg, int nColor), "D2Client.dll", 0x75EB0)
FPTR(void __stdcall, PrintParty, (wchar_t* msg, int nColor), "D2Client.dll", 0x75C70)
FPTR(void __stdcall, DrawLine, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwUnk), "D2GFX.dll", 0x81A0)
FPTR(UnitAny* __stdcall, GetPlayerUnit, (void), "D2Client.dll", 0x613C0)
FPTR(int __fastcall, GetUnitX, (UnitAny* pUnit), "D2Client.dll", 0x1210)
FPTR(int __fastcall, GetUnitY, (UnitAny* pUnit), "D2Client.dll", 0x1240)
FPTR(void __stdcall, SendPacket, (size_t aLen, DWORD arg1, BYTE* aPacket), "D2Net.dll", 0x6F20)
FPTR(UnitAny* __fastcall, FindClientSideUnit, (DWORD dwID, DWORD dwType), "D2Client.dll", 0x620B0)
FPTR(UnitAny* __fastcall, FindServerSideUnit, (DWORD dwID, DWORD dwType), "D2Client.dll", 0x620D0)
FPTR(BOOL __stdcall, GetItemName, (UnitAny* pItem, wchar_t* wBuffer, DWORD dwSize), "D2Client.dll", 0x958C0)

//////////////////////////////////////////////////////////////////////
// D2Client Variable Pointers
//////////////////////////////////////////////////////////////////////
VPTR(DWORD, ScreenSizeX, "D2Client.dll", 0xF7034)
VPTR(DWORD, ScreenSizeY, "D2Client.dll", 0xF7038)
VPTR(DWORD, CursorHoverX, "D2Client.dll", 0xEE4AC)
VPTR(DWORD, CursorHoverY, "D2Client.dll", 0xEE4B0)
VPTR(int, MouseOffsetX, "D2Client.dll", 0x106844)
VPTR(int, MouseOffsetY, "D2Client.dll", 0x106840)
VPTR(DWORD, AutoMapOn, "D2Client.dll", 0x11C8B8)
VPTR(int, AutoMapMode, "D2Client.dll", 0xF34F8)
VPTR(AutomapLayer*, AutomapLayer, "D2Client.dll", 0x11CF28)
VPTR(POINT, Offset, "D2Client.dll", 0x11CF5C)
VPTR(DWORD, AlwaysRun, "D2Client.dll", 0x11D234)
VPTR(GameStructInfo*, GameInfo, "D2Client.dll", 0x109738)
VPTR(DWORD, MouseX, "D2Client.dll", 0x11C950)
VPTR(DWORD, MouseY, "D2Client.dll", 0x11C94C)
VPTR(int, ViewportX, "D2Client.dll", 0x106844)
VPTR(int, ViewportY, "D2Client.dll", 0x106840)
VPTR(int, AreaID, "D2Client.dll", 0x1246C4)



//////////////////////////////////////////////////////////////////////
// D2Common Function Pointers
//////////////////////////////////////////////////////////////////////
FPTR(DWORD __stdcall, GetItemLevelRequirements, (UnitAny* pitem, UnitAny* pPlayer), "D2Common.dll", 0x45660)
FPTR(DWORD __stdcall, GetItemPrice, (UnitAny* MyUnit, UnitAny* pItem, DWORD U1_, DWORD U2_, DWORD U3_, DWORD U4_), "D2Common.dll", 0x48620)
FPTR(DWORD __stdcall, GetItemRepairCost, (DWORD _1, UnitAny* pUnit, DWORD dwNpcId, DWORD dwDifficulty, DWORD dwItemPriceList, DWORD _2), "D2Common.dll", 0x48AD0)
FPTR(char* __stdcall, GetItemMagicalMods, (WORD wPrefixNum), "D2Common.dll", 0x62AF0)
FPTR(UnitAny* __stdcall, GetItemFromInventory, (Inventory* inv), "D2Common.dll", 0x37520)
FPTR(UnitAny* __stdcall, GetNextItemFromInventory, (UnitAny* pItem), "D2Common.dll", 0x38160)
FPTR(ItemText* __stdcall, GetItemText, (DWORD dwItemNo), "D2Common.dll", 0x62C70)

//////////////////////////////////////////////////////////////////////
// D2Common Variable Pointers
//////////////////////////////////////////////////////////////////////
FPTR(void __stdcall, AbsScreenToMap, (long* pX, long* pY), "D2Common.dll", 0x35810)
FPTR(void __stdcall, MapToAbsScreen, (long* px, long* py), "D2Common.dll", 0x35AA0)

//////////////////////////////////////////////////////////////////////
// D2Client ASM Pointers
//////////////////////////////////////////////////////////////////////
APTR(ClickParty_I, "D2Client.dll", 0xA2250)
APTR(Say_I, "D2Client.dll", 0xB27A6)


//////////////////////////////////////////////////////////////////////
// D2Lang Function Pointers
//////////////////////////////////////////////////////////////////////
FPTR(wchar_t* __fastcall, GetLocaleText, (WORD nLocaleTxtNo), "D2Lang.dll", 0x98A0)

//////////////////////////////////////////////////////////////////////
// D2Lang ASM Pointers
//////////////////////////////////////////////////////////////////////
APTR(Say_II, "D2Lang.dll", 0x8C60)

//////////////////////////////////////////////////////////////////////
// D2Win Function Pointers
//////////////////////////////////////////////////////////////////////
FPTR(void* __fastcall, SetControlText, (Control* box, wchar_t* text), "D2Win.dll", 0x10680);

FPTR(void __fastcall, DrawText, (const wchar_t* wstr, int x, int y, DWORD color, DWORD unk), "D2Win.dll", 0x13B30)

//////////////////////////////////////////////////////////////////////
// D2Win Variable Pointers
//////////////////////////////////////////////////////////////////////
VPTR(Control*, FirstControl, "D2Win.dll", 0x8DB34)

//////////////////////////////////////////////////////////////////////
// D2GFX Function Pointers
//////////////////////////////////////////////////////////////////////
FPTR(HWND __stdcall, GetHwnd, (void), "D2gfx.dll", 0xB0C0)

//FPTR(DWORD __stdcall, InitMPQ, (char *dll, const char *mpqfile, char *mpqname, int v4, int v5), "D2Win.DLL", 0x7E50)
//FPTR(char __cdecl, DecodeAndLoadKeys, (), "Bnclient.dll", 0x10920)
////////////////////////////////////////////////////////////////////////////////////////////////
// D2Game Functions
////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCPTR(D2GAME, Rand, DWORD __fastcall, (DWORD* seed), 0x1050)

////////////////////////////////////////////////////////////////////////////////////////////////
// Bnclient Variable Pointers
////////////////////////////////////////////////////////////////////////////////////////////////

//these are just added for the LoadMPQ
//we can rewrite these to use your struct but I think it's nice like this
//since you can call it like BNCLIENT_CLassicKey or D2WIN_InitMPQ
#define _D2PTRS_START	D2WIN_InitMPQ
FUNCPTR(D2WIN, InitMPQ, DWORD __stdcall, (char *dll, const char *mpqfile, char *mpqname, int v4, int v5), 0x7E50)
ASMPTR(BNCLIENT, DClass, 0x15EB8)
ASMPTR(BNCLIENT, DName, 0x1607D)
ASMPTR(BNCLIENT, DLod, 0x161BD)
VARPTR(BNCLIENT, ClassicKey, char*, 0x1E928)
VARPTR(BNCLIENT, XPacKey, char*, 0x1E930)
VARPTR(BNCLIENT, KeyOwner, char*, 0x1E934)
FUNCPTR(BNCLIENT, DecodeAndLoadKeys, char __cdecl, (), 0x10920)
#define _D2PTRS_END	BNCLIENT_DecodeAndLoadKeys

#undef FPTR
#undef VPTR
#undef APTR
#undef VARPTR
#undef FUNCPTR
#undef ASMPTR

#define D2CLIENT_TestPvpFlag(dwId1, dwId2, dwFlag)		(D2CLIENT_TestPvpFlag_STUB(dwId1, dwId2, dwFlag))
#define D2CLIENT_GetUIState(dwVarNo)					(D2CLIENT_GetUIVar_STUB(dwVarNo))
#define D2CLIENT_SetUIState(dwVarNo, value)				(D2CLIENT_SetUIVar(dwVarNo, value, 0))
#define D2CLIENT_InitAutomapLayer(layerlvl)				((AutomapLayer*)D2CLIENT_InitAutomapLayer_STUB(layerlvl))
#define D2CLIENT_GetUnitName(x)							(wchar_t*)D2CLIENT_GetUnitName_STUB((DWORD)x)
#define D2CLIENT_SetSelectedUnit(x)						(D2CLIENT_SetSelectedUnit_STUB((DWORD)x))
#define D2CLIENT_LoadUIImage(x)							((CellFile*)D2CLIENT_LoadUIImage_ASM(x))
#define D2CLIENT_Interact_STUB(x)						(D2CLIENT_Interact_ASM((DWORD)x))
#define D2CLIENT_ClickParty(x,y)						(D2CLIENT_ClickParty_ASM((DWORD)x, (DWORD)y))
#define D2CLIENT_RightClickItem(x, y, loc, player, invdata) D2CLIENT_ClickItemRight_ASM(x,y, loc, (DWORD)player, (DWORD)invdata)
#define D2CLIENT_ClickBeltRight(pPlayer, pInventory, dwShift, dwPotPos)	D2CLIENT_ClickBeltRight_ASM((DWORD)pPlayer, (DWORD)pInventory, dwShift, dwPotPos)
#define D2CLIENT_GetItemDesc(pUnit, pBuffer)			D2CLIENT_GetItemDesc_ASM((DWORD)pUnit, pBuffer)
#define D2CLIENT_MercItemAction(bPacketType, dwSlotId)	D2CLIENT_MercItemAction_ASM(bPacketType, dwSlotId)
#define D2CLIENT_SendGamePacket(dwLen, bPacket)			D2CLIENT_SendGamePacket_ASM(dwLen, bPacket)
