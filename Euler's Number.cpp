#include <stdio.h>
#include <conio.h>

#define RANGE 13
#define DECIMAL_RANGE 9

int pow(int num1, int num2)
{
	int i, result;
	if(num2 == 0) return 1;
	for(i = 1, result = 1; i <= num2; i++)
	{
		result *= num1;
	}
	return result;
}

int fact(int iNum)
{
	int iCount, result;
	
	if(iNum > 0)
	{
		for(result = 1; iNum > 0; iNum--)
		{
			result *= iNum;
			//printf("<%d/%d>", result, iNum);
		}
		//printf("[%d] ", result);
		return result;
	}
	return 1;
}

int main()
{
	int i;
	double e;
	
	for(i = 0, e = 0; i < RANGE; i++)
	{
		e += 1 / double(fact(i));
		//printf("%f(%d)[%f] / ", e, i, 1/double(fact(i)));
		//printf("%d(%d) ", fact(i), i);
	}
	//printf("%d\n", pow(10, 9));
	printf("> e = %.10lf +- %.1lfx10^-%d", e, 1/double(fact(i))*pow(10, DECIMAL_RANGE), DECIMAL_RANGE);
	
	getch();
}
