// De 03/06/2022 a 03/06/2022

#include <iostream>
#include <Windows.h>

// Set default state to false
bool bState{ false };

void menu(bool bState)
{
	// Clears and prints to the console
	system("cls");

	std::cout << "Autoclicker v1.0\n";

	if (bState)
	{
		std::cout << "Status: ON\n";
	}
	else
	{
		std::cout << "Status: OFF\n";
	}
}

void Type(const char* p)
{
	if (p == NULL)
	{
		return;
	}

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	while (*p)
	{
		// Press the key
		ip.ki.wVk = *p++; // virtual-key code for the key
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));
	}
	Sleep(10);
}

int main()
{
	menu(bState);
	while (true)
	{
		// Check if 'X' is pressed
		if (GetAsyncKeyState(0x58) & 1)
		{
			// Switch bState value
			bState = !bState;
			// Print menu to console
			menu(bState);
		}

		if (bState)
		{
			// Simulate mouse click
			//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

			Type("GAY");

			char c[2];
			c[0] = VK_RETURN;
			c[1] = '\0';
			Type(c);
		}
		Sleep(100);
	}
}