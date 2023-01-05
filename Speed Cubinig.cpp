// De 10/11/2020 a 12/11/2020
// 09/02/2021: Protection against repeated or canceling moves

// SpeedCubinig.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>


int main()
{ 
	// Variáveis
	const char move[18][3] = { "F", "R", "U", "L", "B", "D",
						"F'", "R'", "U'", "L'", "B'", "D'",
						"F2", "R2", "U2", "L2", "B2", "D2" };
	char c, lastMove = '/0';
	int startTime, deltaTime, randNum;
	bool Break = false, isTiming = false;
	srand(time(NULL));
	
	setlocale(LC_ALL, "");
	printf("Cornômetro De Cubo\n\n");
	printf("(Press ESC to close program / c to clear console)\n\n");

	// Loop principal
	for (;;)
	{
		// Scramble
		printf("Press space to scramble...");
		while (true)
		{
			if (_kbhit())
			{
				c = _getch();
				if (c == 'c')
				{
					system("cls");
					printf("Cornômetro De Cubo\n\n");
					printf("(Press ESC to close program / c to clear console)\n\n");
					printf("Press space to scramble...");
				}
				if (c == ' ')
				{
					break;
				}
				if (c == 27)
				{
					Break = true;
					break;
				}
			}
		}
		if (Break) break;

		printf("\n\nScramble:\n");
		for (int i = 0; i < 25; i++)
		{
			randNum = rand() % 18;
			switch (lastMove)
			{
				case 'F':
					while (move[randNum][0] == 'F')
					{
						randNum = rand() % 18;
					}
					break;
				case 'R':
					while (move[randNum][0] == 'R')
					{
						randNum = rand() % 18;
					}
					break;
				case 'U':
					while (move[randNum][0] == 'U')
					{
						randNum = rand() % 18;
					}
					break;
				case 'L':
					while (move[randNum][0] == 'L')
					{
						randNum = rand() % 18;
					}
					break;
				case 'B':
					while (move[randNum][0] == 'B')
					{
						randNum = rand() % 18;
					}
					break;
				case 'D':
					while (move[randNum][0] == 'D')
					{
						randNum = rand() % 18;
					}
					break;
			}
			lastMove = move[randNum][0];
			printf("%s  ", move[randNum]);
		}
		printf("\n\n");

		printf("Press space to start timer...");
		while (true)
		{
			if (_kbhit())
			{
				c = _getch();
				if (c == 'c')
				{
					system("cls");
					printf("Cornômetro De Cubo\n\n");
					printf("(Press ESC to close program / c to clear console)\n\n");
					isTiming = false;
					break;
				}
				if (c == ' ')
				{
					isTiming = true;
					break;
				}
				if (c == 27)
				{
					Break = true;
					break;
				}
			}
		}
		if (Break) break;

		if (isTiming == true)
		{
			// Cronômetro
			printf("\n");
			startTime = GetTickCount64();
			do
			{
				deltaTime = GetTickCount64() - startTime;

				// Impressão do tempo
				printf("\r\r\r\r\r\r\r\r\r\rTime: %02d:", deltaTime / 60000);
				deltaTime %= 60000;
				printf("%02d:", deltaTime / 1000);
				deltaTime %= 1000;
				printf("%03d", deltaTime);

				if (_kbhit())
				{
					c = _getch();
					//if (c == 'c')
					//{
					//	system("cls");
					//	printf("Cornômetro De Cubo\n\n");
					//	printf("(Press ESC to close program / c to clear console)\n\n");
					//	break;
					//}
					if (c == 27)
					{
						Break = true;
						break;
					}
					else
					{
						printf("\n\n\n\n\n");
					}
					break;
				}
			} while (true);
			if (Break) break;

			deltaTime = 0;
		}
	}

	system("cls");
	printf("Program closing\n\nPress any key to continue...");
	while(!_kbhit());

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu