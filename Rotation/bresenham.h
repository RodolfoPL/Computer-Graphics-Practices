#include <stdio.h>

void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
void drawLine2(int x1, int y1, int x2, int y2, int r, int g, int b);
void drawLine3(int x1, int y1, int x2, int y2, int r, int g, int b);
void drawLine4(int x1, int y1, int x2, int y2, int r, int g, int b);
void putpixel(int x, int y, int r, int g, int b);
void draw();
void vertical(int x1, int x2, int y, int r, int g, int b);
void horizontal(int x, int y1, int y2, int r, int g, int b);
void defineLine(int x1, int y1, int x2, int y2, int r, int g, int b);

#define width 1920
#define height 1080

int raster[width][height][3];

void defineLine(int x1, int y1, int x2, int y2, int r, int g, int b){

	if(x2 < x1){
		int aux = x1;
		x1 = x2;
		x2 = aux;

		aux = y1;
		y1 = y2;
		y2 = aux;
	}

	if(x1 == x2){
		horizontal(x1, y1, y2, r, g, b);
	}

	else if(y1 == y2){
		vertical(x1, x2, y1, r, g, b);
	}
	else if((x2-x1) < (y2-y1)){
		drawLine3(y1, x1, y2, x2, r, g, b);
	}
	else if(abs((y2-y1)/(x2 - x1)) >= 1 && (y2-y1)<0){
		drawLine2(y2, x1, y1, x2, r, g, b);
	}	
	else if(abs((y2-y1)/(x2 - x1)) < 1 && (y2-y1)<0){
		drawLine4(x1, y2, x2, y1, r, g, b);
	}	
	else{
		drawLine(x1, y1, x2, y2, r, g, b);
	}
}

void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b){
	int dx = x2 - x1;
	int dy = y2 - y1;
	int incE = 2*dy;
	int incNE = 2*(dy-dx);

	int d = 2*dy - dx;
	putpixel(x1, y1, r, g, b); 

	int x = x1, y = y1;

	while(x < x2){
		if(d > 0){
			d += incNE;
			x++;
			y++;
		}
		else{
			d += incE;
			x++;
		}
		/*if(x >= width || y >= height || x < 0 || y < 0)
			return;*/
		putpixel(x, y, r, g, b);
	
	}
	putpixel(x2, y2, r, g, b);
}

void drawLine2(int x1, int y1, int x2, int y2, int r, int g, int b){
	int dx = x2 - x1;
	int dy = y2 - y1;
	int incE = 2*dy;
	int incNE = 2*(dy-dx);

	int d = 2*dy - dx;

	int n = x2-x1+1;

	int line[2][n];
	line[0][0] = x1;
	line[1][0] = y1;


	int x = x1, y = y1;
	int i = 1;
	while(x < x2){
		if(d > 0){
			d += incNE;
			x++;
			y++;
		}
		else{
			d += incE;
			x++;
		}
		/*if(x >= width || y >= height || x < 0 || y < 0)
			return;*/
		line[0][i] = x;
		line[1][i] = y;
		i++;
	}
	line[0][n-1] = x2;
	line[1][n-1] = y2;

	for(i=0; i<n; i++){
		putpixel(line[1][i], line[0][(n-1)-i], r, g, b);
	}
}

void drawLine3(int x1, int y1, int x2, int y2, int r, int g, int b){
	int dx = x2 - x1;
	int dy = y2 - y1;
	int incE = 2*dy;
	int incNE = 2*(dy-dx);

	int d = 2*dy - dx;

	int n = x2-x1+1;

	int line[2][n];
	/*line[0][0] = x1;
	line[1][0] = y1;*/
	putpixel(y1, x1);


	int x = x1, y = y1;
	int i = 1;
	while(x < x2){
		if(d > 0){
			d += incNE;
			x++;
			y++;
		}
		else{
			d += incE;
			x++;
		}
		/*if(x >= width || y >= height || x < 0 || y < 0)
			return;*/
		/*line[0][i] = x;
		line[1][i] = y;*/
		putpixel(y, x);
		i++;
	}
	line[0][n-1] = x2;
	line[1][n-1] = y2;

	/*for(i=0; i<n; i++){
		putpixel(line[1][i], line[0][i]);
	}*/
	putpixel(y2, x2, r, g, b);
}

void drawLine4(int x1, int y1, int x2, int y2, int r, int g, int b){
	int dx = x2 - x1;
	int dy = y2 - y1;
	int incE = 2*dy;
	int incNE = 2*(dy-dx);

	int d = 2*dy - dx;

	int n = x2-x1+1;

	int line[2][n];
	line[0][0] = x1;
	line[1][0] = y1;
	//

	int x = x1, y = y1;
	int i = 1;
	while(x < x2){
		if(d > 0){
			d += incNE;
			x++;
			y++;
		}
		else{
			d += incE;
			x++;
		}
		/*if(x >= width || y >= height || x < 0 || y < 0)
			return;*/
		line[0][i] = x;
		line[1][i] = y;
		//putpixel(y, x);
		i++;
	}
	line[0][n-1] = x2;
	line[1][n-1] = y2;

	for(i=0; i<n; i++){
		putpixel(line[0][i], line[1][(n-1)-i], r, g, g);
	}
	//putpixel(y2, x2);
}

void horizontal(int x, int y1, int y2, int r, int g, int b){
	int y;
	for(y = y1; y<=y2; y++)
		putpixel(x, y, r, g, b);
}

void vertical(int x1, int x2, int y, int r, int g, int b){
	int x;
	for(x = x1; x<=x2; x++)
		putpixel(x, y, r, g, b);
}

void putpixel(int x, int y, int r, int g, int b){
	if(x < width && y < height && x >= 0 && y >= 0){
		raster[x][y][0] = r;
		raster[x][y][1] = g;
		raster[x][y][2] = b;
	}
}



void draw(){
	int x, y;

	printf("P3\n %d %d\n 255\n", width, height);

	for(y=height; y>=0; y--){
		for(x=0; x<width; x++){
			printf("%d  %d  %d ", raster[x][y][0], raster[x][y][1], raster[x][y][2]);
		}
		printf("\n");
	}
	return;
}