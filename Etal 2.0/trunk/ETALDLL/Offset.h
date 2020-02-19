#ifndef _OFFSET_H
#define _OFFSET_H

#define INST_INT3	0xCC
#define INST_CALL	0xE8
#define INST_NOP	0x90
#define INST_JMP	0xE9
#define INST_RET	0xC3

typedef struct PatchHook_t
{
	void(*pFunc)(DWORD, DWORD, DWORD);
	DWORD dwAddr;
	DWORD dwFunc;
	DWORD dwLen;
	BYTE *bOldCode;
} PatchHook;


#endif