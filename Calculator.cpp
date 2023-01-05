#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include <cmath>

int main()
{
	setlocale(LC_ALL,"");
	system("color 02");
	
	float x,y;
	char continuar='s',op;
	
	
	printf("Calculadora\n\n");
	
	scanf("%f",&x);
	scanf("%c",&op);
	scanf("%f",&y);
	
	while (continuar=='s')
	{
		switch(op)
		{
		case '+':printf("\n= %.2f\n\n",x+y);break;
		case '-':printf("\n= %.2f\n\n",x-y);break;
		case '*':printf("\n= %.2f\n\n",x*y);break;
		case '^':printf("\n= %.2f\n\n",pow(x,y));break;
		case '/':if(y==0)
			{
				printf("\nERRO, ");
				printf("OPERAÇÃO INVÁLIDA!\n\n");
			}
			else
			{
				printf("\n= %.2f\n\n",x/y);break;
			}
		default:printf("\nOperador inválido!\n\n");
		}
		scanf("%f",&x);
		scanf("%c",&op);
		scanf("%f",&y);
	}
	return 0;
}
