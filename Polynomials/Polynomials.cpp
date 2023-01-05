// De 31/12/2021 a 02/01/2022

#include <stdio.h>
#include <stdlib.h>
#include "Poly.h"

char s[100];

Polynomial pol_1, pol_2, pol_3, pol_4, pol_5, pol_6, pol_7, pol_8;

int main()
{
	unsigned int deg_1, deg_2;
	printf("Grau do polinomio 1 (0 - 9): ");
	scanf_s("%u", &deg_1);
	printf("Digite o polinomio 1:\n");
	scanf_s("%s", &s, 100);
	printf("\n");

	pol_1.Set(deg_1);

	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 'x' && i > 1)
		{
			char c[3] = "  ";
			c[0] = s[i + 1];
			int k = atoi(c);
			c[0] = s[i - 2];
			c[1] = s[i - 1];
			int j = atoi(c);
			pol_1.p[k] += j;
		}
		i++;
	}
	for (unsigned int i = 0; i <= pol_1.degree; i++)
	{
		printf("%.0lfx%d\n", pol_1.p[i], i);
	}
	printf("\nDerivada:\n");
	pol_7.Copy(&pol_1);
	pol_7.DifferentiateSelf();
	for (unsigned int i = 0; i <= pol_7.degree; i++)
	{
		printf("%.0lfx%d\n", pol_7.p[i], i);
	}
	printf("\n\n\n");
	for (unsigned int i = 0; i <= pol_1.degree; i++)
	{
		printf("%.0lfx%d\n", pol_1.p[i], i);
	}


	printf("\n\n\n");


	printf("Grau do polinomio 1 (0 - 9): ");
	scanf_s("%d", &deg_2);
	printf("Digite o polinomio 2:\n");
	scanf_s("%s", &s, 100);
	printf("\n");

	pol_2.Set(deg_2);

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 'x' && i > 1)
		{
			char c[3] = "  ";
			c[0] = s[i + 1];
			int k = atoi(c);
			c[0] = s[i - 2];
			c[1] = s[i - 1];
			int j = atoi(c);
			pol_2.p[k] += j;
		}
		i++;
	}
	for (unsigned int i = 0; i <= pol_2.degree; i++)
	{
		printf("%.0lfx%d\n", pol_2.p[i], i);
	}
	printf("\nDerivada:\n");
	pol_8.Copy(&pol_2);
	pol_8.DifferentiateSelf();
	for (unsigned int i = 0; i <= pol_8.degree; i++)
	{
		printf("%.0lfx%d\n", pol_8.p[i], i);
	}


	printf("\n\n\n");


	printf("Soma:\n");
	pol_3.Copy(&pol_2);
	pol_3.SumSelf(&pol_1);
	for (unsigned int i = 0; i <= pol_3.degree; i++)
	{
		printf("%.0lfx%d\n", pol_3.p[i], i);
	}

	printf("\n\n");

	pol_4.Sum(&pol_1, &pol_2);
	for (unsigned int i = 0; i <= pol_4.degree; i++)
	{
		printf("%.0lfx%d\n", pol_4.p[i], i);
	}


	printf("\n\n\n");


	printf("Produto:\n");
	pol_5.Copy(&pol_1);
	pol_5.MultiplySelf(&pol_2);
	for (unsigned int i = 0; i <= pol_5.degree; i++)
	{
		printf("%.0lfx%d\n", pol_5.p[i], i);
	}

	printf("\n\n");

	pol_6.Multiply(&pol_1, &pol_2);
	for (unsigned int i = 0; i <= pol_6.degree; i++)
	{
		printf("%.0lfx%d\n", pol_6.p[i], i);
	}

	printf("\n\n\n");
	printf("f_1(2) = % .0lf\n", pol_1.f(2));
	printf("f_2(2) = %.0lf\n", pol_2.f(2));
}