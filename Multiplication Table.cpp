#include <cstdio>
#include <cstdlib>
#include <locale.h>

int main()
{
	setlocale(LC_ALL,"");
	system("color 02");
	
	int n,i,x;
	char cont = 's';
	
	printf("Tabuáda\n\n");
	
	
	while(cont=='s')
	{
		printf("Digite um número inteiro: ");
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
		
		printf("\nContinuar? (s = sim) (n = não)\n");
		scanf("%s",&cont);
		system("cls");
		printf("Tabuáda\n\n");
		
		while(cont!='s'&cont!='n')
		{
			printf("\nResposta inválida!\n\n");
			printf("\nContinuar? (s = sim) (n = não)\n");
			scanf("%s",&cont);
			system("cls");
			printf("Tabuáda\n\n");
		}
	}
	return 0;
}
