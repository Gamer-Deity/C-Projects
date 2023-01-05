// Conway's Game of Shit V3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Término: 08/01/2021


//Header files
#include <conio.h>
#include <cstdio>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>


//Variáveis
//Console size: height = 47, width = 188
#define height 40
#define width 80
#define cell 219	//█ = 219 / ♂ = 12 / Cool characters: 1-6

int iterationGap, delay;
int col, line, iteration, nc, livecells;
char ctrue = cell, cfalse = ' ';
bool bmap[height][width], nextbmap[height][width];
bool loop, delayIsSet = false, isSelecting = false;


//Protótipos
int iscanf(int size);
void gotoxy(int linha, int coluna);
void showPreview();
bool confirmChoice();
void mapSetUp();
void showMap();
void printMap();
void clearMap();
void setChange();
void makeChange();
int mainLoop();

void Line();
void selectLiveCells();
void infiniteGrowth();
void randCells();
void rPentomino();
void smallExploder();
void exploder();
void theVirus();
void JohnConway();
void gosperGliderGun();
void setLiveCells();


//Funções

//==============================================================================

int iscanf(int size)
{
	int i, t = 0;
	char c[10];

	for (i = 0;;)
	{
		do
		{
			t = _getch();
			if ((t == 13 || t == 8) && i > 0) break;
		} while (t > '9' || t < '0');

		if (t == 13) break;

		if (t == 8)
		{
			printf("\b \b");
			i--;
			c[i] = '\0';
		}
		else
		{
			if (i < size)
			{
				c[i] = t;
				c[i + 1] = '\0';
				printf("%c", c[i]);
				i++;
			}
		}
		//printf(" (%d)-(%s) ", i, c);
	}

	c[i] = '\0';

	//printf(" %s ", c);

	return atoi(c);
}

//==============================================================================

