#include <stdio.h>
#include <stdlib.h>

#include "bresenham.h"


void main(){
	int x1, x2, y1, y2, i;
	int N = 1000;
	for(i=0; i<N; i++){
		//printf("%d\n", i);
		
		x1 = rand()%width;
		y1 = rand()%height;
		x2 = rand()%width;
		y2 = rand()%height;

		defineLine(x1, y1, x2, y2);
	}
	/*x1 = 0, y1 = 0;
	x2 = 1000, y2 = 10;
	defineLine(x1, y1, x2, y2);

	x1 = 0, y1 = 0;
	x2 = 10, y2 = 1000;
	defineLine(x1, y1, x2, y2);

	x1 = 10, y1 = 1000;
	x2 = 20, y2 = 0;
	defineLine(x1, y1, x2, y2);

	x1 = 0, y1 = 10;
	x2 = 1000, y2 = 0;
	defineLine(x1, y1, x2, y2);*/

	draw();
	return;
}