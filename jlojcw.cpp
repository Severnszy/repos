#include <bits/stdc++.h>
#include <windows.h>

#define is_keydown(vkey) (GetAsyncKeyState(vkey) & 0x8000)

using namespace std;

void keydown(int vkey) { keybd_event(vkey, 0, 0, 0); }
void keyup(int vkey) { keybd_event(vkey, 0, 2, 0); }
void keypress(int vkey) { keydown(vkey); keyup(vkey); }

int main()
{
	POINT p;
	p.x = 1571, p.y = 99;
	for (int i = 1; i <= 20; i++)
	{
		SetCursorPos(p.x, p.y);
		Sleep(20);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(20);
		keypress(VK_TAB);
		Sleep(20);
		keypress('K');
		Sleep(20);
		keypress('L');
		Sleep(20);
		keypress('C');
		/*
		Sleep(20);
		keypress('1');
		*/
		Sleep(20);
		keypress(VK_TAB);
		Sleep(20);
		for (int i = 1; i <= 10; i++) keypress('1');
		Sleep(20);
		keypress(VK_TAB);
		Sleep(20);
		keypress('Z');
		Sleep(20);
		keypress('T');
		Sleep(20);
		keypress('Y');
		/*
		Sleep(20);
		keypress('1');
		*/
		Sleep(20);
		keypress(VK_TAB);
		Sleep(20);
		keydown(VK_LCONTROL);
		Sleep(20);
		keypress('V');
		Sleep(20);
		keyup(VK_LCONTROL);
		Sleep(20);
		keypress(VK_TAB);
		Sleep(20);
		keypress(VK_TAB);
		Sleep(20);
		keypress(VK_RETURN);
		Sleep(500);
	}
}