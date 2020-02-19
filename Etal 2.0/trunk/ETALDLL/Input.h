//////////////////////////////////////////////////////////////////////
// Input.h
//////////////////////////////////////////////////////////////////////
#pragma once

// Hotkeys
#define EXIT_GAME VK_END

#include <Windows.h>
#include <string>
#include "Common.h"
#include "D2Pointers.h"

class Input
{
public:
	Input(void);
	~Input(void);

public:
	bool Initialize();
	void Shutdown();

	static void SendMouseClick(int x, int y, int button);

	static LRESULT CALLBACK KeyPress(int code, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MouseMove(int code, WPARAM wParam, LPARAM lParam);
};
