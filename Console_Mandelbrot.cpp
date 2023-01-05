// De ? a 03/04/2021

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define WIDTH 800
#define HEIGHT 200
#define MAX_ITER 1000

void ScreenToPoint(int x, int y, float* px, float* py)
{
	*px = ((float)x - WIDTH / 1.75f) / (WIDTH / 4);
  	*py = ((float)y - HEIGHT / 2) / (HEIGHT / 2);
  	//printf("[[%f,%f,%d,%d]]",*px,*py,x,y);
}

void drawMandelbrot(int i, int j)
{
	float x0, y0, x, y, xTemp, iter;
	x0 = 0, y0 = 0, x = 0, y = 0, xTemp = 0, iter = 0;
	
	ScreenToPoint(i, j, &x0, &y0);
	//printf("[%d,%d,%f,%f]",i,j,x0,y0);

	while(x*x + y*y < 4 && iter < MAX_ITER)
	{
		xTemp = x*x - y*y + x0;
		y = 2*x*y + y0;
		x = xTemp;
		iter++;
		//printf("[%.5f|%.5f]{%.2f}", x, y, iter);
	}
	
	if(iter < MAX_ITER)
	{
		//char color[10];
		//sprintf(color, "color %c", iter);
		//system(color);
		printf("%c", 219);
	}
	else printf(" ");
}

int main()
{
	int i, j;
	
	for(j = 0; j < HEIGHT; j++)
	{
		for(i = 0; i < WIDTH; i++)
		{
			drawMandelbrot(i,j);
		}
		printf("\n");
	}
	getch();
}
