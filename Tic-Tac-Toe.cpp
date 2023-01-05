#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

//Variáveis
char tabuleiro[3][3], nome1[100], nome2[100];
int lin, col, player = 1, jogada = 1, vencedor;
bool endGame = false, b = true;

//Funções
void beep()
{
	int i = 0;
	if(b)
	{	
		for(i == 0; i < 5; i++)
		{
			Beep(2000,200);
		}
	}
	else
	{
		for(i == 0; i < 4; i++)
		{
			Beep(200,400);
		}
	}
}

void registrarJogadores()
{
	printf("\nNome do jogador 1: ");
	scanf("%s", &nome1);
	printf("\nNome do jogador 2: ");
	scanf("%s", &nome2);
	printf("\n");
}

void imprimirTabuleiro()
{
	system("CLS");
	switch(player)
	{
		case 1:	printf("Vez de %s\n", nome1);
			break;
		case 2:	printf("Vez de %s\n", nome2);
			break;
	}
	printf("Jogada %d:\n", jogada);
	
	for(lin = 0; lin < 3; lin++)
	{
		for(col = 0; col < 3; col++)
		{
			if(tabuleiro[lin][col] != 'X' && tabuleiro[lin][col] != 'O')
			{
				tabuleiro[lin][col] = ' ';
			}
		}
	}
	printf("    1   2   3\n\n");
	printf("1   %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
	printf("    __|___|__\n");
	printf("      |   |\n");
	printf("2   %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
	printf("    __|___|__\n");
	printf("      |   |\n");
	printf("3   %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

void imprimirTabuleiroFinal()
{
	printf("Jogada: %d\n", jogada);
	printf("    1   2   3\n\n");
	printf("1   %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
	printf("    __|___|__\n");
	printf("      |   |\n");
	printf("2   %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
	printf("    __|___|__\n");
	printf("      |   |\n");
	printf("3   %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

void registrarJogada()
{
	printf("\nLinha: ");
	scanf("%d",&lin);
	printf("Coluna: ");
	scanf("%d",&col);
	printf("\n");
}

void checarJogada()
{
	while(tabuleiro[lin - 1][col - 1] == 'X' || tabuleiro[lin - 1][col - 1] == 'O' || lin > 3 || col > 3 || lin < 1 || col < 1)
	{
		if(tabuleiro[lin - 1][col - 1] == 'X' || tabuleiro[lin - 1][col - 1] == 'O')
		{
			printf("\nCasa ocupada\nSelecione outra casa para jogar: ");
			printf("\nLinha: ");
			scanf("%d",&lin);
			printf("Coluna: ");
			scanf("%d",&col);
			printf("\n");
		}
		if(lin != 1 && lin != 2 && lin != 3 || col != 1 && col != 2 && col != 3)
		{
			printf("\nCasa invalida\nSelecione outra casa para jogar: ");
			printf("\nLinha: ");
			scanf("%d",&lin);
			printf("Coluna: ");
			scanf("%d",&col);
			printf("\n");
		}
	}
}

void efetuarJogada()
{
	if(player == 1)
	{
		tabuleiro[lin - 1][col - 1] = 'X';
		player = 2;
	}
	else if(player == 2)
	{
		tabuleiro[lin - 1][col - 1] = 'O';
		player = 1;
	}
	jogada++;
}

void imprimirVencedor()
{
	int i;
	switch(vencedor)
	{
		case 1:
			{
				while(nome1[i] != '\0')
				{
					printf("%c", nome1[i]);
					i++;
				}
			}
			break;
		case 2:
			{
				while(nome2[i] != '\0')
				{
					printf("%c", nome2[i]);
					i++;
				}
			}
	}
}

void checarVitoria()
{
	system("CLS");
	if((tabuleiro[0][0] == 'X' && tabuleiro[0][1] == 'X' && tabuleiro[0][2] == 'X') || (tabuleiro[1][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[1][2] == 'X') || (tabuleiro[2][0] == 'X' && tabuleiro[2][1] == 'X' && tabuleiro[2][2] == 'X') || (tabuleiro[0][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][2] == 'X') || (tabuleiro[2][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[0][2] == 'X') || (tabuleiro[0][0] == 'X' && tabuleiro[1][0] == 'X' && tabuleiro[2][0] == 'X') || (tabuleiro[0][1] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][1] == 'X') || (tabuleiro[0][2] == 'X' && tabuleiro[1][2] == 'X' && tabuleiro[2][2] == 'X'))
	{
		vencedor = 1;
		jogada -= 1;
		printf("Vitoria: %s (X)\n", nome1);
		imprimirTabuleiroFinal();
		printf("\n");
		endGame = true;
		beep();
	}
	else if((tabuleiro[0][0] == 'O' && tabuleiro[0][1] == 'O' && tabuleiro[0][2] == 'O') || (tabuleiro[1][0] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[1][2] == 'O') || (tabuleiro[2][0] == 'O' && tabuleiro[2][1] == 'O' && tabuleiro[2][2] == 'O') || (tabuleiro[0][0] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][2] == 'O') || (tabuleiro[2][0] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[0][2] == 'O') || (tabuleiro[0][0] == 'O' && tabuleiro[1][0] == 'O' && tabuleiro[2][0] == 'O') || (tabuleiro[0][1] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][1] == 'O') || (tabuleiro[0][2] == 'O' && tabuleiro[1][2] == 'O' && tabuleiro[2][2] == 'O'))
	{
		vencedor = 2;
		jogada -= 1;
		printf("Vitoria: %s (O)\n", nome2);
		imprimirTabuleiroFinal();
		printf("\n");
		endGame = true;
		beep();
	}
	else if(tabuleiro[0][0] != ' ' && tabuleiro[0][1] != ' ' && tabuleiro[0][2] != ' ' && tabuleiro[1][0] != ' ' && tabuleiro[1][1] != ' ' && tabuleiro[1][2] != ' ' && tabuleiro[2][0] != ' ' && tabuleiro[2][1] != ' ' && tabuleiro[2][2] != ' ')
	{
		jogada -= 1;
		printf("\nVelha!\n");
		imprimirTabuleiroFinal();
		printf("\n");
		endGame = true;
		b = false;
		beep();
	}
}


//main
int main()
{
	registrarJogadores();

	while(!endGame)
	{
		imprimirTabuleiro();
		
		registrarJogada();
		
		checarJogada();
		
		efetuarJogada();
		
		checarVitoria();
	}
	
	system("pause");
	return 0;
}
