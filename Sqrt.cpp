// Feito em 11/14/2021

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define ITER_COUNT 1000000
bool b;

int iScanf(int size)
{
	int i, t = 0;
	char c[101];

	if (size > 100) size = 100;
	for (i = 0;;)
	{
		do
		{
			t = _getch();
			if ((t == 13 || t == 8) && i > 0) break;
		} while (t > '9' || t < '0');

		if (t == 13) break;

		if (t == 8 && i > 0)
		{
			printf("\b \b");
			i--;
			c[i] = '\0';
		}
		else
		{
			if (i <= size - 1)
			{
				c[i] = t;
				c[i + 1] = '\0';
				printf("%c", c[i]);
				i++;
			}
		}
	}

	c[i] = '\0';

	return atoi(c);
}

int main()
{
	double n, x;
	int i;
	char c;

	b = true;
	while (b)
	{
		printf("> ");
		n = iScanf(9);
		x = n;
		if (n != 0)
		{
			for (i = 0; i < ITER_COUNT; i++)
			{
				x = x - (x * x - n) / (x + x);
			}
		}
		printf("\n=> %.10lf\n\n", x);
	}
}