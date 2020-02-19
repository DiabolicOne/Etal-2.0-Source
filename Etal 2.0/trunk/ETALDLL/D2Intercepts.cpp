#include "D2Intercepts.h"
#include "OOG.h"

VOID __declspec(naked) __fastcall ClassicSTUB()
{
	*p_BNCLIENT_ClassicKey = Vars.szClassic;
	__asm {
		lea eax, dword ptr ss : [Vars.szClassic]
			mov dword ptr ds : [0x6FF3E928], eax
			jmp BNCLIENT_DClass;
	}
}

VOID _declspec(naked) _fastcall NameSTUB()
{
	*p_BNCLIENT_KeyOwner = Vars.szKeyOwner;
	_asm {
		lea eax, dword ptr ss : [Vars.szKeyOwner]
			mov dword ptr ds : [0x6FF3E934], eax		
			jmp BNCLIENT_DName;
	}
}

VOID __declspec(naked) __fastcall LodSTUB()
{
	*p_BNCLIENT_XPacKey = Vars.szLod;
	__asm {
		lea eax, dword ptr ss : [Vars.szLod]
			mov dword ptr ds : [0x6FF3E930], eax
			jmp BNCLIENT_DLod;
	}
}