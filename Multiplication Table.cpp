#include <cstdio>
#include <cstdlib>
#include <locale.h>

int main()
{
	setlocale(LC_ALL,"");
	system("color 02");
	
	int n,i,x;
	char cont = 's';
	
	printf("Tabu�da\n\n");
	
	
	while(cont=='s')
	{
		printf("Digite um n�mero inteiro: ");
		scanf("%d",&n);
		printf("\n");
		
		if(n<=10)
		{
			x = 10;
		}
		else
		{
			x = n;
		}
	
		for(i=1;i<=x;i++)
		{
			printf("%d x %d = %d\n",n,i,n*i);
		}
		
		printf("\nContinuar? (s = sim) (n = n�o)\n");
		scanf("%s",&cont);
		system("cls");
		printf("Tabu�da\n\n");
		
		while(cont!='s'&cont!='n')
		{
			printf("\nResposta inv�lida!\n\n");
			printf("\nContinuar? (s = sim) (n = n�o)\n");
			scanf("%s",&cont);
			system("cls");
			printf("Tabu�da\n\n");
		}
	}
	return 0;
}