void gotoxy(int linha, int coluna)
{
	COORD point;
	point.X = coluna;
	point.Y = linha;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

//==============================================================================

bool confirmChoice()
{
	int x0 = 0, y0 = 8, x = 0, y = 0, sHeight = height + y0 - 1, sWidth = width + x0 - 1;
	char answer;

	if (delayIsSet == false) return false;

	printf("Keep this configuration? (y / n)\n");
	if (isSelecting == true) printf("Press \"WASD\" (or arrows) to control position / Press space to select cell");

	gotoxy(y0 + height / 2, x0 + width / 2);
	x = x0 + width / 2;
	y = y0 + height / 2;
	do
	{
		gotoxy(y0 - 1, 0);
		printf("Preview: (X:%d Y:%d)  ", x - x0, y - y0);
		gotoxy(y, x);

		answer = _getch();
		if (isSelecting == true)
		{
			switch (answer)
			{
			case ' ':
				bmap[y - y0][x - x0] = !bmap[y - y0][x - x0];
				gotoxy(y0, x0);
				showMap();
				break;
			case 72:
			case 'w':
				y--;
				break;
			case 75:
			case 'a':
				x--;
				break;
			case 80:
			case 's':
				y++;
				break;
			case 77:
			case 'd':
				x++;
				break;
			case 27:
				delayIsSet = false;
				return false;
				break;
			}
			if (y > sHeight) y = y0;
			if (y < y0) y = sHeight;
			if (x > sWidth) x = x0;
			if (x < x0) x = sWidth;
		}
	} while (answer != 'y' && answer != 'n');

	switch (answer)
	{
	case 'y': clearMap();
		isSelecting = false;
		return true;
	case 'n': clearMap();
		isSelecting = false;
		return false;
	}
}

//==============================================================================

void showPreview()
{
	printf("Preview: \n");
	showMap();
}

//==============================================================================

//==============================================================================
void Line()
{
	for (int i = 0; i < width; i++) bmap[height / 2][i] = true;
	isSelecting = true;
}
//==============================================================================
void selectLiveCells()
{
	isSelecting = true;
}
//==============================================================================
void randCells()
{
	int x, y;
	
	for (y = 0; y < height; y++)
		for(x = 0; x < width; x++)
			bmap[y][x] = rand() % 2;

	isSelecting = true;
}
//==============================================================================
void infiniteGrowth()
{
	int i, x = width / 2 - 19, y = height / 2;

	for (i = 0; i < 38; i++)
	{
		if (i == 8 || i == 14 || i == 15 || i == 16 || i == 20 || i == 21 || i == 22 || i == 25 || i == 33) bmap[y][x + i] = false;
		else bmap[y][x + i] = true;
	}

	isSelecting = true;
}
//==============================================================================
void rPentomino()
{
	int x = width / 2, y = height / 2;

	bmap[y - 1][x + 1] = true;
	bmap[y - 1][x] = true;
	bmap[y][x] = true;
	bmap[y][x - 1] = true;
	bmap[y + 1][x] = true;

	isSelecting = true;
}
//==============================================================================
void smallExploder()
{
	int y = height / 2, x = width / 2;

	bmap[y][x] = true;
	bmap[y - 1][x] = true;
	bmap[y][x - 1] = true;
	bmap[y][x + 1] = true;
	bmap[y + 1][x - 1] = true;
	bmap[y + 1][x + 1] = true;
	bmap[y + 2][x] = true;

	isSelecting = true;
}
//==============================================================================
void exploder()
{
	int y = height / 2, x = width / 2;

	bmap[y][x] = true;
	bmap[y - 2][x - 2] = true;
	bmap[y - 1][x - 2] = true;
	bmap[y][x - 2] = true;
	bmap[y + 1][x - 2] = true;
	bmap[y + 2][x - 2] = true;
	bmap[y - 2][x] = true;
	bmap[y + 2][x] = true;
	bmap[y - 2][x + 2] = true;
	bmap[y - 1][x + 2] = true;
	bmap[y][x + 2] = true;
	bmap[y + 1][x + 2] = true;
	bmap[y + 2][x + 2] = true;

	isSelecting = true;
}
//==============================================================================
void theVirus() //10 cell row
{
	int randline = rand() % height, randcol = rand() % width, i;
	for (i = 0; i < 10; i++) bmap[randline][(randcol + i) % width] = true;

	isSelecting = true;
}
//==============================================================================
void JohnConway()
{
	int randline = rand() % height, randcol = rand() % width;

	//Body
	bmap[randline][randcol] = true;
	bmap[(randline > 0) ? randline - 1 : height - 1][randcol] = true;
	bmap[(randline + 1) % height][randcol] = true;
	bmap[(randline + 2) % height][randcol] = true;

	//Head
	bmap[randline > 3 ? randline - 4 : (randline > 2 ? height - 1 : (randline > 1 ? height - 2 : (randline > 0 ? height - 3 : height - 4)))][randcol] = true;
	bmap[randline > 1 ? randline - 2 : (randline > 0 ? height - 1 : height - 2)][(randcol > 0) ? randcol - 1 : width - 1] = true;
	bmap[randline > 2 ? randline - 3 : (randline > 1 ? height - 1 : (randline > 0 ? height - 2 : height - 3))][(randcol > 0) ? randcol - 1 : width - 1] = true;
	bmap[randline > 3 ? randline - 4 : (randline > 2 ? height - 1 : (randline > 1 ? height - 2 : (randline > 0 ? height - 3 : height - 4)))][(randcol > 0) ? randcol - 1 : width - 1] = true;
	bmap[randline > 1 ? randline - 2 : (randline > 0 ? height - 1 : height - 2)][(randcol + 1) % width] = true;
	bmap[randline > 2 ? randline - 3 : (randline > 1 ? height - 1 : (randline > 0 ? height - 2 : height - 3))][(randcol + 1) % width] = true;
	bmap[randline > 3 ? randline - 4 : (randline > 2 ? height - 1 : (randline > 1 ? height - 2 : (randline > 0 ? height - 3 : height - 4)))][(randcol + 1) % width] = true;

	//Left arm
	bmap[randline][(randcol + 1) % width] = true;
	bmap[(randline + 1) % height][(randcol + 2) % width] = true;
	bmap[(randline + 2) % height][(randcol + 3) % width] = true;
	
	//Right arm
	bmap[randline][(randcol > 0) ? randcol - 1 : width - 1] = true;
	bmap[(randline + 1) % height][(randcol > 1) ? randcol - 2 : (randcol > 0 ? width - 1 : width - 2)] = true;
	bmap[randline][(randcol > 2) ? randcol - 3 : width - 3] = true;
	
	//Legs
	bmap[(randline + 3) % height][(randcol + 1) % width] = true;
	bmap[(randline + 3) % height][(randcol > 0) ? randcol - 1 : width - 1] = true;
	bmap[(randline + 4) % height][(randcol + 1) % width] = true;
	bmap[(randline + 4) % height][(randcol > 0) ? randcol - 1 : width - 1] = true;

	isSelecting = true;
}
//==============================================================================
void gosperGliderGun()
{
	int y = height / 2, x = width / 2;

	//Center point:
	bmap[y][x] = true;

	//Squares:
	//Left square
	bmap[y - 6][x - 19] = true;
	bmap[y - 6][x - 18] = true;
	bmap[y - 5][x - 19] = true;
	bmap[y - 5][x - 18] = true;

	//Right square
	bmap[y - 8][x + 15] = true;
	bmap[y - 8][x + 16] = true;
	bmap[y - 7][x + 15] = true;
	bmap[y - 7][x + 16] = true;

	//Prisms:
	//Left prism
	bmap[y - 4][x - 11] = true;
	bmap[y - 4][x - 10] = true;
	bmap[y - 5][x - 11] = true;
	bmap[y - 5][x - 9] = true;
	bmap[y - 6][x - 10] = true;
	bmap[y - 6][x - 9] = true;

	//Right prism
	bmap[y - 6][x + 3] = true;
	bmap[y - 6][x + 4] = true;
	bmap[y - 7][x + 3] = true;
	bmap[y - 7][x + 5] = true;
	bmap[y - 8][x + 4] = true;
	bmap[y - 8][x + 5] = true;

	//Gliders:
	//Left glider
	bmap[y - 2][x - 3] = true;
	bmap[y - 3][x - 3] = true;
	bmap[y - 3][x - 1] = true;
	bmap[y - 4][x - 3] = true;
	bmap[y - 4][x - 2] = true;

	//Middle glider
	bmap[y + 4][x + 5] = true;
	bmap[y + 4][x + 6] = true;
	bmap[y + 4][x + 7] = true;
	bmap[y + 5][x + 5] = true;
	bmap[y + 6][x + 6] = true;

	//Right glider
	bmap[y - 1][x + 16] = true;
	bmap[y - 1][x + 17] = true;
	bmap[y][x + 16] = true;
	bmap[y][x + 18] = true;
	bmap[y + 1][x + 16] = true;

	isSelecting = true;
}
//==============================================================================
void setLiveCells()
{
	int selection;

	clearMap();

	gotoxy(0, 0);
	printf("Chose an option:\n");
	printf("0. Select living cells		5. Small exploder\n");
	printf("1. Random cells			6. Exploder\n");
	printf("2. Line				7. The virus (10 line row)\n");
	printf("3. Infinite Growth		8. XKCD RIP John Conway\n");
	printf("4. R-Pentomino			9. Gosper Glider Gun\n");
	printf("(Press ESC to leave)\n");

	do
	{
		selection = _getch();
		if (selection == 27) break;
	} while (selection < '0' || selection > '9');

	switch (selection)
	{
	case '0': selectLiveCells(); //Select the starting live cells
		break;
	case '1': randCells(); //Random cells
		break;
	case '2': Line(); //Make a line of cells
		break;
	case '3': infiniteGrowth(); //Infinite growth
		break;
	case '4': rPentomino(); //R-Pentomino
		break;
	case '5': smallExploder(); //Small exploder
		break;
	case '6': exploder(); //Exploder
		break;
	case '7': theVirus(); //The virus
		break;
	case '8': JohnConway(); //XKCD RIP John Conway
		break;
	case '9': gosperGliderGun(); //Gosper Glider Gun
		break;
	case 27: delayIsSet = false;
		break;
	}
}

//==============================================================================

void mapSetUp() //Estabelece o mapa inicial
{
	iteration = 0;
	clearMap();

	memset(bmap, 0, sizeof(bmap));
	memset(nextbmap, 0, sizeof(nextbmap));

	if (!delayIsSet)
	{
		printf("Set iteration delay (ms): ");
		delay = iscanf(4);
		delayIsSet = true;
		printf("\nSet iteration gap: ");
		iterationGap = iscanf(4);
		printf("\n");

		//do
		//{
		//	delay = _getch();
		//} while (true);
	}

	setLiveCells();
	if (delayIsSet) showPreview();

	if (confirmChoice())
	{
		loop = true;
	}
	else
	{
		loop = false;
	}
}

//==============================================================================

void showMap()
{
	for (line = 0; line < height; line++)
	{
		for (col = 0; col < width; col++)
		{
			if (bmap[line][col])
			{
				printf("%c", ctrue);
				livecells++;
			}
			else if (!bmap[line][col])
			{
				printf("%c", cfalse);
			}
		}
		printf("|\n");
	}
	for (col = 0; col < width; col++) printf("-");
	printf("/\n");
}

//==============================================================================

void printMap() //Imprime o mapa na tela
{
	if (iteration == 1) Sleep(1000);
	livecells = 0;
	gotoxy(0, 0);
	showMap();
	printf("- Iteration: %d / Cells alive: %d   ", iteration, livecells);
	printf("\nPress ESC to leave\n");
}

//==============================================================================

void clearMap()
{
	system("CLS");
}

//==============================================================================

void setChange() //Estabelece as células que devem mudar na próxima iteração
{
	nc = 0; //nc = neighbour cells
	memset(nextbmap, 0, sizeof(nextbmap));

	for (line = 0; line < height; line++)
	{
		for (col = 0; col < width; col++)
		{
			nc = bmap[(line > 0) ? line - 1 : height - 1][(col > 0) ? col - 1 : width - 1] + bmap[(line > 0) ? line - 1 : height - 1][col] + bmap[(line > 0) ? line - 1 : height - 1][(col + 1) % width] + bmap[line][(col > 0) ? col - 1 : width - 1] + bmap[line][(col + 1) % width] + bmap[(line + 1) % height][(col > 0) ? col - 1 : width - 1] + bmap[(line + 1) % height][col] + bmap[(line + 1) % height][(col + 1) % width];

			switch (bmap[line][col])
			{
			case true:
			{
				switch (nc)
				{
				case 2: nextbmap[line][col] = true;
				case 3: nextbmap[line][col] = true;
					break;
				default: nextbmap[line][col] = false;
					break;
				}
				break;
			}
			case false:
			{
				switch (nc)
				{
				case 3: nextbmap[line][col] = true;
					break;
				default: nextbmap[line][col] = false;
					break;
				}
				break;
			}
			}
		}
	}
}

//==============================================================================

void makeChange() //Efetua as mudanças nas células
{
	memcpy(bmap, nextbmap, sizeof(bmap));
}

//==============================================================================

int mainLoop() //Loop principal
{
	int i;

	for (;;)
	{
		if (loop)
		{
			printMap();
			if (livecells == 0)
			{
				system("pause");
				clearMap();
				printf("HAHA LOSER\n(Iterations: %d)\n\n", iteration);
				system("pause");
				break;
			}
			for (i = 0; i < iterationGap; i++) //Gap de iterações entre cada impressão 
			{
				setChange();
				makeChange();
				iteration++;
			}
			Sleep(delay);

			if (_kbhit())
			{
				if (_getch() == 27)
				{
					delayIsSet = false;
					return 1;
				}
			}
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

//==============================================================================

 int main() //Função Main
 {
 	srand(time(NULL));
 
 	do
 	{
 		mapSetUp();
 	} while(mainLoop());
 
 	return 0;
 }

//==============================================================================

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu